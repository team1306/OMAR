#ifndef __TOURNAMENT_H__
#define __TOURNAMENT_H__

#include <vector>
#include <string>
#include "cv.h"
#include "highgui.h"
#include "page.h"

class Tournament {
 public:
  Tournament(std::vector<std::string>&);
  Tournament(std::string);
  std::vector<std::string> readLoaded(void);
  void loadScans(std::vector<std::string>, bool = 0);
  void loadScans(std::string, bool = 0);
  void prepare(const std::string, const std::string);
  void process();
  void report(std::string);
  int getDir(std::string, std::vector<std::string>&);
  std::vector<std::vector<bool> > answers(void);
  std::vector<point> getUR(void) {return ur;}
  std::vector<point> getLL(void) {return ll;}
  size calibrationRect;
 private:
  std::vector<std::string> questions;
  std::vector<Page> pages;
  std::vector<Mat> srcs;
  std::vector<std::string> names;
  std::vector<point> ur, ll;
};

#endif
