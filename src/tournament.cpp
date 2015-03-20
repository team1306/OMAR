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
#include "database.h"

using namespace cv;

Tournament::Tournament(std::string dir, std::string posFile, std::string calFile, Database* db) {
  database = db;
  std::vector<std::string> files;
  getDir(dir, files);
  prepare(files, posFile, calFile);
}

std::vector<std::string> Tournament::readLoaded(void) {
  std::vector<std::string> filenames;
  std::vector<Page> pages = database->getPages();
  for(int i=0; i<pages.size(); i++) {
    filenames.push_back(pages[i].filename());
  }
  return filenames;
}

void Tournament::prepare(std::vector<std::string> files, const std::string posFile, const std::string calFile) { // read calibration circles and add Page instance for each one
  std::cout << posFile << std::endl;
  std::ifstream pos (posFile.c_str());
  std::ifstream cal (calFile.c_str());

  std::vector<Point> circles;
  Point c;
  for(int i=0; i<4; i++) {
    cal >> c.x >> c.y;
    circles.push_back(c);
  }
  calibrationRect.width = circles[3].x - circles[0].x;
  calibrationRect.height = circles[0].y - circles[1].y;
  std::cout << "Read calibration circles" << std::endl;

  std::string s;
  int x, y;
  Point a, b;
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

  std::vector<std::string> filenames = readLoaded();

  Mat m;
  for(int i=0; i<files.size(); i++) {
    
    if(std::find(filenames.begin(), filenames.end(), files[i]) == filenames.end()) {
      m = imread(files[i]);
      std::cout << "Read " << files[i] << std::endl;
      // 635 x 813
      resize(m, m, Size(635, 813), 0, 0, INTER_LINEAR);
      names.push_back(files[i]);

      std::vector<Question> qs;
      for(int x=0; x<questions.size(); x++) {
	qs.push_back(Question(ur[x], ll[x], questions[x]));
      }
      pages.push_back(Page (qs, m, calibrationRect, m.size(), names[i]));
      pages[pages.size() - 1].align();
      pages[pages.size() - 1].crop();
    }
    else {
      std::cout << "Already read " << files[i] << std::endl;
    }
  }
  std::cout << "Added pages" << std::endl;
}

void Tournament::process(void) { // read each Page instance
  std::cout << "page count: " << pages.size() << std::endl;
  for(int i=0; i<pages.size(); i++) {
    std::cout << "Processing " << pages[i].filename() << std::endl;
    pages[i].read();
    database->updatePage(pages[i]);
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
