#include "HashDatbase.h"

#include <iostream>

// Метод проверки наличия хеша в базе данных
int HashDatBase::checkHashinBase(std::string& hash) {
  std::ifstream file(baseFile, std::ios::in);  // Открываем файл базы для чтения

  if (!file.is_open()) {
    // Ошибка открытия файла базы
    std::cerr << "Cannot open file: " + baseFile +
                     " in function \"checkHashinBase\""
              << std::endl;
    return 2;  // Код ошибки: не удалось открыть файл
  } else {
    std::string hashBase;
    // Построчное чтение файла базы
    while (getline(file, hashBase)) {
      // Извлекаем вердикт (все что после 32-го символа)
      std::string verdict = hashBase.substr(33);
      // Оставляем только хеш (первые 32 символа)
      hashBase.erase(32);

      // Сравниваем хеш из базы с искомым хешем
      if (hashBase == hash) {
        file.clear();  // Сбрасываем флаги ошибок файла
        // Добавляем вердикт к исходному хешу
        hash += " " + verdict;
        return 0;  // Успех: хеш найден
      }
    }
  }
  return 1;  // Хеш не найден в базе
}