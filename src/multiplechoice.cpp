#include "multiplechoice.h"

MultipleChoice::MultipleChoice(std::vector<Question> qs) {
  questions = qs;
}

void MultipleChoice::parse() {
  int index = -1;
  for(int i=0; i<questions.size(); i++) {
    if(questions[i].getAnswer()) {
      index = i;
      break;
    }
  }

  if(index == -1) {
    value = "";
  }
  else {
    value = questions[index].getName();
  }

  tag = split(questions[0].getName(), '.')[0];
}

