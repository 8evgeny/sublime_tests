#pragma once
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <dirent.h>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>


class Plot
{
public:
    Plot(){};
    Plot(const std::string& confing, bool &ok);
    void get_H(const cv::Mat & im);
    float work(const cv::Mat & im);


    float power(float c, int n);
    std::vector<double> mnk_koef(const std::vector<cv::Point2d> v_p, const int k); // возвращает коэффициенты полинома k-ой степени (в порядке от 0 до k)
    double calculate_polinom(const double x, const std::vector<double> v_b); // функция расчитывает значение y полинома(v_b) k-ой степени от аргумента x

    template<typename Tp>
    void getGraph(const std::vector<Tp> & vfunc, const std::vector<Tp> & varg, std::string winname = "win", int type_ = 0, cv::Mat img = cv::Mat(cv::Size(1200,800), CV_8UC3, cv::Scalar(255,255,255)) )
    {
        using namespace cv;
        using namespace std;

        img = Scalar(255,255,255);
        if (!vfunc.size())
        {
            cout << "Not correct size func data!" << endl;
            return;
        } // END if (!vfunc.size())
        if (vfunc.size() != varg.size())
        {
            cout << "Not ok sizes func(arg)!" << endl;
        }
        float maxf = *max_element(vfunc.begin(), vfunc.end());
        float minf = *min_element(vfunc.begin(), vfunc.end());
        float maxa = *max_element(varg.begin(), varg.end());
        float mina = *min_element(varg.begin(), varg.end());
        vector<float> vbuf = vfunc;
        vector<float> vbufa = varg;
        if (maxf == 0 && minf == 0)
        {
            minf = 0;
            maxf = 1;
        }
        if (maxa == 0 && mina == 0)
        {
            mina = 0;
            maxa = 1;
        }
        if (type_ == 2)
        {
            minf = 0;
            mina = 0;
        }
        for(int i = 0; i < vbuf.size(); i++) // нормировали значения функции в пределах
        {
            vbuf[i] = (vfunc[i] - minf) / (maxf - minf);
            vbufa[i] = (varg[i] - mina) / (maxa - mina);
        } // END for(int i = 0; i < vbuf.size(); i++)
        int y0 = img.rows;
        int x0 = 0;
        if (minf < 0 && maxf > 0)
        {
            y0 = round(maxf / (abs(minf) + maxf) * img.rows);
        } // END if ((minf <  0 && maxf > 0))
        if (mina < 0 && maxa > 0)
        {
            x0 = round(mina / (abs(mina) + maxa) * img.cols);
        } // END if ((minf <  0 && maxf > 0))
        drawMarker(img,Point(x0,y0), Scalar(100,100,100),MARKER_CROSS, 4 * max(img.cols, img.rows), 1);

        double kf_xsz = (double)img.cols;
        double kf_ysz =  (double)img.rows;

        for (int i = 1; i < vfunc.size(); i++)
        {
            Point p_0 = Point(round(vbufa[i-1] * kf_xsz), img.rows - round(vbuf[i-1] * kf_ysz));
            Point p_1 = Point(round(vbufa[i] * kf_xsz), img.rows - round(vbuf[i] * kf_ysz));
            if (type_ == 0) // кривая
            {line(img, p_0 , p_1, Scalar(0,0,255), 1);}
            if (type_ == 1) // точки + мнк
            {circle(img, p_1, 0, Scalar(0,0,255), 3);}
        } // END for (int i = 1; i < vfunc.size(); i++)


        if (type_ == 1 || type_ == 2) //type 1 - значения точки + МНК
        {
            vector<Point2d> v2mnk;
            v2mnk.resize(vbuf.size());
            for (int i = 0; i < vbuf.size(); i++)
            {
                v2mnk[i].x = vbufa[i];
                v2mnk[i].y = vbuf[i];
            } // END for (int i = 0; i < vbuf.size(); i++)

            vector<double> v_mnk_kf = mnk_koef(v2mnk, 3); /// MNK KOEF
            for (int i = 0; i < vbuf.size(); i++)
            {
                v2mnk[i].y = calculate_polinom(vbufa[i], v_mnk_kf);
            } // END  for (int i = 0; i < vbuf.size(); i++)
            for (int i = 1; i < vfunc.size(); i++)
            {
                Point p_0 = Point(round(vbufa[i-1] * kf_xsz), img.rows - round(v2mnk[i-1].y * kf_ysz));
                Point p_1 = Point(round(vbufa[i] * kf_xsz), img.rows - round(v2mnk[i].y * kf_ysz));
                circle(img, p_1, 0, Scalar(255,0,0), 3);
                //            line(img, p_0 , p_1, Scalar(125,125,125), 2);
            } // END for (int i = 1; i < vfunc.size(); i++)
        } // END if (type == 1)     //type 1 - значения точки + МНК

        cout << "dbg:: " << winname << ": maxf=" << maxf << "; minf = " << minf << "; maxa = " << maxa << "; mina = " << mina << endl;

        putText(img, to_string(maxf), Point(img.cols - to_string(maxf).size() * 10, 10), 1, 1, Scalar(0,0,0));
        putText(img, to_string(minf), Point(img.cols - to_string(minf).size() * 10, img.rows - 10), 1, 1, Scalar(0,0,0));
        namedWindow(winname, WINDOW_AUTOSIZE);
        imshow(winname, img);
        //    imwrite("../../../Pictures/" + winname + ".png", img);
        return;
    } // -- END void getGraph()

