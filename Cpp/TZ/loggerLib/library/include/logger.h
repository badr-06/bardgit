#pragma once

#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

typedef enum { INFO, WARNING, ERROR } Level;

class logger {
 private:
  std::ofstream File;
  Level LevelMessage;
  std::string TimeMessage;

 public:
  logger(const std::string& pathFile = "../../logs/log.txt",
         Level level = INFO);
  ~logger();

  void logs(Level level, std::string& message);
  void setLevelMessage(Level lm);
  std::string getCurrentTime();
  Level getLevelMessage();
};
