/*!
  \example example_3-14.cpp cvAddWeighted() を用いたアルファブレンド処理サンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include <cv.h>
#include <highgui.h>


int main(int argc, char *argv[])
{
    IplImage* src1 = NULL;
    IplImage* src2 = NULL;

    if ((argc == 9) && ((src1 = cvLoadImage(argv[1], 1)) != 0) &&
        ((src2 = cvLoadImage(argv[2], 1)) != 0)) {
        int x = atoi(argv[3]);
        int y = atoi(argv[4]);
        int width = atoi(argv[5]);
        int height = atoi(argv[6]);

        double alpha = (double)atof(argv[7]);
        double beta = (double)atof(argv[8]);
        cvSetImageROI(src1, cvRect(x, y, width, height));
        cvSetImageROI(src2, cvRect(0, 0, width, height));
        cvAddWeighted(src1, alpha, src2, beta, 0.0, src1);
        cvResetImageROI(src1);

        const char* window_name = "Alpha_blend";
        cvNamedWindow(window_name, 1);
        cvShowImage(window_name, src1);
        cvWaitKey();
    }

    return 0;
}
