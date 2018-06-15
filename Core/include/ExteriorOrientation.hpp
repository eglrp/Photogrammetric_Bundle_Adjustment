#include "ExteriorOrientation.h"
namespace Core {
template <typename TDataType>
void ExteriorOrientation<TDataType>::setTranslation(
    const TDataType tx, const TDataType ty, const TDataType tz,
    const Eigen::Matrix<TDataType, 3, 3> &var) {
  mTranslation =
      Point<TDataType, 3>(Eigen::Matrix<TDataType, 3, 1>{tx, ty, tz}, var);
}

template <typename TDataType>
void ExteriorOrientation<TDataType>::setRotation(
    const TDataType omega, const TDataType phi, const TDataType kappa,
    const bool inDegreeFlag, const Eigen::Matrix<TDataType, 3, 3> &var) {
  isInDegree = inDegreeFlag;
  mRotation = Point<TDataType, 3>(
      Eigen::Matrix<TDataType, 3, 1>{omega, phi, kappa}, var);
}

template <typename TDataType>
const Point<TDataType, 3> &
ExteriorOrientation<TDataType>::getTranslation() const {
  return mTranslation;
}

template <typename TDataType>
Point<TDataType, 3> &ExteriorOrientation<TDataType>::getTranslation() {
  return mTranslation;
}

template <typename TDataType>
const Point<TDataType, 3> &ExteriorOrientation<TDataType>::getRotation() const {
  return mRotation;
}

template <typename TDataType>
Point<TDataType, 3> &ExteriorOrientation<TDataType>::getRotation() {
  return mRotation;
}

template <typename TDataType>
Point<TDataType, 3>
ExteriorOrientation<TDataType>::getRotationInDegrees() const {
  if (isInDegree) {
    return mRotation;
  } else {
    return ConvertRotationToDegrees(mRotation);
  }
}

template <typename TDataType>
Point<TDataType, 3>
ExteriorOrientation<TDataType>::getRotationInRadians() const {
  if (isInDegree) {
    return ConvertRotationToRadians(mRotation);
  } else {
    return mRotation;
  }
}

template <typename TDataType>
ExteriorOrientation<TDataType> ExteriorOrientation<TDataType>::transformTo(
    const ExteriorOrientation<TDataType> &transform) {
  // Compute rotation: R_a_c = R_b_c * R_a_b
  Eigen::Matrix<TDataType, 3, 3> R_a_b =
      CreateRotationMatrixFromEulerAnglesInDegrees(
          this->getRotationInDegrees());
  Eigen::Matrix<TDataType, 3, 3> R_b_c =
      CreateRotationMatrixFromEulerAnglesInDegrees(
          transform.getRotationInDegrees());
  Eigen::Matrix<TDataType, 3, 3> R_a_c = R_b_c * R_a_b;
  auto eulerAngles = GetEulerAnglesInDegreesFromRotationMatrix(R_a_c);

  // Compute translation: r_a_c = r_b_c + R_b_c * r_a_b
  Eigen::Matrix<TDataType, 3, 1> r_a_c =
      transform.getTranslation() + R_b_c * this->getTranslation();

  ExteriorOrientation<TDataType> newExteriorOrientation;
  newExteriorOrientation.setRotation(eulerAngles[0], eulerAngles[1],
                                     eulerAngles[2]);
  newExteriorOrientation.setTranslation(r_a_c[0], r_a_c[1], r_a_c[2]);
  return newExteriorOrientation;
}

template <typename TDataType>
void ExteriorOrientation<TDataType>::ConvertRotationToDegrees(
    Eigen::Matrix<TDataType, 3, 1> &rotation) {
  TDataType conversionFactor = static_cast<TDataType>(RadiansToDegree);
  rotation[0] = rotation[0] * conversionFactor;
  rotation[1] = rotation[1] * conversionFactor;
  rotation[2] = rotation[2] * conversionFactor;
}

template <typename TDataType>
Eigen::Matrix<TDataType, 3, 1>
ExteriorOrientation<TDataType>::ConvertRotationToDegrees(
    const Eigen::Matrix<TDataType, 3, 1> &rotation) {
  // Make a copy of rotation
  auto copyRotation = rotation;
  ConvertRotationToDegrees(copyRotation);
  return copyRotation;
}

template <typename TDataType>
void ExteriorOrientation<TDataType>::ConvertRotationToRadians(
    Eigen::Matrix<TDataType, 3, 1> &rotation) {
  TDataType conversionFactor = static_cast<TDataType>(DegreeToRadians);
  rotation[0] = rotation[0] * conversionFactor;
  rotation[1] = rotation[1] * conversionFactor;
  rotation[2] = rotation[2] * conversionFactor;
}

template <typename TDataType>
Eigen::Matrix<TDataType, 3, 1>
ExteriorOrientation<TDataType>::ConvertRotationToRadians(
    const Eigen::Matrix<TDataType, 3, 1> &rotation) {
  // Make a copy of rotation
  auto copyRotation = rotation;
  ConvertRotationToRadians(copyRotation);
  return copyRotation;
}

template <typename TDataType>
bool ExteriorOrientation<TDataType>::convertRotationToDegrees() {
  if (!isInDegree) {
    TDataType conversionFactor = static_cast<TDataType>(RadiansToDegree);
    mRotation[0] = mRotation[0] * conversionFactor;
    mRotation[1] = mRotation[1] * conversionFactor;
    mRotation[2] = mRotation[2] * conversionFactor;
    // Reset isInDegree flag
    isInDegree = false;
    return true;
  }
  return false;
}

template <typename TDataType>
bool ExteriorOrientation<TDataType>::convertRotationToRadians() {
  if (isInDegree) {
    TDataType conversionFactor = static_cast<TDataType>(DegreeToRadians);
    mRotation[0] = mRotation[0] * conversionFactor;
    mRotation[1] = mRotation[1] * conversionFactor;
    mRotation[2] = mRotation[2] * conversionFactor;
    // Reset isInDegree flag
    isInDegree = true;
    return true;
  }
  return false;
}

template <typename TDataType>
Eigen::Matrix<TDataType, 3, 3>
ExteriorOrientation<TDataType>::CreateRotationMatrixFromEluerAnglesInRadians(
    const Eigen::Matrix<TDataType, 3, 1> &rotationAngles) {
  // Note: This rotation matrix (i.e., R matrix) describes the rotation from the
  // camera to the mapping coordinate system.If the rotation from the mapping to
  // the camera (i.e., M matrix) is needed, the transpose of this matrix has to
  // be used.
  const TDataType cosw = std::cos(rotationAngles[0]);
  const TDataType sinw = std::sin(rotationAngles[0]);
  const TDataType cosp = std::cos(rotationAngles[1]);
  const TDataType sinp = std::sin(rotationAngles[1]);
  const TDataType cosk = std::cos(rotationAngles[2]);
  const TDataType sink = std::sin(rotationAngles[2]);

  Eigen::Matrix<TDataType, 3, 3> rotationMatrix;

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

template <typename TDataType>
Eigen::Matrix<TDataType, 3, 3>
ExteriorOrientation<TDataType>::CreateRotationMatrixFromEulerAnglesInDegrees(
    const Eigen::Matrix<TDataType, 3, 1> &rotationAngles) {
  Eigen::Matrix<TDataType, 3, 1> anglesInRadians =
      rotationAngles * DegreeToRadians;
  return CreateRotationMatrixFromEluerAnglesInRadians(anglesInRadians);
}

template <typename TDataType>
Eigen::Matrix<TDataType, 3, 1>
ExteriorOrientation<TDataType>::GetEulerAnglesInRadiansFromRotationMatrix(
    const Eigen::Matrix<TDataType, 3, 3> &rotationMatrix) {
  // Note: phi has to be in the range of [-pi/2, pi/2].
  const TDataType phi = std::asin(rotationMatrix(0, 2));
  // Compute cos(Phi)
  const TDataType cosp = std::cos(phi);
  const TDataType omega =
      std::atan2(-rotationMatrix(1, 2) / cosp, rotationMatrix(2, 2) / cosp);
  const TDataType kappa =
      std::atan2(-rotationMatrix(0, 1) / cosp, rotationMatrix(0, 0) / cosp);

  return Eigen::Matrix<TDataType, 3, 1>{omega, phi, kappa};
}

template <typename TDataType>
Eigen::Matrix<TDataType, 3, 1>
ExteriorOrientation<TDataType>::GetEulerAnglesInDegreesFromRotationMatrix(
    const Eigen::Matrix<TDataType, 3, 3> &rotationMatrix) {

  return GetEulerAnglesInRadiansFromRotationMatrix(rotationMatrix) *
         RadiansToDegree;
}

} // namespace Core
