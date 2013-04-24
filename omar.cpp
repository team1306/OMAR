#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include "project.h"

int main(void) {
  Tournament t ("./scans");
  t.prepare();
  std::cout << "Prepared" << std::endl;
  t.process();
  std::cout << "Processed" << std::endl;
  t.report("report.csv");
  std::cout << "Reported" << std::endl;
  std::system("python ./bintonum.py");
  std::cout << "Converted" << std::endl;
  return 0;
}
