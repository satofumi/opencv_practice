/*!
  \example example_3-11.c HSV 画像の S と V の要素を最大化させるサンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;


namespace
{
    void saturate_sv(IplImage* image)
    {
        for (int y = 0; y < image->height; ++y) {
            char* p = image->imageData + (y * image->widthStep);
            for (int x = 0; x < image->width; ++x) {
                p[3 * x + 1] = 0xff;
                p[3 * x + 2] = 0xff;
            }
        }
    }
}


int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "usage: " << argv[0] << " <movie file>" << endl;
        return 1;
    }

    const char* image_file = argv[1];
    IplImage* img = cvLoadImage(image_file);

    saturate_sv(img);

    const char* window_title = "Example 11";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    cvShowImage(window_title, img);
    cvWaitKey(0);

    cvReleaseImage(&img);
    cvDestroyWindow(window_title);

    return 0;
}
