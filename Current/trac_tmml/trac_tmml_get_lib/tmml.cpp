#include "tmml.hpp"

using namespace std;
using namespace cv;

tmml::tmml(bool &ok, float& min_max_Val0)
{
    cout <<"START Constructor tmml\n";
    min_max_Val = min_max_Val0;
#ifndef NO_GPU
    //error_Val = 1 - min_max_Val0;
    min_max_Val2 = min_max_Val0 * min_max_Val0;
    cuda_Malloc();
    fill_result_array();
    //fill_template_array();
    fill1level();
#endif // END ifndef NO_GPU
    ok = true;
    cout << "Constructor tmml, ok= " << ok << endl;
} // END tmml



tmml::~tmml()
{
#ifndef NO_GPU
    cuda_Free();
#endif // END ifndef NO_GPU
    cout << "Destructor tmml" << endl;
} // END ~tmml


#ifdef NO_GPU
   void tmml::work_tmml(const Mat& img_work, const Mat& img_temp, Pix& max_pix)
   {
       matchTemplate(img_work, img_temp, img_result, TM_CCORR);  // TM_CCOEFF_NORMED ; TM_CCOEFF
       minMaxLoc(img_result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
       max_pix.x = maxLoc.x;
       max_pix.y = maxLoc.y;
   }   // END void work_tmml
#endif // END ifdef NO_GPU
