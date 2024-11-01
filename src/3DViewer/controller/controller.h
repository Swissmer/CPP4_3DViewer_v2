#ifndef CPP4_SRC_CONTROLLER_CONTROLLER_H
#define CPP4_SRC_CONTROLLER_CONTROLLER_H

#include "../model/helpinfo.h"
#include "../model/model.h"
#include "../pattern/pattern_command.h"

namespace s21 {
class Controller {
 public:
  explicit Controller(Model *model);
  ~Controller() = default;
  void InitData(Data &data);
  void ParseObjFile(std::string path, Data &data, Errors &err);
  void Normalize(Data &data);
  void Transformate(TransformCommand *command, char coordinate, Data &data,
                    double value);

  void Scale(Data &data, double value);

 private:
  Model *model_;
};

}  // namespace s21

#endif  // CPP4_SRC_CONTROLLER_CONTROLLER_H
