#include <QtCore>
#include <QImage>
#include "main.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

extern QElapsedTimer eTimer;
extern quint64 timeSerial;

Mat img; Mat templ; Mat result;
const char* image_window = "matches openCV";
const char* result_window = "result matches openCV";
int match_method = TM_CCORR;

//TM_SQDIFF
//TM_SQDIFF_NORMED
//TM_CCORR
//TM_CCORR_NORMED
//TM_CCOEFF
//TM_CCOEFF_NORMED

int max_Trackbar = 5;

void matchesOpenCV()
{
    /// Load image and template
    img = imread("image", IMREAD_COLOR );
    templ = imread("template", IMREAD_COLOR );

    namedWindow( image_window, WINDOW_AUTOSIZE );
    namedWindow( result_window, WINDOW_AUTOSIZE );
    moveWindow(image_window, 100,100);
    moveWindow(result_window, 550, 140);
    // Create Trackbar (Переклюячение метода вручную)
    const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

    eTimer.restart();
    MatchingMethod( 0, 0 );

    cout<< "Time matching CPU OpenCV = " << (float)timeSerial/1000000 <<" ms"<<endl<<endl;
    waitKey(0);
}

void MatchingMethod( int, void* )
{
  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

  result.create( result_cols, result_rows, CV_32FC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  timeSerial = eTimer.nsecsElapsed();

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  /// Show me what you got
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

  imshow( image_window, img_display );
  imshow( result_window, result );

  return;
}

