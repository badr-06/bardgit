#pragma once  // Защита от множественного включения заголовочного файла

// Стандартные библиотеки для многопоточной работы
#include <atomic>              // Для атомарных операций (std::atomic)
#include <condition_variable>  // Для условных переменных (синхронизация потоков)
#include <mutex>              // Для мьютексов (защита доступа к общим данным)
#include <queue>              // Для очереди сообщений
#include <thread>             // Для работы с потоками

// Подключение класса логгера
#include "../library/include/logger.h"

// Класс для асинхронной обработки логов
class logProcessor {
  logger& log;  // Ссылка на объект логгера
  std::queue<std::pair<Level, std::string>> logQueue;  // Очередь сообщений
  std::mutex QueueMutex;  // Мьютекс для защиты доступа к очереди
  std::thread worker;     // Рабочий поток для обработки сообщений
  std::condition_variable queueCV;  // Условная переменная для синхронизации
  std::atomic<bool> running{true};  // Флаг работы потока (атомарный)

 public:
  // Конструктор:
  // l - ссылка на объект логгера
  // worker - создание потока, вызывающего метод process()
  logProcessor(logger& l) : log(l), worker(&logProcessor::process, this) {}

  // Деструктор:
  // Останавливает поток и дожидается его завершения
  ~logProcessor() {
    running = false;         // Сброс флага работы
    queueCV.notify_all();    // Уведомление всех ждущих потоков
    worker.join();           // Ожидание завершения рабочего потока
  }

  // Основной метод обработки сообщений (будет запущен в отдельном потоке)
  void process();

  // Добавление сообщения в очередь:
  // level - уровень важности сообщения
  // message - текст сообщения
  void add(Level level, const std::string& message);

  // Проверка сообщений (возвращает 1 если встреталась цифра, 0 еслипустая строка и 2 в остальных случаях):
  // str - строка для поиска
  // i - индекс совпадения (передается по ссылке)
  int check(const std::string& str, int& i);

  // Получение указателя на очередь сообщений
  std::queue<std::pair<Level, std::string>>* getlogQueue();
};