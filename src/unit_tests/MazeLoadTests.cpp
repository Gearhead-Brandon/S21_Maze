#include "../App/Model/Maze/Maze.h"
#include "Tests.h"

using namespace s21;

class MazeLoadTests : public testing::Test {
protected:
  Maze maze_;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(MazeLoadTests, MazeLoadTest) {
    // Act
    OpResult result = maze_.load("test_files/test_maze_4_4.txt");
    std::vector<Line> lines = maze_.get(500, 500);

    // Assert
    EXPECT_TRUE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "");
    EXPECT_EQ(lines.size(), 13);
}