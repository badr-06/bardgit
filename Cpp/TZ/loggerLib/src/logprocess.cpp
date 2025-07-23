#include "logprocess.h"

void logProcessor::process() {
  while (running) {
    std::unique_lock<std::mutex> lock(QueueMutex);

    queueCV.wait(lock, [this] { return !logQueue.empty() || !running; });

    while (!logQueue.empty()) {
      std::pair<Level, std::string> current = logQueue.front();
      logQueue.pop();

      lock.unlock();

      log.logs(current.first, current.second);

      lock.lock();
    }
  }
}

void logProcessor::add(Level level, const std::string& message) {
  std::lock_guard<std::mutex> lock(std::mutex);
  logQueue.emplace(level, message);
  queueCV.notify_one();
}

int logProcessor::check(const std::string& str, int& i) {
  while (str[i] != '\0') {
    if (isdigit(str[i])) {
      return 1;
    }
    if (str[i] != ' ' && str[i] != '\n') {
      return 2;
    }
    i++;
  }

  return 0;
}

std::queue<std::pair<Level, std::string>>* logProcessor::getlogQueue() {
  return &logQueue;
}
