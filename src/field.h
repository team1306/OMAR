#ifndef __FIELD_H__
#define __FIELD_H__

#include <string>
#include "question.h"

class Field {
 public:
  virtual void parse();
  virtual std::string getValue();
};

#endif
