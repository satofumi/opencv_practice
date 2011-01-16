/*!
  \example example_3-16.cpp 構造体の設定を読み書きする例

  \author Satofumi KAMIMURA

  $Id$
*/

#include <opencv/cxcore.h>
#include <opencv/cv.h>


namespace
{
    void save_storage(const CvMat* cmatrix)
    {
        CvFileStorage* fs = cvOpenFileStorage("cfg.xml", 0, CV_STORAGE_WRITE);
        cvWriteInt(fs, "frame_count", 10);
        cvStartWriteStruct(fs, "frame_size", CV_NODE_SEQ);
        cvWriteInt(fs, 0, 320);
        cvWriteInt(fs, 0, 200);
        cvEndWriteStruct(fs);
        cvWrite(fs, "color_cvt_matrix", cmatrix);
        cvReleaseFileStorage(&fs);
    }
}


int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    CvMat* matrix = cvCreateMat(2, 2, CV_32FC1);
    cvmSet(matrix, 0, 0, 1.0);
    cvmSet(matrix, 1, 0, 2.0);
    cvmSet(matrix, 0, 1, 3.0);
    cvmSet(matrix, 1, 1, 4.0);

    save_storage(matrix);

    return 0;
}
