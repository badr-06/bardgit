#include <gtest/gtest.h>  // Google Test framework
#include <filesystem>     // Для работы с файловой системой

#include "../library/include/logger.h"  // Заголовок логгера
#include "../src/logprocess.h"          // Заголовок процессора логов

namespace fs = std::filesystem;  // Алиас для удобства

// Вспомогательная структура для временных файлов
struct TempFile {
  std::string path;
  TempFile() : path("log_test.txt") {}  // Конструктор создает путь к файлу
  ~TempFile() {  // Деструктор удаляет файл после использования
    if (fs::exists(path)) fs::remove(path);
  }
};

// Тест конструктора логгера с параметрами по умолчанию
TEST(logger, logger_constructor1) {
  TempFile TF;  // Создаем временный файл

  logger log(TF.path);  // Создаем логгер
  ASSERT_TRUE(fs::exists(TF.path));  // Проверяем создание файла
  ASSERT_EQ(log.getLevelMessage(), INFO);  // Проверяем уровень по умолчанию
}

// Тест конструктора логгера с указанием уровня
TEST(logger, logger_constructor2) {
  TempFile TF;

  logger log(TF.path, WARNING);  // Создаем логгер с уровнем WARNING
  ASSERT_TRUE(fs::exists(TF.path));
  ASSERT_EQ(log.getLevelMessage(), WARNING);  // Проверяем установленный уровень
}

// Тест записи сообщения в лог
TEST(logger, logs) {
  TempFile TF;
  logger log(TF.path);
  
  std::string str = "Hello InfoTecs";
  log.logs(INFO, str);  // Записываем тестовое сообщение

  std::string time = log.getCurrentTime();  // Получаем текущее время
  time.pop_back();  // Удаляем символ новой строки

  // Читаем записанное сообщение из файла
  std::ifstream file(TF.path);
  std::string line;
  std::getline(file, line);

  // Формируем ожидаемую строку для сравнения
  std::string temp = "\"Hello InfoTecs\" [INFO] " + time;

  ASSERT_EQ(line, temp);  // Проверяем корректность записи
}

// Тест изменения уровня логирования
TEST(logger, setLevelMessage) {
  TempFile TF;
  logger log(TF.path);

  ASSERT_EQ(log.getLevelMessage(), INFO);  // Проверяем уровень по умолчанию
  log.setLevelMessage(ERROR);  // Меняем уровень
  ASSERT_EQ(log.getLevelMessage(), ERROR);  // Проверяем изменение
}

// Тест добавления и обработки сообщений процессором
TEST(logprocess, add_and_process) {
  TempFile TF;
  logger log(TF.path);
  logProcessor logPr(log);  // Создаем процессор

  std::string str = "Hello InfoTecs";
  auto logQueue = logPr.getlogQueue();  // Получаем очередь
  ASSERT_TRUE(logQueue->empty());  // Проверяем, что очередь пуста

  logPr.add(INFO, str);  // Добавляем сообщение

  // Проверяем корректность добавления
  ASSERT_EQ(str, logQueue->front().second);
  ASSERT_EQ(INFO, logQueue->front().first);
  ASSERT_FALSE(logQueue->empty());

  // Даем время на обработку
  std::this_thread::sleep_for(std::chrono::seconds(1));

  ASSERT_TRUE(logQueue->empty());  // Проверяем, что сообщение обработано
}

// Тест функции проверки строки
TEST(logprocess, check_function) {
  TempFile TF;
  logger log(TF.path);
  logProcessor logPr(log);

  int i = 0;
  // Проверяем строку, начинающуюся с цифры
  int temp = logPr.check("1 Hello InfoTecs", i);
  ASSERT_EQ(temp, 1);  // Ожидаем код 1 (найдена цифра)

  i = 0;
  // Проверяем строку с недопустимыми символами
  temp = logPr.check("     Hello InfoTecs", i);
  ASSERT_EQ(temp, 2);  // Ожидаем код 2 (найдены недопустимые символы)
}

// Точка входа для тестов
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);  // Инициализация Google Test
  return RUN_ALL_TESTS();  // Запуск всех тестов
}