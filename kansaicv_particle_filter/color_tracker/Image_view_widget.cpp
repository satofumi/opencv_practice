/*!
  \file
  \brief 画像の表示用 Widget

  \author Satofumi Kamimura

  $Id$
*/

#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QRgb>
#include <QMouseEvent>
#include <QMutexLocker>
#include <cv.h>
#include <highgui.h>
#include <opencv2/legacy/legacy.hpp>
#include "Image_view_widget.h"

#include <cstdio>

using namespace cv;


namespace
{
    typedef vector<CvPoint> Points;

    const double Sigma = 10.0;

    enum {
        Num_of_particles = 1000,
    };
}


struct Image_view_widget::pImpl
{
    Image_view_widget* widget_;
    QMutex mutex_;
    QImage* image_;
    QLabel image_label_;
    CvConDensation* particle_filter_;
    CvMat* lower_bound_;
    CvMat* upper_bound_;
    QRgb target_;
    Points sample_points_;


    pImpl(Image_view_widget* widget)
        : widget_(widget), image_(NULL),
          particle_filter_(NULL), lower_bound_(NULL), upper_bound_(NULL)
    {
        sample_points_.reserve(Num_of_particles);
        target_ = QColor(Qt::black).rgb();
    }


    void initialize_form(void)
    {
        QVBoxLayout* layout = new QVBoxLayout(widget_);
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


    void paint(QPainter& painter)
    {
        if (!image_) {
            return;
        }

        painter.drawImage(QPoint(0, 0), *image_);

        // サンプル位置を描画
        QPen pen(QColor(Qt::green));
        painter.setPen(pen);
        for (Points::const_iterator it = sample_points_.begin();
             it != sample_points_.end(); ++it) {
            const CvPoint& p = *it;
            painter.drawPoint(p.x, p.y);
        }
    }


    void initialize_tracking(const QImage* frame)
    {
        // Condensation 構造体を作成する
        const int Dimension = 4;
        particle_filter_ = cvCreateConDensation(Dimension, 0, Num_of_particles);

        // 状態ベクトルの範囲の指定
        lower_bound_ = cvCreateMat(4, 1, CV_32FC1);
        upper_bound_ = cvCreateMat(4, 1, CV_32FC1);

        cvmSet(lower_bound_, 0, 0, 0.0);
        cvmSet(lower_bound_, 1, 0, 0.0);
        cvmSet(lower_bound_, 2, 0, -3.0);
        cvmSet(lower_bound_, 3, 0, -3.0);

        cvmSet(upper_bound_, 0, 0, frame->width());
        cvmSet(upper_bound_, 1, 0, frame->height());
        cvmSet(upper_bound_, 2, 0, +3.0);
        cvmSet(upper_bound_, 3, 0, +3.0);

        // Condensation 構造体の初期化
        cvConDensInitSampleSet(particle_filter_, lower_bound_, upper_bound_);

        // 状態遷移行列の設定
        const double matrix_elements[] = {
            1.0, 0.0, 1.0, 0.0,
            0.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0,
        };
        size_t n = sizeof(matrix_elements) / sizeof(matrix_elements[0]);
        for (size_t i = 0; i < n; ++i) {
            particle_filter_->DynamMatr[i] = matrix_elements[i];
        }

        // システムノイズの分布モデルを設定
        // 平均 0, 分散 1 の正規分布
        cvRandInit(&(particle_filter_->RandS[0]), 0, 1, 1, CV_RAND_NORMAL);
        cvRandInit(&(particle_filter_->RandS[1]), 0, 1, 2, CV_RAND_NORMAL);
        cvRandInit(&(particle_filter_->RandS[2]), 0, 1, 3, CV_RAND_NORMAL);
        cvRandInit(&(particle_filter_->RandS[3]), 0, 1, 4, CV_RAND_NORMAL);
    }


    void update_color(const QColor& color)
    {
        target_ = color.rgb();
    }


    void cleanup_tracking(void)
    {
        cvReleaseConDensation(&particle_filter_);
        cvReleaseMat(&lower_bound_);
        cvReleaseMat(&upper_bound_);

        lower_bound_ = NULL;
        upper_bound_ = NULL;
        particle_filter_ = NULL;
    }


    void update_tracking(const QImage* image)
    {
        if (!particle_filter_) {
            initialize_tracking(image_);
        }

        // 各サンプルの尤度を計算する
        sample_points_.clear();
        for (int i = 0; i < Num_of_particles; ++i) {
            int x = particle_filter_->flSamples[i][0];
            int y = particle_filter_->flSamples[i][1];

            if ((x < 0) || (x >= image->width()) ||
                (y < 0) || (y >= image->height())) {
                // 画像の範囲を超えたものは尤度を 0 にしておく
                particle_filter_->flConfidence[i] = 0.0;
            } else {
                // 尤度の計算
                particle_filter_->flConfidence[i] = likelihood(image, x, y);
                sample_points_.push_back(cvPoint(x, y));
            }
        }

        cvConDensUpdateByTime(particle_filter_);
    }


    // 尤度推定
    double likelihood(const QImage* image, int x, int y)
    {
        // 色の取得
        QRgb rgb = image->pixel(x, y);

        // 色空間内の距離を計算
        double color_dist = sqrt(pow(qRed(rgb) - qRed(target_), 2) +
                                 pow(qGreen(rgb) - qGreen(target_), 2) +
                                 pow(qBlue(rgb) - qBlue(target_), 2));

        // 尤度を計算
        return 1.0 / (sqrt(2.0 * M_PI) * Sigma)
            * exp(-pow(color_dist, 2) / (2.0 * pow(Sigma, 2)));
    }


#if 0
    void draw(void)
    {
        if (!image_) {
            return;
        }

        //QRgb rgb = (QColor(Qt::green).rgb());
        fprintf(stderr, "%p\n", image_);
        QRgb rgb = image_->pixel(0, 0);
        for (Points::const_iterator it = sample_points_.begin();
             it != sample_points_.end(); ++it) {
            const CvPoint& p = *it;
            fprintf(stderr, "(%d, %d, %08x), ", p.x, p.y, rgb);
            //image_->setPixel(p.x, p.y, rgb);
        }
        image_label_.setPixmap(QPixmap::fromImage(*image_));
    }
#endif
};


Image_view_widget::Image_view_widget(QWidget* parent)
    : QWidget(parent), pimpl(new pImpl(this))
{
    pimpl->initialize_form();
}


Image_view_widget::~Image_view_widget(void)
{
}


void Image_view_widget::update_tracking(void)
{
    QMutexLocker locker(&pimpl->mutex_);

    pimpl->update_tracking(pimpl->image_);
    repaint();
}


void Image_view_widget::set_image(cv::Mat& frame)
{
    QMutexLocker locker(&pimpl->mutex_);

    pimpl->set_image(frame);
}


#if 1
void Image_view_widget::paintEvent(QPaintEvent *event)
{
    static_cast<void>(event);

    QPainter painter(this);
    pimpl->paint(painter);
}
#endif


void Image_view_widget::mousePressEvent(QMouseEvent* event)
{
    QMutexLocker locker(&pimpl->mutex_);

    Qt::MouseButton button = event->button();
    if (button & Qt::LeftButton) {
        QPoint p = event->pos();
        if (pimpl->image_) {
            QColor color(pimpl->image_->pixel(p.x(), p.y()));
            pimpl->update_color(color);
            pimpl->cleanup_tracking();
            emit picked_color(color);
        }
    }
}


#if 0
void Image_view_widget::draw(void)
{
    QMutexLocker locker(&pimpl->mutex_);

    pimpl->draw();
}
#endif
