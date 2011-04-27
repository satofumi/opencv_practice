/*!
  \example example_4-2.cpp トラックバーを用いたボタンの実現

  \author Satofumi KAMIMURA

  $Id$
*/

#include <highgui.h>
#include <iostream>

using namespace std;


namespace
{
    const char* window_name = "Demo Window";
    int switch_value_ = 0;


    void switch_on_function(void)
    {
        cout << "on" << endl;
    }


    void switch_off_function(void)
    {
        cout << "off" << endl;
    }


    void switch_callback(int position)
    {
        if (position == 0) {
            switch_off_function();
        } else {
            switch_on_function();
        }
    }
}


int main(int argc, char *argv[])
{
    cvNamedWindow(window_name);

    // トラックバーの作成
    cvCreateTrackbar("Switch", window_name, &switch_value_, 1, switch_callback);

    // ESC が押されるまで待機
    enum {
        Wait_msec = 15,
        ESC_key = 27,
    };
    while (true) {
        if (cvWaitKey(Wait_msec) == ESC_key) {
            break;
        }
    }

    cvDestroyWindow(window_name);
    return 0;
}
