#include "cv.h"
#include "highgui.h"
#include "align.h"
#include "page.h"
#include "tournament.h"
#include <iostream>

using namespace cv;

int main(int argv, char** argc) {

  Tournament t ("./scans");

  t.prepare("", "");
  std::cout << "prepared" << std::endl;
  t.process();
  t.report("report.csv");

  std::vector<std::vector<bool> > answers;
  answers = t.answers();
  std::cout << answers[0].size() << std::endl;
  for(int x=0; x<answers.size(); x++) {
    for(int y=0; y<answers[x].size(); y++) {
      std::cout << answers[x][y] << ", ";
    }
    std::cout << std::endl;
  }

  std::vector<std::string> fs;
  t.getDir(argc[1], fs);
  std::cout << "here" << std::endl;
  for(int y = 0; y < fs.size(); y++) {
    Mat src = imread(fs[y]);
    pyrDown(src, src, Size(src.cols/2, src.rows/2));
    namedWindow("org", CV_WINDOW_AUTOSIZE);
    imshow("org", src);
    align(src, src);
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
    imwrite("./verification/"+fs[y], src);
    std::cout << fs[y] << std::endl;
  }
    
    return 0;
}
