#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include "project.h"

int main(void) {
  Tournament t ("./scans");
  t.prepare();
  t.process();
  t.report("report.csv");
  std::system("python ./bintonum.py");
  return 0;
}
