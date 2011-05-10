/*!
  \example teapot_perspective.cpp 顔検出で表示の視点を変えるサンプル

  \author Satofumi KAMIMURA

  $Id$
*/

#include <GL/glut.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace std;


namespace
{
    double width_ = 1.0;
    double height_ = 1.0;

    CvCapture* capture_ = NULL;
    CvHaarClassifierCascade* cascade_ = NULL;
    CvMemStorage* storage_ = NULL;

    int first_x_ = 0;
    int first_y_ = 0;
    int current_x_ = 0;
    int current_y_ = 0;


    void update_face_position(int *x, int *y)
    {
        IplImage* image = cvQueryFrame(capture_);

        int scale = 2;
        IplImage* small_image =
            cvCreateImage(cvSize(image->width/scale,image->height/scale),
                          IPL_DEPTH_8U, 3);
        cvPyrDown(image, small_image, CV_GAUSSIAN_5x5);

        CvSeq* faces = cvHaarDetectObjects(small_image, cascade_, storage_,
                                           1.2, 2, CV_HAAR_DO_CANNY_PRUNING);
        cvReleaseImage(&small_image);

        static int previous_x = 0;
        static int previous_y = 0;

        if (faces->total <= 0) {
            *x = previous_x;
            *y = previous_y;
            return;
        }

        // 最後に検出した顔の位置を使う
        //!< \todo 直前に用いた顔の位置に対し、近い方の矩形を使うように変更すべき
        CvRect face_rect = *(CvRect*)cvGetSeqElem(faces, faces->total - 1);
        *x = face_rect.x + (face_rect.width / 2);
        *y = face_rect.y + (face_rect.height / 2);

        previous_x = *x;
        previous_y = *y;
    }


    void initialize_face_detection(void)
    {
        capture_ = cvCreateCameraCapture(0);
        if (!capture_) {
            cout << "camera device is not found." << endl;
            cout << "try by root user." << endl;
            exit(1);
        }

        const char* classifier_path =
            "/usr/local/share/opencv/"
            "haarcascades/haarcascade_frontalface_default.xml";

        cascade_ = (CvHaarClassifierCascade*)cvLoad(classifier_path);
        storage_ = cvCreateMemStorage(0);

        update_face_position(&first_x_, &first_y_);
    }


    void init(void)
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
    }


    void display(void)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        gluPerspective(20.0, (double)width_ / (double)height_, 1.0, 100.0);

        // 検出した顔の位置を考慮して視点を決定する
        gluLookAt(1.0 + current_x_, 1.0 + current_y_, 20.0,
                  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        double size = 1.5;
        glutWireTeapot(size);

        glutSwapBuffers();
    }


    void resize(int w, int h)
    {
        width_ = w;
        height_ = h;

        glViewport(0, 0, w, h);
    }


    void idle(void)
    {
        // 顔の検出を行う
        int x;
        int y;

        update_face_position(&x, &y);

        //!< \todo 位置については、移動平均などのフィルタを適用すべき
        double ratio = 0.5;
        current_x_ = (x - first_x_) * ratio;
        current_y_ = -(y - first_y_) * ratio;

        //fprintf(stderr, "%d, %d, %d, %d\n", current_x_, current_y_, current_x_, current_y_);

        glutPostRedisplay();
    }
}


int main(int argc, char *argv[])
{
    // 顔検出まわりの初期化
    initialize_face_detection();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);

    init();
    glutMainLoop();

    return 0;
}
