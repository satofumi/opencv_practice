/*
  コンピュータビジョン最先端ガイド１の 6.2.2 のサンプル

  色領域の追従を OpenCV の CvConDensation 用いて実現する。
*/

#include <cv.h>
#include <highgui.h>
#include <opencv2/legacy/legacy.hpp>
#include <math.h>
#include <vector>

using namespace std;


namespace
{
    double target_r_ = 120.0;
    double target_g_ = 63.0;
    double target_b_ = 45.0;

    const double sigma_ = 10.0;
    const int Dimension = 4;
    const int Num_of_particles = 1000;

    bool is_restart_ = false;


    void pick_color(double* r, double* g, double* b,
                    const IplImage* image, int x, int y)
    {
        // 色の取得
        int index = (image->widthStep * y) + (x * 3);
        *b = static_cast<unsigned char>(image->imageData[index]);
        *g = static_cast<unsigned char>(image->imageData[index + 1]);
        *r = static_cast<unsigned char>(image->imageData[index + 2]);
    }


    // 尤度推定
    double likelihood(IplImage* image, int x, int y)
    {
        // 色の取得
        double r, g, b;
        pick_color(&r, &g, &b, image, x, y);

        // 肌色との色空間内の距離を計算
        double color_dist = sqrt(pow(r - target_r_, 2) +
                                 pow(g - target_g_, 2) +
                                 pow(b - target_b_, 2));

        // 尤度を計算して返す
        return 1.0 / (sqrt(2.0 * M_PI) * sigma_)
            * exp(-pow(color_dist, 2) / (2.0 * pow(sigma_, 2)));
    }


    void initialize_particle_filter(CvConDensation*& particle_filter,
                                    CvMat*& lower_bound, CvMat*& upper_bound,
                                    int width, int height)
    {
        // Condensation 構造体を作成する
        if (particle_filter) {
            cvReleaseConDensation(&particle_filter);
        }
        particle_filter = cvCreateConDensation(Dimension, 0, Num_of_particles);

        // 状態ベクトルの範囲の指定
        if (lower_bound) {
            cvReleaseMat(&lower_bound);
            cvReleaseMat(&upper_bound);
        }
        lower_bound = cvCreateMat(4, 1, CV_32FC1);
        upper_bound = cvCreateMat(4, 1, CV_32FC1);

        cvmSet(lower_bound, 0, 0, 0.0);
        cvmSet(lower_bound, 1, 0, 0.0);
        cvmSet(lower_bound, 2, 0, -3.0);
        cvmSet(lower_bound, 3, 0, -3.0);

        cvmSet(upper_bound, 0, 0, width);
        cvmSet(upper_bound, 1, 0, height);
        cvmSet(upper_bound, 2, 0, +3.0);
        cvmSet(upper_bound, 3, 0, +3.0);

        // Condensation 構造体の初期化
        cvConDensInitSampleSet(particle_filter, lower_bound, upper_bound);

        // 状態遷移行列の設定
        const double matrix_elements[] = {
            1.0, 0.0, 1.0, 0.0,
            0.0, 1.0, 0.0, 1.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0,
        };
        size_t n = sizeof(matrix_elements) / sizeof(matrix_elements[0]);
        for (size_t i = 0; i < n; ++i) {
            particle_filter->DynamMatr[i] = matrix_elements[i];
        }

        // システムノイズの分布モデルを設定
        // 平均 0, 分散 1 の正規分布
        cvRandInit(&(particle_filter->RandS[0]), 0, 1, 1, CV_RAND_NORMAL);
        cvRandInit(&(particle_filter->RandS[1]), 0, 1, 2, CV_RAND_NORMAL);
        cvRandInit(&(particle_filter->RandS[2]), 0, 1, 3, CV_RAND_NORMAL);
        cvRandInit(&(particle_filter->RandS[3]), 0, 1, 4, CV_RAND_NORMAL);
    }


    void on_mouse(int event, int x, int y, int flags, void *param)
    {
        static_cast<void>(flags);

        IplImage* image = reinterpret_cast<IplImage*>(param);

        switch (event) {
        case CV_EVENT_LBUTTONDOWN:
            pick_color(&target_r_, &target_g_, &target_b_, image, x, y);
            is_restart_ = true;
            break;
        }
    }
}


int main(int argc, char *argv[])
{
    int camera_index = CV_CAP_ANY;
    if (argc > 1) {
        camera_index = atoi(argv[1]);
    }

    // デバイスの初期化
    CvCapture* capture = cvCreateCameraCapture(camera_index);
    enum { Image_width = 640, Image_height = 480 };
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, Image_width);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, Image_height);

    const char window_name[] = "Particle Filter";
    cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
    IplImage* image = cvQueryFrame(capture);
    cvSetMouseCallback(window_name, on_mouse, image);

    CvConDensation* particle_filter = NULL;
    CvMat* lower_bound = NULL;
    CvMat* upper_bound = NULL;
    initialize_particle_filter(particle_filter, lower_bound, upper_bound,
                               image->width, image->height);

    // ここから追跡開始
    while (cvWaitKey(1) != 'q') {
        // 画像取得
        image = cvQueryFrame(capture);

        // 各サンプルの尤度を計算する
        vector<CvPoint> points;
        for (int i = 0; i < Num_of_particles; ++i) {
            int x = particle_filter->flSamples[i][0];
            int y = particle_filter->flSamples[i][1];

            if ((x < 0) || (x >= image->width) ||
                (y < 0) || (y >= image->height)) {
                // 画像の範囲を超えたものは尤度を 0 にしておく
                particle_filter->flConfidence[i] = 0.0;
            } else {
                // 尤度の計算
                particle_filter->flConfidence[i] = likelihood(image, x, y);
                points.push_back(cvPoint(x, y));
            }
        }

        // サンプル位置を描画
        for (vector<CvPoint>::const_iterator it = points.begin();
             it != points.end(); ++it) {
            cvCircle(image, *it, 2, CV_RGB(0, 0, 255), 1, 8, 0);
        }

        // 結果を表示
        cvShowImage(window_name, image);

        // 状態更新
        cvConDensUpdateByTime(particle_filter);

        if (is_restart_) {
            initialize_particle_filter(particle_filter,
                                       lower_bound, upper_bound,
                                       image->width, image->height);
            is_restart_ = false;
        }
    }

    cvReleaseImage(&image);
    cvReleaseCapture(&capture);
    cvReleaseConDensation(&particle_filter);
    cvReleaseMat(&lower_bound);
    cvReleaseMat(&upper_bound);

    return 0;
}
