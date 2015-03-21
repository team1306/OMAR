#include "number.h"
#include <vector>
#include <string>

Number::Number(std::vector<Question> qs) {
  questions = qs;
}

void Number::parse() {
  std::vector<std::string> splitQ;
  int total = 0;
  for(int i=0; i<questions.size(); i++) {
    if(questions[i].getAnswer()) {
      splitQ = split(questions[i].getName(), '.');
      value += std::stoi(splitQ[1]) * std::stoi(splitQ[2]);
    }
  }

  value = std::to_string(total);
  tag = split(questions[0].getName(), '.')[0];
}
