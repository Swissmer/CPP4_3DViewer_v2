#include "controller.h"

namespace s21 {
Controller::Controller(Model *model) : model_(model) {}

void Controller::InitData(Data &data) { model_->InitData(data); }

void Controller::ParseObjFile(std::string path, Data &data, Errors &err) {
  model_->ParseObjFile(path, data, err);
}

void Controller::Normalize(Data &data) { model_->Normalize(data); }

void Controller::Scale(Data &data, double value) { model_->Scale(data, value); }

void Controller::Transformate(TransformCommand *command, char coordinate,
                              Data &data, double value) {
  model_->Transformate(command, coordinate, data, value);
}

}  // namespace s21
