#ifndef CPP4_SRC_PATTERN_PATTERN_COMMAND_H
#define CPP4_SRC_PATTERN_PATTERN_COMMAND_H

#include <cmath>

#include "../model/helpinfo.h"

#define K 0.01f

namespace s21 {
class TransformCommand {
 public:
  virtual ~TransformCommand() {}
  virtual void transform(char coordinate, Data &data, double value) = 0;
};

class TransformInvoker {
 public:
  void run(TransformCommand *command, char coordinate, Data &data,
           double value);
};

class Mover : public TransformCommand {
 public:
  void transform(char coordinate, Data &data, double value) override;
};

class Rotater : public TransformCommand {
 public:
  void transform(char coordinate, Data &data, double angle) override;
};
}  // namespace s21

#endif  // CPP4_SRC_PATTERN_PATTERN_COMMAND_H
