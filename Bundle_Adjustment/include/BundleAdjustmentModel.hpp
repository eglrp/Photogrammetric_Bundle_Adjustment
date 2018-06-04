#include "BundleAdjustmentModel.h"

namespace BundleAdjustment {
template <typename TDataType, typename TImagePointType,
          typename TDistortionFunctorType>
void ComputeCollinearityReprojectionErrors(
    const TDataType *const cameraIOPs, const TDataType *const objectPoint,
    const TDataType *const bodyFrameEOPs,
    const TDataType *const refCameraToBodyFrameParams,
    const TDataType *const nonRefCameraToRefCameraParams,
    const TDataType *residuals, const TImagePointType &imagePoint,
    TDistortionFunctorType distortionModelFunctor) {}
} // namespace BundleAdjustment
