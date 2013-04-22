#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <dirent.h>
#include "cv.h"
#include "highgui.h"
#include "project.h"
#include "page.h"
#include "align.h"

using namespace cv;

Tournament::Tournament(std::vector<std::string>& s) {
  loadScans(s);
}

Tournament::Tournament(std::string dir) {
  loadScans(dir);
}

void Tournament::loadScans(std::vector<std::string> s) {
  Mat m;
  for(int i=0; i<s.size(); i++) {
    m = imread(s[i]);
    pyrDown(m, m, Size(m.cols/2, m.rows/2));
    align(m, m);
    crop(m, m);
    srcs.push_back(m);
  }
}

void Tournament::loadScans(std::string dir) {
  std::vector<std::string> s;
  getDir(dir, s);
  loadScans(s);
}

void Tournament::prepare(void) {
  std::ifstream pos ("source.pos");
  std::ifstream cal ("source.cal");

  std::vector<point> circles;
  point c;
  for(int i=0; i<4; i++) {
    cal >> c.x >> c.y;
    circles.push_back(c);
  }
  sp.width = circles[3].x - circles[0].x;
  sp.height = circles[0].y - circles[1].y;

  std::string s;
  int x, y;
  point a, b;
  while(!pos.eof()) {
    pos >> s >> a.x >> a.y >> b.x >> b.y;
    a.x -= circles[1].x;
    a.y -= circles[1].y;
    b.x -= circles[1].x;
    b.y -= circles[1].y;
    ur.push_back(a);
    ll.push_back(b);
    questions.push_back(s);
  }

  size z;
  for(int i=0; i<srcs.size(); i++) {
    z.width = srcs[i].cols;
    z.height = srcs[i].rows;
    pages.push_back(Page (questions, ur, ll, srcs[i], sp, z));
  }
}

void Tournament::process(void) {
  for(int i=0; i<pages.size(); i++) {
    pages[i].read();
  }
}

void Tournament::report(std::string file) {
  std::ofstream fout (file.c_str());
  for(int i=0; i<questions.size(); i++) {
    fout << questions[i] << ";";
  }
  fout << std::endl;
  std::vector<bool> a;
  for(int i=0; i<pages.size(); i++) {
    a = pages[i].answers();
    for(int x=0; x<a.size(); x++) {
      fout << a[x] << ";";
    }
    fout << std::endl;
  }
}

int Tournament::getDir(std::string dir, std::vector<std::string> &files) {
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    std::cout << "Error opening " << dir << std::endl;
    return 1;
  }
  
  while ((dirp = readdir(dp)) != NULL) {
    files.push_back(dir + "/" + string(dirp->d_name));
  }
  closedir(dp);
  files.erase(files.begin());
  files.erase(files.begin());
  return 0;
}

std::vector<std::vector<bool> > Tournament::answers(void) {
  std::vector<std::vector<bool> > as;
  for(int i=0; i<pages.size(); i++) {
    as.push_back(pages[i].answers());
  }
  return as;
}
