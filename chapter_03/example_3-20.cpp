/*!
  \example example_3-16.cpp IPP のインストール確認

  \author Satofumi KAMIMURA

  $Id$
*/

#include "opencv/cv.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
    const char* libraries;
    const char* modules;

    cvGetModuleInfo(0, &libraries, &modules);
    cout << "Libraries: " << libraries << endl
         << "Modules: " << modules << endl;

    return 0;
}
