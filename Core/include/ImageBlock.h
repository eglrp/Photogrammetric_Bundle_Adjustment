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
  /// Get pointer to the camera with the given cameraId
  std::shared_ptr<CameraType> getCamera(const std::string &cameraId);

  /// Add an image to current image block
  bool addImage(const std::string &imageId,
                const std::shared_ptr<ImageType> &image);
  /// Get pointer to the image with the given imageId
  std::shared_ptr<ImageType> getImage(const std::string &imageId);

  /// Add an object point to current image block
  bool addObjectPoint(const std::string &pointId,
                      const std::shared_ptr<ObjectPointType> &point);
  /// Return a mutable copy of object point with the given pointId
  /// Note: Returning a mutable copy instead of a pointer can be easier to
  /// access the object coordinates.
  ObjectPointType &getObjectPoint(const std::string &pointId);

  /// Add a GNSS/INS measurements with timestamp to current image block
  bool addNavigationData(
      const unsigned int timestamp,
      const std::shared_ptr<ExteriorOrientation<DataType>> &navigation);
  /// Get pointer to a GNSS/INS measurement with the given timestamp
  std::shared_ptr<ExteriorOrientation<DataType>>
  getNavigationMeasurement(const unsigned int timestamp);

  /// Get the number of the utilized cameras
  unsigned int getNumberOfCameras() const;
  /// Get the number of the involved images
  unsigned int getNumberOfImages() const;
  /// Get the number of object points
  unsigned int getNumberOfObjectPoints() const;
  /// Get the number of navigation measurements
  unsigned int getNumberOfNavigationMeasurements() const;

private:
  /// Collection of the utilized cameras
  std::unordered_map<std::string, std::shared_ptr<CameraType>> mCameras;
  /// Collection of the involved images
  std::unordered_map<std::string, std::shared_ptr<ImageType>> mImages;
  /// Collection of the object points
  std::unordered_map<std::string, std::shared_ptr<ObjectPointType>>
      mObjectPoints;
  /// Collection of the navigation data (i.e., GNSS/INS measurements)
  std::unordered_map<unsigned int,
                     std::shared_ptr<ExteriorOrientation<DataType>>>
      mNavigationData;
};
} // namespace Core

#include "ImageBlock.hpp"

#endif // CORE_IMAGEBLOCK_H
