#ifndef __FIELD_H__
#define __FIELD_H__

#include <string>
#include "question.h"

class Field {
 public:
  virtual void parse();
  std::string getValue();
  std::string getTag();

 protected:
  std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);
  std::vector<std::string> split(const std::string &s, char delim);

  std::string value;
  std::string tag;
};

#endif
