/*!
  \example example_2-2.cpp ビデオファイルの再生サンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include <highgui.h>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "usage: " << argv[0] << " <movie file>" << endl;
        return 1;
    }

    const char* movie_file = argv[1];
    const char* window_title = "Example 2";

    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    CvCapture* capture = cvCreateFileCapture(movie_file);
    while (true) {
        IplImage* frame = cvQueryFrame(capture);
        if (!frame) {
            break;
        }
        cvShowImage(window_title, frame);

        enum {
            Escape_key = 27,
            Wait_msec = 33,
        };
        char ch = cvWaitKey(Wait_msec);
        if (ch == Escape_key) {
            break;
        }
    }

    cvReleaseCapture(&capture);
    cvDestroyWindow(window_title);

    return 0;
}
