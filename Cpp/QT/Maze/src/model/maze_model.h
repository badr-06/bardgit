#ifndef MAZE_MODEL_H
#define MAZE_MODEL_H

#include <QString>
#include <vector>

struct Point {
  int y;
  int x;
};

class MazeModel {
 public:
  static constexpr int kMaxSize = 50;

  int rows() const { return rows_; }
  int columns() const { return columns_; }

  const std::vector<std::vector<int>>& verticalWalls() const { return matrix1_; }
  const std::vector<std::vector<int>>& horizontalWalls() const { return matrix2_; }
  const std::vector<std::vector<int>>& solution() const { return matrix3_; }

  void init();
  bool loadFromFile(const QString& filename);
  bool saveToFile(const QString& filename) const;
  void generate(int rows, int columns);
  bool solve(int y1, int x1, int y2, int x2);
  void clearSolution();

 private:
  int rows_ = 0;
  int columns_ = 0;
  std::vector<std::vector<int>> matrix1_;
  std::vector<std::vector<int>> matrix2_;
  std::vector<std::vector<int>> matrix3_;

  void resize(int rows, int columns);
  bool generationBool();
  void mergeSets(std::vector<int>& matrix, int a, int b);
  void checkLowerBounds(int i, std::vector<int>& matrix);
  bool dfs(std::vector<std::vector<bool>>& visit, Point current, Point end,
           std::vector<Point>& path);
};

#endif
