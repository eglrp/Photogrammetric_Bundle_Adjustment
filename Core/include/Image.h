#ifndef CORE_IMAGE_H
#define CORE_IMAGE_H

#include <unordered_map>

#include "boost/filesystem.hpp"

#include "ExteriorOrientation.h"
#include "PointCloud.h"

namespace Core {
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

private:
  /// Id for the utilized camera
  std::string mCameraId;
  /// Exterior Orientation Parameters
  ExteriorOrientation<DataType> mEOPs;
  /// The optional image file path
  boost::optional<boost::filesystem::path> mImageFilePath = boost::none;
};
} // namespace Core

#include "Image.hpp"

#endif // CORE_IMAGE_H
