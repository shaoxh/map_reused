//
// Created by godu on 2021/4/25.
//

#ifndef MAP_REUSED_MAPLOAD_H
#define MAP_REUSED_MAPLOAD_H

#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "../include/MappointDto.h"
#include "vector"
#include <sstream>
#include <iterator>

#include "Converter.h"
#include "iostream"
#include "../include/FeatureDto.h"
#include "../include/SystemSetting.h"
#include "../include/InitKeyFrame.h"

using namespace std;

class MapLoad {
public:
    vector<FeatureDto> LoadKeyFrame(ifstream &f, string mapId);

    vector<FeatureDto> LoadKeyFrame(ifstream &f, string mapId, SystemSetting* mySystemSetting);

    vector<MappointDto> LoadMappoint(ifstream &f, string mapId);

private:
    string Mat2String(cv::Mat mat, int i) {
        stringstream ss;
        string str;
        vector<int> vec;
        ss << "[";
        for (int j = 0; j < mat.cols; j++) {
            vec.push_back(mat.at<cv::Vec3b>(i, j)[0]);
            vec.push_back(mat.at<cv::Vec3b>(i, j)[1]);
            vec.push_back(mat.at<cv::Vec3b>(i, j)[2]);
        }
        copy(vec.begin(), vec.end(), ostream_iterator<int>(ss, ","));
        str = ss.str();
        str.erase(str.end() - 1);
        ss.str("");
        ss << str<<"]";
        str = ss.str();
//        cout << str << endl;   //  1234
        return str;
    }
};

#endif //MAP_REUSED_MAPLOAD_H
