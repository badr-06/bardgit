#include "../include/logger.h"

#include <stdexcept>

logger::logger(const std::string& pathFile, Level level) {
  File.open(pathFile, std::ios::out | std::ios::app);
  if (!File.is_open()) {
    std::cerr << "Error open to file: " << pathFile << std::endl;
    exit(1);
  }
  LevelMessage = level;
}

logger::~logger() {
  if (File.is_open()) {
    File.close();
  }
}

void logger::logs(Level level, std::string& message) {
  if (level < LevelMessage) return;

  File << '\"' + message + '\"';

  switch (level) {
    case INFO:
      File << " [INFO] ";
      break;
    case WARNING:
      File << " [WARNING] ";
      break;
    case ERROR:
      File << " [ERROR] ";
      break;
  }

  File << getCurrentTime();

  File << std::flush;
}

void logger::setLevelMessage(Level lm) { LevelMessage = lm; }

std::string logger::getCurrentTime() {
  std::time_t currentTime = std::time(nullptr);
  std::tm localTime;

  localtime_r(&currentTime, &localTime);

  std::stringstream buffer;
  buffer << std::put_time(&localTime, "%H:%M:%S\n");
  return buffer.str();
}

Level logger::getLevelMessage() { return LevelMessage; }
