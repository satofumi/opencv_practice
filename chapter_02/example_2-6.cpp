/*!
  \brief example_2-6.cpp Canny エッジ検出フィルタの適用

  \author Satofumi KAMIMURA

  $Id$
*/

#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;


namespace
{
    IplImage* do_canny(IplImage* original,
                       double low_threshold,
                       double high_threshold,
                       double aperture)
    {
        if (original->nChannels != 1) {
            // グレスケール画像以外は扱わない
            cout << "nChannels: " << original->nChannels << endl;
            return NULL;
        }

        IplImage* converted = cvCreateImage(cvGetSize(original),
                                            IPL_DEPTH_8U, 1);

        cvCanny(original, converted, low_threshold, high_threshold, aperture);
        return converted;
    }
}


int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "usage: " << argv[0] << " <image file>" << endl;
        return 1;
    }

    const char* image_file = argv[1];
    IplImage* original = cvLoadImage(image_file, CV_LOAD_IMAGE_GRAYSCALE);
    IplImage* converted = do_canny(original, 10.0, 100.0, 3.0);

    const char* window_name = "Example 6";
    cvNamedWindow(window_name);
    cvShowImage(window_name, converted);

    // キーの入力待ち
    cvWaitKey(0);
    cvDestroyWindow(window_name);

    return 0;
}