    template<typename Tp>
    void getGraph(int fps, const std::vector<Tp> & vfunc_t, std::string winname = "win", int type_ = 0, cv::Mat img = cv::Mat(cv::Size(1200,800), CV_8UC3,cv::Scalar(255,255,255)))
    {
        using namespace cv;
        using namespace std;
        vector<double> vfunc;
        vfunc.resize(vfunc_t.size());
        for (int i = 0; i < vfunc_t.size(); i++)
        {
            auto buf = vfunc_t[i];
            vfunc[i] = buf;
        } // END for (int i = 0; i < vfunc_t.size(); i++)

        img = Scalar(255,255,255);
        if (!vfunc.size())
        {
            cout << "Not correct size func data!" << endl;
            return;
        } // END if (!vfunc.size())


        float maxf = *max_element(vfunc.begin(), vfunc.end());
        float minf = *min_element(vfunc.begin(), vfunc.end());
        std::vector<double> vbuf = vfunc;
        minf = 0;
        if (maxf == 0 && minf == 0)
        {
            minf = 0;
            maxf = 1;
        }
        if (type_ == 2)
        {
            minf = 0;
        }
        for(int i = 0; i < vbuf.size(); i++)
        {
            vbuf[i] = (vfunc[i] - minf) / (maxf - minf);
        } // END for(int i = 0; i < vbuf.size(); i++)

        int y0 = img.rows;
        if (minf < 0 && maxf > 0)
        {
            int y0 = round(maxf / (abs(minf) + maxf) * img.rows);
            line(img, Point(0, y0), Point(img.cols, y0), Scalar(100,100,100));
        } // END if ((minf <  0 && maxf > 0))
        double kf_ysz =  (double)img.rows;
        double kf_xsz = (double)img.cols / (double)vfunc.size();
        for (int i = 1; i < vfunc.size(); i++)
        {
            Point p_0 = Point(round((i-1) * kf_xsz), img.rows - round(vbuf[i-1] * kf_ysz));
            Point p_1 = Point(round((i) * kf_xsz), img.rows - round(vbuf[i] * kf_ysz));
            if (type_ == 0) // кривая
            {line(img, p_0 , p_1, Scalar(0,0,255), 1);}
            if (type_ == 1) // точки + мнк
            {circle(img, p_1, 0, Scalar(0,0,255), 1);}
            if (type_ == 2) // "гистограмма
            {
                Scalar clr = Scalar();
                switch ((int)vfunc[i-1])
                {
                case 1:
                {clr = black; break;}
                case 2:
                {clr = green; break;}
                case 3:
                {clr = blue; break;}
                case 4:
                {clr = yell; break;}
                case 5:
                {clr = cyan; break;}
                case 6:
                {clr = viol; break;}
                case 7:
                {clr = gray_green; break;}
                case 8:
                {clr = red; break;}
                default:
                {break;}
                } // END switch switch (vbuf[i-1])
                //            cout << "dbg:: vbuf = " << vfunc[i-1] << endl;
                //            cout << " " << endl;
                line(img, p_0, Point(round((i-1) * kf_xsz), y0), clr, 1);
            } // END if (type_ == 2)
        } // END for (int i = 1; i < vfunc.size(); i++)


        if (type_ == 1 || type_ == 2) //type 1 - значения точки + МНК
        {
            vector<Point2d> v2mnk;
            v2mnk.resize(vbuf.size());
            for (int i = 0; i < vbuf.size(); i++)
            {
                v2mnk[i].x = i;
                v2mnk[i].y = vbuf[i];
            } // END for (int i = 0; i < vbuf.size(); i++)

            vector<double> v_mnk_kf = mnk_koef(v2mnk, 3); /// MNK KOEF
            for (int i = 0; i < vbuf.size(); i++)
            {
                v2mnk[i].y = calculate_polinom(i, v_mnk_kf);
            } // END  for (int i = 0; i < vbuf.size(); i++)
            for (int i = 1; i < vfunc.size(); i++)
            {
                Point p_0 = Point(round((i-1) * kf_xsz), img.rows - round(v2mnk[i-1].y * kf_ysz));
                Point p_1 = Point(round((i) * kf_xsz), img.rows - round(v2mnk[i].y * kf_ysz));
                line(img, p_0 , p_1, Scalar(125,125,125), 3);
            } // END for (int i = 1; i < vfunc.size(); i++)
        } // END if (type == 1)     //type 1 - значения точки + МНК

        putText(img, to_string(maxf), Point(img.cols - to_string(maxf).size() * 10, 10), 1, 1, Scalar(0,0,0));
        putText(img, to_string(minf), Point(img.cols - to_string(minf).size() * 10, img.rows - 10), 1, 1, Scalar(0,0,0));
        namedWindow(winname, WINDOW_AUTOSIZE);
        imshow(winname, img);
        imwrite("../../../Pictures/" + winname + ".png", img);
        return;
    } // -- END void getGraph()template<typename Tp>


