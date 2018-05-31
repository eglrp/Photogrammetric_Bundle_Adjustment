#include "ExteriorOrientation.h"
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
const Point<DataType, 3> &
ExteriorOrientation<DataType>::getTranslation() const {
  return mTranslation;
}

template <typename DataType>
Point<DataType, 3> &ExteriorOrientation<DataType>::getTranslation() {
  return mTranslation;
}

template <typename DataType>
const Point<DataType, 3> &ExteriorOrientation<DataType>::getRotation() const {
  return mRotation;
}

template <typename DataType>
Point<DataType, 3> &ExteriorOrientation<DataType>::getRotation() {
  return mRotation;
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
void ExteriorOrientation<DataType>::ConvertRotationToDegrees(
    Eigen::Matrix<DataType, 3, 1> &rotation) {
  DataType conversionFactor = static_cast<DataType>(RadiansToDegree);
  rotation[0] = rotation[0] * conversionFactor;
  rotation[1] = rotation[1] * conversionFactor;
  rotation[2] = rotation[2] * conversionFactor;
}

template <typename DataType>
Eigen::Matrix<DataType, 3, 1>
ExteriorOrientation<DataType>::ConvertRotationToDegrees(
    const Eigen::Matrix<DataType, 3, 1> &rotation) {
  // Make a copy of rotation
  auto copyRotation = rotation;
  ConvertRotationToDegrees(copyRotation);
  return copyRotation;
}

template <typename DataType>
void ExteriorOrientation<DataType>::ConvertRotationToRadians(
    Eigen::Matrix<DataType, 3, 1> &rotation) {
  DataType conversionFactor = static_cast<DataType>(DegreeToRadians);
  rotation[0] = rotation[0] * conversionFactor;
  rotation[1] = rotation[1] * conversionFactor;
  rotation[2] = rotation[2] * conversionFactor;
}

template <typename DataType>
Eigen::Matrix<DataType, 3, 1>
ExteriorOrientation<DataType>::ConvertRotationToRadians(
    const Eigen::Matrix<DataType, 3, 1> &rotation) {
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

template <typename DataType>
Eigen::Matrix<DataType, 3, 3>
ExteriorOrientation<DataType>::CreateRotationMatrixFromEluerAnglesInRadians(
    const Eigen::Matrix<DataType, 3, 1> &rotationAngles) {
  // Note: This rotation matrix (i.e., R matrix) describes the rotation from the
  // camera to the mapping coordinate system.If the rotation from the mapping to
  // the camera (i.e., M matrix) is needed, the transpose of this matrix has to
  // be used.
  const DataType cosw = std::cos(rotationAngles[0]);
  const DataType sinw = std::sin(rotationAngles[0]);
  const DataType cosp = std::cos(rotationAngles[1]);
  const DataType sinp = std::sin(rotationAngles[1]);
  const DataType cosk = std::cos(rotationAngles[2]);
  const DataType sink = std::sin(rotationAngles[2]);

  Eigen::Matrix<DataType, 3, 3> rotationMatrix;

  // 1st row
  rotationMatrix(0, 0) = cosp * cosk;
  rotationMatrix(0, 1) = -cosp * sink;
  rotationMatrix(0, 2) = sinp;
  // 2nd row
  rotationMatrix(1, 0) = cosw * sink + sinw * sinp * cosk;
  rotationMatrix(1, 1) = cosw * cosk - sinw * sinp * sink;
  rotationMatrix(1, 2) = -sinw * cosp;
  // 3rd row
  rotationMatrix(2, 0) = sinw * sink - cosw * sinp * cosk;
  rotationMatrix(2, 1) = sinw * cosk + cosw * sinp * sink;
  rotationMatrix(2, 2) = cosw * cosp;

  return rotationMatrix;
}

template <typename DataType>
Eigen::Matrix<DataType, 3, 3>
ExteriorOrientation<DataType>::CreateRotationMatrixFromEulerAnglesInDegrees(
    const Eigen::Matrix<DataType, 3, 1> &rotationAngles) {
  Eigen::Matrix<DataType, 3, 1> anglesInRadians =
      rotationAngles * DegreeToRadians;
  return CreateRotationMatrixFromEluerAnglesInRadians(anglesInRadians);
}

template <typename DataType>
Eigen::Matrix<DataType, 3, 1>
ExteriorOrientation<DataType>::GetEulerAnglesInRadiansFromRotationMatrix(
    const Eigen::Matrix<DataType, 3, 3> &rotationMatrix) {
  // Note: phi has to be in the range of [-pi/2, pi/2].
  const DataType phi = std::asin(rotationMatrix(0, 2));
  // Compute cos(Phi)
  const DataType cosp = std::cos(phi);
  const DataType omega =
      std::atan2(-rotationMatrix(1, 2) / cosp, rotationMatrix(2, 2) / cosp);
  const DataType kappa =
      std::atan2(-rotationMatrix(0, 1) / cosp, rotationMatrix(0, 0) / cosp);

  return Eigen::Matrix<DataType, 3, 1>{omega, phi, kappa};
}

template <typename DataType>
Eigen::Matrix<DataType, 3, 1>
ExteriorOrientation<DataType>::GetEulerAnglesInDegreesFromRotationMatrix(
    const Eigen::Matrix<DataType, 3, 3> &rotationMatrix) {

  return GetEulerAnglesInRadiansFromRotationMatrix(rotationMatrix) *
         RadiansToDegree;
}

} // namespace Core
