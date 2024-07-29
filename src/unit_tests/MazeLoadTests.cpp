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

    std::vector<Line> expectedLines = {
        {0, 1, 500, 1},
        {1, 500, 1, 0},
        {499, 499, 0, 499},
        {499, 0, 499, 499},
        {0, 125, 125, 125},
        {250, 125, 375, 125},
        {125, 125, 125, 250},
        {375, 125, 375, 250},
        {250, 250, 375, 250},
        {0, 375, 125, 375},
        {250, 250, 250, 375},
        {125, 375, 250, 375},
        {375, 375, 500, 375}
    };

    // for(auto line : expectedLines){
    //     std::cout << "{" << line.begin.col << ", " << line.begin.row << ", " << line.end.col << ", " << line.end.row << "}," << std::endl;
    // }
    // std::cout << std::endl;

    // for(auto line : lines){
    //     std::cout << "{" << line.begin.col << ", " << line.begin.row << ", " << line.end.col << ", " << line.end.row << "}," << std::endl;
    // }

    EXPECT_EQ(lines.size(), expectedLines.size());
    EXPECT_EQ(lines, expectedLines);
}