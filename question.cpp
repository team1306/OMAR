#include "question.h"
#include "cv.h"
#include <string>
#include <iostream>

Question::Question(int a, int b, int c, int d, std::string quest) {
  ur.x = a;
  ur.y = b;
  ll.x = c;
  ll.y = d;
  q = quest;
}

Question::Question(point n1, point n2, std::string quest) {
  ur.x = n1.x;
  ur.y = n1.y;
  ll.x = n2.x;
  ll.y = n2.y;
  q = quest;
}

Question::Question(int a, int b, int c, int d, int width, int height, int spx, int spy, std::string quest) {
  ur.x = a;
  ur.y = b;
  ll.x = c;
  ll.y = d;
  q = quest;
  scale(width, height, spx, spy);
}

Question::Question(point n1, point n2, size a, size b, std::string quest) { //first size is rows/cols second size is distance between circles
  ur.x = n1.x;
  ur.y = n1.y;
  ll.x = n2.x;
  ll.y = n2.y;
  q = quest;
  scale(a, b);
}

void Question::scale(int width, int height, int spx, int spy) { // scale all positions of boxes
  ur.x = (double(ur.x) / double(spx)) * width; // sp is distance in same units
  ur.y = (1 - double(ur.y) / double(spy)) * height; // height and width are size given by rows and cols
  ll.x = (double(ll.x) / double(spx)) * width;
  ll.y = (1 - double(ll.y) / double(spx)) * height;
}

void Question::scale(size a, size b) {
  ur.x = (double(ur.x) / double(a.width)) * b.width;
  ur.y = (1 - double(ur.y) / double(a.height)) * b.height;
  ll.x = (double(ll.x) / double(a.width)) * b.width;
  ll.y = (1 - double(ll.y) / double(a.height)) * b.height;
}

point Question::getUR(void) {
  point p;
  p.x = cvFloor(ur.x);
  p.y = cvFloor(ur.y);
  return p;
}

point Question::getLL(void) {
  point p;
  p.x = cvFloor(ll.x);
  p.y = cvFloor(ll.y);
  return p;
}

void Question::setAnswer(bool b) {
  answer = b;
}
