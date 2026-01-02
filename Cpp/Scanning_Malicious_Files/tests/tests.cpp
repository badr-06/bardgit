#include <gtest/gtest.h>

#include <filesystem>
#include <fstream>

#include "../scannerLib/FileScanner.h"

namespace fs = std::filesystem;

// Вспомогательная функция для создания файлов
void create_file(const std::string& path, const std::string& content) {
  std::ofstream(path) << content;
}

// Вспомогательная функция для создания тестовой базы
void create_test_base(const std::string& base_path) {
  std::ofstream base_file(base_path);
  if (base_file.is_open()) {
    base_file << "6cd3556deb0da54bca060b4c39479839;Malicious\n";
    base_file.close();
  }
}

// =============================
// Тест 1: проверка MD5
// =============================
TEST(FileScanTest, MD5Correct) {
  const std::string test_file = "test_file.txt";
  create_file(test_file, "Hello, world!");

  FileScan scanner;
  scanner.setPath(test_file);

  std::string hash = scanner.md5_from_file(test_file);

  EXPECT_EQ(hash, "6cd3556deb0da54bca060b4c39479839");  // MD5 "Hello, world!"

  fs::remove(test_file);
}

// =============================
// Тест 2: сканирование директории
// =============================
TEST(FileScanTest, ScanDirectoryCountsFiles) {
  const std::string test_dir = "test_dir";
  fs::create_directory(test_dir);
  create_file("test_dir/file1.txt", "abc");
  create_file("test_dir/file2.txt", "def");
  const std::string log_file = "report.log";
  const std::string base_file = "base.cvs";
  create_file(log_file, "");
  create_file(base_file, "");

  FileScan scanner(test_dir, log_file, base_file);

  const InfoScan& result = scanner.scanner();

  EXPECT_EQ(result.totalNumberFile_.load(), 2);

  fs::remove_all(test_dir);
  fs::remove(log_file);
  fs::remove(base_file);
}

// =============================
// Тест 3: обработка несуществующего файла
// =============================
TEST(FileScanTest, HandleNonExistingFile) {
  FileScan scanner;

  std::string hash = scanner.md5_from_file("non_existing_file.txt");

  EXPECT_TRUE(hash.empty());
  EXPECT_GT(scanner.getInfoScan().totalErrorFile_.load(), 0);
}

// =============================
// Тест 4: Проверка обнаружения malicious файлов
// =============================
TEST(FileScanTest, DetectMaliciousFiles) {
  const std::string test_dir = "test_detect";
  const std::string log_file = "detect.log";
  const std::string base_file = "detect_base.csv";

  fs::create_directory(test_dir);
  create_file(test_dir + "/malicious.txt",
              "Hello, world!");  // MD5: 6cd3556deb0da54bca060b4c39479839
  create_file(test_dir + "/clean.txt",
              "abc");  // MD5: 900150983cd24fb0d6963f7d28e17f72
  create_test_base(base_file);
  create_file(log_file, "");

  FileScan scanner(test_dir, log_file, base_file);
  const InfoScan& result = scanner.scanner();

  EXPECT_EQ(result.totalNumberFile_.load(), 2);
  EXPECT_EQ(result.totalMaliciousFile_.load(), 1);
  EXPECT_EQ(result.totalErrorFile_.load(), 0);

  // Проверяем содержимое лог-файла
  std::ifstream log(log_file);
  std::string log_content((std::istreambuf_iterator<char>(log)),
                          std::istreambuf_iterator<char>());
  EXPECT_TRUE(log_content.find("malicious.txt") != std::string::npos);
  EXPECT_TRUE(log_content.find("Malicious") != std::string::npos);

  fs::remove_all(test_dir);
  fs::remove(log_file);
  fs::remove(base_file);
}

// =============================
// Тест 5: Проверка многопоточного сканирования
// =============================
TEST(FileScanTest, MultiThreadedScanning) {
  const std::string test_dir = "test_mt";
  const std::string log_file = "mt.log";
  const std::string base_file = "mt_base.csv";

  fs::create_directory(test_dir);

  // Создаем много файлов для тестирования многопоточности
  for (int i = 0; i < 10; ++i) {
    create_file(test_dir + "/file" + std::to_string(i) + ".txt",
                "content" + std::to_string(i));
  }

  create_test_base(base_file);
  create_file(log_file, "");

  FileScan scanner(test_dir, log_file, base_file);
  const InfoScan& result = scanner.scanner();

  EXPECT_EQ(result.totalNumberFile_.load(), 10);

  fs::remove_all(test_dir);
  fs::remove(log_file);
  fs::remove(base_file);
}

// =============================
// Тест 7: Проверка с файлом без прав чтения
// =============================
TEST(FileScanTest, ErrorReading) {
  const std::string test_dir = "test_error";
  const std::string log_file = "error.log";
  const std::string base_file = "error_base.csv";

  fs::create_directory(test_dir);

  // Создаем файл без прав на чтение
  create_file(test_dir + "/no_access.txt", "test");
  fs::permissions(test_dir + "/no_access.txt", fs::perms::none,
                  fs::perm_options::replace);

  create_test_base(base_file);
  create_file(log_file, "");

  FileScan scanner(test_dir, log_file, base_file);
  const InfoScan& result = scanner.scanner();

  EXPECT_GT(result.totalErrorFile_.load(), 0);

  // Восстанавливаем права для очистки
  fs::permissions(test_dir + "/no_access.txt", fs::perms::owner_all,
                  fs::perm_options::replace);

  fs::remove_all(test_dir);
  fs::remove(log_file);
  fs::remove(base_file);
}

// // =============================
// // Тест 8: Проверка с файлом с правами на чтение
// // =============================
// TEST(FileScanTest, Reding) {
//     const std::string test_dir = "test_error";
//     const std::string log_file = "error.log";
//     const std::string base_file = "error_base.csv";

//     fs::create_directory(test_dir);

//     // Создаем файл без прав на чтение
//     create_file(test_dir + "/no_access.txt", "test");

//     create_test_base(base_file);
//     create_file(log_file, "");

//     FileScan scanner(test_dir, log_file, base_file);
//     const InfoScan& result = scanner.scanner();

//     EXPECT_GT(result.totalErrorFile_.load(), 1);

//     // Восстанавливаем права для очистки
//     fs::permissions(test_dir + "/no_access.txt",
//                    fs::perms::owner_all,
//                    fs::perm_options::replace);

//     fs::remove_all(test_dir);
//     fs::remove(log_file);
//     fs::remove(base_file);
// }

// =============================
// main для запуска тестов
// =============================
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
