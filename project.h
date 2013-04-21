#ifndef __PROJECT_H__
#define __PROJECT_H__

#include <vector>
#include <string>
#include "cv.h"
#include "highgui.h"
#include "page.h"

class Tournament {
 public:
  Tournament(std::vector<std::string>&);
  Tournament(std::string);
  void loadScans(std::vector<std::string>);
  void loadScans(std::string);
  void prepare(void);
  void process(void);
  int getDir(std::string, std::vector<std::string>&);
  std::vector<std::vector<bool> > answers(void);
  std::vector<point> getUR(void) {return ur;}
  std::vector<point> getLL(void) {return ll;}
  size sp;
 private:
  std::vector<Page> pages;
  std::vector<Mat> srcs;
  std::vector<point> ur, ll;
};

#endif
