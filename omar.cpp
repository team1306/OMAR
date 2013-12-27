#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include "tournament.h"

int main(int argv, char** argc) {
  string filename;
  if(argv == 1) {
    filename = "./scans";
  }
  else {
    filename = argc[1];
  }
  Tournament t (filename);
  t.prepare();
  std::cout << "Prepared" << std::endl;
  t.process();
  std::cout << "Processed" << std::endl;
  t.report("report.dat");
  std::cout << "Reported" << std::endl;
  std::system("python ./bintonum.py");
  std::cout << "Converted to csv" << std::endl;
  //std::system("python ./main.py");
  std::cout << "Ranked teams" << std::endl;
  return 0;
}
