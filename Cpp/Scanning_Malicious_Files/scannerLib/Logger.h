#pragma once
#include <fstream>
#include <mutex>
#include <string>

// Класс для потокобезопасного логирования
class Logger {
  std::string logFile;  // Путь к файлу лога
  std::mutex log_mutex;  // Мьютекс для синхронизации доступа к файлу

 public:
  Logger() {}  // Конструктор по умолчанию
  Logger(std::string log)
      : logFile(log) {}  // Конструктор с указанием файла лога
  ~Logger(){};  // Деструктор

  // Записывает запись в лог-файл
  // Возвращает: false (0) - успех, true (1) - ошибка
  bool writeinLog(std::string pathtoFile, std::string hash);

  // Устанавливает путь к файлу лога
  void setPath(std::string str) { logFile = str; }

  // Возвращает путь к файлу лога
  const std::string getPath() const { return logFile; }
};