/*!
  \example example_3-19.cpp 構造体の設定を読み書きする例

  \author Satofumi KAMIMURA

  $Id$
*/

#include <opencv/cxcore.h>
#include <opencv/cv.h>
#include <iostream>

using namespace std;


namespace
{
    void load_storage(CvMat* cmatrix)
    {
        CvFileStorage* fs = cvOpenFileStorage("cfg.xml", 0, CV_STORAGE_READ);
        int frame_count = cvReadIntByName(fs, 0, "frame_count", 5);

        cout << "frame_count: " << frame_count << endl;

        // !!!
#if 0
        cvWriteInt(fs, "frame_count", 10);
        cvStartWriteStruct(fs, "frame_size", CV_NODE_SEQ);
        cvWriteInt(fs, 0, 320);
        cvWriteInt(fs, 0, 200);
        cvEndWriteStruct(fs);
        cvWrite(fs, "color_cvt_matrix", cmatrix);
        cvReleaseFileStorage(&fs);
#endif
    }
}


int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    CvMat* matrix = cvCreateMat(2, 2, CV_32FC1);
    load_storage(matrix);

    return 0;
}
