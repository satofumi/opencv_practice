/*!
  \file
  \brief カメラ接続のための Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include "Camera_connection_widget.h"

#include <cstdio>


struct Camera_connection_widget::pImpl
{
    Camera_connection_widget* widget_;
    QComboBox combobox_;
    QPushButton button_;


    pImpl(Camera_connection_widget* widget)
        : widget_(widget), combobox_(widget)
    {
    }


    void initialize_form(void)
    {
        QHBoxLayout* layout = new QHBoxLayout(widget_);
        layout->addWidget(&combobox_);
        layout->addWidget(&button_);
        widget_->setLayout(layout);

        button_.setText("open");

        connect(&button_, SIGNAL(clicked()), widget_, SLOT(open_clicked()));
    }


    void update_combobox(int size)
    {
        combobox_.clear();
        for (int i = 0; i < size; ++i) {
            enum { Buffer_size = 32 };
            char buffer[Buffer_size];
            snprintf(buffer, Buffer_size, "Camera %d", i);
            combobox_.addItem(buffer);
        }

        bool is_device_exist = (size > 0) ? true : false;
        if (is_device_exist) {
            combobox_.setCurrentIndex(size - 1);
        }
        button_.setEnabled(is_device_exist);
    }
};


Camera_connection_widget::Camera_connection_widget(QWidget* parent)
    : QWidget(parent), pimpl(new pImpl(this))
{
    pimpl->initialize_form();
}


Camera_connection_widget::~Camera_connection_widget(void)
{
}


void Camera_connection_widget::set_device_size(int size)
{
    pimpl->update_combobox(size);
}


void Camera_connection_widget::open_clicked(void)
{
    emit opened(pimpl->combobox_.currentIndex());
}
