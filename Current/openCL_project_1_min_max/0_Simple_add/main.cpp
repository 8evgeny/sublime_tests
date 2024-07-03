// https://simpleopencl.blogspot.com/2013/06/tutorial-simple-start-with-opencl-and-c.html
#include <iostream>
#include <CL/cl.hpp>
#include <QtCore>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
QElapsedTimer eTimer;
quint64 timeSerial, timeParallel;

using namespace std;

vector<int> randomVector(size_t size)
{
    vector<int> v(size);
    std::random_device randD;
    std::mt19937 randMT(randD());
    std::uniform_int_distribution <int> range(0, 1000000);
    generate(v.begin(), v.end(), [&]{return range(randMT);});
    return v;
}

void vectorsAddSerial(vector<int>&v1,vector<int>&v2,vector<int>&v3)
{
    eTimer.restart();
    for(int i = 0; i<v1.size();++i)
    {
        v3[i] = v1[i] + v2[i];
    }
    timeSerial = eTimer.nsecsElapsed();
    cout<<"timeSerial="<<(float)timeSerial/1000<<" mks "<<endl;
}

int main(){
    //get all platforms (drivers)
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if(all_platforms.size()==0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";
 
    //get default device of the default platform
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Device default_device = all_devices[0];
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";
 
 
    cl::Context context({default_device});
 
    cl::Program::Sources sources;
 
    // kernel calculates for each element C=A+B

    // Load OpenCL program
    QFile kernelFile("simple_add.cl");
    kernelFile.open(QIODevice::ReadOnly | QIODevice::Text);
    std::string kernel_code_from_file = kernelFile.readAll().toStdString();
    kernelFile.close();

//    std::string kernel_code=
//            "   void kernel simple_add(global const int* A, global const int* B, global int* C){       "
//            "       C[get_global_id(0)]=A[get_global_id(0)]+B[get_global_id(0)];                 "
//            "   }  ";

    sources.push_back({kernel_code_from_file.c_str(), kernel_code_from_file.length()});
 
    cl::Program program(context,sources);
    if(program.build({default_device})!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }
 
    // create buffers on the device
    cl::Buffer buffer_A(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_B(context,CL_MEM_READ_WRITE,sizeof(int)*10);
    cl::Buffer buffer_C(context,CL_MEM_READ_WRITE,sizeof(int)*10);
 
    vector<int> v1(randomVector(1000000));
//    copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
    cout<<endl;
    vector<int> v2(randomVector(1000000));
//    copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
    cout<<endl;
    vector<int> v3(1000000);


    vectorsAddSerial(v1,v2,v3);
//    copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, " "));

    int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int B[] = {0, 1, 2, 0, 1, 2, 0, 1, 2, 0};
 
    //create queue to which we will push commands for the device.
    cl::CommandQueue queue(context, default_device);
 
    //write arrays A and B to the device
    queue.enqueueWriteBuffer(buffer_A,CL_TRUE,0,sizeof(int)*10,A);
    queue.enqueueWriteBuffer(buffer_B,CL_TRUE,0,sizeof(int)*10,B);
 
 
    //run the kernel
//    cl::KernelFunctor simple_add(cl::Kernel(program,"simple_add"),queue,cl::NullRange,cl::NDRange(10),cl::NullRange);
//    simple_add(buffer_A,buffer_B,buffer_C);
 
    //alternative way to run the kernel
    cl::Kernel kernel_add=cl::Kernel(program,"simple_add");
    kernel_add.setArg(0,buffer_A);
    kernel_add.setArg(1,buffer_B);
    kernel_add.setArg(2,buffer_C);
    queue.enqueueNDRangeKernel(kernel_add,cl::NullRange,cl::NDRange(10),cl::NullRange);
    queue.finish();
 
    int C[10];
    //read result C from the device to array C
    queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(int)*10, C);
 
    std::cout<<"result parallel: \n";
    for(int i=0;i<10;i++)
    {
        std::cout<<C[i]<<" ";
    }
    std::cout<<"\n";
    return 0;
}





