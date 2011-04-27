/*!
  \example example_4-3.cpp ビデオを特定する４文字のコードを取得する

  \author Satofumi KAMIMURA

  $Id$
*/

#include <highgui.h>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    const char* movie_file_name = argv[1];
    CvCapture* capture = cvCreateFileCapture(movie_file_name);
    cvQueryFrame(capture);

    double f = cvGetCaptureProperty(capture, CV_CAP_PROP_FOURCC);
    char* fourcc = (char *)(&f);

    cout << f << endl;
    cout << fourcc << endl;

    return 0;
}
