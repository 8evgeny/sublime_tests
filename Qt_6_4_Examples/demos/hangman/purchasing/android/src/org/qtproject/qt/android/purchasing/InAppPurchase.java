// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

package org.qtproject.qt.android.purchasing;

import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import com.android.billingclient.api.AcknowledgePurchaseParams;
import com.android.billingclient.api.AcknowledgePurchaseResponseListener;
import com.android.billingclient.api.BillingClient;
import com.android.billingclient.api.BillingClientStateListener;
import com.android.billingclient.api.BillingFlowParams;
import com.android.billingclient.api.BillingResult;
import com.android.billingclient.api.ConsumeParams;
import com.android.billingclient.api.ConsumeResponseListener;
import com.android.billingclient.api.Purchase;
import com.android.billingclient.api.Purchase.PurchaseState;
import com.android.billingclient.api.PurchasesResponseListener;
import com.android.billingclient.api.PurchasesUpdatedListener;
import com.android.billingclient.api.SkuDetails;
import com.android.billingclient.api.SkuDetailsParams;
import com.android.billingclient.api.SkuDetailsResponseListener;


/***********************************************************************
 ** More info: https://developer.android.com/google/play/billing
 ** Add Dependencies below to build.gradle file:

dependencies {
    def billing_version = "4.0.0"
    implementation "com.android.billingclient:billing:$billing_version"
}

***********************************************************************/

public class InAppPurchase implements PurchasesUpdatedListener
{
    private Context m_context = null;
    private long m_nativePointer;
    private String m_publicKey = null;
    private int purchaseRequestCode;


    private BillingClient billingClient;

    public static final int RESULT_OK = BillingClient.BillingResponseCode.OK;
    public static final int RESULT_USER_CANCELED = BillingClient.BillingResponseCode.USER_CANCELED;
    public static final String TYPE_INAPP = BillingClient.SkuType.INAPP;
    public static final String TAG = "InAppPurchase";

    // Should be in sync with InAppTransaction::FailureReason
    public static final int FAILUREREASON_NOFAILURE    = 0;
    public static final int FAILUREREASON_USERCANCELED = 1;
    public static final int FAILUREREASON_ERROR        = 2;

    public InAppPurchase(Context context, long nativePointer)
    {
        m_context = context;
        m_nativePointer = nativePointer;
    }

    public void initializeConnection(){
        billingClient = BillingClient.newBuilder(m_context)
                .enablePendingPurchases()
                .setListener(this)
                .build();
        billingClient.startConnection(new BillingClientStateListener() {
            @Override
            public void onBillingSetupFinished(BillingResult billingResult) {
                if (billingResult.getResponseCode() == RESULT_OK) {
                    purchasedProductsQueried(m_nativePointer);
                }
            }

            @Override
            public void onBillingServiceDisconnected() {
                Log.w(TAG, "Billing service disconnected");
            }
        });
    }

    @Override
    public void onPurchasesUpdated(BillingResult billingResult, List<Purchase> purchases) {

        int responseCode = billingResult.getResponseCode();

        if (purchases == null) {
            purchaseFailed(purchaseRequestCode, FAILUREREASON_ERROR, "Data missing from result");
            return;
        }

        if (billingResult.getResponseCode() == RESULT_OK) {
            handlePurchase(purchases);
        } else if (responseCode == RESULT_USER_CANCELED) {
            purchaseFailed(purchaseRequestCode, FAILUREREASON_USERCANCELED, "");
        } else {
            String errorString = getErrorString(responseCode);
            purchaseFailed(purchaseRequestCode, FAILUREREASON_ERROR, errorString);
        }
    }

