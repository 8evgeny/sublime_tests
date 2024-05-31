#include "plot.hpp"

float Plot::power(float c, int n)
{
    if (n == 0)
    {
        return 1.f;
    } // END  if (n == 0)
    float m = 1;
    if (n > 0)
    {
        for (int count = 0; count < n; count ++)
        {
            m *= c;
        } // END for (int count = 1; count < n; count ++)
    } // END if (n > 0)
    else
    {
        for (int count = 0; count < n; count ++)
        {
            m /= c;
        } // END for (int count = 1; count < n; count ++)
    } // END else
    return m;
} // END float power(float c, int n )

std::vector<double> Plot::mnk_koef(const std::vector<cv::Point2d> v_p, const int k) // возвращает коэффициенты полинома k-ой степени (в порядке от 0 до k)
{
    std::vector<double> v_b;
    v_b.resize(k + 1);
    if (!v_p.size() || v_p.size() < k)
    {
        std::cout << "Невозможно найти коэффициенты уравнения" << std::endl;
        return {0};
    } // END if (v_x.size() != v_y.size())
    cv::Mat A(cv::Size(k+1,k+1), CV_64F, 0.0);
    cv::Mat C(cv::Size(1,k+1), CV_64F, 0.0);

    for (int i = 0; i <= k; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            for (int l = 0; l < v_p.size(); l++)
            {
                A.at<double>(i,j) += power(v_p[l].x, i+j);
            } // END for (int l = 0; l < v_p.size(); l++)
        } // END for (int j = 0; j < k; j++)

        for (int l = 0; l < v_p.size(); l++)
        {
            C.at<double>(0,i) += power(v_p[l].x, i) * v_p[l].y;
        } // END for (int l = 0; l < v_p.size(); l++)
    } // END for (int i = 0; i < A.cols())
    A.at<double>(0,0) = v_p.size();
    cv::Mat B = A.inv() * C;
    for (int i = 0; i < B.rows; i++)
    {
        v_b[i] = B.at<double>(0,i);
    } // END for (int i = 0; i < B.rows; i++)
    return v_b;
} // END vector<double> MNK(const vector<cv::Point2d> v_p, const int k)


double Plot::calculate_polinom(const double x, const std::vector<double> v_b) // функция расчитывает значение y полинома(v_b) k-ой степени от аргумента x
{
    double y = 0;
    for (int k = 0; k < v_b.size(); k++)
    {
        y += v_b[k] * power(x, k);
    } // END for (int k = 0; k < v_b.size(); k++)
    return y;
} // END double calculate_polinom(const double x, const vector<double> v_b)



