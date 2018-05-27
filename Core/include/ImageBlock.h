#ifndef CORE_IMAGEBLOCK_H
#define CORE_IMAGEBLOCK_H

#include <memory>
#include <unordered_map>

#include "Camera.h"
#include "Image.h"
#include "Point.h"

namespace Core {
template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType = double>
class ImageBlock {
public:
  /// Default constructor
  ImageBlock() = default;
  ~ImageBlock() = default;

  /// Add a camera to current image block
  bool addCamera(const std::string &cameraId,
                 const std::shared_ptr<CameraType> &camera);
  /// Get a mutable copy of camera with the given cameraId
  CameraType &getCamera(const std::string &cameraId);

  /// Add an image to current image block
  bool addImage(const std::string &imageId,
                const std::shared_ptr<ImageType> &image);
  /// Get a mutable copy of image with the given imageId
  ImageType &getImage(const std::string &imageId);

  /// Add an object point to current image block
  bool addObjectPoint(const std::string &pointId,
                      const std::shared_ptr<ObjectPointType> &point);
  /// Get a mutable copy of object point with the given pointId
  ObjectPointType &getObjectPoint(const std::string &pointId);

  /// Get the number of the utilized cameras
  unsigned int getNumberOfCameras() const;
  /// Get the number of the involved images
  unsigned int getNumberOfImages() const;
  /// Get the number of object points
  unsigned int getNumberOfObjectPoints() const;

private:
  /// Collection of the utilized cameras
  std::unordered_map<std::string, std::shared_ptr<CameraType>> mCameras;
  /// Collection of the involved images
  std::unordered_map<std::string, std::shared_ptr<ImageType>> mImages;
  /// Collection of the object points
  std::unordered_map<std::string, std::shared_ptr<ObjectPointType>>
      mObjectPoints;
  /// Collection of the navigation data (i.e., GNSS/INS measurements)
  std::unordered_map<unsigned int, ExteriorOrientation<DataType>>
      mNavigationData;
};
} // namespace Core

#include "ImageBlock.hpp"

#endif // CORE_IMAGEBLOCK_H
