/*!
  \brief example_2-5.cpp 画像サイズの変更

  \author Satofumi KAMIMURA

  $Id$
*/

#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;


namespace
{
    IplImage* do_pyr_down(IplImage* input)
    {
#if 0
        assert(((input->width % 2) == 0) &&
               ((input->height % 2) == 0));
#endif

        IplImage* output = cvCreateImage(cvSize(input->width / 2,
                                                input->height / 2),
                                         input->depth,
                                         input->nChannels);
        cvPyrDown(input, output);
        return output;
    }
}


int main(int argc, char *argv[])
{
    if (argc <= 1) {
        cout << "usage: " << argv[0] << " <image file>" << endl;
        return 1;
    }

    const char* image_file = argv[1];
    IplImage* original = cvLoadImage(image_file);
    IplImage* converted = do_pyr_down(original);

    const char* window_name = "Example 5";
    cvNamedWindow(window_name);
    cvShowImage(window_name, converted);

    // キーの入力待ち
    cvWaitKey(0);
    cvDestroyWindow(window_name);

    return 0;
}
