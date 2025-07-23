#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

#include "../library/include/logger.h"

class logProcessor {
  logger& log;
  std::queue<std::pair<Level, std::string>> logQueue;
  std::mutex QueueMutex;
  std::thread worker;
  std::condition_variable queueCV;
  std::atomic<bool> running{true};

 public:
  logProcessor(logger& l) : log(l), worker(&logProcessor::process, this) {}

  ~logProcessor() {
    running = false;
    queueCV.notify_all();
    worker.join();
  }

  void process();
  void add(Level level, const std::string& message);
  int check(const std::string& str, int& i);
  std::queue<std::pair<Level, std::string>>* getlogQueue();
};
