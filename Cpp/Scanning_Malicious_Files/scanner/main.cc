#include <chrono>
#include <iostream>
#include <unordered_map>

#include "../scannerLib/FileScanner.h"

struct Args {
  std::string base;
  std::string log;
  std::string path;
};

void checkAgrs(Args& args) {
  if (args.base == "" || args.log == "" || args.path == "") {
    throw std::runtime_error{
        "Функция \"void checkAgrs(Args& args)\": Не переданы все аргументы\n"
        "Пример: scanner.exe --base <имя файла базы хешов> "
        "--log <имя файла для логирования> "
        "--path <имя директории>"};
  }
}

Args parser(int argc, char** argv) {
  Args result;
  std::unordered_map<std::string, std::string*> map{{"--base", &result.base},
                                                    {"--log", &result.log},
                                                    {"--path", &result.path}};

  for (int i = 0; i < argc; ++i) {
    const std::string key = argv[i];

    if (map.contains(key)) {
      if (i + 1 < argc && !map.contains(argv[i + 1])) {
        *map[key] = argv[i + 1];
        i++;
      } else {
        throw std::runtime_error{
            "Функция \"Args parser(int argc, char **argv)\": Опция " + key +
            " требует аргумент"};
      }
    }
  }

  checkAgrs(result);

  return result;
}

int main(int argc, char** argv) {
  auto start = std::chrono::high_resolution_clock::now();

  Args args;

  try {
    args = parser(argc, argv);
  } catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << std::endl;
    return 1;
  }

  FileScan fr(args.path, args.log, args.base);
  const InfoScan& info = fr.scanner();

  std::cout << "Total Number File: " << info.totalNumberFile_ << std::endl;
  std::cout << "Total Malicious File: " << info.totalMaliciousFile_
            << std::endl;
  std::cout << "Total Error File: " << info.totalErrorFile_ << std::endl;

  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> time = end - start;
  std::cout << "Total Running Time: " << time.count() << std::endl;

  return 0;
}