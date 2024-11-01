#include "model.h"

namespace s21 {

void Model::InitData(Data &data) { init_.InitData(data); }

void Model::ParseObjFile(std::string path, Data &data, Errors &err) {
  parser_.ParseObjFile(path, data, err);
}

void Model::Normalize(Data &data) { normalize_.NormalizeCoords(data); }

void Model::Scale(Data &data, double value) {
  for (size_t i = 0; i < data.vertex_.size(); i++) {
    data.vertex_[i] *= value;
  }
  data.min_.x *= value;
  data.min_.y *= value;
  data.min_.z *= value;
  data.max_.x *= value;
  data.max_.y *= value;
  data.max_.z *= value;
}

void Model::Transformate(TransformCommand *command, char coordinate, Data &data,
                         double value) {
  transform_.run(command, coordinate, data, value);
}

}  // namespace s21
