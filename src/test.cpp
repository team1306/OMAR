#include <iostream>
#include <string>
#include <vector>
#include "report.h"
#include "database.h"
#include "page.h"

int main(int argv, char** argc) {
  Database database ("./data/omar.db", "./tex/regional2015.pos");
  Report report (&database);
  
  report.initialize();
  report.parse();
  report.writeToFile("./data/report.dat");
    
  return 0;
}
