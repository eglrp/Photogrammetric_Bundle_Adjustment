#include "Image.h"

namespace Core {

template <typename DataType>
void ExteriorOrientation<DataType>::SetTranslation(
    const DataType tx, const DataType ty, const DataType tz,
    const Eigen::Matrix<DataType, 3, 3> &var) {
  mTranslation =
      Point<DataType, 3>(Eigen::Matrix<DataType, 3, 1>{tx, ty, tz}, var);
}

template <typename DataType>
void ExteriorOrientation<DataType>::SetRotation(
    const DataType omega, const DataType phi, const DataType kappa,
    const bool inDegreeFlag, const Eigen::Matrix<DataType, 3, 3> &var) {
  isInDegree = inDegreeFlag;
  mRotation =
      Point<DataType, 3>(Eigen::Matrix<DataType, 3, 1>{omega, phi, kappa}, var);
}

template <typename DataType>
Point<DataType, 3> ExteriorOrientation<DataType>::getTranslation() const {
  return mTranslation;
}

template <typename DataType>
Point<DataType, 3> ExteriorOrientation<DataType>::getRotationInDegrees() const {
  if (isInDegree) {
    return mRotation;
  } else {
    return ConvertRotationToDegrees(mRotation);
  }
}

template <typename DataType>
Point<DataType, 3> ExteriorOrientation<DataType>::getRotationInRadians() const {
  if (isInDegree) {
    return ConvertRotationToRadians(mRotation);
  } else {
    return mRotation;
  }
}

template <typename DataType>
Point<DataType, 3> &ExteriorOrientation<DataType>::getMutableTranslation() {
  return mTranslation;
}

template <typename DataType>
Point<DataType, 3> &ExteriorOrientation<DataType>::getMutableRotation() {
  return mRotation;
}

template <typename DataType>
void ExteriorOrientation<DataType>::ConvertRotationToDegrees(
    Point<DataType, 3> &rotation) {
  DataType conversionFactor = static_cast<DataType>(RadiansToDegree);
  rotation[0] = rotation[0] * conversionFactor;
  rotation[1] = rotation[1] * conversionFactor;
  rotation[2] = rotation[2] * conversionFactor;
}

template <typename DataType>
Point<DataType, 3> ExteriorOrientation<DataType>::ConvertRotationToDegrees(
    const Point<DataType, 3> &rotation) {
  // Make a copy of rotation
  auto copyRotation = rotation;
  ConvertRotationToDegrees(copyRotation);
  return copyRotation;
}

template <typename DataType>
void ExteriorOrientation<DataType>::ConvertRotationToRadians(
    Point<DataType, 3> &rotation) {
  DataType conversionFactor = static_cast<DataType>(DegreeToRadians);
  rotation[0] = rotation[0] * conversionFactor;
  rotation[1] = rotation[1] * conversionFactor;
  rotation[2] = rotation[2] * conversionFactor;
}

template <typename DataType>
Point<DataType, 3> ExteriorOrientation<DataType>::ConvertRotationToRadians(
    const Point<DataType, 3> &rotation) {
  // Make a copy of rotation
  auto copyRotation = rotation;
  ConvertRotationToRadians(copyRotation);
  return copyRotation;
}

template <typename DataType>
bool ExteriorOrientation<DataType>::convertRotationToDegrees() {
  if (!isInDegree) {
    DataType conversionFactor = static_cast<DataType>(RadiansToDegree);
    mRotation[0] = mRotation[0] * conversionFactor;
    mRotation[1] = mRotation[1] * conversionFactor;
    mRotation[2] = mRotation[2] * conversionFactor;
    // Reset isInDegree flag
    isInDegree = false;
    return true;
  }
  return false;
}

template <typename DataType>
bool ExteriorOrientation<DataType>::convertRotationToRadians() {
  if (isInDegree) {
    DataType conversionFactor = static_cast<DataType>(DegreeToRadians);
    mRotation[0] = mRotation[0] * conversionFactor;
    mRotation[1] = mRotation[1] * conversionFactor;
    mRotation[2] = mRotation[2] * conversionFactor;
    // Reset isInDegree flag
    isInDegree = true;
    return true;
  }
  return false;
}

template <typename PointType, typename DataType>
const std::string &Image<PointType, DataType>::cameraId() const {
  return mCameraId;
}

template <typename PointType, typename DataType>
const ExteriorOrientation<DataType> &Image<PointType, DataType>::eop() const {
  return mEOPs;
}

template <typename PointType, typename DataType>
const std::unordered_map<std::string, ImagePoint> &
Image<PointType, DataType>::getImagePoints() const {
  return this->getPoints();
}

template <typename PointType, typename DataType>
unsigned int Image<PointType, DataType>::getTimeTag() const {
  return mTimeTag;
}

} // namespace Core
