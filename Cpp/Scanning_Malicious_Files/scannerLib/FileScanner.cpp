#include "FileScanner.h"

// Основной метод сканирования директории
const InfoScan& FileScan::scanner() {
  // Создаем пул потоков по количеству ядер процессора
  ThreadPool pool(std::thread::hardware_concurrency());
  std::vector<std::future<void>> futures;

  // Рекурсивный обход всех файлов в директории
  for (auto& to : fs::recursive_directory_iterator(namePath_)) {
    if (fs::is_regular_file(to)) {
      infoscan_.totalNumberFile_++;  // Увеличиваем счетчик файлов

      // Добавляем задачу сканирования файла в пул потоков
      futures.push_back(pool.enqueue(
          [this, path = to.path()] { scannerFile(path.string()); }));
    }
  }

  // Ожидаем завершения всех задач
  for (auto& f : futures) {
    f.get();
  }

  return infoscan_;
}

// Метод сканирования одного файла
void FileScan::scannerFile(const std::string& nameFile) {
  std::string hash;
  // Вычисляем MD5 хеш файла
  if ((hash = md5_from_file(nameFile)) != "") {
    // Проверяем хеш в базе данных
    int flag = hashDataBase_.checkHashinBase(hash);
    if (!flag) {
      // Найден вредоносный файл
      infoscan_.totalMaliciousFile_++;
      // Записываем в лог информацию о вредоносном файле
      if (logger_.writeinLog(nameFile, hash)) {
        infoscan_.totalErrorFile_++;  // Ошибка записи в лог
      }
    } else if (flag == 2) {
      // Ошибка открытия базы данных
      infoscan_.totalErrorFile_++;
    }
  }
}

// Вычисление MD5 хеша файла
std::string FileScan::md5_from_file(const std::string& filename) {
  // открываем файл для чтения в бинароном режиме
  std::ifstream file(filename, std::ios::binary);

  if (!file.is_open()) {
    // Ошибка открытия файла
    std::cerr << "Cannot open file: " + filename +
                     " in function \"md5_from_file\""
              << std::endl;
    infoscan_.totalErrorFile_++;
  } else {
    // Инициализация контекста MD5
    MD5_CTX context;
    MD5_Init(&context);

    // Чтение файла блоками и обновление хеша
    char buffer[1024];
    while (file.read(buffer, sizeof(buffer)) || file.gcount()) {
      MD5_Update(&context, buffer, file.gcount());
    }

    // Финализация хеша
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_Final(digest, &context);

    // Преобразование бинарного хеша в hex-строку
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
      ss << std::setw(2) << (unsigned int)digest[i];
    }
    return ss.str();
  }

  return std::string();  // Возвращаем пустую строку при ошибке
}