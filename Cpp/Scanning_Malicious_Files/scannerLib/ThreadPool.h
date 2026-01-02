#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// Класс пула потоков для параллельного выполнения задач
class ThreadPool {
 public:
  // Конструктор: создает указанное количество потоков (по умолчанию - по
  // количеству ядер)
  ThreadPool(size_t threads = std::thread::hardware_concurrency())
      : stop_(false) {
    for (size_t i = 0; i < threads; ++i) {
      workers_.emplace_back([this] {
        while (true) {
          std::function<void()> task;

          // Блокировка и ожидание задач
          {
            std::unique_lock<std::mutex> lock(mutex_);
            // Ожидаем, пока не появятся задачи или не будет остановки
            cv_.wait(lock, [this] { return stop_ || !tasks_.empty(); });

            // Выход, если остановка и задачи закончились
            if (stop_ && tasks_.empty()) return;

            // Берем задачу из очереди
            task = std::move(tasks_.front());
            tasks_.pop();
          }

          // Выполняем задачу без блокировки мьютекса
          task();
        }
      });
    }
  }

  // Добавление задачи в очередь на выполнение
  template <class F, class... Args>
  auto enqueue(F&& f, Args&&... args)
      -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    // Создаем packaged_task для получения future
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();

    // Блокировка для добавления задачи в очередь
    {
      std::unique_lock<std::mutex> lock(mutex_);
      if (stop_) throw std::runtime_error("enqueue on stopped ThreadPool");
      tasks_.emplace([task]() { (*task)(); });  // Обертка для выполнения задачи
    }

    // Уведомляем один поток о новой задаче
    cv_.notify_one();
    return res;
  }

  // Деструктор: останавливает все потоки
  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> lock(mutex_);
      stop_ = true;  // Устанавливаем флаг остановки
    }
    cv_.notify_all();  // Уведомляем все потоки

    // Ожидаем завершения всех рабочих потоков
    for (std::thread& worker : workers_) worker.join();
  }

 private:
  std::vector<std::thread> workers_;  // Вектор рабочих потоков
  std::queue<std::function<void()>> tasks_;  // Очередь задач

  std::mutex mutex_;  // Мьютекс для синхронизации доступа к очереди
  std::condition_variable cv_;  // Условная переменная для ожидания задач
  std::atomic<bool> stop_;  // Атомарный флаг остановки пула
};