    template<typename Tp>
    void get_graph_v_approx(const std::vector<std::vector<Tp>> & vvfunc, std::string winname = "win", bool norm_mnk = 1, int ord = 3, cv::Mat &  img = cv::Mat(cv::Size(1200,800), CV_8UC3,cv::Scalar(255,255,255)))
{
    using namespace cv;
    using namespace std;

    namedWindow(winname, WINDOW_NORMAL);
    img = Scalar(255,255,255);
    double kf_ysz =  (double)img.rows;
    double kf_xsz = (double)img.cols / (double)vvfunc[0].size();

    if (!vvfunc.size())
    {
        cout << "Not correct size func data!" << endl;
        return;
    } // END if (!vfunc.size())

    vector<vector<float>> vv_mnk_koef; // вектор для хранения векторов к-ов полиномов
    vv_mnk_koef.resize(vvfunc.size());

    for (int i = 0; i < vvfunc.size(); i++)
    {
        Scalar clr = Scalar(127,127,127);
        switch (i)
        {
        case 0:
        {clr = red; break;}
        case 1:
        {clr = green; break;}
        case 2:
        {clr = blue; break;}
        case 3:
        {clr = cyan; break;}
        case 4:
        {clr = viol; break;}
        case 5:
        {clr = yell; break;}
        case 6:
        {clr = gray_green; break;}
        case 7:
        {clr = black; break;}
        default:
        {clr = Scalar(127,127,127); break;}
        } // END switch switch (vbuf[i-1])


        float max = *max_element(vvfunc[i].begin(), vvfunc[i].end());
        float min = *min_element(vvfunc[i].begin(), vvfunc[i].end());
        vector<Tp> vbuf = vvfunc[i];

        if (max == 0 && min == 0)
        {
            min = 0;
            max = 1;
        }
        for(int j = 0; j < vbuf.size(); j++)
        {
            vbuf[j] = (vvfunc[i][j] - min) / (max - min);
        } // END for(int i = 0; i < vbuf.size(); i++)

        int y0 = img.rows;
        if (min < 0 && max > 0)
        {
            int y0 = round(max / (abs(min) + max) * img.rows);
            line(img, Point(0, y0), Point(img.cols, y0), Scalar(100,100,100));
        } // END if ((min <  0 && max > 0))

        vector<Point2d> v2mnk;
        v2mnk.resize(vbuf.size());
        for (int j = 0; j < vbuf.size(); j++)
        {
            v2mnk[j].x = j;
            v2mnk[j].y = vbuf[j];
        } // END for (int j = 0; j < vbuf.size(); j++)

        vector<double> v_mnk_kf = mnk_koef(v2mnk, ord); /// MNK KOEF
        vector<float> vmnkres;
        for (int j = 0; j < vbuf.size(); j++)
        {
            vmnkres.emplace_back(calculate_polinom(j, v_mnk_kf));
            //            v2mnk[j].y = calculate_polinom(j, v_mnk_kf);
        } // END  for (int j = 0; j < vbuf.size(); j++)

        float maxp = *max_element(vmnkres.begin(), vmnkres.end());
        float minp = *min_element(vmnkres.begin(), vmnkres.end());
        vector<float> vbufp = vmnkres;

        if (max == 0 && min == 0)
        {
            min = 0;
            max = 1;
        }
        for(int j = 0; j < vbufp.size(); j++)
        {
            if (!norm_mnk)
            {minp = 0; maxp  = 1;}
            vbufp[j] = (vmnkres[j] - minp) / (maxp - minp);
        } // END for(int i = 0; i < vbufp.size(); i++)
        for (int j = 1; j < vmnkres.size(); j++)
        {
            Point p_0 = Point(round((j-1) * kf_xsz), img.rows - round(vbufp[j-1] * kf_ysz));
            Point p_1 = Point(round((j) * kf_xsz), img.rows - round(vbufp[j] * kf_ysz));
            line(img, p_0 , p_1, clr, 3);
        } // END for (int j = 1; j < vfunc.size(); j++)

        string namefile;
        if (norm_mnk)
        {
            namefile = winname + "_normmnk_" + to_string(ord) + ".png";
        } // END if (norm_mnk)
        else
        {
            namefile = winname + "_" + to_string(ord) + ".png";
        } // END else
        //        imwrite("../../..//QtProg/Hu_model/result_1k/" + namefile, img);
        imshow(winname, img);
        //        waitKey(0);
    } // END for (int i = 0; i < vvfunc.size(); i++)
    return;
} // -- END get_graph_v_approx()


