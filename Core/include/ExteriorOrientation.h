#ifndef CORE_EXTERIORORIENTATION_H
#define CORE_EXTERIORORIENTATION_H

#include "tgmath.h"

#include "Point.h"

namespace Core {
/**
 * This is the class for image Exterior Orientation Parameters (EOPs) with
 * variance-covariance matrices
 */
template <typename TDataType = double> class ExteriorOrientation {
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
  void setTranslation(const TDataType tx, const TDataType ty,
                      const TDataType tz,
                      const Eigen::Matrix<TDataType, 3, 3> &var =
                          Eigen::Matrix<TDataType, 3, 3>::Identity(3, 3));

  /**
   * Set up rotation
   * @param[in] omega rotation angle around x-axis
   * @param[in] phi rotation angle around y-axis
   * @param[in] kappa rotation angle around z-axis
   * @param[in] var variance-covariance matrix of the three rotation angles
   * @param[in] inDegreeFlag flag used to indicate the rotation is in degrees or
   * radians (True: in degrees; False: in radians)
   */
  void setRotation(const TDataType omega, const TDataType phi,
                   const TDataType kappa, const bool inDegreeFlag = true,
                   const Eigen::Matrix<TDataType, 3, 3> &var =
                       Eigen::Matrix<TDataType, 3, 3>::Identity(3, 3));

  /// Get a const reference of translation
  const Point<TDataType, 3> &getTranslation() const;

  /**
   * Get a mutable copy of translation
   * Note: This function can be used only when you want to directly modify the
   * content in the translation vector
   */
  Point<TDataType, 3> &getTranslation();

  /// Get a const reference of rotation
  const Point<TDataType, 3> &getRotation() const;

  /**
   * Get a mutable copy of rotation
   * Note: This function can be used only when you want to directly modify the
   * content of rotation
   */
  Point<TDataType, 3> &getRotation();

  /// Get a copy of rotation in degrees
  Point<TDataType, 3> getRotationInDegrees() const;

  /// Get a copy of rotation in radians
  Point<TDataType, 3> getRotationInRadians() const;

  /**
   * This funtion transforms current ExteriorOrientation to another coordinate
   * system specified by @c transform.
   * Specifically, if current ExteriorOrientation defines the rotation and
   * translation from frame a to frame b (i.e., R_a_b and r_a_b), and the input
   * ExteriorOrientation @transform descrbies the transformation from frame b to
   * frame c (i.e., R_b_c and r_b_c), the derived ExteriorOrientation is the
   * rotation and translation from frame a to c (i.e., R_a_c and r_a_c).
   * R_a_c = R_b_c * R_a_c
   * r_a_c = r_b_c + R_b_c * r_a_b
   * @param[in] transform The coordinate system to be transformed to
   * @return ExteriorOrientation defined in the coordinate system specified by
   * @c transform
   */
  ExteriorOrientation<TDataType>
  transformTo(const ExteriorOrientation<TDataType> &transform);

  /// Static function to convert rotation angles to radians
  static void
      ConvertRotationToRadians(Eigen::Matrix<TDataType, 3, 1> &rotation);
  static Eigen::Matrix<TDataType, 3, 1>
  ConvertRotationToRadians(const Eigen::Matrix<TDataType, 3, 1> &rotation);

  /// Static function to convert rotation angles to degrees
  static void
      ConvertRotationToDegrees(Eigen::Matrix<TDataType, 3, 1> &rotation);
  static Eigen::Matrix<TDataType, 3, 1>
  ConvertRotationToDegrees(const Eigen::Matrix<TDataType, 3, 1> &rotation);

  /// Member function to convert rotation angles to radians
  bool convertRotationToRadians();

  /// Member function to convert rotation angles to degrees
  bool convertRotationToDegrees();

  /**
   * Static function to convert the three rotation angles (in radians) to
   * rotation matrix
   * @param[in] rotationAngles Three Euler angles in radians
   */
  static Eigen::Matrix<TDataType, 3, 3>
  CreateRotationMatrixFromEluerAnglesInRadians(
      const Eigen::Matrix<TDataType, 3, 1> &rotationAngles);

  /**
   * Static function to convert the three rotation angles (in degrees) to
   * rotation matrix
   * @param[in] rotationAngles Three Euler angles in degrees
   */
  static Eigen::Matrix<TDataType, 3, 3>
  CreateRotationMatrixFromEulerAnglesInDegrees(
      const Eigen::Matrix<TDataType, 3, 1> &rotationAngles);

  /**
   * Static function to convert the 3 x 3 rotation matrix to the three Euler
   * angles (in radians)
   * Note: This is the inverse process of
   * CreateRotationMatrixFromEluerAnglesInRadians
   * @param[in] rotationMatrix The 3 x 3 rotation matrix
   */
  static Eigen::Matrix<TDataType, 3, 1>
  GetEulerAnglesInRadiansFromRotationMatrix(
      const Eigen::Matrix<TDataType, 3, 3> &rotationMatrix);

  /**
   * Static function to convert the 3 x 3 rotation matrix to the three Euler
   * angles (in degrees)
   * @param[in] rotationAngles The 3 x 3 rotation matrix
   */
  static Eigen::Matrix<TDataType, 3, 1>
  GetEulerAnglesInDegreesFromRotationMatrix(
      const Eigen::Matrix<TDataType, 3, 3> &rotationMatrix);

private:
  /// Translation (X, Y, and Z coordinates)
  Point<TDataType, 3> mTranslation;
  /// Rotation (Omega, Phi, and Kappa)
  /// Note: The default rotation angles are all in degrees.
  Point<TDataType, 3> mRotation;
  /// The flag indicates if the rotation angles are in degrees or radians
  /// True: in degrees; False: in radians
  bool isInDegree = true;
};

} // namespace Core

#include "ExteriorOrientation.hpp"

#endif // CORE_EXTERIORORIENTATION_H
