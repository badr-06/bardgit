#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

#include "HashDatbase.h"
#include "Logger.h"
#include "ThreadPool.h"

#define OPENSSL_API_COMPAT \
  10101  // Отключает предупреждения об устаревших функциях в OpenSSL 3.0+
#include <openssl/md5.h>  // Для вычисления MD5 хешей

namespace fs = std::filesystem;

// Структура для хранения статистики сканирования
struct InfoScan {
  std::atomic<int> totalNumberFile_{0};  // Общее количество файлов
  std::atomic<int> totalMaliciousFile_{0};  // Количество вредоносных файлов
  std::atomic<int> totalErrorFile_{0};  // Количество файлов с ошибками
};

// Класс для сканирования файловой системы и проверки файлов
class FileScan {
  std::string namePath_;  // Путь к директории для сканирования
  HashDatBase hashDataBase_;  // База данных хешей и вердиктов
  Logger logger_;  // Логгер для записи результатов
  InfoScan infoscan_;  // Статистика сканирования

 public:
  FileScan(){};  // Конструктор по умолчанию

  // Конструктор с параметрами
  FileScan(std::string np, std::string lf, std::string bf)
      : namePath_(np),      // Путь для сканирования
        hashDataBase_(bf),  // Файл базы данных хешей
        logger_(lf) {}      // Файл для логирования

  ~FileScan(){};  // Деструктор

  // Основной метод сканирования директории (многопоточный)
  const InfoScan& scanner();

  // Метод сканирования одного файла
  void scannerFile(const std::string& nameFile);

  // Вычисление MD5 хеша файла
  std::string md5_from_file(const std::string& filename);

  // Установка пути для сканирования
  void setPath(const std::string& path) { namePath_ = path; }

  // Получение статистики сканирования
  const InfoScan& getInfoScan() const { return infoscan_; }
};