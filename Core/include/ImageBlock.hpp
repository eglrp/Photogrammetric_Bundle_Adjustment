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
std::shared_ptr<CameraType>
ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::getCamera(
    const std::string &cameraId) {
  auto search = mCameras.find(cameraId);
  if (search != mCameras.end()) {
    return search->second;
  } else {
    throw std::invalid_argument(
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
std::shared_ptr<ImageType>
ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::getImage(
    const std::string &imageId) {
  auto search = mImages.find(imageId);
  if (search != mImages.end()) {
    return search->second;
  } else {
    throw std::invalid_argument(
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
    return true;
  }
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
ObjectPointType &
ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::getObjectPoint(
    const std::string &pointId) {
  auto search = mObjectPoints.find(pointId);
  if (search != mObjectPoints.end()) {
    return *(search->second);
  } else {
    throw std::invalid_argument(
        "Cannot find the given pointId in the image block!");
  }
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
bool ImageBlock<CameraType, ImageType, ObjectPointType, DataType>::
    addNavigationData(
        const unsigned int timestamp,
        const std::shared_ptr<ExteriorOrientation<DataType>> &navigation) {
  if (mNavigationData.count(timestamp) != 0) {
    return false;
  } else {
    mNavigationData[timestamp] = navigation;
    return true;
  }
}

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
std::shared_ptr<ExteriorOrientation<DataType>>
ImageBlock<CameraType, ImageType, ObjectPointType,
           DataType>::getNavigationMeasurement(const unsigned int timestamp) {
  auto search = mNavigationData.find(timestamp);
  if (search != mNavigationData.end()) {
    return search->second;
  } else {
    throw std::invalid_argument(
        "Cannot find the given timestamp in the image block!");
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

template <typename CameraType, typename ImageType, typename ObjectPointType,
          typename DataType>
unsigned int ImageBlock<CameraType, ImageType, ObjectPointType,
                        DataType>::getNumberOfNavigationMeasurements() const {
  return mNavigationData.size();
}

} // namespace Core
