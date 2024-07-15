#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <CL/cl.hpp>


#define BUSY 0
#define EMPTY 255
#define NUM_ITERATIONS_GPU  100
struct result
{
	int xpos, ypos;
    uint SAD;
};

class TemplateMatch {
public:
	int HEIGHT,WIDTH;


	TemplateMatch(  cv::Mat img );
    cv::Mat imageIn;
    cv::Mat imageOut;
//    result matchesCPU(cv::Mat _template, int t_rows, int t_cols);
};


void loadDataMatToUchar(uchar *data, cv::Mat &image, int nchannels)
{
    int width = image.cols;
    int height = image.rows;
    for (int y=0; y<height;y++)
	{
        for (int x = 0 ; x<width ; x++)
		{
            data[(long)y * (long)width * (long)nchannels + (long)x*nchannels + 0] = image.at<uchar>(y,x);
            if (nchannels==3)
			{
                data[(long)y * (long)width * (long)nchannels + (long)x*nchannels + 1] = image.at<uchar>(y,x);
                data[(long)y * (long)width * (long)nchannels + (long)x*nchannels + 2] = image.at<uchar>(y,x);
            }
        }
    }
}

void ucharToMat(uchar *data,cv::Mat &image)
{
	for (int y=0; y<image.rows;y++)
	{
		for (int x = 0 ; x<image.cols ; x++)
		{
			image.at<uchar>(y,x) = data[(long)y * (long)image.cols + x] ;
		}
	}
}


TemplateMatch::TemplateMatch( cv::Mat img )
{
	WIDTH = img.cols;
	HEIGHT = img.rows;
    imageIn = img;
}


