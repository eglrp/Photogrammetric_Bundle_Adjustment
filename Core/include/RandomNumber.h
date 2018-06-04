#ifndef CORE_RANDOMNUMBER_H
#define CORE_RANDOMNUMBER_H

#include <time.h>

#include "boost/random.hpp"

namespace Core {
/**
 * This is a wrapper class of boost::random for generating random numbers with
 * different types of distributions
 */
template <typename TDistributionType> class RandomNumber {
public:
  using DataType = typename TDistributionType::result_type;

  /**
   * Constructor to initialize the random number generator for the range of
   * [minValue, maxValue)
   * Note: This constructor automatically use current clock time to seed the
   * random number generator.
   * @param[in] minValue Minimum value for the generated random numbers
   * @param[in] maxValue Maximum value for the generated random numbers
   */
  RandomNumber(const DataType minValue, const DataType maxValue);

  /// Get a random number from mRandomNumberGenerator
  DataType getRandomNumber();

private:
  boost::random::mt19937 mGenerator;
  boost::random::variate_generator<boost::mt19937 &, TDistributionType>
      mRandomNumberGenerator;
};
// Double random number generator with uniform distribution
using RandomFloatGenerator = RandomNumber<boost::uniform_real<double>>;
// Float random number generator with uniform distribution
using RandomDoubleGenerator = RandomNumber<boost::uniform_real<float>>;
// Integer random number generator with uniform distribution
using RandomIntegerGenerator =
    RandomNumber<boost::random::uniform_int_distribution<int>>;
} // namespace Core

#include "RandomNumber.hpp"

#endif // CORE_RANDOMNUMBER_H
