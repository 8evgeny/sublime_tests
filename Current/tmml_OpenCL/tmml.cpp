#include "tmml.hpp"

using namespace std;
using namespace cv;

tmml::tmml(bool &ok, float& min_max_Val0)
{
    min_max_Val = min_max_Val0;
    //error_Val = 1 - min_max_Val0;
    min_max_Val2 = min_max_Val0 * min_max_Val0;
    cuda_Malloc();
    fill_result_array();
    //fill_template_array();
    fill1level();
    ok = true;
    if (ok)
        cout << "ctor cuda OK " << endl;
    else
        cout << "ctor cuda ERROR " << endl;




} // END tmml



tmml::~tmml()
{
#ifndef NO_GPU
    cuda_Free();
#endif // END ifndef NO_GPU
    cout << "Destructor tmml" << endl;
} // END ~tmml

