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

    void update_tracking(void);
    void set_image(cv::Mat& frame);

 protected:
#if 1
    void paintEvent(QPaintEvent *event);
#endif
    void mousePressEvent(QMouseEvent* event);

 public slots:
#if 0
    void draw(void);
#endif

 signals:
    void picked_color(const QColor& color);

 private:
    Image_view_widget(const Image_view_widget& rhs);
    Image_view_widget& operator = (const Image_view_widget& rhs);

    struct pImpl;
    std::auto_ptr<pImpl> pimpl;
};

#endif
