#ifndef COLOR_PICKER_WIDGET_H
#define COLOR_PICKER_WIDGET_H

/*!
  \file
  \brief 色の取得を操作するための Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <memory>
#include <QWidget>


class Color_picker_widget : public QWidget
{
    Q_OBJECT;

 public:
    Color_picker_widget(QWidget* parent = NULL);
    ~Color_picker_widget(void);

 private:
    Color_picker_widget(const Color_picker_widget& rhs);
    Color_picker_widget& operator = (const Color_picker_widget& rhs);

    struct pImpl;
    std::auto_ptr<pImpl> pimpl;
};

#endif
