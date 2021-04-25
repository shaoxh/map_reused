//
// Created by godu on 2021/4/24.
//

#ifndef UNTITLED1_CONVERTER_H
#define UNTITLED1_CONVERTER_H

#include<opencv2/core/core.hpp>

#include<Eigen/Dense>

class Converter
{
public:
    static cv::Mat toCvMat(const Eigen::Matrix3d &m);
    static cv::Mat toCvMat(const std::vector<float> &v);//for map Loading
    };
#endif //UNTITLED1_CONVERTER_H
