/*!
  \example example_4-0.cpp 画像を表示して ESC で終了するプログラム

  \author Satofumi KAMIMURA

  $Id$
*/

#include <highgui.h>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "usage: " << argv[0] << " <image file>" << endl;
        return 1;
    }

    // そのファイル名の名前のウィンドウを作成する
    const char* window_name = argv[0];
    cvNamedWindow(window_name);

    // 指定されたファイルから画像を読み込む
    const char* file_name = argv[1];
    IplImage* img = cvLoadImage(file_name);
    if (!img) {
        // エラー出力
        // !!!
        return 1;
    }

    // ウィンドウに画像を表示する
    cvShowImage(window_name, img);

    // ユーザが ESC キーを入力するまで待つ
    enum {
        Wait_msec = 100,
        ESC_key = 27,
    };
    while (true) {
        if (cvWaitKey(Wait_msec) == ESC_key) {
            break;
        }
    }

    // メモリを解放して終了する
    cvDestroyWindow(window_name);
    cvReleaseImage(&img);

    return 0;
}
