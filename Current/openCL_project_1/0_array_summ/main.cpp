#include <iostream>
#include <CL/cl.hpp>
#include <QtCore>
#include <vector>
#include <array>
#include <random>
#include <algorithm>
#include <iterator>
QElapsedTimer eTimer;
quint64 timeSerial, timeParallel;

using namespace std;
constexpr int arraySize = 255;

void arraySummSerial(array<float, arraySize> & arr, float & summ)
{
    eTimer.restart();
    for(int i = 0; i < arr.size();++i)
    {
        summ += arr[i];
    }
    timeSerial = eTimer.nsecsElapsed();
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
 
    // Load OpenCL program
    QFile kernelFile("kernel");
    kernelFile.open(QIODevice::ReadOnly | QIODevice::Text);
    std::string kernel_code_from_file = kernelFile.readAll().toStdString();
    kernelFile.close();

    sources.push_back({kernel_code_from_file.c_str(), kernel_code_from_file.length()});
 
    cl::Program program(context,sources);
    if(program.build({default_device})!=CL_SUCCESS)
    {
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }
 
    // create buffers on the device
    cl::Buffer InputArray(context,CL_MEM_READ_WRITE,sizeof(int) * arraySize);
    cl::Buffer OutputResult(context,CL_MEM_READ_WRITE,sizeof(ulong));
 
    array<float, arraySize > arr;
    std::random_device randD;
    std::mt19937 randMT(randD());
    std::uniform_int_distribution <int> range(0, 1000'000);
    generate(arr.begin(), arr.end(), [&]{return (float)range(randMT)/1000'000;});

//    copy(arr.begin(), arr.end(), ostream_iterator<float>(cout, " "));

    float resultSerialSumm;
    arraySummSerial (arr, resultSerialSumm);


    float resultParallelSumm;
    //create queue to which we will push commands for the device.
    cl::CommandQueue queue(context, default_device);
 
    //write arrays to the device
    queue.enqueueWriteBuffer(InputArray,CL_TRUE,0,sizeof(float)*arraySize, arr.data());

    //run the kernel
    cl::Kernel kernel_add=cl::Kernel(program,"reduction");
    kernel_add.setArg(0, arraySize);
    kernel_add.setArg(1, InputArray);
    kernel_add.setArg(2, OutputResult);

    eTimer.restart();
    queue.enqueueNDRangeKernel(kernel_add,cl::NullRange,cl::NDRange(arraySize),cl::NullRange);
    timeParallel = eTimer.nsecsElapsed();
    queue.finish();

    //read result from the device
    queue.enqueueReadBuffer(OutputResult, CL_TRUE, 0, sizeof(float), &resultParallelSumm);
 
    cout << "\nresultSerialSumm = " << resultSerialSumm <<endl;
    cout << "resultparallelSumm = " << resultParallelSumm <<endl;
    cout.precision(3);
    cout << "timeSerial = "<<(float)timeSerial/1000'000<<" ms "<<endl;
    cout<<"timeParallel = "<<(float)timeParallel/1000'000<<" ms "<<endl;
    return 0;
}





