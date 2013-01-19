#ifndef CAPTURE_THREAD_H
#define CAPTURE_THREAD_H

/*!
  \file
  \brief データ取得スレッド

  \author Satofumi Kamimura

  $Id$
*/

#include <memory>
#include <QThread>
#include <cv.h>

namespace cv
{
    class VideoCapture;
}

class Image_view_widget;


class Capture_thread : public QThread
{
    Q_OBJECT;

 public:
    Capture_thread(cv::VideoCapture& capture,
                   Image_view_widget* image_view_widget);
    ~Capture_thread(void);

    void run(void);

 signals:
    //void captured(void);

 private:
    Capture_thread(void);
    Capture_thread(const Capture_thread& rhs);
    Capture_thread& operator = (const Capture_thread& rhs);

    struct pImpl;
    std::auto_ptr<pImpl> pimpl;
};

#endif
