/*!
  \file
  \brief 選択した色の位置をパーティクルフィルタを用いて検出するプログラム

  \author Satofumi Kamimura

  OpenCV のパーティクルフィルタのサンプルを参考にしている。
  http://opencv.jp/sample/estimators.html

  $Id$
*/

#include <QApplication>
#include "Color_tracking_widget.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Color_tracking_widget widget;
    widget.show();

    return app.exec();
}
