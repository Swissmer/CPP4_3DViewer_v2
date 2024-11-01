#include "normalization.h"

namespace s21 {
void NormalizeClass::NormalizeCoords(Data &data) {
  std::list<double> x;
  std::list<double> y;
  std::list<double> z;
  std::vector<double>::iterator it = data.vertex_.begin();
  for (; it != data.vertex_.end(); ++it) {
    x.push_back(*it);
    ++it;
    y.push_back(*it);
    ++it;
    z.push_back(*it);
  }

  data.max_.x = *std::max_element(x.begin(), x.end());
  data.max_.y = *std::max_element(y.begin(), y.end());
  data.max_.z = *std::max_element(z.begin(), z.end());

  data.min_.x = *std::min_element(x.begin(), x.end());
  data.min_.y = *std::min_element(y.begin(), y.end());
  data.min_.z = *std::min_element(z.begin(), z.end());

  double xRange = data.max_.x - data.min_.x;
  double yRange = data.max_.y - data.min_.y;
  double zRange = data.max_.z - data.min_.z;

  double xCentral = data.min_.x + xRange / 2;
  double yCentral = data.min_.y + yRange / 2;
  double zCentral = data.min_.z + zRange / 2;

  double dmax = std::max({xRange, yRange, zRange});
  double scale = (1 - (1 * (-3))) / dmax;

  it = data.vertex_.begin();
  for (; it != data.vertex_.end(); ++it) {
    *it = (*it - xCentral) * scale;
    ++it;
    *it = (*it - yCentral) * scale;
    ++it;
    *it = (*it - zCentral) * scale;
  }
}
}  // namespace s21
