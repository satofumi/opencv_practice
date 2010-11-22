/*!
  \example example_2-2.cpp ビデオファイルの再生サンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include "highgui.h"
#include <iostream>

using namespace std;


namespace
{
    int slider_position_ = 0;
    CvCapture* capture_ = NULL;
    bool is_manual_changed_ = false;


    void on_trackbar_slide(int position)
    {
        if (is_manual_changed_) {
            cvSetCaptureProperty(capture_, CV_CAP_PROP_POS_FRAMES, position);
        }
        is_manual_changed_ = true;
    }
}


int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "usage: " << argv[0] << " <movie file>" << endl;
        return 1;
    }

    const char* movie_file = argv[1];
    const char* window_title = "Example 3";
    const char* track_bar_title = "Position";

    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    capture_ = cvCreateFileCapture(movie_file);
    int frames = cvGetCaptureProperty(capture_, CV_CAP_PROP_FRAME_COUNT);
    if (frames != 0) {
        cvCreateTrackbar(track_bar_title, window_title, &slider_position_,
                         frames, on_trackbar_slide);
    }

    IplImage* frame;
    while (true) {
        frame = cvQueryFrame(capture_);
        if (!frame) {
            break;
        }
        frames = cvGetCaptureProperty(capture_, CV_CAP_PROP_POS_FRAMES);
        is_manual_changed_ = false;
        cvSetTrackbarPos(track_bar_title, window_title, frames);
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

    cvReleaseCapture(&capture_);
    cvDestroyWindow(window_title);

    return 0;
}
