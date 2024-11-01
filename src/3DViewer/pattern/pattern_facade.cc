#include "pattern_facade.h"

namespace s21 {
Facade::Facade() : model_(), controller_(&model_), w_(nullptr, &controller_) {}

void Facade::build() { w_.show(); }
}  // namespace s21
