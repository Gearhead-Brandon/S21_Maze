#include "../../App/Model/Maze/Maze.h"
#include "../Tests.h"

using namespace s21;

class MazeGenerateTests : public testing::Test {
 protected:
  Maze maze_;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(MazeGenerateTests, MazeGenerateTest) {
  // Act
  OpResult result = maze_.generate(5, 5);
  std::vector<Line> lines = std::move(maze_.get(500, 500));

  // Assert
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "");

  EXPECT_TRUE(lines.size() > 0);

  // Act
  result = maze_.load("generatedMazes/maze_0.txt");
  lines = std::move(maze_.get(500, 500));

  // Assert
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "");

  // Act
  result = maze_.generate(50, 50);
  lines = std::move(maze_.get(500, 500));

  // Assert
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "");

  EXPECT_TRUE(lines.size() > 0);

  // Act
  result = maze_.load("generatedMazes/maze_1.txt");
  lines = std::move(maze_.get(500, 500));

  // Assert
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "");
}

TEST_F(MazeGenerateTests, IncorrectMazeSize) {
  // Act
  OpResult result = maze_.generate(0, 5);
  std::vector<Line> lines = std::move(maze_.get(500, 500));

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect maze size");

  EXPECT_EQ(lines.size(), 0);

  // Act
  result = maze_.generate(5, 0);
  lines = std::move(maze_.get(500, 500));

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect maze size");

  EXPECT_EQ(lines.size(), 0);

  // Act
  result = maze_.generate(50, 0);
  lines = std::move(maze_.get(500, 500));

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect maze size");

  EXPECT_EQ(lines.size(), 0);

  // Act
  result = maze_.generate(0, 50);
  lines = std::move(maze_.get(500, 500));

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect maze size");

  EXPECT_EQ(lines.size(), 0);
}