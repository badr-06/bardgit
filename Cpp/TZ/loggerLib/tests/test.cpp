#include <gtest/gtest.h>

#include <filesystem>

#include "../library/include/logger.h"
#include "../src/logprocess.h"

namespace fs = std::filesystem;

struct TempFile {
  std::string path;
  TempFile() : path("log_test.txt") {}
  ~TempFile() {
    if (fs::exists(path)) fs::remove(path);
  }
};

TEST(logger, logger_constructor1) {
  TempFile TF;

  logger log(TF.path);
  ASSERT_TRUE(fs::exists(TF.path));
  ASSERT_EQ(log.getLevelMessage(), INFO);
}

TEST(logger, logger_constructor2) {
  TempFile TF;

  logger log(TF.path, WARNING);
  ASSERT_TRUE(fs::exists(TF.path));
  ASSERT_EQ(log.getLevelMessage(), WARNING);
}

TEST(logger, logs) {
  TempFile TF;

  logger log(TF.path);
  std::string str = "Hello InfoTecs";
  log.logs(INFO, str);

  std::string time = log.getCurrentTime();
  time.pop_back();

  std::ifstream file(TF.path);
  std::string line;
  std::getline(file, line);

  std::string temp = "\"Hello InfoTecs\" [INFO] " + time;

  ASSERT_EQ(line, temp);
}

TEST(logger, setLevelMessage) {
  TempFile TF;
  logger log(TF.path);

  ASSERT_EQ(log.getLevelMessage(), INFO);
  log.setLevelMessage(ERROR);
  ASSERT_EQ(log.getLevelMessage(), ERROR);
}

TEST(logprocess, add_and_process) {
  TempFile TF;
  logger log(TF.path);
  logProcessor logPr(log);

  std::string str = "Hello InfoTecs";
  auto logQueue = logPr.getlogQueue();
  ASSERT_TRUE(logQueue->empty());

  logPr.add(INFO, str);

  ASSERT_EQ(str, logQueue->front().second);
  ASSERT_EQ(INFO, logQueue->front().first);
  ASSERT_FALSE(logQueue->empty());

  std::this_thread::sleep_for(std::chrono::seconds(1));

  ASSERT_TRUE(logQueue->empty());
}

TEST(logprocess, check_function) {
  TempFile TF;
  logger log(TF.path);
  logProcessor logPr(log);

  int i = 0;
  int temp = logPr.check("1 Hello InfoTecs", i);

  ASSERT_EQ(temp, 1);

  i = 0;
  temp = logPr.check("     Hello InfoTecs", i);

  ASSERT_EQ(temp, 2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}