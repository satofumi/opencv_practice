/*!
  \file
  \brief 色の追従情報を表示するための Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QShortcut>
#include <QMessageBox>
#include <highgui.h>
#include "Color_tracking_widget.h"
#include "Camera_connection_widget.h"
#include "Color_picker_widget.h"
#include "Image_view_widget.h"
#include "Capture_thread.h"

#include <cstdio>

using namespace cv;


struct Color_tracking_widget::pImpl
{
    Color_tracking_widget* widget_;
    Camera_connection_widget connection_widget_;
    Color_picker_widget color_picker_widget_;
    Image_view_widget image_view_widget_;
    VideoCapture capture_;
    Capture_thread capture_thread_;


    pImpl(Color_tracking_widget* widget)
        : widget_(widget), capture_thread_(capture_, &image_view_widget_)
    {
    }


    void initialize_form(void)
    {
        // layout setting
        QVBoxLayout* layout = new QVBoxLayout(widget_);
        QHBoxLayout* header = new QHBoxLayout;
        header->addWidget(&connection_widget_);
        header->addStretch();
        header->addWidget(&color_picker_widget_);
        layout->addLayout(header);
        layout->addWidget(&image_view_widget_);
        widget_->setLayout(layout);

        // signals
        connect(widget_, SIGNAL(set_device_size(int)),
                &connection_widget_, SLOT(set_device_size(int)));
        connect(&connection_widget_, SIGNAL(opened(int)),
                widget_, SLOT(opened(int)));
#if 0
        connect(&capture_thread_, SIGNAL(captured()),
                &image_view_widget_, SLOT(draw()));
#endif
        connect(&image_view_widget_, SIGNAL(picked_color(const QColor&)),
                &color_picker_widget_, SLOT(set_color(const QColor&)));

        // 終了ショートカットの登録
        (void) new QShortcut(Qt::CTRL + Qt::Key_Q, widget_, SLOT(close()));
        (void) new QShortcut(Qt::ALT + Qt::Key_F4, widget_, SLOT(close()));
    }


    void update_camera_devices(void)
    {
        enum { Max_camera_size = 18 };
        for (int i = 0; i < Max_camera_size; ++i) {
            VideoCapture capture(i);
            if (!capture.isOpened()) {
                emit widget_->set_device_size(i);
                return;
            }
        }
        emit widget_->set_device_size(-1);
    }


    bool open_camera(int device_id)
    {
        if (!capture_.open(device_id)) {
            return false;
        }

        enum { Image_width = 640, Image_height = 480 };
        capture_.set(CV_CAP_PROP_FRAME_WIDTH, Image_width);
        capture_.set(CV_CAP_PROP_FRAME_HEIGHT, Image_height);

        return true;
    }


    void start_capture(void)
    {
        capture_thread_.start();
    }
};


Color_tracking_widget::Color_tracking_widget(QWidget* parent)
    : QWidget(parent), pimpl(new pImpl(this))
{
    pimpl->initialize_form();
    pimpl->update_camera_devices();
}


Color_tracking_widget::~Color_tracking_widget(void)
{
}


void Color_tracking_widget::opened(int device_id)
{
    if (!pimpl->open_camera(device_id)) {
        QMessageBox::warning(this, tr("Open error"),
                             tr("Cannot open camera device"));
        return;
    }
    pimpl->start_capture();
}
