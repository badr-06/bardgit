#pragma once
#include <fstream>
#include <string>

// Класс для работы с базой данных хешей
class HashDatBase {
  std::string baseFile;  // Путь к файлу базы данных хешей

 public:
  HashDatBase(){};  // Конструктор по умолчанию
  HashDatBase(std::string nb)
      : baseFile(nb) {}  // Конструктор с параметром пути
  ~HashDatBase(){};      // Деструктор

  // Проверяет наличие хеша в базе данных
  // Возвращает: 0 - найден, 1 - не найден, 2 - ошибка файла
  // Модифицирует параметр hash, добавляя вердикт при нахождении
  int checkHashinBase(std::string& hash);

  // Устанавливает путь к файлу базы данных
  void setPath(std::string str) { baseFile = str; }

  // Возвращает путь к файлу базы данных
  const std::string getPath() const { return baseFile; }
};