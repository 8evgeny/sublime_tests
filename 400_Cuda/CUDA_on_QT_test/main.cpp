#include <QCoreApplication>
#include <QDebug>

#include <cuda_runtime.h>
extern "C" cudaError_t cuda_helloWorld();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cudaError_t cuerr = cuda_helloWorld();

    if (cuerr == cudaError::cudaSuccess)
    {
        qDebug() << "CUDA success: " << cudaGetErrorString(cuerr);
    }
    else
    {
        qDebug() << "CUDA Error: " << cudaGetErrorString(cuerr);
    }

    return a.exec();
}
