#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wctor-dtor-privacy"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#pragma GCC diagnostic pop

#include "duplo_dispatcher.h"
#include "duplo_dispatcher_exception.h"

static const char* kHost = "localhost:8092";

using ::testing::Return;
using ::testing::Sequence;
using ::testing::Throw;
using namespace sadko;
class Mock_MessengerServiceSoapBindingProxy
    : public MessengerServiceSoapBindingProxy {
 public:
  MOCK_METHOD2(process, int(ns1__process*, ns1__processResponse&));
};

TEST(Duplo, Ok) {
  DuploDispatcher duplo(kHost);

  auto mock = std::make_shared<Mock_MessengerServiceSoapBindingProxy>();
  duplo.SetMessengerService(mock);
  ViolationOrder violation_order;
  EXPECT_CALL((*mock), process).Times(1).WillRepeatedly(::testing::Return(0));
  //  auto message = fadapter.convert_data(violation_order);
  //  ASSERT_NO_THROW(evd(message));
  ASSERT_NO_THROW(duplo.SendMessage(violation_order));
}

TEST(Duplo, ConnectionException) {
  DuploDispatcher duplo(kHost);
  ViolationOrder violation_order;
  auto mock = std::make_shared<Mock_MessengerServiceSoapBindingProxy>();
  duplo.SetMessengerService(mock);

  EXPECT_CALL((*mock), process).Times(1).WillRepeatedly(::testing::Return(28));

  ASSERT_THROW(duplo.SendMessage(violation_order), SOAPConnectionException);
}

class DuploFault : public ::testing::TestWithParam<std::string> {
 protected:
  std::shared_ptr<Mock_MessengerServiceSoapBindingProxy> proxy;

  std::string fault_code = "";
  std::string fault_message = "";

  void SetFaultCodeAndMessage(const std::string& code,
                              const std::string& message);

  void SetUp() override;
};

void DuploFault::SetFaultCodeAndMessage(const std::string& code,
                                        const std::string& message) {
  fault_code = code;
  fault_message = message;
}

void DuploFault::SetUp() {
  proxy = std::make_shared<Mock_MessengerServiceSoapBindingProxy>();

  proxy->fault = new SOAP_ENV__Fault;
  proxy->fault->SOAP_ENV__Detail = new SOAP_ENV__Detail;
  proxy->fault->SOAP_ENV__Detail->ns1__DuploFault = new ns1__duploFault;

  auto duplo_fault = proxy->fault->SOAP_ENV__Detail->ns1__DuploFault;
  duplo_fault->faultCode = &fault_code;
  duplo_fault->faultMessage = &fault_message;
}

TEST_F(DuploFault, Fault) {
  DuploDispatcher duplo(kHost);

  EXPECT_CALL((*proxy), process).Times(1).WillRepeatedly(::testing::Return(12));

  duplo.SetMessengerService(proxy);

  SetFaultCodeAndMessage("101", "Error");
  ViolationOrder violation_order;
  ASSERT_THROW(duplo.SendMessage(violation_order), SOAPDuploFault);
}

TEST_F(DuploFault, SqlError) {
  DuploDispatcher duplo(kHost);

  Sequence s1;

  EXPECT_CALL((*proxy), process)
      .Times(2)
      .InSequence(s1)
      .WillRepeatedly(Return(12));
  EXPECT_CALL((*proxy), process).InSequence(s1).WillOnce(Return(0));

  duplo.SetMaxResendNumberOnError(2);
  duplo.SetMessengerService(proxy);

  SetFaultCodeAndMessage("SQL_08003", "");
  ViolationOrder violation_order;
  ASSERT_NO_THROW(duplo.SendMessage(violation_order));
}

TEST_F(DuploFault, SqlLimitErrorCount) {
  DuploDispatcher duplo(kHost);

  Sequence s1;

  EXPECT_CALL((*proxy), process)
      .Times(21)
      .InSequence(s1)
      .WillRepeatedly(Return(12));

  duplo.SetMaxResendNumberOnError(20);
  duplo.SetMessengerService(proxy);

  SetFaultCodeAndMessage("SQL_08003", "");
  ViolationOrder violation_order;
  ASSERT_THROW(duplo.SendMessage(violation_order), SOAPDuploFaultSql);
}

TEST_P(DuploFault, CheckSqlErrorCode) {
  DuploDispatcher duplo(kHost);

  Sequence s1;

  EXPECT_CALL((*proxy), process)
      .Times(2)
      .InSequence(s1)
      .WillRepeatedly(Return(12));

  duplo.SetMaxResendNumberOnError(1);
  duplo.SetMessengerService(proxy);

  const auto fault_code = GetParam();
  SetFaultCodeAndMessage(fault_code, "");
  ViolationOrder violation_order;
  ASSERT_THROW(duplo.SendMessage(violation_order), SOAPDuploFaultSql);
}

static std::vector<std::string> sql_fault_code = {
    "SQL_08003",
    "SQL_08006",
};

INSTANTIATE_TEST_CASE_P(DuploFaultSql, DuploFault,
                        ::testing::ValuesIn(sql_fault_code));

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
