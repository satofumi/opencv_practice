/*!
  \example example_2-9.cpp ビデオからの画像取り込み

  \author Satofumi KAMIMURA

  $Id$
*/

#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    CvCapture* capture = cvCreateCameraCapture(0);
    if (!capture) {
        cout << "camera device is not found." << endl;
        cout << "try by root user." << endl;
        return 1;
    }

    const char* window_title = "Example 9";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
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
