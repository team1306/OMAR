#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <string>

struct point {
  int x, y;
};

struct size {
  int width, height;
};

struct pt {
  double x, y;
};

class Question {
 public:
  Question(int, int, int, int, std::string);
  Question(point, point, std::string);
  Question(int, int, int, int, int, int, int, int, std::string);
  Question(point, point, size, size, std::string);
  void scale(int, int, int, int);
  void scale(size, size);
  point getUR(void);
  point getLL(void);
  std::string getName(void) {return q;}
  void setAnswer(bool);
  bool getAnswer(void) {return answer;}
 private:
  pt ur, ll;
  std::string q;
  bool answer;
};

#endif
