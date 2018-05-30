#ifndef CORE_EXTERIORORIENTATION_H
#define CORE_EXTERIORORIENTATION_H

#include "tgmath.h"

#include "Point.h"

namespace Core {
/**
 * This is the class for image Exterior Orientation Parameters (EOPs) with
 * variance-covariance matrices
 */
template <typename DataType = double> class ExteriorOrientation {
public:
  /// Default constructor
  ExteriorOrientation() = default;
  /**
   * Set up translation
   * @param[in] tx x component of the translation vector
   * @param[in] ty y component of the translation vector
   * @param[in] tz z component of the translation vector
   * @param[in] var variance-covariance matrix of the translation vector
   */
  void SetTranslation(const DataType tx, const DataType ty, const DataType tz,
                      const Eigen::Matrix<DataType, 3, 3> &var =
                          Eigen::Matrix<DataType, 3, 3>::Identity(3, 3));

  /**
   * Set up rotation
   * @param[in] omega rotation angle around x-axis
   * @param[in] phi rotation angle around y-axis
   * @param[in] kappa rotation angle around z-axis
   * @param[in] var variance-covariance matrix of the three rotation angles
   * @param[in] inDegreeFlag flag used to indicate the rotation is in degrees or
   * radians (True: in degrees; False: in radians)
   */
  void SetRotation(const DataType omega, const DataType phi,
                   const DataType kappa, const bool inDegreeFlag = true,
                   const Eigen::Matrix<DataType, 3, 3> &var =
                       Eigen::Matrix<DataType, 3, 3>::Identity(3, 3));

  /// Get a const reference of translation
  const Point<DataType, 3> &getTranslation() const;

  /**
   * Get a mutable copy of translation
   * Note: This function can be used only when you want to directly modify the
   * content in the translation vector
   */
  Point<DataType, 3> &getTranslation();

  /// Get a const reference of rotation
  const Point<DataType, 3> &getRotation() const;

  /**
   * Get a mutable copy of rotation
   * Note: This function can be used only when you want to directly modify the
   * content of rotation
   */
  Point<DataType, 3> &getRotation();

  /// Get a copy of rotation in degrees
  Point<DataType, 3> getRotationInDegrees() const;

  /// Get a copy of rotation in radians
  Point<DataType, 3> getRotationInRadians() const;

  /// Static function to convert rotation angles to radians
  static void ConvertRotationToRadians(Eigen::Matrix<DataType, 3, 1> &rotation);
  static Eigen::Matrix<DataType, 3, 1>
  ConvertRotationToRadians(const Eigen::Matrix<DataType, 3, 1> &rotation);

  /// Static function to convert rotation angles to degrees
  static void ConvertRotationToDegrees(Eigen::Matrix<DataType, 3, 1> &rotation);
  static Eigen::Matrix<DataType, 3, 1>
  ConvertRotationToDegrees(const Eigen::Matrix<DataType, 3, 1> &rotation);

  /// Member function to convert rotation angles to radians
  bool convertRotationToRadians();

  /// Member function to convert rotation angles to degrees
  bool convertRotationToDegrees();

  /**
   * Static function to convert the three rotation angles (in radians) to
   * rotation matrix
   * @param[in] rotationAngles Three Euler angles in radians
   */
  static Eigen::Matrix<DataType, 3, 3>
  CreateRotationMatrixFromEluerAnglesInRadians(
      const Eigen::Matrix<DataType, 3, 1> &rotationAngles);

  /**
   * Static function to convert the three rotation angles (in degrees) to
   * rotation matrix
   * @param[in] rotationAngles Three Euler angles in degrees
   */
  static Eigen::Matrix<DataType, 3, 3>
  CreateRotationMatrixFromEulerAnglesInDegrees(
      const Eigen::Matrix<DataType, 3, 1> &rotationAngles);

  /**
   * Static function to convert the 3 x 3 rotation matrix to the three Euler
   * angles (in radians)
   * Note: This is the inverse process of
   * CreateRotationMatrixFromEluerAnglesInRadians
   * @param[in] rotationMatrix The 3 x 3 rotation matrix
   */
  static Eigen::Matrix<DataType, 3, 1>
  GetEulerAnglesInRadiansFromRotationMatrix(
      const Eigen::Matrix<DataType, 3, 3> &rotationMatrix);

  /**
   * Static function to convert the 3 x 3 rotation matrix to the three Euler
   * angles (in degrees)
   * @param[in] rotationAngles The 3 x 3 rotation matrix
   */
  static Eigen::Matrix<DataType, 3, 1>
  GetEulerAnglesInDegreesFromRotationMatrix(
      const Eigen::Matrix<DataType, 3, 3> &rotationMatrix);

private:
  /// Translation (X, Y, and Z coordinates)
  Point<DataType, 3> mTranslation;
  /// Rotation (Omega, Phi, and Kappa)
  /// Note: The default rotation angles are all in degrees.
  Point<DataType, 3> mRotation;
  /// The flag indicates if the rotation angles are in degrees or radians
  /// True: in degrees; False: in radians
  bool isInDegree = true;
};

} // namespace Core

#include "ExteriorOrientation.hpp"

#endif // CORE_EXTERIORORIENTATION_H
