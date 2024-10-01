#include "opencv2/core.hpp"
#include "tracshats/trac_api.hpp"
#include "tracshats/tracshats.hpp"
#include "tools/colors.h"

struct TrackerContainer
{
    cv::Scalar color = color::viol;
    cv::Rect2f aimRect = cv::Rect2f(0,0,0,0);
    cv::Rect2f roi = cv::Rect2f(0,0,0,0);
    cv::Point startTrackersPoint = cv::Point(0,0);
    cv::Point startInfoPoint = cv::Point(0,0);
    //    bool on = false;
    bool isInitedFlag = false;
    bool initReqFlag = false;
    bool found = false;
    const std::string name = "Tr";

    int getID()
    {
        return id;
    }
    virtual void setID(int id)
    {
        this->id = id;
    }
    virtual void setFrameCounter(int cnt){}

    virtual bool isInited()
    {
        return isInitedFlag;
    }

protected:
    int id = 0;
}; // END struct TrackerContainer


struct TracShatsContainer : public TrackerContainer
{
    TracShatsContainer()
    {
        startTrackersPoint = cv::Point(100, 120);
        startInfoPoint = cv::Point(50, 120);
    }
    std::unique_ptr<TracShats> tracker = nullptr;
    bool isFirstInitedFlag = false;
    const std::string name = "TrSh";
    cv::Mat frame;
    bool isInited() override
    {
        return tracker->isInited();
    } // END isInited
    void setID(int id) override
    {
        this->id = id;
        tracker->setTrackerId(id);
    } // END setID
    void setFrameCounter(int cnt) override
    {
        tracker->setWorkNumber(cnt);
    } // END setFrameCounter
}; // END struct TracShatsContainer
