#include "checkbox.h"
#include "question.h"
#include "field.h"
#include <vector>
#include <string>

CheckBox::CheckBox(std::vector<Question> qs) {
  questions = qs;
}

void CheckBox::parse() {
  value = questions[0].getAnswer();
  tag = split(questions[0].getName(), '.')[0];
}

std::string CheckBox::getValue() {
  return std::to_string(value);
}

std::string CheckBox::getTag() {
  return tag;
}
