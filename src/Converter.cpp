//
// Created by godu on 2021/4/24.
//

#include "../include/Converter.h"

cv::Mat Converter::toCvMat(const std::vector<float> &v) //For map loading
{
    Eigen::Quaterniond q;
    q.x()  = v[0];
    q.y()  = v[1];
    q.z()  = v[2];
    q.w()  = v[3];
    Eigen::Matrix<double,3,3>eigMat(q);
    cv::Mat M = toCvMat(eigMat);
    return M;
}

cv::Mat Converter::toCvMat(const Eigen::Matrix3d &m)
{
    cv::Mat cvMat(3,3,CV_32F);
    for(int i=0;i<3;i++)
        for(int j=0; j<3; j++)
            cvMat.at<float>(i,j)=m(i,j);

    return cvMat.clone();
}
