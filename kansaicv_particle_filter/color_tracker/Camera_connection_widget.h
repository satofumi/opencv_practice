#ifndef CAMERA_CONNECTION_WIDGET_H
#define CAMERA_CONNECTION_WIDGET_H

/*!
  \file
  \brief カメラ接続のための Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <memory>
#include <QWidget>


class Camera_connection_widget : public QWidget
{
    Q_OBJECT;

 public:
    Camera_connection_widget(QWidget* parent = NULL);
    ~Camera_connection_widget(void);

 public slots:
    void set_device_size(int size);

 private slots:
    void open_clicked(void);

 signals:
    void opened(int device_id);

 private:
    Camera_connection_widget(const Camera_connection_widget& rhs);
    Camera_connection_widget& operator = (const Camera_connection_widget& rhs);

    struct pImpl;
    std::auto_ptr<pImpl> pimpl;
};

#endif
