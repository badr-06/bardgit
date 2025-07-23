#include "logprocess.h"

int main(int argc, char **argv) {
  logger log;  // Создаём логгер
  logProcessor processor(log);
  Level level = INFO;

  std::cout << "Введите сообщения (формат: 'уровень текст')\n"
            << "Уровни: 0=INFO, 1=WARNING, 2=ERROR\n"
            << "уровень важности сообщений по умолчанию " << level
            << ", чтобы изменить просто введите цифру уровня ↑ без текста\n"
            << "'exit' для выхода\n";

  while (true) {
    std::cout << "> ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "exit") break;

    std::string message = input;

    // Если первый символ - цифра уровня
    int idx = 0;
    if (processor.check(input, idx) == 1) {
      int levelNum = input[idx] - '0';
      if (levelNum >= 0 && levelNum <= 2) {
        idx += 1;
        if (processor.check(input, idx) == 2) {
          message = input.substr(idx);
          processor.add(static_cast<Level>(levelNum), message);
        } else {
          level = static_cast<Level>(levelNum);
          log.setLevelMessage(level);
          continue;  // меняем уровень по умолчанию и пропускаем цикл
        }
      } else {
        processor.add(level, input.substr(idx));
      }
    } else if (processor.check(input, (idx = 0)) == 2) {
      input.substr(idx);

      processor.add(level, message);
    }
  }

  return 0;
}