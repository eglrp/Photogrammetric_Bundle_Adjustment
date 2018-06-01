#include "RandomNumber.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(RandomNumber, GenerateRandomNumber) {
  // Prepare the 1st float random number generator
  Core::RandomFloatGenerator randomFloat1(0.f, 1.f);
  // Prepare the 2nd float random number generator
  Core::RandomFloatGenerator randomFloat2(0.f, 1.f);
  // The two random number generators are expected to output different numbers
  unsigned int numbers = 10;
  for (unsigned int i = 0; i < numbers; ++i) {
    double randomNumber1 = randomFloat1.getRandomNumber();
    double randomNumber2 = randomFloat2.getRandomNumber();
    std::cout << randomNumber1 << "\t" << randomNumber2 << std::endl;
    EXPECT_TRUE(randomNumber1 != randomNumber2);
  }
}
