#include "number.h"
#include <vector>
#include <string>

Number::Number(std::vector<Question> &qs) {
  questions = qs;
}

void Number::parse() {
  std::vector<std::string> splitQ;
  for(int i=0; i<questions.size(); i++) {
    if(questions[i].getAnswer()) {
      splitQ = split(questions[i].getName(), '.');
      value += std::stoi(splitQ[1]) * std::stoi(splitQ[2]);
    }
  }
}

std::string Number::getValue() {
  return std::to_string(value);
}

std::vector<std::string>& Number::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> Number::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
