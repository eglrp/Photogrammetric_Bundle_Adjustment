#include "RandomNumber.h"

namespace Core {
template <typename TDistributionType>
RandomNumber<TDistributionType>::RandomNumber(const DataType minValue,
                                              const DataType maxValue)
    : mGenerator(clock()),
      mRandomNumberGenerator(
          boost::variate_generator<boost::mt19937 &, TDistributionType>(
              mGenerator, TDistributionType(minValue, maxValue))) {}

template <typename TDistributionType>
typename RandomNumber<TDistributionType>::DataType
RandomNumber<TDistributionType>::getRandomNumber() {
  return mRandomNumberGenerator();
}
} // namespace Core