    //Get list of purchases from onPurchasesUpdated
    private void handlePurchase(List<Purchase> purchases) {

        for (Purchase purchase : purchases) {
            try {
                if (m_publicKey != null && !Security.verifyPurchase(m_publicKey, purchase.getOriginalJson(), purchase.getSignature())) {
                    purchaseFailed(purchaseRequestCode, FAILUREREASON_ERROR, "Signature could not be verified");
                    return;
                }
                int purchaseState = purchase.getPurchaseState();
                if (purchaseState != PurchaseState.PURCHASED) {
                    purchaseFailed(purchaseRequestCode, FAILUREREASON_ERROR, "Unexpected purchase state in result");
                    return;
                }
            } catch (Exception e) {
                e.printStackTrace();
                purchaseFailed(purchaseRequestCode, FAILUREREASON_ERROR, e.getMessage());
            }
            purchaseSucceeded(purchaseRequestCode, purchase.getSignature(), purchase.getOriginalJson(), purchase.getPurchaseToken(), purchase.getOrderId(), purchase.getPurchaseTime());
        }
    }

    public void queryDetails(final String[] productIds) {

        int index = 0;
        while (index < productIds.length) {
            List<String> productIdList = new ArrayList<>();
            for (int i = index; i < Math.min(index + 20, productIds.length); ++i) {
                productIdList.add(productIds[i]);
            }
            index += productIdList.size();

            SkuDetailsParams.Builder params = SkuDetailsParams.newBuilder();
            params.setSkusList(productIdList).setType(TYPE_INAPP);
            billingClient.querySkuDetailsAsync(params.build(),
                    new SkuDetailsResponseListener() {
                        @Override
                        public void onSkuDetailsResponse(BillingResult billingResult, List<SkuDetails> skuDetailsList) {
                            int responseCode = billingResult.getResponseCode();

                            if (responseCode != RESULT_OK) {
                                Log.e(TAG, "queryDetails: Couldn't retrieve sku details.");
                                return;
                            }
                            if (skuDetailsList == null) {
                                Log.e(TAG, "queryDetails: No details list in response.");
                                return;
                            }

                            for (SkuDetails skuDetails : skuDetailsList) {
                                try {
                                    String queriedProductId = skuDetails.getSku();
                                    String queriedPrice = skuDetails.getPrice();
                                    String queriedTitle = skuDetails.getTitle();
                                    String queriedDescription = skuDetails.getDescription();
                                    registerProduct(m_nativePointer,
                                            queriedProductId,
                                            queriedPrice,
                                            queriedTitle,
                                            queriedDescription);
                                } catch (Exception e) {
                                    e.printStackTrace();
                                }
                            }
                        }
                    });


            queryPurchasedProducts(productIdList);
        }
    }

    //Launch Google purchasing screen
    public void launchBillingFlow(String identifier, int requestCode){

        purchaseRequestCode = requestCode;
        List<String> skuList = new ArrayList<>();
        skuList.add(identifier);
        SkuDetailsParams.Builder params = SkuDetailsParams.newBuilder();
        params.setSkusList(skuList).setType(TYPE_INAPP);
        billingClient.querySkuDetailsAsync(params.build(),
                new SkuDetailsResponseListener() {
                    @Override
                    public void onSkuDetailsResponse(BillingResult billingResult, List<SkuDetails> skuDetailsList) {

                        if (billingResult.getResponseCode() != RESULT_OK) {
                            Log.e(TAG, "Unable to launch Google Play purchase screen");
                            String errorString = getErrorString(requestCode);
                            purchaseFailed(requestCode, FAILUREREASON_ERROR, errorString);
                            return;
                        }
                        else if (skuDetailsList == null){
                            purchaseFailed(purchaseRequestCode, FAILUREREASON_ERROR, "Data missing from result");
                            return;
                        }

                        BillingFlowParams purchaseParams = BillingFlowParams.newBuilder()
                                .setSkuDetails(skuDetailsList.get(0))
                                .build();

                        //Results will be delivered to onPurchasesUpdated
                        billingClient.launchBillingFlow((Activity) m_context, purchaseParams);
                    }
                });
    }

    public void consumePurchase(String purchaseToken){

        ConsumeResponseListener listener = new ConsumeResponseListener() {
            @Override
            public void onConsumeResponse(BillingResult billingResult, String purchaseToken) {
                if (billingResult.getResponseCode() != RESULT_OK) {
                    Log.e(TAG, "Unable to consume purchase. Response code: " + billingResult.getResponseCode());
                }
            }
        };
        ConsumeParams consumeParams =
                ConsumeParams.newBuilder()
                        .setPurchaseToken(purchaseToken)
                        .build();
        billingClient.consumeAsync(consumeParams, listener);
    }

