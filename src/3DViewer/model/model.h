#ifndef CPP4_SRC_MODEL_MODEL_H
#define CPP4_SRC_MODEL_MODEL_H

// #include <cmath>

#include "../pattern/pattern_command.h"
#include "helpinfo.h"
#include "normalization.h"
#include "parser.h"

#define K 0.01f

namespace s21 {
class Model {
 public:
  Model() : parser_{}, init_{}, normalize_{}, transform_{} {}
  ~Model() = default;
  void InitData(Data &data);
  void ParseObjFile(std::string path, Data &data, Errors &err);
  void Normalize(Data &data);
  void Transformate(TransformCommand *command, char coordinate, Data &data,
                    double value);

  void Scale(Data &data, double value);

 private:
  Parser parser_;
  HelpInfo init_;
  NormalizeClass normalize_;
  TransformInvoker transform_;
};

}  // namespace s21

#endif  // CPP4_SRC_MODEL_MODEL_H
