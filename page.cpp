#include <string>
#include <vector>
#include <iostream>
#include "page.h"
#include "question.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

Page::Page(std::vector<string>& q, std::vector<point> pointsur, std::vector<point> pointsll, const Mat& src, size a, size b, std::string fn) { // constructor copys Mat image to variable
  sp = a;
  page = b;
  src.copyTo(image);
  for(int i=0; i<q.size(); i++) {
    questions.push_back(Question (pointsur[i], pointsll[i], q[i]));
  }
  fname = fn;
}
  
void Page::read(void) { // read all boxes and set questions' values
  Scalar total;
  Mat t;
  Mat display (image);
  for(int i=0; i<questions.size(); i++) {
    t = Mat(image, Rect(Point((double(questions[i].getLL().x)/double(sp.width))*page.width, page.height - (double(questions[i].getLL().y)/double(sp.height))*page.height), Point((double(questions[i].getUR().x)/double(sp.width))*page.width, page.height - (double(questions[i].getUR().y)/double(sp.height))*page.height))); // assign a Mat to where a box should be
    total = mean(t); // finds average magnitude for the box
    if(pow(total[0], 2) + pow(total[1], 2) + pow(total[2], 2) < 67500) { // checks to see if box is black (filled in) and sets question's answer accordingly
      questions[i].setAnswer(true);
    }
    else {
      questions[i].setAnswer(false);
    }
    rectangle(display, Rect(Point((double(questions[i].getLL().x)/double(sp.width))*page.width, page.height - (double(questions[i].getLL().y)/double(sp.height))*page.height), Point((double(questions[i].getUR().x)/double(sp.width))*page.width, page.height - (double(questions[i].getUR().y)/double(sp.height))*page.height)), Scalar(0, 0, 255));
  }
  namedWindow("display", 1);
  imshow("display", display);
  waitKey(0);
}

std::vector<bool> Page::answers(void) { // return all answers to questions
  std::vector<bool> a;
  for(int i=0; i<questions.size(); i++) {
    a.push_back(questions[i].getAnswer());
  }
  return a;
}

std::string Page::filename(void) {
  return fname;
}
