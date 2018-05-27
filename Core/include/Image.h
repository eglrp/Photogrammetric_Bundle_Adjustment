#ifndef CORE_IMAGE_H
#define CORE_IMAGE_H

#include <unordered_map>

#include "boost/filesystem.hpp"

#include "Point.h"
#include "PointCloud.h"

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
                   const DataType kappa,
                   const Eigen::Matrix<DataType, 3, 3> &var =
                       Eigen::Matrix<DataType, 3, 3>::Identity(3, 3),
                   const bool inDegreeFlag = true);

  /// Get a copy of translation
  Point<DataType, 3> getTranslation() const;

  /// Get a copy of rotation in degrees
  Point<DataType, 3> getRotationInDegrees() const;

  /// Get a copy of rotation in radians
  Point<DataType, 3> getRotationInRadians() const;

  /// Static function to convert rotation angles to radians
  static void ConvertRotationToRadians(Point<DataType, 3> &rotation);
  static Point<DataType, 3>
  ConvertRotationToRadians(const Point<DataType, 3> &rotation);

  /// Static function to convert rotation angles to degrees
  static void ConvertRotationToDegrees(Point<DataType, 3> &rotation);
  static Point<DataType, 3>
  ConvertRotationToDegrees(const Point<DataType, 3> &rotation);

  /// Member function to convert rotation angles to radians
  bool convertRotationToRadians();

  /// Member function to convert rotation angles to degrees
  bool convertRotationToDegrees();

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

/**
 * This is the class for an image object with corresponding Exterior Orientation
 * Parameters (EOPs) and all detected image points
 */
template <typename PointType, typename DataType = double>
class Image : public PointCloud<PointType> {
public:
  /// Default constructor
  Image() = default;
  ~Image() = default;

  /// Accessor of mCameraId
  const std::string &cameraId() const;
  /// Accessor of mEOPs
  const ExteriorOrientation<DataType> &eop() const;
  /// Accessor of image points
  const std::unordered_map<std::string, ImagePoint> &getImagePoints() const;
  /// Accessor of time tag
  unsigned int getTimeTag() const;

private:
  /// Id for the utilized camera
  std::string mCameraId;
  /// Exterior Orientation Parameters
  ExteriorOrientation<DataType> mEOPs;
  /// The optional image file path
  boost::optional<boost::filesystem::path> mImageFilePath = boost::none;
  /// Time tag of the image
  unsigned int mTimeTag;
};
} // namespace Core

#include "Image.hpp"

#endif // CORE_IMAGE_H
