#include "../include/logger.h"  // Подключение заголовочного файла класса logger
#include <stdexcept>            // Для обработки исключений (не используется в текущей реализации)

// Конструктор класса logger
// pathFile - путь к файлу для логирования
// level - минимальный уровень логирования (по умолчанию INFO)
logger::logger(const std::string& pathFile, Level level) {
  // Открытие файла в режиме добавления (append)
  File.open(pathFile, std::ios::out | std::ios::app);
  
  // Проверка успешности открытия файла
  if (!File.is_open()) {
    std::cerr << "Error open to file: " << pathFile << std::endl;
    exit(1);  // Аварийное завершение при ошибке открытия файла
  }
  
  LevelMessage = level;  // Установка уровня логирования
}

// Деструктор класса logger
logger::~logger() {
  // Закрытие файла, если он открыт
  if (File.is_open()) {
    File.close();
  }
}

// Метод записи сообщения в лог
// level - уровень важности сообщения
// message - текст сообщения
void logger::logs(Level level, std::string& message) {
  // Пропуск сообщений с уровнем ниже установленного
  if (level < LevelMessage) return;

  // Запись сообщения в файл в кавычках
  File << '\"' + message + '\"';

  // Добавление метки уровня логирования
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

  // Добавление временной метки
  File << getCurrentTime();

  // Сброс буфера для немедленной записи в файл
  File << std::flush;
}

// Установка минимального уровня логирования
void logger::setLevelMessage(Level lm) { LevelMessage = lm; }

// Получение текущего времени в формате строки
std::string logger::getCurrentTime() {
  std::time_t currentTime = std::time(nullptr);  // Текущее системное время
  std::tm localTime;                             // Структура для локального времени

  // Преобразование в локальное время (потокобезопасная версия)
  localtime_r(&currentTime, &localTime);

  // Форматирование времени в строку
  std::stringstream buffer;
  buffer << std::put_time(&localTime, "%H:%M:%S\n");
  return buffer.str();
}

// Получение текущего уровня логирования
Level logger::getLevelMessage() { return LevelMessage; }