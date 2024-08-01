#include "tmml_cl.hpp"
#include <random>

using namespace std;
using namespace cv;
using namespace cl;

tmml_cl::tmml_cl(bool& ok, float& min_max_Val0)
{
    cout <<"START Construktor tmml_cl\n";
    heat_gpu();

    initDevice(ok);
    if(!ok){cout<< "error initDevice!!!\n"; return;}
    loadAndBuildProgram(ok, string(KERNEL_FILE));
    if(!ok){cout<< "error loadAndBuildProgram!!!\n"; return;}
    imageData_ptr = make_unique<cl_uchar[]>(WORK_AREA);
    templateData_ptr = make_unique<cl_uchar[]>(TEMPLATE_AREA);
    mData_ptr = make_unique<cl_float[]>(RESULT_AREA);

    clInputImg = Buffer(context, CL_MEM_READ_ONLY  | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * WORK_AREA);
    clInputTemp = Buffer(context, CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR, sizeof(unsigned char) * TEMPLATE_AREA);
    clmData = Buffer(context,CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,sizeof(cl_uint) * RESULT_AREA);

    // Kernels
    int clError = 0;
    clkProcess = Kernel(program, KERNEL_NAME, &clError );
    if(clError != 0 )
    {
        cout << "clError=" << clError << "; KERNEL_NAME=" << KERNEL_NAME << " =============== !!!" << endl;
        ok = false;
        return;
    }// END if (clError != 0 )
    queue.enqueueWriteBuffer(clmData, CL_TRUE, 0,  sizeof(cl_float) * RESULT_AREA, &mData_ptr[0]);

    // Init Kernel arguments
    clkProcess.setArg(0, clInputImg);
    clkProcess.setArg(1, clInputTemp);
    clkProcess.setArg(2, clmData);
    ok = true;
    cout <<"Constructor tmml_cl ok=" << ok << endl;
}// END tmml_cl::tmml_cl

tmml_cl::~tmml_cl()
{
    cout <<"Destructor tmml_cl\n";
}// END tmml_cl::~tmml_cl

