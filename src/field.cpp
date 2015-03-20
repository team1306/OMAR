#include "field.h"
#include "question.h"
#include <vector>

Field::Field(std::vector<Question> questions) {}

void Field::parse() {}

std::string Field::getValue() {}

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
