#include "OpenCL.h"
#include "ConvNN.h"
#include "util.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace cv;

void read_Mnist(string filename, vector<vector<float>> &vec);
void read_Mnist_Label(string filename, vector<vector<float>> &vec, vector<float> &testtargets, bool testflag);
void printInput(vector<float> &inputs);
void read_CIFAR10(Mat &trainX, Mat &testX, Mat &trainY, Mat &testY);

int main(void)
{
    try
    {
        // First initialize OpenCL
		OpenCL::initialize_OpenCL();

		util::Timer timer;
		timer.reset();

        //Create vectors for input and targes
        vector<vector<float> > inputs;
        vector<vector<float> > targets;
        vector<vector<float> > testinputs;
        vector<float> testtargets;

		/*//////////////////////////////////
        vector<float> intemp(28 * 28);

        for (int i = 0; i < 28 * 28; i++)
        {
			intemp.at(i) = 0.5;
		}

		for (int j = 0; j < 10000; j++)
			inputs.push_back(intemp);

        vector<float> temp(10);

		for (int i = 0; i < 1; i++)
			temp.at(i) = 0;
		temp.at(1) = 1;

		for (int j = 0; j < 10000; j++)
			targets.push_back(temp);

		testinputs = inputs;
		for (int i = 0; i < 10000; i++)
			testtargets.push_back(1);

		////////////////////////////////////////////////////////*/

		///MNIST
		/*//////////////////////////////////////////////////
		read_Mnist("train-images.idx3-ubyte", inputs);
		read_Mnist_Label("train-labels.idx1-ubyte", targets,testtargets,0);

        cout << "MNIST loaded in: " <<timer.getTimeMilliseconds()/1000.0 <<" s"<<endl;

		timer.reset();
		read_Mnist("t10k-images.idx3-ubyte", testinputs);
		read_Mnist_Label("t10k-labels.idx1-ubyte", targets, testtargets, 1);

		//for (int i = 0; i < 30; i++)
            //cout << " " <<testtargets[i];
        cout << "MNIST test loaded in: " << timer.getTimeMilliseconds() / 1000.0 << " s" << endl;

		//printInput(inputs[54]);

		////////////////////////////////////////////////////*/


		///CIFAR10
		/////////////////////////////////////////////////////////
        Mat trainX, testX;
        Mat trainY, testY;
        trainX = Mat::zeros(1024, 50000, CV_32FC1);
        testX = Mat::zeros(1024, 10000, CV_32FC1);
        trainY = Mat::zeros(1, 50000, CV_32FC1);
        testY = Mat::zeros(1, 10000, CV_32FC1);

		read_CIFAR10(trainX, testX, trainY, testY);

        cout << "Cifar10 loaded in: " << timer.getTimeMilliseconds() / 1000.0 << " s" << endl;

		timer.reset();

        for (int i = 0; i < 50000; i++)
        {
			inputs.push_back(trainX.col(i));
            vector<float> tempvec(10);

            for (int j = 0; j < 10; j++)
            {
				if (j == trainY.col(i).at<float>(0))
					tempvec[j] = (float)1.0;
				else
					tempvec[j] = (float) 0.0;
			}
			targets.push_back(tempvec);

        }//END for (int i = 0; i < 50000; i++)

        for (int i = 0; i < 10000; i++)
        {
			testinputs.push_back(testX.col(i));
			testtargets.push_back(testY.col(i).at<float>(0));
        }//END for (int i = 0; i < 10000; i++)

        cout << "Cifar10 converted in: " << timer.getTimeMilliseconds() / 1000.0 << " s" << endl;
		timer.reset();

		////////////////////////////////////////////////////////*/
/*
		///CNN
		//////////////////////////////////////////////////////////

		ConvNN m_nn;
		m_nn.createConvNN(7, 7, 32);//num of filters,filterdim,imagedim

		//todo::many filters  3d kernel
        vector<int> netVec;
		netVec = { 169 * 7,10 };
		m_nn.createFullyConnectedNN(netVec, 0, 32);

		m_nn.train(inputs, targets, testinputs, testtargets, 1000000);

        cout << "trained in : " << timer.getTimeMilliseconds() / 1000.0 << " s" << endl;

		//////////////////////////////////////////////////////////////////////////////*/

		/// FCNN
        ////////////////////////////////////////////////////
        //Define our neural network
        ConvNN m_nn;

        vector<int> netVec;
        netVec = { 1024, 10 };
        m_nn.createFullyConnectedNN(netVec, 1, 32);

        //m_nn.forwardFCNN(inputs[0]);

        //Train the network
        m_nn.trainFCNN(inputs, targets, testinputs, testtargets, 50000);

        cout << "trained in : " << timer.getTimeMilliseconds() / 1000.0 << " s" << endl;

        //Test accuracy on test data
        m_nn.trainingAccuracy(testinputs, testtargets, 2000, 1);
       /////////////////////////////////////////////////////////////

    }//END try

	catch (cl::Error e) 
	{
        cout << "opencl error: " << e.what() << endl;
        cout << "error number: " << e.err() << endl;
	}
	catch (int e)
	{
        cout << "An exception occurred. Exception Nr. " << e << '\n';
	}
	
}//END int main(void)
