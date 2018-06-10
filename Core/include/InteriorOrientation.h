#ifndef CORE_INTERIORORIENTATION_H
#define CORE_INTERIORORIENTATION_H

#include "Point.h"

namespace Core {
/**
 * This is the class for Interior Orientation Parameters (IOPs) of the utilized
 * frame camera
 * TDataType: data type of iops
 * Size: the number of distortion parameters associated with iops
 * default = 9:
 * 4 radial distortion parameters: k1, k2, and k3
 * 3 de-centric distortion parameters: p1, and p2
 * 2 affine distortion parameters: a1, and a2
 */
template <typename TDataType = double, int Size = 9> class InteriorOrientation {
public:
  /// Default constructor
  InteriorOrientation() = default;

  /**
   * This function calculates distortion at a given image point.
   * Note: It can be overridden in the derived camera class.
   * @param[in] x x ccordinates of an image point
   * @param[in] y y coordinates of an image point
   * @return A 2 x 1 vector of image distortions
   */
  virtual Eigen::Matrix<TDataType, 2, 1> calculateDistortion(const TDataType x,
                                                             const TDataType y);

  /**
   * This function takes distortion-free coordinates of an image point, and
   * returns the same point after adding distortion and correcting principal
   * offset.
   * Note: It can be overridden in the derived camera class.
   * @param[in] x x ccordinates of a distortion-free image point
   * @param[in] y y coordinates of a distortion image point
   * @param[in] tolerance Tolerance to stop adding distortion (default = 1e-6)
   * @param[in] maxIteration Maximum number of iterations to add distortion
   * (default = 100)
   * @return A 2 x 1 vector of image coordinates after adding distortions and
   * principal offset
   */
  virtual Eigen::Matrix<TDataType, 2, 1>
  addDistortion(const TDataType x, const TDataType y,
                const TDataType tolerance = 1e-6,
                const unsigned int maxIteration = 100);

  /**
   * This function converts pixel location (i.e, row and col) to local image
   * coordinate system (origin is defined at image center; x is pointing to
   * right, and y is pointing up).
   */
  Eigen::Matrix<TDataType, 2, 1>
  ConvertPixelToImageCoordinates(const TDataType row, const TDataType col);

  /**
   * This function converts image coordinates to corresponding pixel location
   * (i.e., row and col)
   */
  Eigen::Matrix<TDataType, 2, 1>
  ConvertImageCoordinatesToPixel(const TDataType x, const TDataType y);

  /**
   * This function concatenates xp, yp, c and distortion parameters to a single
   * TDataType array, and returns the pointer of this array.
   */
  const TDataType *convertToArray();

  /// Width and Height of image
  unsigned int width;
  unsigned int height;
  /// Pixel size
  TDataType xPixelSize;
  TDataType yPixelSize;
  /// Principal offset and Pricipal distance (xp, yp, c)
  Point<TDataType, 3> xyc;
  /// Distortion parameters (Size x 1 vector)
  Point<TDataType, Size> distortionParameters;
};
} // namespace Core

#include "InteriorOrientation.hpp"

#endif // CORE_INTERIORORIENTATION_H
