#ifndef __MULTCHOICE_H__
#define __MULTCHOICE_H__

#include "field.h"
#include "question.h"
#include <vector>
#include <string>

class MultipleChoice : public Field {
 public:
  MultipleChoice(std::vector<Question>);
  void parse();
  std::string getValue();
 private:
  int value;
  std::vector<Question> questions;
};

#endif
