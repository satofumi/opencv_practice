/*!
  \file
  \brief 画像の表示用 Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <QHBoxLayout>
#include <QLabel>
#include <cv.h>
#include <highgui.h>
#include "Image_view_widget.h"

#include <cstdio>

using namespace cv;


struct Image_view_widget::pImpl
{
    Image_view_widget* widget_;
    QLabel image_label_;
    QImage* image_;


    pImpl(Image_view_widget* widget)
        : widget_(widget), image_(NULL)
    {
    }


    void initialize_form(void)
    {
        QHBoxLayout* layout = new QHBoxLayout(widget_);
        layout->addWidget(&image_label_);
        widget_->setLayout(layout);

        enum { Width = 640, Height = 480 };
        image_label_.setMinimumSize(Width, Height);
    }


    void set_image(Mat& frame)
    {
        delete image_;
        image_ = new QImage(frame.data, frame.cols, frame.rows, frame.step,
                            QImage::Format_RGB888);
    }


    void update_image(void)
    {
        image_label_.setPixmap(QPixmap::fromImage(*image_));
    }
};


Image_view_widget::Image_view_widget(QWidget* parent)
    : QWidget(parent), pimpl(new pImpl(this))
{
    pimpl->initialize_form();
}


Image_view_widget::~Image_view_widget(void)
{
}


void Image_view_widget::set_image(cv::Mat& frame)
{
    pimpl->set_image(frame);
}


void Image_view_widget::captured(void)
{
    pimpl->update_image();
}
