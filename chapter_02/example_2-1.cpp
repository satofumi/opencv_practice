/*!
  \example example_2-1.cpp 画像ファイルをスクリーンに表示するサンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include <highgui.h>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "usage: " << argv[0] << " <image file>" << endl;
        return 1;
    }

    const char* image_file = argv[1];
    IplImage* img = cvLoadImage(image_file);

    const char* window_title = "Example 1";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    cvShowImage(window_title, img);
    cvWaitKey(0);

    cvReleaseImage(&img);
    cvDestroyWindow(window_title);

    return 0;
}
