#ifndef CPP4_SRC_PARSER_PARSER_H
#define CPP4_SRC_PARSER_PARSER_H

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>

#include "../pattern/pattern_strategy.h"
#include "helpinfo.h"

namespace s21 {
class Parser {
 public:
  void ParseObjFile(std::string path, Data &data, Errors &err);
  int CalculateSpaces(const std::string &line);

 private:
  StrategyInvoker strategy_;
};

}  // namespace s21

#endif  // CPP4_SRC_PARSER_PARSER_H
