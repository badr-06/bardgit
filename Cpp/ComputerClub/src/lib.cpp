#include "../library/lib.h"

computerClub::computerClub(int number, int cost, std::string begin,
                           std::string end)
    : numberOfComputers_(number), numbAvailableComp_(number), costHour_(cost) {
  beginWorkDay_ = conversionToMinutes(begin);
  endWorkDay_ = conversionToMinutes(end);

  computers_.resize(numberOfComputers_);
}

auto computerClub::conversionToMinutes(std::string str) -> int {
  int hours = stoi(str.substr(0, 2));
  int minutes = stoi(str.substr(3, 4));

  return (hours * 60 + minutes);
}

auto computerClub::conversionToString(int minutes) -> std::string {
  int hours = minutes / 60;
  minutes %= 60;
  std::string strHours =
      hours < 10 ? ("0" + std::to_string(hours)) : std::to_string(hours);
  std::string strMinutes =
      minutes < 10 ? ("0" + std::to_string(minutes)) : std::to_string(minutes);

  return strHours + ":" + strMinutes;
}

auto computerClub::calculatingRevenue(int timeWhenStandUp, int timeWhenSatDown)
    -> int {
  timeWhenStandUp -= timeWhenSatDown;
  int revenue = timeWhenStandUp / 60 * costHour_;
  timeWhenStandUp %= 60;

  if (timeWhenStandUp != 0)
    revenue += costHour_;

  return revenue;
}

void computerClub::kickingAllClients() {
  std::string end = conversionToString(endWorkDay_);

  if (!expectedClients_.empty()) {
    for (auto to : expectedClients_) {
      std::cout << end << ' ' << 11 << ' ' << to << std::endl;
    }
    expectedClients_.clear();
  }

  if (!clients_.empty()) {
    for (auto to : clients_) {
      std::cout << end << ' ' << 11 << ' ' << to.first << std::endl;
      clientLeaves(end, 11, to.first);
    }
    clients_.clear();
  }
}

void computerClub::printRevenu() {
  for (size_t i = 0; i < computers_.size(); ++i) {
    std::string worked = conversionToString(computers_[i].worked);
    std::cout << i + 1 << ' ' << computers_[i].revenue_ << ' ' << worked
              << std::endl;
  }
}

auto computerClub::clientArrived(const std::string time,
                                 const std::string &name) -> int {
  if (beginWorkDay_ > conversionToMinutes(time) ||
      endWorkDay_ < conversionToMinutes(time)) {
    std::cerr << time << ' ' << 13 << ' ' << "NotOpenYet" << std::endl;
    return 1;
  } else if (clients_.contains(name)) {
    std::cerr << time << ' ' << 13 << ' ' << "YouShallNotPass" << std::endl;
    return 2;
  }

  clients_.emplace(name, infoClient{false, 0, 0});

  return 0;
}

auto computerClub::clientSatDown(std::string time, const std::string &name,
                                 const int number) -> int {
  if (computers_[number - 1].status_ == false ||
      computers_[number - 1].name_ == name) {
    std::cerr << time << ' ' << 13 << ' ' << "PlaceIsBusy" << std::endl;
    return 1;
  } else if (!clients_.contains(name)) {
    std::cerr << time << ' ' << 13 << ' ' << "ClientUnknown" << std::endl;
    return 2;
  }

  int minutes = conversionToMinutes(time);

  if (clients_[name].status_) {
    auto &infoComp = computers_[clients_[name].numberComputer_ - 1];
    // освободил компьютер
    infoComp.status_ = true;
    infoComp.name_ = "";
    infoComp.revenue_ +=
        calculatingRevenue(minutes, clients_[name].satDownComp);
    infoComp.worked += minutes - clients_[name].satDownComp;

    // сел за другим компьютером
    clients_[name].numberComputer_ = number;
    clients_[name].satDownComp = minutes;
    computers_[number - 1].status_ = false;
    computers_[number - 1].name_ = name;

  } else {
    clients_[name].status_ = true;
    clients_[name].numberComputer_ = number;
    clients_[name].satDownComp = minutes;
    computers_[number - 1].status_ = false;
    computers_[number - 1].name_ = name;
    if (numbAvailableComp_)
      --numbAvailableComp_;
  }

  return 0;
}

auto computerClub::clientExpecting(const std::string time,
                                   const std::string &name) -> int {
  if (numbAvailableComp_) {
    std::cerr << time << ' ' << 13 << ' ' << "ICanWaitNoLonger" << std::endl;
    return 1;
  } else if (expectedClients_.size() >= numberOfComputers_) {
    std::cerr << time << ' ' << 11 << ' ' << name << std::endl;
    return 2;
  }

  expectedClients_.emplace(name);

  return 0;
}

auto computerClub::clientLeaves(std::string time, const int id,
                                const std::string &name) -> int {
  if (!clients_.contains(name)) {
    std::cerr << time << ' ' << 13 << ' ' << "ClientUnknown" << std::endl;
    return 1;
  }

  if (clients_[name].status_) {
    int num = clients_[name].numberComputer_;
    int minutes = conversionToMinutes(time);

    computers_[num - 1].status_ = true;
    computers_[num - 1].name_ = "";
    computers_[num - 1].revenue_ +=
        calculatingRevenue(minutes, clients_[name].satDownComp);
    computers_[num - 1].worked += minutes - clients_[name].satDownComp;
    if (!expectedClients_.empty()) {
      std::string nameExpected = *expectedClients_.begin();
      std::cout << time << ' ' << 12 << ' ' << nameExpected << ' ' << num
                << std::endl;
      clientSatDown(time, nameExpected, num);
      expectedClients_.erase(expectedClients_.begin());
    } else
      ++numbAvailableComp_;
  }

  if (id != 11)
    clients_.erase(name);

  return 0;
}
