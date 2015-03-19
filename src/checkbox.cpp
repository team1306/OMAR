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
}

std::string CheckBox::getValue() {
  return std::to_string(value);
}
