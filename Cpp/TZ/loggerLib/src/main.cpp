#include "logprocess.h"

int main(int argc, char **argv) {
  logger log;  // Создаём логгер
  logProcessor processor(log);  // Создаём процессор логов
  Level level = INFO;  // Устанавливаем уровень логирования по умолчанию

  // Выводим инструкции для пользователя
  std::cout << "Введите сообщения (формат: 'уровень текст')\n"
            << "Уровни: 0=INFO, 1=WARNING, 2=ERROR\n"
            << "уровень важности сообщений по умолчанию " << level
            << ", чтобы изменить просто введите цифру уровня ↑ без текста\n"
            << "'exit' для выхода\n";

  // Основной цикл обработки ввода пользователя
  while (true) {
    std::cout << "> ";  // Приглашение для ввода
    std::string input;
    std::getline(std::cin, input);  // Читаем ввод пользователя

    if (input == "exit") break;  // Выход из программы

    std::string message = input;  // Сообщение для логирования

    // Проверяем, начинается ли ввод с цифры (уровня логирования)
    int idx = 0;
    if (processor.check(input, idx) == 1) {  // Если первый символ - цифра
      int levelNum = input[idx] - '0';  // Преобразуем символ в число
      
      if (levelNum >= 0 && levelNum <= 2) {  // Проверяем допустимость уровня
        idx += 1;  // Переходим к следующему символу
        
        // Проверяем, есть ли текст после цифры
        if (processor.check(input, idx) == 2) {
          // Если есть текст - извлекаем его и добавляем в лог с указанным уровнем
          message = input.substr(idx);
          processor.add(static_cast<Level>(levelNum), message);
        } else {
          // Если текста нет - меняем уровень по умолчанию
          level = static_cast<Level>(levelNum);
          log.setLevelMessage(level);
          continue;  // Пропускаем цикл, так как сообщения нет
        }
      } else {
        // Если уровень недопустим - логируем всё сообщение с уровнем по умолчанию
        processor.add(level, input.substr(idx));
      }
    } 
    // Если ввод не начинается с цифры, но содержит текст
    else if (processor.check(input, (idx = 0)) == 2) {
      input.substr(idx);  // Извлекаем текст (избыточная операция)
      processor.add(level, message);  // Добавляем сообщение с уровнем по умолчанию
    }
  }

  return 0;
}