    template<typename Tp>
    void get_graph_v(const std::vector<std::vector<Tp>> & vvfunc, std::string winname = "win", cv::Mat img = cv::Mat(cv::Size(800,600), CV_8UC3,cv::Scalar(255,255,255)) )
    {
        using namespace cv;
        using namespace std;

        namedWindow(winname, WINDOW_NORMAL);
        img = Scalar(255,255,255);
        double kf_ysz =  (double)img.rows;
        double kf_xsz = (double)img.cols / (double)vvfunc[0].size();

        if (!vvfunc.size())
        {
            cout << "Not correct size func data!" << endl;
            return;
        } // END if (!vfunc.size())

        vector<vector<float>> vv_mnk_koef; // вектор для хранения векторов к-ов полиномов
        vv_mnk_koef.resize(vvfunc.size());

        for (int i = 0; i < vvfunc.size(); i++)
        {
            Scalar clr = Scalar(127,127,127);
            switch (i)
            {
            case 0:
            {clr = red; break;}
            case 1:
            {clr = green; break;}
            case 2:
            {clr = blue; break;}
            case 3:
            {clr = cyan; break;}
            case 4:
            {clr = viol; break;}
            case 5:
            {clr = yell; break;}
            case 6:
            {clr = gray_green; break;}
            case 7:
            {clr = black; break;}
            default:
            {clr = Scalar(127,127,127); break;}
            } // END switch switch (vbuf[i-1])

            float max = *max_element(vvfunc[i].begin(), vvfunc[i].end());
            float min = *min_element(vvfunc[i].begin(), vvfunc[i].end());
            vector<Tp> vbuf = vvfunc[i];

            if (max == 0 && min == 0)
            {
                min = 0;
                max = 1;
            } // END if (max == 0 && min == 0)
            for(int j = 0; j < vbuf.size(); j++)
            {
                vbuf[j] = (vvfunc[i][j] - min) / (max - min);
            } // END for(int i = 0; i < vbuf.size(); i++)

            int y0 = img.rows;
            if (min < 0 && max > 0)
            {
                int y0 = round(max / (abs(min) + max) * img.rows);
                line(img, Point(0, y0), Point(img.cols, y0), Scalar(100,100,100));
            } // END if ((min <  0 && max > 0))
            for (int j = 1; j < vvfunc[i].size(); j++)
            {
                Point p_0 = Point(round((j-1) * kf_xsz), img.rows - round(vbuf[j-1] * kf_ysz));
                Point p_1 = Point(round((j) * kf_xsz), img.rows - round(vbuf[j] * kf_ysz));
                line(img, p_0 , p_1, clr, 1);
            }    // END for (int i = 1; i < vfunc.size(); i++)
            putText(img, to_string(max), Point(img.cols - to_string(max).size() * 10, (i+1) * 10), 1, 1, clr);
            putText(img, to_string(min), Point(img.cols - to_string(min).size() * 10, img.rows - (vvfunc.size() - i) * 10), 1, 1, clr);
            namedWindow(winname, WINDOW_AUTOSIZE);

            imshow(winname, img);
            //        imwrite("../../..//QtProg/Hu_model/result_1k/" + winname + ".png",img);

            //        waitKey(0);

        } // END for (int i = 0; i < vvfunc.size(); i++)
        return;
    } // -- END get_graph_v()


