#include "Point.h"

template <typename DataType, int Dim>
Point<DataType, Dim>::Point(const Eigen::Matrix<DataType, Dim, 1> &vec,
                            const Eigen::Matrix<DataType, Dim, Dim> &var)
    : Eigen::Matrix<DataType, Dim, 1>(vec), covariance(var) {}
