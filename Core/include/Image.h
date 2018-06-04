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
template <typename TPointType, typename TDataType = double>
class Image : public ExteriorOrientation<TDataType>,
              public PointCloud<TPointType> {
public:
  /// Default constructor
  Image() = default;
  ~Image() = default;

  /// Accessor of mCameraId
  const std::string &cameraId() const;
  /// Accessor of image points
  const std::unordered_map<std::string, ImagePoint> &getImagePoints() const;

private:
  /// Id for the utilized camera
  std::string mCameraId;
  /// The optional image file path
  boost::optional<boost::filesystem::path> mImageFilePath = boost::none;
};
} // namespace Core

#include "Image.hpp"

#endif // CORE_IMAGE_H
