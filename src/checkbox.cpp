#include "checkbox.h"
#include "question.h"
#include "field.h"
#include <vector>
#include <string>

CheckBox::CheckBox(std::vector<Question> qs) {
  questions = qs;
}

void CheckBox::parse() {
  value = std::to_string(questions[0].getAnswer());
  tag = split(questions[0].getName(), '.')[0];
}

