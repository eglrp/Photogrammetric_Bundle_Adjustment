#include "InteriorOrientation.h"

namespace Core {
template <typename TDataType, int Size>
Eigen::Matrix<TDataType, 2, 1>
InteriorOrientation<TDataType, Size>::calculateDistortion(const TDataType x,
                                                          const TDataType y) {
  /**
   * The default distortion parameters includes:
   * 3 radial distortion parameters: k1, k2, and k3
   * 2 de-centric distortion parameters: p1, and p2
   * 2 affine distortion parameters: a1, and a2
   */
  // Compute distance from image point to principal point (xp, yp)
  TDataType dx = x - xyc[0];
  TDataType dy = y - xyc[1];
  TDataType dxy = dx * dy;
  TDataType dx2 = dx * dx;
  TDataType dy2 = dy * dy;
  TDataType r2 = dx2 + dy2;
  // Compute radial distortion
  TDataType k0 = distortionParameters[0];
  TDataType k1 = distortionParameters[1];
  TDataType k2 = distortionParameters[2];
  TDataType k3 = distortionParameters[3];
  TDataType radialDistortion = k0 + k1 * r2 + k2 * r2 * r2 + k3 * r2 * r2 * r2;
  TDataType radialDistortionX = dx * radialDistortion;
  TDataType radialDistortionY = dy * radialDistortion;
  // Compute de-centric distortion
  TDataType p1 = distortionParameters[4];
  TDataType p2 = distortionParameters[5];
  TDataType p3 = distortionParameters[6];
  TDataType decentricDistortion = static_cast<TDataType>(1) + p3 * r2;
  TDataType decentricDistortionX =
      decentricDistortion * (p1 * (r2 + 2 * dx2) + 2 * p2 * dxy);
  TDataType decentricDistortionY =
      decentricDistortion * (2 * p1 * dxy + p2 * (r2 + 2 * dy2));
  // Compute affine distortion
  TDataType a1 = distortionParameters[7];
  TDataType a2 = distortionParameters[8];
  TDataType affineDistortionX = -a1 * dx + a2 * dy;
  TDataType affineDistortionY = a1 * dy;

  Eigen::Matrix<TDataType, 2, 1> distortions;
  distortions[0] = radialDistortionX + decentricDistortionX + affineDistortionX;
  distortions[1] = radialDistortionY + decentricDistortionY + affineDistortionY;

  return distortions;
}

template <typename TDataType, int Size>
Eigen::Matrix<TDataType, 2, 1>
InteriorOrientation<TDataType, Size>::addDistortion(
    const TDataType x, const TDataType y, const TDataType tolerance,
    const unsigned int maxIteration) {
  TDataType xp = xyc[0];
  TDataType yp = xyc[1];
  TDataType xUpdated = x;
  TDataType yUpdated = y;
  unsigned int numberOfIterations = 0;
  // Keep adding distortions until it converges
  do {
    ++numberOfIterations;
    // Note: Since calculateDistortion function corrects principal offsets, we
    // have to add xp, yp to xUpdated and yUpdated.
    auto distortions = calculateDistortion(xUpdated + xp, yUpdated + yp);
    TDataType dx = x - (xUpdated - distortions[0]);
    TDataType dy = y - (yUpdated - distortions[1]);
    TDataType dist = sqrt(dx * dx + dy * dy);
    if (dist < tolerance) {
      break;
    }
    xUpdated = x + distortions[0];
    yUpdated = y + distortions[1];
  } while (numberOfIterations < maxIteration);
  if (numberOfIterations >= maxIteration) {
    throw std::runtime_error(
        "Cannot converge when adding distortion for the given image point!");
  }
  return Eigen::Matrix<TDataType, 2, 1>{xUpdated + xp, yUpdated + yp};
}

template <typename TDataType, int Size>
Eigen::Matrix<TDataType, 2, 1>
InteriorOrientation<TDataType, Size>::ConvertPixelToImageCoordinates(
    const TDataType row, const TDataType col) {
  TDataType x = (col - width * 0.5) * xPixelSize;
  TDataType y = (height * 0.5 - row) * yPixelSize;
  return Eigen::Matrix<TDataType, 2, 1>{x, y};
}

template <typename TDataType, int Size>
Eigen::Matrix<TDataType, 2, 1>
InteriorOrientation<TDataType, Size>::ConvertImageCoordinatesToPixel(
    const TDataType x, const TDataType y) {
  TDataType row = height * 0.5 - y / yPixelSize;
  TDataType col = x / xPixelSize + width * 0.5;
  return Eigen::Matrix<TDataType, 2, 1>(row, col);
}

} // namespace Core
