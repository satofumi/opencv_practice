/*!
  \example example_2-4.cpp 画像の平滑化

  \author Satofumi KAMIMURA

  $Id$
*/

#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;


namespace
{
    void example_2_4(IplImage* original)
    {
        // 入力画像と変換後の画像を表示する
        const char* original_window = "Example4-in";
        const char* converted_window = "Example4-out";
        cvNamedWindow(original_window);
        cvNamedWindow(converted_window);

        cvShowImage(original_window, original);

        // 画像の平滑化
        IplImage* converted =
            cvCreateImage(cvGetSize(original), IPL_DEPTH_8U, 3);
        cvSmooth(original, converted, CV_GAUSSIAN, 3, 3);

        cvShowImage(converted_window, converted);

        cvReleaseImage(&converted);

        // キーの入力待ち
        cvWaitKey(0);
        cvDestroyWindow(converted_window);
        cvDestroyWindow(original_window);
    }
}


int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "usage: " << argv[0] << " <image file>" << endl;
        return 1;
    }

    const char* image_file = argv[1];
    IplImage* original = cvLoadImage(image_file);

    example_2_4(original);

    return 0;
}
