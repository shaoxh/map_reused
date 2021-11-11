#include <iostream>

#include "opencv2/highgui/highgui.hpp"
#include <vector>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "./include/Converter.h"
#include "./include/MyDb.h"
#include "./include/MyDbHelper.h"
#include "./include/FeatureDto.h"
#include "./include/MapLoad.h"
#include "./include/SystemSetting.h"
#include "./include/InitKeyFrame.h"

using namespace std;

vector<string> getFiles(string dirc) {
    vector<string> files;
    struct dirent *ptr;
    char base[1000];
    DIR *dir;
    dir = opendir(dirc.c_str());
    /*
    if(dir == NULL){
        perror("open dir error ...");
        exit(1);
    }*/
    while ((ptr = readdir(dir)) != NULL) {
        if (ptr->d_type == 8)//it;s file
        {
            files.push_back(dirc + '/' + ptr->d_name);
        } else if (ptr->d_type == 10)//link file
            continue;
        else if (ptr->d_type == 4) {
            files.push_back(ptr->d_name);
        }
    }
    closedir(dir);
    sort(files.begin(), files.end());
    for (size_t i = 0; i < files.size(); ++i) {
        cout << files[i] << endl;
    }
    return files;
}


void LoadKeyFrame(ifstream &f) {
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

//    for ( int i = 0; i < 4; i ++ )
//    {
//      for ( int j = 0; j < 4; j ++ )
//      {
//              f.read((char*)&T.at<float>(i,j), sizeof(float));
//              cerr<<"T.at<float>("<<i<<","<<j<<"):"<<T.at<float>(i,j)<<endl;
//      }
//    }

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
}

int main(int argc, char **argv) {


    MapInfoDto aMap;

    string mapId = "2c30ff9e-5734-4225-9506-721aec148e08";
    aMap.id = mapId;
    aMap.comment = "1002-1020 测绘学院走一圈";

    MyDb db;

    bool connected = db.initDB("localhost", "root", "passwd", "visual-db", 3306);
    cout << "mysql is connected: " << connected << endl;
    string sql = MyDbHelper::buildInsertMapInfo(aMap);
    db.exeSQL(sql);

    cout << "tbl_map_info: " << endl;
    db.exeSQL("select * from tbl_map_info");

    auto *mapLoad = new MapLoad();
    ifstream f;
    f.open("/home/godu/Documents/orbslam-save-map/ORB_SLAM2/MapPointandKeyFrame.bin");
    vector<MappointDto> mappointDtos = mapLoad->LoadMappoint(f, mapId);
    for (const MappointDto &dto : mappointDtos) {
        sql = MyDbHelper::buildInsertMappoint(dto);
        db.exeSQL(sql);
    }

//    string strVocFile = argv[1];
//    SystemSetting *mySystemSetting = new SystemSetting();
//    mySystemSetting->LoadSystemSetting(argv[2]);
//    InitKeyFrame initkf(*mySystemSetting);

    unsigned long int nKeyFrames;
    f.read((char *) &nKeyFrames, sizeof(nKeyFrames));
    cerr << "Map.cc :: The number of KeyFrames:" << nKeyFrames << endl;
    for (int i = 0; i < nKeyFrames; i++) {
        cout << "processing keyframe: " << i << "/" << nKeyFrames << endl;
        auto featureDtos = mapLoad->LoadKeyFrame(f, mapId);
        for (const FeatureDto &dto  : featureDtos) {
            if (dto.size == 0.0 || dto.imgTimestamp < 0.10) {
                continue;
            }
            sql = MyDbHelper::buildInsertFeature(dto);
            db.exeSQL(sql);
        }
    }
    cout << "map loaded!" << endl;
    f.close();

}