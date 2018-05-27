#include "ImageBlock.h"

namespace Core {
template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
bool ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::addCamera(
    const std::string &cameraId, const std::shared_ptr<CameraType> &camera) {
  if (mCameras.count(cameraId) != 0) {
    return false;
  } else {
    mCameras[cameraId] = camera;
    return true;
  }
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
std::shared_ptr<CameraType> &
ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::getCamera(
    const std::string &cameraId) {
  auto search = mCameras.find(cameraId);
  if (search != mCameras.end()) {
    return search->second;
  } else {
    throw std::runtime_error(
        "Cannot find the given cameraId in the image block!");
  }
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
bool ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::addImage(
    const std::string &imageId, const std::shared_ptr<ImageType> &image) {
  if (mImages.count(imageId) != 0) {
    return false;
  }
  mImages[imageId] = image;
  return true;
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
std::shared_ptr<ImageType> &
ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::getImage(
    const std::string &imageId) {
  auto search = mImages.find(imageId);
  if (search != mImages.end()) {
    return search->second;
  } else {
    throw std::runtime_error(
        "Cannot find the given imageId in the image block!");
  }
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
bool ImageBlock<CameraType, ImageType, ObjectPointType,
                DataType>::addObjectPoint(const std::string &pointId,
                                          const std::shared_ptr<ObjectPointType>
                                              &point) {
  if (mObjectPoints.count(pointId) != 0) {
    return false;
  } else {
    mObjectPoints[pointId] = point;
  }
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
std::shared_ptr<ObjectPointType> &
ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::getObjectPoint(
    const std::string &pointId) {
  auto search = mObjectPoints.find(pointId);
  if (search != mObjectPoints.end()) {
    return search->second;
  } else {
    throw std::runtime_error(
        "Cannot find the given pointId in the image block!");
  }
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
unsigned int ImageBlock<CameraType, ImageType, ObjectPointType,
                        DataType>::getNumberOfCameras() const {
  return mCameras.size();
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
unsigned int ImageBlock<CameraType, ImageType, ObjectPointType,
                        DataType>::getNumberOfImages() const {
  return mImages.size();
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
unsigned int ImageBlock<CameraType, ImageType, ObjectPointType,
                        DataType>::getNumberOfObjectPoints() const {
  return mObjectPoints.size();
}

} // namespace Core
