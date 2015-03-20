#include "number.h"
#include <vector>
#include <string>

Number::Number(std::vector<Question> qs) {
  questions = qs;
  value = 0;
}

void Number::parse() {
  std::vector<std::string> splitQ;
  for(int i=0; i<questions.size(); i++) {
    if(questions[i].getAnswer()) {
      splitQ = split(questions[i].getName(), '.');
      value += std::stoi(splitQ[1]) * std::stoi(splitQ[2]);
    }
  }

  tag = split(questions[0].getName(), '.')[0];
}

std::string Number::getValue() {
  return std::to_string(value);
}

std::string Number::getTag() {
  return tag;
}
