#include "../../App/Model/Cave/Cave.h"
#include "../Tests.h"

using namespace s21;

class CaveGenerationTests : public testing::Test {
 protected:
  Cave cave_;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(CaveGenerationTests, GenerationCave) {
  // Act
  OpResult result = cave_.generate(5, 5, 50);
  std::vector<Rect> field = cave_.get(500, 500);

  // Assert
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "");

  EXPECT_TRUE(field.size() > 0);

  // Act
  result = cave_.generate(50, 50, 40);
  field = cave_.get(500, 500);

  // Assert
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "");

  EXPECT_TRUE(field.size() > 0);
}

TEST_F(CaveGenerationTests, IncorrectInitChance) {
  // Act
  OpResult result = cave_.generate(5, 5, 101);

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect init chance");

  // Act
  result = cave_.generate(5, 5, 0);

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect init chance");
}

TEST_F(CaveGenerationTests, IncorrectCaveSize) {
  // Act
  OpResult result = cave_.generate(0, 5, 50);

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect cave size");

  // Act
  result = cave_.generate(5, 0, 50);

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect cave size");

  // Act
  result = cave_.generate(51, 5, 0);

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect cave size");

  // Act
  result = cave_.generate(5, 51, 0);

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect cave size");
}