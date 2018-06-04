#include "Point.h"

namespace Core {
template <typename TDataType, int Dim>
Point<TDataType, Dim>::Point(const Eigen::Matrix<TDataType, Dim, 1> &vec,
                             const Eigen::Matrix<TDataType, Dim, Dim> &var)
    : Eigen::Matrix<TDataType, Dim, 1>(vec), covariance(var) {}
} // namespace Core