    public void acknowledgeUnlockablePurchase(String purchaseToken){

        AcknowledgePurchaseParams acknowledgePurchaseParams = AcknowledgePurchaseParams.newBuilder()
                .setPurchaseToken(purchaseToken)
                .build();

        AcknowledgePurchaseResponseListener acknowledgePurchaseResponseListener = new AcknowledgePurchaseResponseListener() {
            @Override
            public void onAcknowledgePurchaseResponse(BillingResult billingResult) {
                if (billingResult.getResponseCode() != RESULT_OK){
                    Log.e(TAG, "Unable to acknowledge purchase. Response code: " + billingResult.getResponseCode());
                }
            }
        };
        billingClient.acknowledgePurchase(acknowledgePurchaseParams, acknowledgePurchaseResponseListener);
    }

    public void queryPurchasedProducts(List<String> productIdList) {

        billingClient.queryPurchasesAsync(TYPE_INAPP, new PurchasesResponseListener() {
            @Override
            public void onQueryPurchasesResponse(BillingResult billingResult, List<Purchase> list) {
                for (Purchase purchase : list) {

                    if (productIdList.contains(purchase.getSkus().get(0))) {
                        registerPurchased(m_nativePointer,
                                purchase.getSkus().get(0),
                                purchase.getSignature(),
                                purchase.getOriginalJson(),
                                purchase.getPurchaseToken(),
                                purchase.getDeveloperPayload(),
                                purchase.getPurchaseTime());
                    }
                }
            }
        });
    }

    private String getErrorString(int responseCode){
        String errorString;
        switch (responseCode) {
            case BillingClient.BillingResponseCode.BILLING_UNAVAILABLE: errorString = "Billing unavailable"; break;
            case BillingClient.BillingResponseCode.ITEM_UNAVAILABLE: errorString = "Item unavailable"; break;
            case BillingClient.BillingResponseCode.DEVELOPER_ERROR: errorString = "Developer error"; break;
            case BillingClient.BillingResponseCode.ERROR: errorString = "Fatal error occurred"; break;
            case BillingClient.BillingResponseCode.ITEM_ALREADY_OWNED: errorString = "Item already owned"; break;
            case BillingClient.BillingResponseCode.ITEM_NOT_OWNED: errorString = "Item not owned"; break;
            default: errorString = "Unknown billing error " + responseCode; break;
        };
        return errorString;
    }

    public void setPublicKey(String publicKey)
    {
        m_publicKey = publicKey;
    }

    private void purchaseFailed(int requestCode, int failureReason, String errorString)
    {
        purchaseFailed(m_nativePointer, requestCode, failureReason, errorString);
    }


    private void purchaseSucceeded(int requestCode,
                                   String signature,
                                   String purchaseData,
                                   String purchaseToken,
                                   String orderId,
                                   long timestamp)
    {
        purchaseSucceeded(m_nativePointer, requestCode, signature, purchaseData, purchaseToken, orderId, timestamp);
    }

    private native static void queryFailed(long nativePointer, String productId);
    private native static void purchasedProductsQueried(long nativePointer);
    private native static void registerProduct(long nativePointer,
                                               String productId,
                                               String price,
                                               String title,
                                               String description);
    private native static void purchaseFailed(long nativePointer,
                                              int requestCode,
                                              int failureReason,
                                              String errorString);
    private native static void purchaseSucceeded(long nativePointer,
                                                 int requestCode,
                                                 String signature,
                                                 String data,
                                                 String purchaseToken,
                                                 String orderId,
                                                 long timestamp);
    private native static void registerPurchased(long nativePointer,
                                                 String identifier,
                                                 String signature,
                                                 String data,
                                                 String purchaseToken,
                                                 String orderId,
                                                 long timestamp);
}
