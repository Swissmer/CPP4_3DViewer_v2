#ifndef CPP4_SRC_HELPINFO_HELPINFO_H
#define CPP4_SRC_HELPINFO_HELPINFO_H

#include <iostream>
#include <vector>

namespace s21 {
enum ErrorCodes { kOk, kWrongCountOfCoords, kEmptyFile };

struct Errors {
  ErrorCodes err_ = ErrorCodes::kOk;
};

struct Point {
  double x = 0;
  double y = 0;
  double z = 0;
};

struct Data {
  unsigned int vertex_in_facete_count_ = 0;

  std::vector<std::vector<int>> polygons_;
  std::vector<double> vertex_;

  int edges_ = 0;

  Point max_;
  Point min_;
};

class HelpInfo {
 public:
  void InitData(Data &data);
};

}  // namespace s21

#endif  // CPP4_SRC_HELPINFO_HELPINFO_H
