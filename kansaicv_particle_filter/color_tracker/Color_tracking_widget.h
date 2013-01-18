#ifndef COLOR_TRACKING_WIDGET_H
#define COLOR_TRACKING_WIDGET_H

/*!
  \file
  \brief 色の追従情報を表示するための Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <memory>
#include <QWidget>


class Color_tracking_widget : public QWidget
{
    Q_OBJECT;

 public:
    Color_tracking_widget(QWidget* parent = NULL);
    ~Color_tracking_widget(void);

 public slots:
    void opened(int device_id);

 signals:
    void set_device_size(int size);

 private:
    Color_tracking_widget(const Color_tracking_widget& rhs);
    Color_tracking_widget& operator = (const Color_tracking_widget& rhs);

    struct pImpl;
    std::auto_ptr<pImpl> pimpl;
};

#endif
