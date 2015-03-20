#include "multiplechoice.h"

MultipleChoice::MultipleChoice(std::vector<Question> qs) {
  questions = qs;
}

void MultipleChoice::parse() {
  for(int i=0; i<questions.size(); i++) {
    if(questions[i].getAnswer()) {
      value = i;
      break;
    }
  }

  tag = split(questions[0].getName(), '.')[0];
}

std::string MultipleChoice::getValue() {
  return questions[value].getName();
}

std::string MultipleChoice::getTag() {
  return tag;
}
