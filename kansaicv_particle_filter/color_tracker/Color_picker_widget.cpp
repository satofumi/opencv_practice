/*!
  \file
  \brief 色の取得を操作するための Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include "Color_picker_widget.h"


struct Color_picker_widget::pImpl
{
    Color_picker_widget* widget_;
    QLabel color_label_;
    QToolButton picker_button_;


    pImpl(Color_picker_widget* widget)
        : widget_(widget)
    {
        QHBoxLayout* layout = new QHBoxLayout(widget_);
        layout->addWidget(&color_label_);
        layout->addWidget(&picker_button_);
        widget_->setLayout(layout);
    }
};


Color_picker_widget::Color_picker_widget(QWidget* parent)
    : QWidget(parent), pimpl(new pImpl(this))
{
}


Color_picker_widget::~Color_picker_widget(void)
{
}

