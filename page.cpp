#include <string>
#include <vector>
#include <iostream>
#include "page.h"
#include "question.h"
#include "cv.h"
#include "highgui.h"

using namespace cv;

Page::Page(std::vector<string>& q, std::vector<point> pointsur, std::vector<point> pointsll, const Mat& src, size a, size b) {
  sp = a;
  page = b;
  src.copyTo(image);
  for(int i=0; i<q.size(); i++) {
    questions.push_back(Question (pointsur[i], pointsll[i], sp, page, q[i]));
  }
}
  
void Page::read(void) {
  std::cout << "1" << std::endl;
  double total;
  int t;
  for(int i=0; i<questions.size(); i++) {
    total = 0;
    for(int x=questions[i].getUR().x; x<questions[i].getLL().x; x++) {
      for(int y=questions[i].getLL().y; y<questions[i].getUR().y; y++) {
	total += double(image.at<uchar>(y, x))/((questions[i].getLL().x - questions[i].getUR().x) * (questions[i].getUR().y - questions[i].getLL().y));
      }
    }
    std::cout << total << std::endl;
    if(total < 200) {
      questions[i].setAnswer(true);
    }
    else {
      questions[i].setAnswer(false);
    }
  }
}

std::vector<bool> Page::answers(void) {
  std::vector<bool> a;
  for(int i=0; i<questions.size(); i++) {
    a.push_back(questions[i].getAnswer());
  }
  return a;
}
