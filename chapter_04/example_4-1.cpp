/*!
  \example example_4-1.cpp スクリーンにマウスで矩形を描画するサンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include "highgui.h"

CvRect box_;


int main(int argc, char *argv[])
{
    // 初期化
    box_ = cvRect(-1, -1, 0, 0);

    IplImage* image = cvCreateImage(cvSize(200, 200), IPL_DEPTH_8U, 3);
    cvZero(image);
    IplImage* temp = cvCloneImage(image);

    // !!! コメントを要約して記述する
    (void)temp;

    // !!!

    return 0;
}
