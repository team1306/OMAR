#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <dirent.h>
#include <ios>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "tournament.h"
#include "page.h"
#include "align.h"

using namespace cv;

Tournament::Tournament(std::vector<std::string>& s) { // in case you already have the list of filenames
  loadScans(s, true);
}

Tournament::Tournament(std::string dir) { // load paths to scans
  loadScans(dir, true);
}

std::vector<std::string> Tournament::readLoaded(void) {
  std::ifstream loaded ("../data/loaded.dat");
  std::vector<std::string> files;
  if(loaded.good()) {
    std::string s;
    while(!loaded.eof()) {
      loaded >> s;
      files.push_back(s);
    }
    loaded.close();
    return files;
  }
  else {
    loaded.close();
    return files;
  }
}

void Tournament::loadScans(std::vector<std::string> s, bool force) { // get names of all scans and load Mats into vector
  Mat m;
  std::ofstream loadfile ("../data/loaded.dat", force ? std::ios::out : std::ios::app);
  std::vector<std::string> loaded = readLoaded();
  int l = 0;
  int al = 0;
  for(int i=0; i<s.size(); i++) {
    if(force || std::find(loaded.begin(), loaded.end(), s[i]) == loaded.end()) {
      m = imread(s[i]);
      std::cout << "Read " << s[i] << std::endl;
      // 635 x 813
      resize(m, m, Size(635, 813), 0, 0, INTER_LINEAR);
      std::vector<Vec3f> circles;
      align(m, m);
      crop(m, m);
      srcs.push_back(m);
      names.push_back(s[i]);
      std::cout << "Loaded " << s[i] << std::endl;
      loadfile << s[i] << std::endl;
      l++;
    }
    else {
      std::cout << "Already loaded " << s[i] << std::endl;
      al++;
    }
  }
  std::cout << "Loaded " << l << " files" << std::endl;
  std::cout << al << " files already loaded" << std::endl;
  loadfile.close();
}

void Tournament::loadScans(std::string dir, bool force) { // gets filenames from directory
  std::vector<std::string> s;
  getDir(dir, s);
  loadScans(s, force);
}

void Tournament::prepare(const std::string posFile, const std::string calFile) { // read calibration circles and add Page instance for each one
  std::ifstream pos (posFile.c_str());
  std::ifstream cal (calFile.c_str());

  std::vector<point> circles;
  point c;
  for(int i=0; i<4; i++) {
    cal >> c.x >> c.y;
    circles.push_back(c);
  }
  sp.width = circles[3].x - circles[0].x;
  sp.height = circles[0].y - circles[1].y;
  std::cout << "Read calibration circles" << std::endl;

  std::string s;
  int x, y;
  point a, b;
  while(!pos.eof()) {
    pos >> s >> a.x >> a.y >> b.x >> b.y;
    a.x -= circles[1].x;
    a.y -= circles[1].y;
    b.x -= circles[1].x;
    b.y -= circles[1].y;
    ur.push_back(b);
    ll.push_back(a);
    questions.push_back(s);
  }
  std::cout << "Read positions" << std::endl;

  size z;
  for(int i=0; i<srcs.size(); i++) {
    std::cout << names[i] << std::endl;
    z.width = srcs[i].cols;
    z.height = srcs[i].rows;
    pages.push_back(Page (questions, ur, ll, srcs[i], sp, z, names[i]));
  }
  std::cout << "Added pages" << std::endl;
}

void Tournament::process(void) { // read each Page instance
  for(int i=0; i<pages.size(); i++) {
    pages[i].read();
  }
}

void Tournament::report(std::string file) { // writes read data to csv file
  std::ofstream fout ((file + "/report.dat").c_str());
  fout << "filename" << ";";
  for(int i=0; i<questions.size(); i++) {
    fout << questions[i] << ";";
  }
  fout << std::endl;
  std::vector<bool> a;
  for(int i=0; i<pages.size(); i++) {
    a = pages[i].answers();
    if(std::find(a.begin(), a.end(), true) == a.end()) {
      std::cout << "Badness! " << file << std::endl;
    }
    fout << pages[i].filename() << ";";
    for(int x=0; x<a.size(); x++) {
      fout << a[x] << ";";
    }
    fout << std::endl;
  }
}

int Tournament::getDir(std::string dir, std::vector<std::string> &files) { // gets filenames from directory path
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    std::cout << "Error opening " << dir << std::endl;
    return 1;
  }
  
  while ((dirp = readdir(dp)) != NULL) {
    if(string(dirp->d_name) != "." && string(dirp->d_name) != "..") {
      files.push_back(dir + "/" + string(dirp->d_name));
    }
  }
  closedir(dp);
  return 0;
}

std::vector<std::vector<bool> > Tournament::answers(void) { // get all answers from Pages
  std::vector<std::vector<bool> > as;
  for(int i=0; i<pages.size(); i++) {
    as.push_back(pages[i].answers());
  }
  return as;
}
