#include "logprocess.h"

// Основной метод обработки сообщений в отдельном потоке
void logProcessor::process() {
  while (running) {  // Работаем пока running == true
    std::unique_lock<std::mutex> lock(QueueMutex);  // Захватываем мьютекс

    // Ожидаем уведомления ИЛИ наличия сообщений в очереди ИЛИ остановки
    queueCV.wait(lock, [this] { return !logQueue.empty() || !running; });

    // Обрабатываем все сообщения в очереди
    while (!logQueue.empty()) {
      // Извлекаем сообщение из очереди
      std::pair<Level, std::string> current = logQueue.front();
      logQueue.pop();

      lock.unlock();  // Освобождаем мьютекс на время записи

      // Записываем сообщение в лог
      log.logs(current.first, current.second);

      lock.lock();  // Снова захватываем мьютекс для следующей итерации
    }
  }
}

// Добавление нового сообщения в очередь
void logProcessor::add(Level level, const std::string& message) {
  std::lock_guard<std::mutex> lock(QueueMutex);  // Захват мьютекса
  logQueue.emplace(level, message);             // Добавление сообщения
  queueCV.notify_one();                         // Уведомление рабочего потока
}

// Проверка строки на наличие цифр или недопустимых символов
int logProcessor::check(const std::string& str, int& i) {
  while (str[i] != '\0') {          // Пока не конец строки
    if (isdigit(str[i])) {          // Если цифра
      return 1;                     // Возвращаем код ошибки 1
    }
    if (str[i] != ' ' && str[i] != '\n') {  // Если не пробел и не перевод строки
      return 2;                     // Возвращаем код ошибки 2
    }
    i++;                            // Переход к следующему символу
  }

  return 0;                         // Нет ошибок
}

// Получение указателя на очередь сообщений
std::queue<std::pair<Level, std::string>>* logProcessor::getlogQueue() {
  return &logQueue;  // Возвращаем указатель на очередь
}