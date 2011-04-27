/*!
  \example example_3-12.cpp widthStep を使って部分領域を変更するサンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;


namespace
{
    void print_help(const char* program_name)
    {
        cout << program_name << " <image> <x> <y> <width> <height> <add>"
             << endl;
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
    CvRect interest_rect;
    interest_rect.x = x;
    interest_rect.y = y;
    interest_rect.width = width;
    interest_rect.height = height;

    int add = atoi(argv[6]);

    IplImage* sub_image =
        cvCreateImageHeader(cvSize(interest_rect.width,
                                   interest_rect.height),
                            image->depth, image->nChannels);
    sub_image->origin = image->origin;
    sub_image->widthStep = image->widthStep;
    sub_image->imageData = image->imageData +
        (interest_rect.x * image->widthStep) +
        (interest_rect.y * image->nChannels);

    cvAddS(sub_image, cvScalar(add), sub_image);
    cvReleaseImageHeader(&sub_image);

    const char* window_title = "Example 13";
    cvNamedWindow(window_title, CV_WINDOW_AUTOSIZE);
    cvShowImage(window_title, image);
    cvWaitKey(0);

    cvReleaseImage(&image);
    cvDestroyWindow(window_title);

    return 0;
}
