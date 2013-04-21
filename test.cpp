#include "cv.h"
#include "highgui.h"
#include "align.h"
#include "page.h"
#include "project.h"
#include <iostream>

using namespace cv;

int main() {
  std::vector<std::string> files;
  files.push_back("form1.jpg");
  files.push_back("form2.jpg");
  files.push_back("form3.jpg");

  Tournament t (files);

  t.prepare();
  std::cout << "prepared" << std::endl;
  t.process();

  std::vector<std::vector<bool> > answers;
  answers = t.answers();
  std::cout << answers[0].size() << std::endl;
  for(int x=0; x<answers.size(); x++) {
    for(int y=0; y<answers[x].size(); y++) {
      std::cout << answers[x][y] << ", ";
    }
    std::cout << std::endl;
  }

  Mat src = imread("source.jpg");
  pyrDown(src, src, Size(src.cols/2, src.rows/2));
  Mat org (src);
  std::vector<Vec3f> v;
  getCalibrationCircles(org, v);
  for(int i=0; i<4; i++) {
    circle(org, Point(v[i][0], v[i][1]), v[i][2], Scalar(0,0,255));
  }
  namedWindow("org", CV_WINDOW_AUTOSIZE);
  imshow("org", src);
  rotateImage(src, src, getAngleOffset(v));
  crop(src, src);

  size sp = t.sp;
  size page;
  page.width = src.cols;
  page.height = src.rows;
  std::vector<point> ur = t.getUR();
  std::vector<point> ll = t.getLL();

  for(int i=0; i<ur.size(); i++) {
    rectangle(src, Point((double(ur[i].x)/double(sp.width))*page.width, page.height - (double(ur[i].y)/double(sp.height))*page.height), Point((double(ll[i].x)/double(sp.width))*page.width, page.height - (double(ll[i].y)/double(sp.height))*page.height), Scalar(0,0,255));
  }

  namedWindow("win", CV_WINDOW_AUTOSIZE);
  imshow("win", src);
  waitKey(0);

  return 0;
}
