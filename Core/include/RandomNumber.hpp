#include "RandomNumber.h"

namespace Core {
template <typename DistributionType>
RandomNumber<DistributionType>::RandomNumber(const DataType minValue,
                                             const DataType maxValue)
    : mGenerator(clock()),
      mRandomNumberGenerator(
          boost::variate_generator<boost::mt19937 &, DistributionType>(
              mGenerator, DistributionType(minValue, maxValue))) {}

template <typename DistributionType>
typename RandomNumber<DistributionType>::DataType
RandomNumber<DistributionType>::getRandomNumber() {
  return mRandomNumberGenerator();
}
} // namespace Core
