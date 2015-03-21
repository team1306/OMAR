#ifndef __MULTCHOICE_H__
#define __MULTCHOICE_H__

#include "field.h"
#include "question.h"
#include <vector>
#include <string>

class MultipleChoice : public Field {
 public:
  MultipleChoice(std::vector<Question>);
  ~MultipleChoice();
  void parse();
  std::string getValue();
  std::string getTag();
 private:
  /*
  std::string value;
  std::string tag;
  */
  std::vector<Question> questions;
};

#endif
