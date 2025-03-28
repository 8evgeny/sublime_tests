#include <QtCore>
#include <QImage>
#include <CL/cl.hpp>
#include "main.hpp"
#include <QApplication>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

//int match_method = matchMetod::TM_SQDIFF;
//int match_method = matchMetod::TM_SQDIFF_NORMED;
//int match_method = matchMetod::TM_CCOEFF;
int match_method = matchMetod::TM_CCOEFF_NORMED;
//int match_method = matchMetod::TM_COMBINED;

bool enable_Serial_stop_after_find_zero = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_UNUSED(a)

    matchesOpenCV();

    matchesGPU();

    return 0;
}

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

void qimage_to_mat(const QImage& image, cv::OutputArray out) {

    switch(image.format()) {
        case QImage::Format_Invalid:
        {
            cv::Mat empty;
            empty.copyTo(out);
            break;
        }
        case QImage::Format_RGB32:
        {
            cv::Mat view(image.height(),image.width(),CV_8UC4,(void *)image.constBits(),image.bytesPerLine());
            view.copyTo(out);
            break;
        }
        case QImage::Format_RGB888:
        {
            cv::Mat view(image.height(),image.width(),CV_8UC3,(void *)image.constBits(),image.bytesPerLine());
            cvtColor(view, out, cv::COLOR_RGB2BGR);
            break;
        }
        default:
        {
            QImage conv = image.convertToFormat(QImage::Format_ARGB32);
            cv::Mat view(conv.height(),conv.width(),CV_8UC4,(void *)conv.constBits(),conv.bytesPerLine());
            view.copyTo(out);
            break;
        }
    }
}

void mat_to_qimage(cv::InputArray image, QImage& out)
{
    switch(image.type())
    {
        case CV_8UC4:
        {
            cv::Mat view(image.getMat());
            QImage view2(view.data, view.cols, view.rows, view.step[0], QImage::Format_ARGB32);
            out = view2.copy();
            break;
        }
        case CV_8UC3:
        {
            cv::Mat mat;
            cvtColor(image, mat, cv::COLOR_BGR2BGRA); //COLOR_BGR2RGB doesn't behave so use RGBA
            QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
            out = view.copy();
            break;
        }
        case CV_8UC1:
        {
            cv::Mat mat;
            cvtColor(image, mat, cv::COLOR_GRAY2BGRA);
            QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
            out = view.copy();
            break;
        }
        default:
        {
            throw invalid_argument("Image format not supported");
            break;
        }
    }
}

void convertToGrey(QImage &imageIn)
{
    // Convert to gray scale
    for (int y = 0; y < imageIn.height(); y++)
    {
        QRgb *line = (QRgb *) imageIn.scanLine(y);

        for (int x = 0; x < imageIn.width(); x++)
        {
            int r = qGray(line[x]);
            int g = r;
            int b = r;
            line[x] = qRgb(r, g, b);
        }
    }
}
