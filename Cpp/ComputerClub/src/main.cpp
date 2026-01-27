#include <algorithm>

#include "../library/lib.h"

auto isValidTime(std::string time) -> int {
  if (time.size() != 5) {
    return 1;
  } else if (!isdigit(time[0]) || !isdigit(time[1]) || time[2] != ':' ||
             !isdigit(time[3]) || !isdigit(time[4])) {
    return 1;
  }

  int hours = std::stoi(time.substr(0, 2));
  int minutes = std::stoi(time.substr(3));

  if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
    return 1;
  }

  return 0;
}

auto isValidName(std::string name) -> int {
  return std::all_of(name.begin(), name.end(), [](char to) {
    return isdigit(to) || islower(to) || to == '_' || to == '-';
  });
}

auto isValidRow(std::string time, int id, std::string name, int number,
                int maxNumber) -> int {
  return isValidTime(time) || !(id >= 1 && id <= 4) || !isValidName(name) ||
         !(number >= 0 && number <= maxNumber);
}

void run(std::ifstream& file) {
  int n;
  file >> n;

  std::string begin, end;
  file >> begin >> end;

  int cost;
  file >> cost;

  computerClub club(n, cost, begin, end);

  std::string time;
  int id;
  std::string name;
  int number;

  std::cout << begin << std::endl;  // начало рабочего дня

  while (file >> time >> id >> name) {
    std::cout << time << ' ' << id << ' ' << name;

    if (id == 2) {
      file >> number;
      std::cout << ' ' << number << std::endl;
    } else
      std::cout << std::endl;

    if (isValidRow(time, id, name, number, n)) exit(1);

    switch (id) {
      case 1:
        club.clientArrived(time, name);
        break;
      case 2:
        club.clientSatDown(time, name, number);
        break;
      case 3:
        club.clientExpecting(time, name);
        break;
      case 4:
        club.clientLeaves(time, id, name);
        break;
      default:
        break;
    }
  }

  club.kickingAllClients();

  std::cout << end << std::endl;  // конец рабочего дня

  club.printRevenu();
}

int main(int argc, char** argv) {
  std::string filename = argv[argc - 1];

  std::ifstream file(filename);
  if (!file) {
    std::cerr << "ERROR: when opening a file " << filename << std::endl;
    exit(1);
  }

  run(file);

  file.close();

  return 0;
}