#ifndef __NUMBER_H__
#define __NUMBER_H__

#include "field.h"
#include "question.h"
#include <vector>
#include <string>

class Number : public Field {
 public:
  Number(std::vector<Question>);
  void parse();
  std::string getValue();
  std::string getTag();

 private:
  /*
  std::string tag;
  std::string value;
  */
  std::vector<Question> questions;
};

#endif
