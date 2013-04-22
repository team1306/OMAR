#include <iostream>
#include <fstream>
#include <string>
#include "project.h"

int main(void) {
  std::string s;
  while(1) {
    std::cout << "> ";
    std::cin >> s;
    std::cout << s << std::endl;
    if(s == "quit") {
      std::cout << "Goodbye" << std::endl;
      return 0;
    }
    else if(s == "load") {
      Tournament t ("./scans");
      std::cout << std::endl << "Loaded scans" << std::endl;
      t.prepare();
      std::cout << "Prepared scans" << std::endl;
      while(1) {
	std::cout << "> ";
	std::cin >> s;
	if(s == "quit") {
	  std::cout << "Goodbye" << std::endl;
	  return 0;
	}
	else if(s == "read") {
	  t.process();
	}
	else if(s == "report") {
	  t.report("report.csv");
	}
	else {
	  std::cout << "Unknown command" << std::endl;
	}
      }
    }
    else {
      std::cout << "Unknown command" << std::endl;
    }
  }
}
