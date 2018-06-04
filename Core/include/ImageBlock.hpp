#include "ImageBlock.h"

namespace Core {
template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
bool ImageBlock<TCameraType, TImageType, TObjectPointType,
                TDataType>::addCamera(const std::string &cameraId,
                                      const std::shared_ptr<TCameraType>
                                          &camera) {
  if (mCameras.count(cameraId) != 0) {
    return false;
  } else {
    mCameras[cameraId] = camera;
    return true;
  }
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
std::shared_ptr<TCameraType>
ImageBlock<TCameraType, TImageType, TObjectPointType, TDataType>::getCamera(
    const std::string &cameraId) {
  auto search = mCameras.find(cameraId);
  if (search != mCameras.end()) {
    return search->second;
  } else {
    throw std::invalid_argument(
        "Cannot find the given cameraId in the image block!");
  }
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
bool ImageBlock<TCameraType, TImageType, TObjectPointType, TDataType>::addImage(
    const std::string &imageId, const std::shared_ptr<TImageType> &image) {
  if (mImages.count(imageId) != 0) {
    return false;
  }
  mImages[imageId] = image;
  return true;
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
std::shared_ptr<TImageType>
ImageBlock<TCameraType, TImageType, TObjectPointType, TDataType>::getImage(
    const std::string &imageId) {
  auto search = mImages.find(imageId);
  if (search != mImages.end()) {
    return search->second;
  } else {
    throw std::invalid_argument(
        "Cannot find the given imageId in the image block!");
  }
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
bool ImageBlock<TCameraType, TImageType, TObjectPointType, TDataType>::
    addObjectPoint(const std::string &pointId,
                   const std::shared_ptr<TObjectPointType> &point) {
  if (mObjectPoints.count(pointId) != 0) {
    return false;
  } else {
    mObjectPoints[pointId] = point;
    return true;
  }
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
TObjectPointType &
ImageBlock<TCameraType, TImageType, TObjectPointType,
           TDataType>::getObjectPoint(const std::string &pointId) {
  auto search = mObjectPoints.find(pointId);
  if (search != mObjectPoints.end()) {
    return *(search->second);
  } else {
    throw std::invalid_argument(
        "Cannot find the given pointId in the image block!");
  }
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
bool ImageBlock<TCameraType, TImageType, TObjectPointType, TDataType>::
    addNavigationData(
        const unsigned int timestamp,
        const std::shared_ptr<ExteriorOrientation<TDataType>> &navigation) {
  if (mNavigationData.count(timestamp) != 0) {
    return false;
  } else {
    mNavigationData[timestamp] = navigation;
    return true;
  }
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
std::shared_ptr<ExteriorOrientation<TDataType>>
ImageBlock<TCameraType, TImageType, TObjectPointType,
           TDataType>::getNavigationMeasurement(const unsigned int timestamp) {
  auto search = mNavigationData.find(timestamp);
  if (search != mNavigationData.end()) {
    return search->second;
  } else {
    throw std::invalid_argument(
        "Cannot find the given timestamp in the image block!");
  }
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
unsigned int ImageBlock<TCameraType, TImageType, TObjectPointType,
                        TDataType>::getNumberOfCameras() const {
  return mCameras.size();
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
unsigned int ImageBlock<TCameraType, TImageType, TObjectPointType,
                        TDataType>::getNumberOfImages() const {
  return mImages.size();
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
unsigned int ImageBlock<TCameraType, TImageType, TObjectPointType,
                        TDataType>::getNumberOfObjectPoints() const {
  return mObjectPoints.size();
}

template <typename TCameraType, typename TImageType, typename TObjectPointType,
          typename TDataType>
unsigned int ImageBlock<TCameraType, TImageType, TObjectPointType,
                        TDataType>::getNumberOfNavigationMeasurements() const {
  return mNavigationData.size();
}

} // namespace Core