    template<typename Tp>
    void get_graph_v(const std::vector<std::vector<Tp>> & vvfunc, const std::vector<Tp> & varg_in, std::string winname = "win", cv::Mat img = cv::Mat(cv::Size(600,400), CV_8UC3,cv::Scalar(255,255,255))) //
    {
        using namespace cv;
        using namespace std;
        namedWindow(winname, WINDOW_NORMAL);
        img = Scalar(255,255,255);
        double kf_ysz =  (double)img.rows;
        double kf_xsz = (double)img.cols;
        std::vector<Tp> varg = varg_in;

        int sz_v = varg.size();
        cout << "dbg:: varg.size = " << varg.size() << endl;
        if (!sz_v) // если пустой вектор аргументов - заполняем его индексами
        {
            sz_v = vvfunc[0].size();
            varg.resize(sz_v);
            for (int i = 0; i < sz_v; i++)
            {
                varg[i] = (float)i;
            } // END for (int i = 0; i < sz_v; i++)
        } // END if (!sz_v)
        for (int i = 0; i < vvfunc.size(); i++) // проверка на совпадение размеров векторов значений с размером вектора аргумента
        {
            if (vvfunc[i].size() != sz_v)
            {
                cout << "Not ok size vfunc in vvfunc!" << endl;
                return;
            } // END if (vvfunc[i].size() != sz_v)
        } // END for (int i = 0; i < vvfunc.size(); i++)

        /// Найдём аппроксимирующие полиномы для всех функций
        vector<vector<double>> vvmnk_kf;
        vector<vector<double>> vvmnkf;

        vvmnk_kf.resize(vvfunc.size());
        vector<vector<Point2d>> vv2mnk;
        vv2mnk.resize(vvfunc.size());
        vvmnkf.resize(vvfunc.size());
        for (int i = 0; i < vvfunc.size(); i++)
        {
            cout << "dbg :: start draw MNK[" << i << "]!" << endl;
            vv2mnk[i].resize(sz_v);
            vvmnkf[i].resize(sz_v);
            for (int j = 0; j < sz_v; j++)
            {
                vv2mnk[i][j].x = varg[j];
                vv2mnk[i][j].y = vvfunc[i][j];
            } // END for (int j = 0; j < sz_v; j++)
            vvmnk_kf[i] =  mnk_koef(vv2mnk[i], 3);

            for (int j = 0; j < sz_v; j++)
            {
                vvmnkf[i][j] = calculate_polinom(varg[j], vvmnk_kf[i]);
                if (vvfunc[i][j] < 0)
                {
                    cout << "dbg:: mnk[" << i << "][" << varg[j] << "]=" << vvmnkf[i][j] << endl;
                    cout << "dbg:: func[" << i << "][" << varg[j] << "]=" << vvfunc[i][j] << endl;
                } // END if (vvfunc[i][j] < 0)
            } // END for (int j = 0; j < sz_v; j++)
        } // END for (int i = 0; i < vvfunc.size(); i++)

        /// Выполним нормировку значений функции, нанесём координатные оси
        float maxf = *max_element(vvmnkf[0].begin(), vvmnkf[0].end());
        float minf = *min_element(vvmnkf[0].begin(), vvmnkf[0].end());
        float maxa = *max_element(varg.begin(), varg.end());
        float mina = *min_element(varg.begin(), varg.end());
        if (vvfunc.size() > 1)
        {
            for (int i = 1; i < vvfunc.size();i++) // найдём max и min значения функции и аргумента
            {
                Tp maxfb = *max_element(vvmnkf[i].begin(), vvmnkf[i].end());
                Tp minfb = *min_element(vvmnkf[i].begin(), vvmnkf[i].end());
                if (maxfb > maxf) {maxf = maxfb;}
                if (minfb < minf) {minf = minfb;}
            } // END for (int i = 0; i < vvfunc.size();i++)
        } // END if (vvfunc.size() > 1)
//        {minf = 0;} /// dbg::
        int y0 = img.rows;
        int x0 = 0;
        if (minf < 0 && maxf > 0)
        {
            y0 = round(maxf / (abs(minf) + maxf) * img.rows);
        } // END if ((minf <  0 && maxf > 0))
        if (mina < 0 && maxa > 0)
        {
            x0 = round(mina / (abs(mina) + maxa) * img.cols);
        } // END if ((minf <  0 && maxf > 0))
        drawMarker(img,Point(x0,y0), Scalar(100,100,100),MARKER_CROSS, 4 * max(img.cols, img.rows)); // Начало координат на графике

        cout << "dbg:: minmax y x = " << Point2d(minf, maxf) << " " << Point2d(mina, maxa) << endl;

        for (int i = 0; i < vvfunc.size();i++) // нарисуем нормированные аппроксимированные функции
        {
            Scalar clr = Scalar(127,127,127);
            switch (i)
            {
            case 0:
            {clr = red; break;}
            case 1:
            {clr = green; break;}
            case 2:
            {clr = blue; break;}
            case 3:
            {clr = cyan; break;}
            case 4:
            {clr = viol; break;}
            case 5:
            {clr = yell; break;}
            case 6:
            {clr = gray_green; break;}
            case 7:
            {clr = black; break;}
            default:
            {clr = Scalar(127,127,127); break;}
            } // END switch switch (vbuf[i-1])

            for (int j = 0; j < sz_v; j++)
            {
                vv2mnk[i][j].y = (vvmnkf[i][j] - minf) / (maxf - minf);
                vv2mnk[i][j].x = (varg[j] - mina) / (maxa - mina);
            } // END for (int j = 0; j < sz_v; j++)
            for (int j = 1; j < sz_v; j++)
            {
                Point p_0 = Point(round(vv2mnk[i][j-1].x * kf_xsz), img.rows - round(vv2mnk[i][j-1].y * kf_ysz));
                Point p_1 = Point(round(vv2mnk[i][j].x * kf_xsz), img.rows - round(vv2mnk[i][j].y * kf_ysz));
                circle(img, p_1, 0, clr, 3);
                //            line(img, p_0 , p_1, clr, 3);
            } // END for (int j = 0; i < varg.size(); i++)
        } // END for (int i = 0; i < vvfunc.size();i++) // нарисуем нормированные аппроксимированные функции

        cout << "dbg :: Imshow!!!" << endl;
        putText(img, to_string(maxf), Point(img.cols - to_string(maxf).size() * 10, 10), 1, 1, Scalar(0,0,0));
        putText(img, to_string(minf), Point(img.cols - to_string(minf).size() * 10, img.rows - 10), 1, 1, Scalar(0,0,0));
        namedWindow(winname, WINDOW_AUTOSIZE);
        imshow(winname, img);
        return;
    } // END get_graph_v(vvfunc, varg)
private:

    cv::Mat img, img_show;
    std::string win_name = "win";
    int win_w = 400;
    int win_h = 300;

    cv::Scalar red =  cv::Scalar(0, 0, 255);
    cv::Scalar blue = cv::Scalar(255, 0, 0);
    cv::Scalar green = cv::Scalar(0, 255, 0);
    cv::Scalar white = cv::Scalar(255, 255, 255);
    cv::Scalar black = cv::Scalar(0, 0, 0);
    cv::Scalar viol = cv::Scalar(255, 0, 255);
    cv::Scalar cyan = cv::Scalar(255, 255, 0);
    cv::Scalar yell = cv::Scalar(0, 255, 255);
    cv::Scalar gray_green = cv::Scalar(64,128,64);

private:
};

