/*!
  \example example_3-19.cpp 構造体の設定を読み込む例

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

        CvSeq* s = cvGetFileNodeByName(fs, 0, "frame_size")->data.seq;
        int frame_width = cvReadInt((CvFileNode*)cvGetSeqElem(s, 0));
        int frame_height = cvReadInt((CvFileNode*)cvGetSeqElem(s, 1));
        cout << "frame_width: " << frame_width << endl
             << "frame_height: " << frame_height << endl;

        CvMat* color_cvt_matrix =
            (CvMat*)cvReadByName(fs, 0, "color_cvt_matrix");

        int rows = color_cvt_matrix->rows;
        int cols = color_cvt_matrix->cols;
        cout << "matrix_rows: " << rows << endl
             << "matrix_cols: " << cols << endl;

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                cout << cvmGet(color_cvt_matrix, x, y) << endl;
            }
        }

        cvReleaseFileStorage(&fs);
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
