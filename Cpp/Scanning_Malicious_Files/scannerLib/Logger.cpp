#include "Logger.h"

#include <iostream>

// Метод для записи информации в лог-файл
bool Logger::writeinLog(std::string pathtoFile, std::string hash) {
  // Блокировка мьютекса для потокобезопасной записи
  std::lock_guard<std::mutex> lock(log_mutex);

  // Открытие файла в режиме добавления (append)
  std::ofstream file(logFile, std::ios::out);
  if (!file.is_open()) {
    // Ошибка открытия файла лога
    std::cerr << "Cannot open file: " + logFile + " in function \"writeinLog\""
              << std::endl;
    return 1;  // Возвращает true при ошибке
  }

  // Запись в формате: [путь_к_файлу] [хеш]
  file << pathtoFile + " " + hash + '\n';

  return 0;  // Возвращает false при успешной записи
}