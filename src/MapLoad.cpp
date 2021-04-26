//
// Created by godu on 2021/4/25.
//

#include "../include/MapLoad.h"

bool MapLoad::LoadKeyFrame(ifstream &f) {
    unsigned long nId;
    double TimeStamp;
    f.read((char *) &nId, sizeof(nId));
    f.read((char *) &TimeStamp, sizeof(double));

// Read position and quaternion
    cv::Mat T = cv::Mat::zeros(4, 4, CV_32F);
    std::vector<float> Quat(4);
//Quat.reserve(4);
    for (int i = 0; i < 4; i++)
        f.read((char *) &Quat[i], sizeof(float));
    cv::Mat R = Converter::toCvMat(Quat);
    for (int i = 0; i < 3; i++)
        f.read((char *) &T.at<float>(i, 3), sizeof(float));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            T.at<float>(i, j) = R.at<float>(i, j);
    T.at<float>(3, 3) = 1;


    // Read feature point number of current Key Frame
    // initkf.N 是 kf 中 关键点的个数
    int N;
    std::vector<cv::KeyPoint> vKps;

    f.read((char *) &N, sizeof(N));
    // reserve 是用来申请内存的
    vKps.reserve(N);
    // ORB 描述子是 32 维的,所以 cols = 32
    cv::Mat Descriptors;

    Descriptors.create(N, 32, CV_8UC1);
    vector<float> KeypointDepth;

    for (int i = 0; i < N; i++) {
        cv::KeyPoint kp;
        f.read((char *) &kp.pt.x, sizeof(kp.pt.x));
        f.read((char *) &kp.pt.y, sizeof(kp.pt.y));
        f.read((char *) &kp.size, sizeof(kp.size));
        f.read((char *) &kp.angle, sizeof(kp.angle));
        f.read((char *) &kp.response, sizeof(kp.response));
        f.read((char *) &kp.octave, sizeof(kp.octave));

        cout << "pt_x " << kp.pt.x << ",pt_y " << kp.pt.y << ";size " << kp.size << ";angle " << kp.angle
             << ";response " << kp.response << ";octave " << kp.octave << endl;

// Read depth value of keypoint.
//float fDepthValue = 0.0;
//f.read((char*)&fDepthValue, sizeof(float));
//KeypointDepth.push_back(fDepthValue);


// Read descriptors of keypoints
// cols 默认是 32 列,因为 orb 特征就是 32 维度的
        f.read((char *) &Descriptors.cols, sizeof(Descriptors.cols));
// for ( int j = 0; j < 32; j ++ ) // Since initkf.Descriptors.cols is always 32, for loop may also write like this.
        for (int j = 0; j < Descriptors.cols; j++)
            f.read((char *) &Descriptors.at<unsigned char>(i, j), sizeof(char));

// Read the mapping from keypoints to MapPoints.
// 读取从 kp 到 map 的对应关系
        unsigned long int mpidx;
        f.read((char *) &mpidx, sizeof(mpidx));
        if (mpidx == ULONG_MAX)
            cout << "this feature has no map point in map!";
        else
            printf("this feature %d has map point %lu", i, mpidx);

// Look up from vmp, which contains all MapPoints, MapPoint of current KeyFrame, and then insert in vpMapPoints.
    }

// Read BoW for relocalization.
// f.read((char*)&initkf.mBowVec, sizeof(initkf.mBowVec));

    std::vector<float> vRight;
    std::vector<float> vDepth;

    cout << "Descriptors: " << endl;
    cout << Descriptors << endl;

    return true;
}

bool MapLoad::LoadMappoint(ifstream &f) {
    unsigned long int nMapPoints;
    f.read((char *) &nMapPoints, sizeof(nMapPoints));
    printf("mappoint = %lu\n", nMapPoints);
    for (unsigned int i = 0; i < nMapPoints; i++) {
        cv::Mat Position(3, 1, CV_32F);
        long unsigned int id;
        f.read((char *) &id, sizeof(id));

        f.read((char *) &Position.at<float>(0), sizeof(float));
        f.read((char *) &Position.at<float>(1), sizeof(float));
        f.read((char *) &Position.at<float>(2), sizeof(float));

        cout << Position.t() << endl;
    }
    cout << " map point 已经加载完毕! 总点数: " << nMapPoints << "个" << endl;
    return true;
}
