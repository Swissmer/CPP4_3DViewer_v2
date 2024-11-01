#include "helpinfo.h"
namespace s21 {

void HelpInfo::InitData(Data &data) {
  data.polygons_.clear();
  data.vertex_.clear();

  data.vertex_in_facete_count_ = 0;

  data.edges_ = 0;

  data.max_ = {0};
  data.min_ = {0};
}

}  // namespace s21
