/*!
  \file
  \brief データ取得スレッド

  \author Satofumi Kamimura

  $Id$
*/

#include <cv.h>
#include <highgui.h>
#include "Capture_thread.h"
#include "Image_view_widget.h"

#include <cstdio>

using namespace cv;


struct Capture_thread::pImpl
{
    VideoCapture& capture_;
    Image_view_widget* image_view_widget_;


    pImpl(VideoCapture& capture, Image_view_widget* image_view_widget)
        : capture_(capture), image_view_widget_(image_view_widget)
    {
    }
};


Capture_thread::Capture_thread(cv::VideoCapture& capture,
                               Image_view_widget* image_view_widget)
    : pimpl(new pImpl(capture, image_view_widget))
{
}


Capture_thread::~Capture_thread(void)
{
}


void Capture_thread::run(void)
{
    while (true) {
        Mat frame;
        pimpl->capture_ >> frame;

        Mat dest;
        cvtColor(frame, dest, CV_BGR2RGB);
        //cvtColor(frame, dest, CV_BGR2Lab);

        pimpl->image_view_widget_->set_image(dest);
        pimpl->image_view_widget_->update_tracking();

        //emit captured();
    }
}
