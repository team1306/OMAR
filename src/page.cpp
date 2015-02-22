#include <string>
#include <vector>
#include <iostream>
#include "page.h"
#include "question.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

Page::Page(std::vector<Question> qs, const Mat& src, size a, size b, std::string fn) {
  calibrationRect = a;
  page = b;
  src.copyTo(image);
  questions = qs;
  fname = fn;
}
  
void Page::read(void) { // read all boxes and set questions' values
  std::cout << "here" << std::endl;
  std::cout << fname << std::endl;
  std::cout << image.cols << std::endl;
  std::cout << image.rows << std::endl << std::endl;
  Scalar total;
  Mat t;
  Mat display;
  image.copyTo(display);

  for(int i=0; i<questions.size(); i++) {
    questions[i].scale(calibrationRect, page);
    std::cout << questions.size() << std::endl;
    std::cout << questions[i].getLL().x << std::endl;
    std::cout << page.height - questions[i].getUR().y << std::endl << std::endl;
    Point topLeftCorner (questions[i].getLL().x, page.height - questions[i].getUR().y);
    Point bottomRightCorner (questions[i].getUR().x, page.height - questions[i].getLL().y);
    t = image(Rect(topLeftCorner, bottomRightCorner)); // assign a Mat to where a box should be
    total = mean(t); // finds average magnitude for the box
    if(pow(total[0], 2) + pow(total[1], 2) + pow(total[2], 2) < 67500) { // checks to see if box is black (filled in) and sets question's answer accordingly
      questions[i].setAnswer(true);
    }
    else {
      questions[i].setAnswer(false);
    }
    rectangle(display, Rect(topLeftCorner, bottomRightCorner), Scalar(0,0,255));
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

size Page::getCalibrationSize() {
  return calibrationRect;
}

size Page::getPageSize() {
  return page;
}
