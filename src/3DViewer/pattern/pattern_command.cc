#include "pattern_command.h"

namespace s21 {
void TransformInvoker::run(TransformCommand *command, char coordinate,
                           Data &data, double value) {
  command->transform(coordinate, data, value);
}

void Mover::transform(char coordinate, Data &data, double value) {
  if (coordinate == 'x') {
    for (size_t i = 0; i < data.vertex_.size(); i++) {
      if (i % 3 == 0) data.vertex_[i] += int(value) * K;
    }
  } else if (coordinate == 'y') {
    for (size_t i = 0; i < data.vertex_.size(); i++) {
      if (i % 3 == 1) data.vertex_[i] += int(value) * K;
    }
  } else {
    for (size_t i = 0; i < data.vertex_.size(); i++) {
      if (i % 3 == 2) data.vertex_[i] += int(value) * K;
    }
  }
}

void Rotater::transform(char coordinate, Data &data, double angle) {
  angle /= 57.29578;
  if (coordinate == 'x') {
    for (size_t i = 2; i < data.vertex_.size(); i += 3) {
      double temp_x = data.vertex_[i - 2];
      double temp_y = data.vertex_[i - 1];
      data.vertex_[i - 2] = (cos(angle) * temp_x - sin(angle) * temp_y);
      data.vertex_[i - 1] = (sin(angle) * temp_x + cos(angle) * temp_y);
    }
  } else if (coordinate == 'y') {
    for (size_t i = 1; i < data.vertex_.size() - 1; i += 3) {
      double temp_x = data.vertex_[i - 1];
      double temp_z = data.vertex_[i + 1];
      data.vertex_[i - 1] = (cos(angle) * temp_x - sin(angle) * temp_z);
      data.vertex_[i + 1] = (sin(angle) * temp_x + cos(angle) * temp_z);
    }
  } else {
    for (size_t i = 0; i < data.vertex_.size() - 2; i += 3) {
      double temp_y = data.vertex_[i + 1];
      double temp_z = data.vertex_[i + 2];
      data.vertex_[i + 1] = (cos(angle) * temp_y - sin(angle) * temp_z);
      data.vertex_[i + 2] = (sin(angle) * temp_y + cos(angle) * temp_z);
    }
  }
}
}  // namespace s21
