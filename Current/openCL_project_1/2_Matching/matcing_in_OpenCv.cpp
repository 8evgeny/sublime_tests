#include <QtCore>
#include <QImage>
#include "main.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

extern quint64 timeOpenCV;
extern chrono::high_resolution_clock::time_point
    time_start_OpenCV, time_end_OpenCV;
Mat img; Mat templ; Mat result;

extern int match_method;

int max_Trackbar = 5;

void matchesOpenCV()
{
    /// Load image and template
    img = imread("image", IMREAD_GRAYSCALE );
    templ = imread("template", IMREAD_GRAYSCALE );


    // Create Trackbar (Переклюячение метода вручную)
    const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
//    createTrackbar( trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod );

    time_start_OpenCV = chrono::high_resolution_clock::now();
    MatchingMethod( 0, 0 );

}

void MatchingMethod( int, void* )
{
  /// Source image to display
  Mat img_display;
  img.copyTo( img_display );

  /// Create the result matrix
  int result_cols =  img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;

//  result.create( result_cols, result_rows, CV_32FC1 );
  result.create( result_cols, result_rows, CV_8UC1 );

  /// Do the Matching and Normalize
  matchTemplate( img, templ, result, match_method );
  normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

  time_end_OpenCV = chrono::high_resolution_clock::now();

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if( match_method  == matchMetod::TM_SQDIFF || match_method == matchMetod::TM_SQDIFF_NORMED )
    { matchLoc = minLoc; }
  else
    { matchLoc = maxLoc; }

  /// Show me what you got
  rectangle( img_display, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );
  rectangle( result, matchLoc, Point( matchLoc.x + templ.cols , matchLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

  const char* image_window = "matches openCV";
  const char* result_window = "result matches openCV";
  namedWindow( image_window, WINDOW_AUTOSIZE );
  namedWindow( result_window, WINDOW_AUTOSIZE );
  moveWindow(image_window, 900,100);
  moveWindow(result_window, 1300, 140);
  imshow( image_window, img_display );
  imshow( result_window, result );

  return;
}

