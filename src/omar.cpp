#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include "tournament.h"
#include "database.h"
#include "report.h"

int main(int argv, char** argc) {
  bool gotScansDir = false;
  bool gotPosFile = false;
  bool gotCalFile = false;
  bool gotDBFile = false;
  bool gotRepFile = false;
  std::string posFile, calFile, scansDir, dbFile, reportFile;
  int i = 1;
  while(i < argv-1) {
    if(argc[i][0] == '-') {
      if(argc[i][1] == 'p') {
	gotPosFile = true;
	posFile = std::string (argc[i+1]);
	i++;
      }
      else if(argc[i][1] == 'c') {
	gotCalFile = true;
	calFile = std::string (argc[i+1]);
	i++;
      }
      else if(argc[i][1] == 's') {
	gotScansDir = true;
	scansDir = std::string (argc[i+1]);
	i++;
      }
      else if(argc[i][1] == 'd') {
	gotDBFile = true;
	dbFile = std::string (argc[i+1]);
	i++;
      }
      else if(argc[i][1] == 'r') {
	gotRepFile = true;
	reportFile = std::string (argc[i+1]);
	i++;
      }
    }
    i++;
  }
  if(!gotScansDir) {
    std::cout << "Missing scans directory (-s)" << std::endl;
    return 1;
  }
  if(!gotPosFile) {
    std::cout << "Missing .pos file (-p)" << std::endl;
    return 1;
  }
  if(!gotCalFile) {
    std::cout << "Missing .cal file (-c)" << std::endl;
    return 1;
  }
  if(!gotDBFile) {
    std::cout << "Missing data directory (-d)" << std::endl;
    return 1;
  }
  if(!gotRepFile) {
    std::cout << "Missing report file (-r)" << std::endl;
    return 1;
  }

  Database database (dbFile, posFile);
  Tournament t (scansDir, posFile, calFile, &database);
  std::cout << "Images prepared" << std::endl;
  t.process();
  std::cout << "Images processed" << std::endl;
  Report report (&database);
  report.initialize();
  std::cout << "Fields initialized" << std::endl;
  report.parse();
  std::cout << "Data parsed" << std::endl;
  report.writeToFile(reportFile);
  std::cout << "Converted to csv" << std::endl;
  return 0;
}
