#include "question.h"
#include <opencv/cv.h>
#include <string>
#include <iostream>

using namespace cv;

Question::Question(int a, int b, int c, int d, std::string quest) {
  ur.x = a;
  ur.y = b;
  ll.x = c;
  ll.y = d;
  q = quest;
}

Question::Question(Point n1, Point n2, std::string quest) {
  ur.x = n1.x;
  ur.y = n1.y;
  ll.x = n2.x;
  ll.y = n2.y;
  q = quest;
}

Question::Question(int a, int b, int c, int d, int width, int height, int calRectX, int calRectY, std::string quest) {
  ur.x = a;
  ur.y = b;
  ll.x = c;
  ll.y = d;
  q = quest;
  scale(width, height, calRectX, calRectY);
}

Question::Question(Point n1, Point n2, Size pageSize, Size calRect, std::string quest) { //first size is rows/cols second size is distance between circles
  ur.x = n1.x;
  ur.y = n1.y;
  ll.x = n2.x;
  ll.y = n2.y;
  q = quest;
  scale(pageSize, calRect);
}

void Question::scale(int width, int height, int calRectX, int calRectY) { // scale all positions of boxes
  ur.x = (double(ur.x) / double(calRectX)) * width; // calRect is distance in same units
  ur.y = (double(ur.y) / double(calRectY)) * height; // height and width are size given by rows and cols
  ll.x = (double(ll.x) / double(calRectX)) * width;
  ll.y = (double(ll.y) / double(calRectY)) * height;
}

void Question::scale(Size a, Size b) {
  ur.x = (double(ur.x) / double(a.width)) * b.width;
  ur.y = (double(ur.y) / double(a.height)) * b.height;
  ll.x = (double(ll.x) / double(a.width)) * b.width;
  ll.y = (double(ll.y) / double(a.height)) * b.height;
}

Point Question::getUR(void) {
  Point p (cvFloor(ur.x), cvFloor(ur.y));
  return p;
}

Point Question::getLL(void) {
  Point p (cvFloor(ll.x), cvFloor(ll.y));
  return p;
}

void Question::setAnswer(bool b) {
  answer = b;
}

bool Question::operator==(Question &other) {
  return (ur == other.getUR() && ll == other.getLL() && q == other.getName());
}
