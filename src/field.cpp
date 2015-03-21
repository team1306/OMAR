#include "field.h"
#include "question.h"
#include <vector>

void Field::parse() {}

std::string Field::getValue() {
  return value;
}

std::string Field::getTag() {
  return tag;
}

std::vector<std::string>& Field::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> Field::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

