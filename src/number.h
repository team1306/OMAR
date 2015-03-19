#ifndef __NUMBER_H__
#define __NUMBER_H__

#include "field.h"
#include "question.h"
#include <vector>
#include <string>

class Number : public Field {
 public:
  Number(std::vector<Question>&);
  void parse();
  std::string getValue();
 private:
  std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
  std::vector<std::string> split(const std::string &s, char delim);

  int value = 0;
  std::vector<Question> questions;
};

#endif
