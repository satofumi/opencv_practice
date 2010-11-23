/*!
  \example example_2-10.cpp 動画の変換

  \author Satofumi KAMIMURA

  $Id$
*/

#include "cv.h"
#include "highgui.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    if (argc <= 2) {
        cout << "usage: " << argv[0] << " <input movie> <output movie>" << endl;
        return 1;
    }

    const char* input_movie_file = argv[1];
    const char* output_movie_file = argv[2];
    CvCapture* capture = cvCreateFileCapture(input_movie_file);
    if (!capture) {
        cout << "cvCreateFileCapture(" << input_movie_file << "): fail."
             << endl;
        return 1;
    }

    IplImage* bgr_frame = cvQueryFrame(capture);
    double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    CvSize size =
        cvSize(cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
               cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT));
    CvVideoWriter* writer =
        cvCreateVideoWriter(output_movie_file,
                            CV_FOURCC('M', 'J', 'P', 'G'), fps, size);
    IplImage* logpolar_frame = cvCreateImage(size, IPL_DEPTH_8U, 3);
    while ((bgr_frame = cvQueryFrame(capture)) != NULL) {
        cvLogPolar(bgr_frame, logpolar_frame,
                   cvPoint2D32f(bgr_frame->width / 2,
                                bgr_frame->height / 2),
                   40, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
        cvWriteFrame(writer, logpolar_frame);
    }

    cvReleaseVideoWriter(&writer);
    cvReleaseImage(&logpolar_frame);
    cvReleaseCapture(&capture);

    return 0;
}
