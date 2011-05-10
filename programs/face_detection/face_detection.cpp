/*!
  \file
  \brief 顔の検出

  http://opencv.jp/opencv-1.0.0/document/opencvref_cv_detection.html を参考にした。

  \author Satofumi KAMIMURA

  $Id$
*/

#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    CvCapture* capture = cvCreateCameraCapture(0);
    if (!capture) {
        cout << "camera device is not found." << endl;
        cout << "try by root user." << endl;
        return 1;
    }

    const char* classifier_path = "/usr/local/share/opencv/haarcascades/haarcascade_frontalface_default.xml";
    CvHaarClassifierCascade* cascade =
        (CvHaarClassifierCascade*)cvLoad(classifier_path);

    const char* window_name = "face detection";
    cvNamedWindow(window_name, CV_WINDOW_AUTOSIZE);
    while (true) {
        IplImage* image = cvQueryFrame(capture);
        if (!image) {
            break;
        }

        int scale = 2;
        IplImage* small_image =
            cvCreateImage(cvSize(image->width/scale,image->height/scale),
                          IPL_DEPTH_8U, 3);
        cvPyrDown( image, small_image, CV_GAUSSIAN_5x5 );

        CvMemStorage* storage = cvCreateMemStorage(0);
        CvSeq* faces = cvHaarDetectObjects(small_image, cascade, storage,
                                           1.2, 2, CV_HAAR_DO_CANNY_PRUNING);

        for(int i = 0; i < faces->total; ++i) {
            CvRect face_rect = *(CvRect*)cvGetSeqElem(faces, i);
            cvRectangle(image, cvPoint(face_rect.x * scale,
                                       face_rect.y * scale),
                        cvPoint((face_rect.x + face_rect.width) * scale,
                                (face_rect.y + face_rect.height) * scale),
                        CV_RGB(255,0,0), 3);
        }

        cvShowImage(window_name, image);
        cvReleaseImage(&small_image);

        if (cvWaitKey(30) >= 0) {
            break;
        }

        cvReleaseMemStorage(&storage);
    }

    return 0;
}
