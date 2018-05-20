#include "Point.h"

namespace Core {
ImagePoint::ImagePoint(const double col, const double row,
                       const std::string &id,
                       const Eigen::Matrix<double, 2, 2> &var)
    : Point<double, 2>(Eigen::Matrix<double, 2, 1>(col, row), var),
      pointId(id) {}

ObjectPoint::ObjectPoint(const double x, const double y, const double z,
                         const std::string &id,
                         const Eigen::Matrix<double, 3, 3> &var)
    : Point<double, 3>(Eigen::Matrix<double, 3, 1>(x, y, z), var), pointId(id) {
}
} // namespace Core
