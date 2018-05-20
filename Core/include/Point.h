#ifndef CORE_POINT_H
#define CORE_POINT_H

#include "eigen3/Eigen/Eigen"

// 2D point with float type
typedef Eigen::Matrix<float, 2, 1> PointXYf;
// 2D point with double type
typedef Eigen::Matrix<double, 2, 1> PointXYd;
// 2D point with int type
typedef Eigen::Matrix<int, 2, 1> PointXYi;

// 3D point with float type
typedef Eigen::Matrix<float, 3, 1> PointXYZf;
// 3D point with double type
typedef Eigen::Matrix<double, 3, 1> PointXYZd;
// 3D point with int type
typedef Eigen::Matrix<int, 3, 1> PointXYZi;

namespace Core {
/**
 * This is a general point class for an N x 1 vector with the corresponding
 * variance-covariance matrix
 */
template <typename DataType, int Dim>
class Point : public Eigen::Matrix<DataType, Dim, 1> {
public:
  /// Constructor, which takes the N x 1 vector and its corresponding
  /// variance-covariance matrixs
  Point(const Eigen::Matrix<DataType, Dim, 1> &vec,
        const Eigen::Matrix<DataType, Dim, Dim> &var);
  /// N x N varaiance-covariance matrix
  Eigen::Matrix<DataType, Dim, Dim> covariance;
};

/**
 * This is the class for a 2D image point with variance-covariance matrix
 * Note: The origin of the coordinate system is defined at the left-upper
 * corner of the image. imagePoint[0]: column coordinate, and imagePoint[1]:
 * row coordinate
 */
class ImagePoint : public Point<double, 2> {
public:
  /// Constructor, which takes input image coordinates, and
  /// variance-covariance matrix of image coordinates
  ImagePoint(const double col, const double row, const std::string &id,
             const Eigen::Matrix<double, 2, 2> &var =
                 Eigen::Matrix<double, 2, 2>::Identity(2, 2));
  /// Point Id
  std::string pointId;
};

/**
 * This is the class for a 3D object point with variance-covariance matrix
 */
class ObjectPoint : public Point<double, 3> {
public:
  /// Constructor, which takes the coordinates of input object point, and
  /// corresponding variance-covariance matrix
  ObjectPoint(const double x, const double y, const double z,
              const std::string &id,
              const Eigen::Matrix<double, 3, 3> &var =
                  Eigen::Matrix<double, 3, 3>::Identity(3, 3));
  /// PointId
  std::string pointId;
};
} // namespace Core

#include "Point.hpp"

#endif // CORE_POINT_H
