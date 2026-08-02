#ifndef CAVE_MODEL_H
#define CAVE_MODEL_H

#include <QString>
#include <vector>

enum class CaveUpdateMode { Automatic, StepByStep };

class CaveModel {
 public:
  static constexpr int kMaxSize = 50;

  int rows() const { return rows_; }
  int columns() const { return columns_; }
  int birthLimit() const { return birth_limit_; }
  int deathLimit() const { return death_limit_; }
  int timeDelay() const { return time_delay_; }
  CaveUpdateMode updateMode() const { return update_mode_; }

  void setBirthLimit(int value) { birth_limit_ = value; }
  void setDeathLimit(int value) { death_limit_ = value; }
  void setTimeDelay(int value) { time_delay_ = value; }
  void setUpdateMode(CaveUpdateMode mode) { update_mode_ = mode; }

  const std::vector<std::vector<int>>& matrix() const { return matrix_; }

  void init();
  bool loadFromFile(const QString& filename);
  void generate(int rows, int columns);
  void updateState();

 private:
  int rows_ = 0;
  int columns_ = 0;
  std::vector<std::vector<int>> matrix_;
  int birth_limit_ = 4;
  int death_limit_ = 4;
  int time_delay_ = 100;
  CaveUpdateMode update_mode_ = CaveUpdateMode::Automatic;

  void resize(int rows, int columns);
  bool generationBool();
  int countNeighbors(int x, int y) const;
};

#endif
