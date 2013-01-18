#ifndef IMAGE_VIEW_WIDGET_H
#define IMAGE_VIEW_WIDGET_H

/*!
  \file
  \brief 画像の表示用 Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <memory>
#include <QWidget>
#include <cv.h>

namespace cv
{
    class Mat;
}


class Image_view_widget : public QWidget
{
    Q_OBJECT;

 public:
    Image_view_widget(QWidget* parent = NULL);
    ~Image_view_widget(void);

    void set_image(cv::Mat& frame);

 public slots:
    void captured(void);

 private:
    Image_view_widget(const Image_view_widget& rhs);
    Image_view_widget& operator = (const Image_view_widget& rhs);

    struct pImpl;
    std::auto_ptr<pImpl> pimpl;
};

#endif
