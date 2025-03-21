#pragma once
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <thread>

#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp> // mat4
#include <glm/trigonometric.hpp> //radians
#include <glm/vec2.hpp> // vec2
#include <glm/vec3.hpp> // vec3

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <boost/program_options.hpp>

#include "CThread.h"
#include "RadarDataConnector.h"
#include "RadarMessage.h"
#include "SystemClock.h"
#include "object.h"

void Polygon(cv::Mat img, cv::Point3d p0, cv::Point3d p1, cv::Point3d p2, cv::Point3d p3, cv::Point3d p4, cv::Scalar color);
void test_rotate_camera();
void readConfig(const char*);
