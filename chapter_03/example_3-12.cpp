/*!
  \example example_3-12.cpp ROI を使って部分領域を変更するサンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;


namespace
{
    void print_help(const char* program_name)
    {
        (void)program_name;
        // !!!
    }
}


int main(int argc, char *argv[])
{
    const char* program_name = argv[0];
    if (argc != 7) {
        print_help(program_name);
        return 1;
    }

    const char* image_file = argv[1];
    IplImage* image = cvLoadImage(image_file);
    if (!image) {
        cout << "Invalid image file: " << image_file << endl;
        return 1;
    }

    int x = atoi(argv[2]);
    int y = atoi(argv[3]);
    int width = atoi(argv[4]);
    int height = atoi(argv[5]);
    int add = atoi(argv[6]);

    cvSetImageROI(image, cvRect(x, y, width, height));
    cvAddS(image, cvScalar(add), image);
    cvResetImageROI(image);

    const char* window_title = "Example 12";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    cvShowImage(window_title, image);
    cvWaitKey(0);

    cvReleaseImage(&image);
    cvDestroyWindow(window_title);

    return 0;
}