void tmml_cl::work_tmml(const Mat& img_work, const Mat& img_temp, Pix& max_pix )
{
    loadDataMatToUchar(imageData_ptr.get(), img_work);
    loadDataMatToUchar(templateData_ptr.get(), img_temp);
    queue.enqueueWriteBuffer(clInputImg, CL_TRUE, 0,  sizeof(unsigned char) * WORK_AREA, &imageData_ptr.get()[0]);
    queue.enqueueWriteBuffer(clInputTemp, CL_TRUE, 0,  sizeof(unsigned char) * TEMPLATE_AREA, &templateData_ptr.get()[0]);
    NDRange gRM = NDRange(RESULT_WIDTH, RESULT_HEIGHT);
    queue.enqueueNDRangeKernel(clkProcess, NullRange, gRM, NullRange );
    queue.finish();
    queue.enqueueReadBuffer(clmData, CL_TRUE, 0, sizeof(cl_float) * RESULT_AREA, &mData_ptr[0]);
    Mat img_result_cpu(RESULT_WIDTH, RESULT_HEIGHT, CV_32F, mData_ptr.get());

//float max = mData_ptr.get()[0];
//for (int i = 0; i < RESULT_AREA; ++i)
//{
//    if (mData_ptr.get()[i] > max)
//        max = mData_ptr.get()[i];
//}
//cout<<"max = "<<max <<"\n";

    minMaxLoc(img_result_cpu, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    max_pix.x = maxLoc.x;
    max_pix.y = maxLoc.y;
    max_pix.bright = mData_ptr.get()[maxLoc.y * RESULT_HEIGHT + maxLoc.x];

}// END work_tmml

#ifdef KernelFromFile
string tmml_cl::loadKernelFile(const string program)
{
    ifstream f(program);
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}// END tmml_cl::loadKernelFile
#endif

void tmml_cl::initDevice(bool & init_OK)
{
    Platform::get(&all_platforms);
    if(!all_platforms.size())
    {
        cout<<" No platforms found. Check OpenCL installation!\n";
        init_OK = false;
    }// END if(all_platforms.size() == 0)
    default_platform=Platform(all_platforms[0]);
    cout << "Using CL platform: \t"<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if (all_devices.size() == 0)
    {
        cout<<" No devices found. Check OpenCL installation!\n";
        init_OK = false;
    }// END if (all_devices.size() == 0)
    default_device=Device(all_devices[0]);
    cout<< "Using CL device: \t"<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
    context=Context(default_device);
    queue=CommandQueue(context, default_device);
    init_OK = true;
}// END initDevice

void tmml_cl::loadAndBuildProgram(bool & init_OK, const string & programFile)
{
    Program::Sources sources;

    #ifdef KernelFromFile
        string kernel_source = loadKernelFile(programFile);
    #endif
    #ifndef KernelFromFile
        string kernel_source = programm_CL_float;
    #endif

    pair<const char*, ::size_t> src(kernel_source.c_str(), kernel_source.length());
    sources.push_back(src);
    program=Program(context, sources);
    vector<Device> devices;
    devices.push_back(default_device);
    if(program.build(devices) != CL_SUCCESS)
    {
        cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        init_OK = false;
    }// END if(program.build(devices)!=CL_SUCCESS)
}// END loadAndBuildProgram

void tmml_cl::loadDataMatToUchar(unsigned char *data, const Mat &image)
{
    int width = image.cols;
    int height = image.rows;
    for (int y = 0; y < height; ++y)
    {
        int posY = y * width;
        for (int x = 0 ; x < width ; ++x)
        {
            data[posY + x ] = image.at<unsigned char>(y, x);
        }// END for (int x = 0 ; x < width ; x++)
    }// END for (int y=0; y < height; y++)
}// END loadDataMatToUchar

void tmml_cl::uintToMat(const unsigned int *data, Mat &image)
{
    int width = image.cols;
    int height = image.rows;
    for (int y = 0; y < height; ++y)
    {
        int posY = y * width;
        for (int x = 0 ; x < width ; ++x)
        {
            image.at<uint>(y,x) = data[posY + x];
        }// END for (int x = 0 ; x < width ; ++x)
    }// END for (int y = 0; y < height; ++y)
}// END uintToMat

vector<int> randomVector(int size)
{
    vector<int> v(size);
    std::random_device randD;
    std::mt19937 randMT(randD());
    std::uniform_int_distribution <int> range(0, 1000000);
    generate(v.begin(), v.end(), [&]{return range(randMT);});
    return v;
}//END vector<int> randomVector(int size)
void tmml_cl::heat_gpu()
{
    cout<<"########################## heat_gpu start ##################################\n";
    constexpr int vectorSize = 100'000'000;
    //get all platforms (drivers)
    vector<Platform> all_platforms;
    Platform::get(&all_platforms);
    if(all_platforms.size()==0)
    {
        cout<<" No platforms found. Check OpenCL installation!\n";
    }//END if(all_platforms.size()==0)
    Platform default_platform=all_platforms[0];
    cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
    //get default device of the default platform
    vector<Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0)
    {
        cout<<" No devices found. Check OpenCL installation!\n";
    }//END if(all_devices.size()==0)
    Device default_device = all_devices[0];
    cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
    Context context({default_device});
    Program::Sources sources;

    // kernel calculates for each element C=A+B
    // Load OpenCL program
    std::string kernel_code =
        "void kernel add_two_vectors(global const int* A, global const int* B, global int* C)"
        "{ "
        "   C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)]; "
        " } ";
    sources.push_back({kernel_code.c_str(), kernel_code.length()});
    Program program(context, sources);
    if(program.build({default_device})!=CL_SUCCESS)
    {
        cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
    }// END if(program.build({default_device})!=CL_SUCCESS)
    // create buffers on the device
    Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(int) * vectorSize);
    Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(int) * vectorSize);
    Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(int) * vectorSize);
    vector<int> v1(randomVector(vectorSize));
//    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
    vector<int> v2(randomVector(vectorSize));
//    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
    vector<int> v3(vectorSize);
    //create queue to which we will push commands for the device.
    CommandQueue queue(context, default_device);
    //write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(int) * vectorSize, v1.data());
    queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(int) * vectorSize, v2.data());
    //run the kernel
    Kernel kernel_add = Kernel(program, "add_two_vectors");
    kernel_add.setArg(0, buffer_A);
    kernel_add.setArg(1, buffer_B);
    kernel_add.setArg(2, buffer_C);
    queue.enqueueNDRangeKernel(kernel_add, NullRange, NDRange(vectorSize), NullRange);
    queue.finish();
    //read result from the device to vector
    queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int)*vectorSize, v3.data());
//    copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, " "));
    cout<<"########################## heat_gpu end ##################################\n";
}// END void heat_gpu()
