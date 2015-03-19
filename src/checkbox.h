#ifndef __CHECKBOX_H__
#define __CHECKBOX_H__

#include "field.h"
#include "question.h"
#include <vector>
#include <string>

class CheckBox : public Field {
 public:
  CheckBox(std::vector<Question>);
  void parse();
  std::string getValue();
 private:
  bool value;
  std::vector<Question> questions;
};

#endif
