#ifndef TRT_DETECTOR_HPP
#define TRT_DETECTOR_HPP

#include <string>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <memory>

#ifdef TKDNN_REPO
    #include "Yolo3Detection.h"
#else
namespace tk{
    namespace dnn{
        struct box {
            int cl;
            float x, y, w, h;
            float prob;
            std::vector<float> probs;

            void print() 
            {
                std::cout<<"x: "<<x<<"\ty: "<<y<<"\tw: "<<w<<"\th: "<<h<<"\tcl: "<<cl<<"\tprob: "<<prob<<std::endl;
            }
        };
    }
}
#endif

using bbox_batch = std::vector<std::vector<tk::dnn::box>>;

namespace trt_detector
{
    class YOLO_TRT_Detector
    {   
    public:
        YOLO_TRT_Detector(const std::string enginePath, float threshold, int n_batch, int n_classes);
        YOLO_TRT_Detector(const std::string enginePath, float threshold, int n_classes);

        std::vector<tk::dnn::box> detect(const cv::Mat &frame);
        bbox_batch detect(const std::vector<cv::Mat> &frames);
        cv::Size getNetInputSise();
        int getMaxBatchSize();
    private:
        std::shared_ptr<void> yolo;
        std::vector<cv::Mat> batch;
        cv::Size netInputSize;
    };
}


#endif //TRT_DETECTOR_HPP
