#pragma once  // Защита от множественного включения заголовочного файла

// Стандартные библиотеки C++ для работы с временем, файлами, форматированием и строками
#include <ctime>       // Для работы со временем (time_t, tm, time())
#include <iostream>    // Для ввода/вывода ошибок и инструкции (не используется напрямую в заголовке)
#include <fstream>     // Для работы с файлами (ofstream)
#include <iomanip>     // Для форматированного вывода (put_time)
#include <string>      // Для работы со строками (std::string)

// Перечисление уровней логирования
typedef enum { INFO, WARNING, ERROR } Level; 

// Класс для логирования сообщений в файл
class logger {
 private:
  std::ofstream File;       // Поток для записи в файл
  Level LevelMessage;       // Текущий уровень логирования
  std::string TimeMessage;  // Время последнего сообщения

 public:
  // Конструктор:
  // pathFile - путь к файлу логов (по умолчанию "../../logs/log.txt")
  // level - уровень логирования (по умолчанию INFO)
  logger(const std::string& pathFile = "../../logs/log.txt",
         Level level = INFO);
  
  // Деструктор (закрывает файл)
  ~logger();

  // Запись сообщения в лог:
  // level - уровень важности сообщения
  // message - текст сообщения
  void logs(Level level, std::string& message);
  
  // Установка уровня логирования:
  // lm - новый уровень (INFO, WARNING, ERROR)
  void setLevelMessage(Level lm);
  
  // Получение текущего времени в формате строки
  std::string getCurrentTime();
  
  // Получение текущего уровня логирования
  Level getLevelMessage();
};