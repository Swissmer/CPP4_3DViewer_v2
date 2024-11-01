#ifndef CPP4_SRC_PATTERN_PATTERN_FACADE_H
#define CPP4_SRC_PATTERN_PATTERN_FACADE_H

#include "../view/view.h"

namespace s21 {
class Facade {
 public:
  Facade();
  void build();

 private:
  s21::Model model_;
  s21::Controller controller_;
  s21::View w_;
};

}  // namespace s21

#endif  // CPP4_SRC_PATTERN_PATTERN_FACADE_H
