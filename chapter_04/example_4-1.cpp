/*!
  \example example_4-1.cpp スクリーンにマウスで矩形を描画するサンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include <highgui.h>
#include <cv.h>


namespace
{
    const char* window_name = "Box Example";
    CvRect box_;
    bool is_drawing_box_ = false;


    void draw_box(IplImage* img, const CvRect& rect)
    {
        cvRectangle(img,
                    cvPoint(box_.x, box_.y),
                    cvPoint(box_.x + box_.width, box_.y + box_.height),
                    cvScalar(0xff, 0x00, 0x00));
    }


    void my_mouse_callback(int event, int x, int y, int flags, void *param)
    {
        IplImage* image = (IplImage*)param;

        switch (event) {
        case CV_EVENT_MOUSEMOVE: {
            if (is_drawing_box_) {
                box_.width = x - box_.x;
                box_.height = y - box_.y;
            }
        }
            break;

        case CV_EVENT_LBUTTONDOWN: {
            is_drawing_box_ = true;
            box_ = cvRect(x, y, 0, 0);
        }
            break;

        case CV_EVENT_LBUTTONUP: {
            is_drawing_box_ = false;
            if (box_.width < 0) {
                box_.x += box_.width;
                box_.width *= -1;
            }
            if (box_.height < 0) {
                box_.y += box_.height;
                box_.height *= -1;
            }
            draw_box(image, box_);
        }
            break;
        }
    }
}


int main(int argc, char *argv[])
{
    // 初期化
    box_ = cvRect(-1, -1, 0, 0);

    IplImage* image = cvCreateImage(cvSize(200, 200), IPL_DEPTH_8U, 3);
    cvZero(image);
    IplImage* temp = cvCloneImage(image);

    cvNamedWindow(window_name);

    // マウスのコールバック関数を登録する
    cvSetMouseCallback(window_name, my_mouse_callback, (void*)image);

    // メイン処理
    // コールバックが発生するのを待つ
    enum {
        Wait_msec = 15,
        ESC_key = 27,
    };
    while (true) {
        cvCopyImage(image, temp);
        if (is_drawing_box_) {
            draw_box(temp, box_);
        }
        cvShowImage(window_name, temp);

        if (cvWaitKey(Wait_msec) == ESC_key) {
            break;
        }
    }

    // メモリを解放する
    cvReleaseImage(&image);
    cvReleaseImage(&temp);
    cvDestroyWindow(window_name);

    return 0;
}
