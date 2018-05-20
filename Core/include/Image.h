#ifndef CORE_IMAGE_H
#define CORE_IMAGE_H

#include <unordered_map>

#include "Point.h"

namespace Core {
/**
 * This is the class for Exterior Orientation Parameters (EOPs) with
 * variance-covariance matrices
 */
class ExteriorOrientation {
public:
  /// Translation (X, Y, and Z coordinates)
  Point<double, 3> position;
  /// Rotation (Omega, Phi, and Kappa)
  Point<double, 3> orientation;
};

/**
 * This is the class for an image object with corresponding Exterior Orientation
 * Parameters (EOPs) and all detected image points
 */
class Image {
public:
  Image() = default;
  ~Image() = default;

  /**
   * Given an image point, add it to mImagePoints
   * @return True: if point is added to mImagePoints; False: if there is already
   * a point with the same pointId in mImagePoints
   */
  bool addPoint(const Core::ImagePoint &point);

  /// Accessor of mEOPs
  const ExteriorOrientation &eop() const;
  /// Accessor of image points
  const std::unordered_map<std::string, Core::ImagePoint> &
  getImagePoints() const;

private:
  /// Image Id
  std::string &imageId;
  /// Exterior Orientation Parameters
  ExteriorOrientation mEOPs;
  /**
   * The set of image points are stored in an unodered_map
   * key: image pointId
   * value: image point coordinates with variance-covariance matrix
   */
  std::unordered_map<std::string, Core::ImagePoint> mImagePoints;
};
} // namespace Core

#endif // CORE_IMAGE_H
