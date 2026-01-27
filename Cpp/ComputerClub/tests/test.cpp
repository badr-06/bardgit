#include <gtest/gtest.h>

#include "../library/lib.h"

// проверка конструктора без аргументов
TEST(test_computer_club, constructor1) {
  computerClub club;

  EXPECT_EQ(club.getnumberOfComputers(), 0);
  EXPECT_EQ(club.getnumbAvailableComp(), 0);
  EXPECT_EQ(club.getcostHour(), 0);
  EXPECT_TRUE(club.getbeginWorkDay() == "00:00");
  EXPECT_TRUE(club.getendWorkDay() == "00:00");
  EXPECT_EQ(club.getclients_().empty(), 1);
  EXPECT_EQ(club.getcomputers_().empty(), 1);
  EXPECT_EQ(club.getexpectedClients_().empty(), 1);
}

// проверка конструктора с аргументами
TEST(test_computer_club, constructor2) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  EXPECT_EQ(club.getnumberOfComputers(), number);
  EXPECT_EQ(club.getnumbAvailableComp(), number);
  EXPECT_EQ(club.getcostHour(), cost);
  EXPECT_TRUE(club.getbeginWorkDay() == "09:00");
  EXPECT_TRUE(club.getendWorkDay() == "18:00");
  EXPECT_EQ(club.getclients_().empty(), 1);
  EXPECT_EQ(club.getexpectedClients_().empty(), 1);

  auto&& comp = club.getcomputers_();

  for (const auto& to : comp) {
    EXPECT_TRUE(to.name_.empty());
    EXPECT_EQ(to.revenue_, 0);
    EXPECT_EQ(to.status_, true);
    EXPECT_EQ(to.worked, 0);
  }
}

// проверка функции конвертации строки в минуты
TEST(test_computer_club, func_conversionToMinutes) {
  computerClub club;

  std::string time1 = "09:00";
  std::string time2 = "09:01";
  std::string time3 = "18:59";
  std::string time4 = "06:06";

  EXPECT_EQ(club.conversionToMinutes(time1), (9 * 60));
  EXPECT_EQ(club.conversionToMinutes(time2), (9 * 60 + 1));
  EXPECT_EQ(club.conversionToMinutes(time3), (18 * 60 + 59));
  EXPECT_EQ(club.conversionToMinutes(time4), (6 * 60 + 6));
}

// проверка функции конвертации минут в строку
TEST(test_computer_club, func_conversionToString) {
  computerClub club;

  std::string time1 = "09:00";
  std::string time2 = "09:01";
  std::string time3 = "18:59";
  std::string time4 = "06:06";

  int minutes1 = club.conversionToMinutes(time1);
  int minutes2 = club.conversionToMinutes(time2);
  int minutes3 = club.conversionToMinutes(time3);
  int minutes4 = club.conversionToMinutes(time4);

  EXPECT_TRUE(club.conversionToString(minutes1) == "09:00");
  EXPECT_TRUE(club.conversionToString(minutes2) == "09:01");
  EXPECT_TRUE(club.conversionToString(minutes3) == "18:59");
  EXPECT_TRUE(club.conversionToString(minutes4) == "06:06");
}

// проверка функции расчета выручки
TEST(test_computer_club, func_calculatingRevenue) {
  int cost = 10;  // стоимость за час

  computerClub club(10, cost, "09:00", "18:00");

  EXPECT_EQ(club.calculatingRevenue(club.conversionToMinutes("10:00"),
                                    club.conversionToMinutes("09:00")),
            10);
  EXPECT_EQ(club.calculatingRevenue(club.conversionToMinutes("10:01"),
                                    club.conversionToMinutes("09:00")),
            20);
  EXPECT_EQ(club.calculatingRevenue(club.conversionToMinutes("10:30"),
                                    club.conversionToMinutes("09:50")),
            10);
  EXPECT_EQ(club.calculatingRevenue(club.conversionToMinutes("18:00"),
                                    club.conversionToMinutes("09:50")),
            90);
}

// проверка когда клиент пришел в не рабочие часы
TEST(test_computer_club, func_clientArrived1) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time = "08:59";
  std::string name = "Client1";

  EXPECT_EQ(club.clientArrived(time, name), 1);
}

// проверка когда клиент пришел в не рабочие часы
TEST(test_computer_club, func_clientArrived2) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time = "18:01";
  std::string name = "Client1";

  EXPECT_EQ(club.clientArrived(time, name), 1);
}

// проверка когда клиент пришел
TEST(test_computer_club, func_clientArrived3) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time = "09:00";
  std::string name = "Client1";

  club.clientArrived(time, name);

  auto&& clients = club.getclients_();

  EXPECT_EQ(clients.empty(), 0);
  EXPECT_TRUE(clients.begin()->first == name);
  EXPECT_EQ(clients.at(name).numberComputer_, 0);
  EXPECT_EQ(clients.at(name).status_, false);
  EXPECT_EQ(clients.at(name).satDownComp, 0);
}

// проверка когда клиент пришед второй раз
TEST(test_computer_club, func_clientArrived4) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time1 = "09:00";
  std::string name1 = "Client1";

  club.clientArrived(time1, name1);

  std::string time2 = "09:10";
  std::string name2 = "Client1";

  EXPECT_EQ(club.clientArrived(time2, name2), 2);
}

// проверка когда пришли несколько клиентов
TEST(test_computer_club, func_clientArrived5) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time1 = "09:00";
  std::string name1 = "Client1";

  club.clientArrived(time1, name1);

  std::string time2 = "09:10";
  std::string name2 = "Client2";

  club.clientArrived(time2, name2);

  std::string time3 = "09:20";
  std::string name3 = "Client3";

  club.clientArrived(time3, name3);

  auto&& clients = club.getclients_();

  EXPECT_EQ(clients.size(), 3);
}

// клиент садится за столом
TEST(test_computer_club, func_clientSatDown1) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time = "09:00";
  std::string name1 = "Client1";
  int numberTable = 1;

  club.clientArrived(time, name1);

  EXPECT_EQ(club.clientSatDown(time, name1, numberTable), 0);

  auto&& clients = club.getclients_();
  auto&& computers = club.getcomputers_();
  const unsigned int& availableComp = club.getnumbAvailableComp();

  EXPECT_EQ(clients.at(name1).numberComputer_, 1);
  EXPECT_EQ(clients.at(name1).satDownComp, club.conversionToMinutes(time));
  EXPECT_EQ(clients.at(name1).status_, true);

  EXPECT_EQ(computers[numberTable - 1].name_, name1);
  EXPECT_EQ(computers[numberTable - 1].revenue_, 0);
  EXPECT_EQ(computers[numberTable - 1].status_, false);
  EXPECT_EQ(computers[numberTable - 1].worked, 0);

  EXPECT_EQ(availableComp, 9);
}

// проверка когда клиент пытается сесть за столом, за которым уже сидит
TEST(test_computer_club, func_clientSatDown2) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time = "09:00";
  std::string name1 = "Client1";
  int numberTable = 1;

  club.clientArrived(time, name1);

  club.clientSatDown(time, name1, numberTable);

  EXPECT_EQ(club.clientSatDown(time, name1, numberTable), 1);
}
// проверка когда клиент пытается сесть за столом который уже занят
TEST(test_computer_club, func_clientSatDown3) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time1 = "09:00";
  std::string name1 = "Client1";
  int numberTable = 1;

  club.clientArrived(time1, name1);

  club.clientSatDown(time1, name1, numberTable);

  std::string time2 = "09:10";
  std::string name2 = "Client2";

  club.clientArrived(time2, name2);

  EXPECT_EQ(club.clientSatDown(time2, name2, numberTable), 1);
}

// провека когда клиента нет в клубе
TEST(test_computer_club, func_clientSatDown4) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time1 = "09:00";
  std::string name1 = "Client1";
  int numberTable = 1;

  EXPECT_EQ(club.clientSatDown(time1, name1, numberTable), 2);
}

// проверка когда клиент персаживается на другой стол
TEST(test_computer_club, func_clientSatDown5) {
  int number = 10;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  std::string time1 = "09:00";
  std::string name1 = "Client1";
  int numberTable1 = 1;

  club.clientArrived(time1, name1);

  club.clientSatDown(time1, name1, numberTable1);

  auto&& clients = club.getclients_();
  auto&& computers = club.getcomputers_();
  int availableComp = club.getnumbAvailableComp();

  EXPECT_EQ(clients.at(name1).numberComputer_, 1);
  EXPECT_EQ(clients.at(name1).satDownComp, club.conversionToMinutes(time1));
  EXPECT_EQ(clients.at(name1).status_, true);

  EXPECT_EQ(computers[numberTable1 - 1].name_, name1);
  EXPECT_EQ(computers[numberTable1 - 1].revenue_, 0);
  EXPECT_EQ(computers[numberTable1 - 1].status_, false);
  EXPECT_EQ(computers[numberTable1 - 1].worked, 0);

  EXPECT_EQ(availableComp, 9);

  std::string time2 = "10:00";
  int numberTable2 = 2;

  club.clientSatDown(time2, name1, numberTable2);

  EXPECT_EQ(clients.at(name1).numberComputer_, 2);
  EXPECT_EQ(clients.at(name1).satDownComp, club.conversionToMinutes(time2));
  EXPECT_EQ(clients.at(name1).status_, true);

  int minutes1 = club.conversionToMinutes(time1);
  int minutes2 = club.conversionToMinutes(time2);

  EXPECT_EQ(computers[numberTable1 - 1].name_, "");
  EXPECT_EQ(computers[numberTable1 - 1].revenue_,
            club.calculatingRevenue(minutes2, minutes1));
  EXPECT_EQ(computers[numberTable1 - 1].status_, true);
  EXPECT_EQ(computers[numberTable1 - 1].worked, minutes2 - minutes1);

  EXPECT_EQ(computers[numberTable2 - 1].name_, name1);
  EXPECT_EQ(computers[numberTable2 - 1].revenue_, 0);
  EXPECT_EQ(computers[numberTable2 - 1].status_, false);
  EXPECT_EQ(computers[numberTable2 - 1].worked, 0);

  EXPECT_EQ(availableComp, 9);
}

// проврка когда несколько клиентов садятся за компьютером
TEST(test_computer_club, func_clientSatDown6) {
  int number = 3;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  // 1 клиент
  std::string time1 = "09:00";
  std::string name1 = "Client1";
  int numberTable1 = 1;

  club.clientArrived(time1, name1);

  club.clientSatDown(time1, name1, numberTable1);

  auto&& clients = club.getclients_();
  auto&& computers = club.getcomputers_();
  const unsigned int& availableComp = club.getnumbAvailableComp();

  EXPECT_EQ(clients.at(name1).numberComputer_, numberTable1);
  EXPECT_EQ(clients.at(name1).satDownComp, club.conversionToMinutes(time1));
  EXPECT_EQ(clients.at(name1).status_, true);

  EXPECT_EQ(computers[numberTable1 - 1].name_, name1);
  EXPECT_EQ(computers[numberTable1 - 1].revenue_, 0);
  EXPECT_EQ(computers[numberTable1 - 1].status_, false);
  EXPECT_EQ(computers[numberTable1 - 1].worked, 0);

  EXPECT_EQ(availableComp, 2);

  // 2 клиент
  std::string time2 = "09:00";
  std::string name2 = "Client2";
  int numberTable2 = 2;

  club.clientArrived(time2, name2);

  club.clientSatDown(time2, name2, numberTable2);

  EXPECT_EQ(clients.at(name2).numberComputer_, numberTable2);
  EXPECT_EQ(clients.at(name2).satDownComp, club.conversionToMinutes(time2));
  EXPECT_EQ(clients.at(name2).status_, true);

  EXPECT_EQ(computers[numberTable2 - 1].name_, name2);
  EXPECT_EQ(computers[numberTable2 - 1].revenue_, 0);
  EXPECT_EQ(computers[numberTable2 - 1].status_, false);
  EXPECT_EQ(computers[numberTable2 - 1].worked, 0);

  EXPECT_EQ(availableComp, 1);

  // 3 клиент
  std::string time3 = "09:00";
  std::string name3 = "Client3";
  int numberTable3 = 3;

  club.clientArrived(time3, name3);

  club.clientSatDown(time3, name3, numberTable3);

  EXPECT_EQ(clients.at(name3).numberComputer_, numberTable3);
  EXPECT_EQ(clients.at(name3).satDownComp, club.conversionToMinutes(time3));
  EXPECT_EQ(clients.at(name3).status_, true);

  EXPECT_TRUE(computers[numberTable3 - 1].name_ == name3);
  EXPECT_EQ(computers[numberTable3 - 1].revenue_, 0);
  EXPECT_EQ(computers[numberTable3 - 1].status_, false);
  EXPECT_EQ(computers[numberTable3 - 1].worked, 0);

  EXPECT_EQ(availableComp, 0);
}

// проверка когда клиент стоит в ожидании, и есть свободные комьютеры
TEST(test_computer_club, func_clientExpecting1) {
  int number = 3;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  // 1 клиент
  std::string time1 = "09:00";
  std::string name1 = "Client1";

  club.clientArrived(time1, name1);

  EXPECT_EQ(club.clientExpecting(time1, name1), 1);
}

// клиент становится в ожидании
TEST(test_computer_club, func_clientExpecting2) {
  int number = 2;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  EXPECT_EQ(club.getnumbAvailableComp(), 2);

  // 1 клиент
  std::string time1 = "09:00";
  std::string name1 = "Client1";

  club.clientArrived(time1, name1);
  club.clientSatDown(time1, name1, 1);

  EXPECT_EQ(club.getnumbAvailableComp(), 1);

  // 2 клиент
  std::string time2 = "09:10";
  std::string name2 = "Client2";

  club.clientArrived(time2, name2);
  club.clientSatDown(time2, name2, 2);

  EXPECT_EQ(club.getnumbAvailableComp(), 0);

  // 3 клиент
  std::string time3 = "09:20";
  std::string name3 = "Client3";

  EXPECT_EQ(club.clientExpecting(time3, name3), 0);

  auto&& expectedclients = club.getexpectedClients_();

  EXPECT_EQ(expectedclients.size(), 1);
}

// проверка когда ожидающих клиентов больше чем количество компьютеров
TEST(test_computer_club, func_clientExpecting3) {
  int number = 2;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  EXPECT_EQ(club.getnumbAvailableComp(), 2);

  // 1 клиент
  std::string time1 = "09:00";
  std::string name1 = "Client1";

  club.clientArrived(time1, name1);
  club.clientSatDown(time1, name1, 1);

  EXPECT_EQ(club.getnumbAvailableComp(), 1);

  // 2 клиент
  std::string time2 = "09:10";
  std::string name2 = "Client2";

  club.clientArrived(time2, name2);
  club.clientSatDown(time2, name2, 2);

  EXPECT_EQ(club.getnumbAvailableComp(), 0);

  auto&& expectedclients = club.getexpectedClients_();

  // 3 клиент
  std::string time3 = "09:20";
  std::string name3 = "Client3";

  club.clientArrived(time3, name3);
  EXPECT_EQ(club.clientExpecting(time3, name3), 0);

  EXPECT_EQ(expectedclients.size(), 1);

  // 4 клиент
  std::string time4 = "09:30";
  std::string name4 = "Client4";

  club.clientArrived(time4, name4);
  EXPECT_EQ(club.clientExpecting(time4, name4), 0);

  EXPECT_EQ(expectedclients.size(), 2);

  // 5 клиент
  std::string time5 = "09:34";
  std::string name5 = "Client5";

  club.clientArrived(time5, name5);
  EXPECT_EQ(club.clientExpecting(time5, name5), 2);

  EXPECT_EQ(expectedclients.size(), 2);
}

// проверка когда уходит клиент которого нет в клубе
TEST(test_computer_club, func_clientLeaves1) {
  int number = 2;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  // 1 клиент
  std::string time = "09:00";
  std::string name = "Client1";

  EXPECT_EQ(club.clientLeaves(time, 4, name), 1);
}

// проверка клиент пришел и сразу уходит
TEST(test_computer_club, func_clientLeaves2) {
  int number = 2;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  auto&& clients = club.getclients_();

  // 1 клиент
  std::string time = "09:00";
  std::string name = "Client1";

  club.clientArrived(time, name);

  EXPECT_EQ(clients.size(), 1);

  EXPECT_EQ(club.clientLeaves(time, 4, name), 0);

  EXPECT_EQ(clients.size(), 0);
}

// проверка клиент пришел садится за стол а потом уходит
TEST(test_computer_club, func_clientLeaves3) {
  int number = 2;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  auto&& clients = club.getclients_();
  auto&& computers = club.getcomputers_();
  const unsigned& availableComp = club.getnumbAvailableComp();

  // 1 клиент
  std::string time = "09:00";
  std::string name = "Client1";
  int numberTable = 1;

  club.clientArrived(time, name);

  EXPECT_EQ(clients.size(), 1);

  club.clientSatDown("09:10", name, numberTable);

  EXPECT_EQ(availableComp, 1);
  EXPECT_EQ(clients.contains(name), true);
  EXPECT_TRUE(computers[numberTable - 1].name_ == name);
  EXPECT_EQ(computers[numberTable - 1].status_, false);
  EXPECT_EQ(computers[numberTable - 1].revenue_, 0);
  EXPECT_EQ(computers[numberTable - 1].worked, 0);

  club.clientLeaves("11:50", 4, name);

  int whenSatDown = club.conversionToMinutes(time);
  int whenStandUp = club.conversionToMinutes("11:50");

  EXPECT_EQ(clients.size(), 0);
  EXPECT_EQ(availableComp, 2);
  EXPECT_EQ(clients.contains(name), false);
  EXPECT_TRUE(computers[numberTable - 1].name_ == "");
  EXPECT_EQ(computers[numberTable - 1].status_, true);
  EXPECT_EQ(computers[numberTable - 1].revenue_,
            club.calculatingRevenue(whenStandUp, whenSatDown));
  EXPECT_TRUE(club.conversionToString(computers[numberTable - 1].worked) ==
              "02:40");
}

// проверка когда уходит клиент и садится клиент который стоит в ожидании
TEST(test_computer_club, func_clientLeaves4) {
  int number = 2;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  auto&& expectedclients = club.getexpectedClients_();
  auto&& computers = club.getcomputers_();
  auto&& clients = club.getclients_();
  const unsigned int& avialableComp = club.getnumbAvailableComp();

  // 1 клиент
  std::string time1 = "09:00";
  std::string name1 = "Client1";
  int numberTable1 = 1;

  club.clientArrived(time1, name1);
  club.clientSatDown(time1, name1, numberTable1);

  EXPECT_EQ(avialableComp, 1);

  // 2 клиент
  std::string time2 = "09:20";
  std::string name2 = "Client2";
  int numberTable2 = 2;

  club.clientArrived(time2, name2);
  club.clientSatDown(time2, name2, numberTable2);

  EXPECT_EQ(avialableComp, 0);

  // 3 клиент
  std::string time3 = "09:30";
  std::string name3 = "Client3";

  club.clientArrived(time3, name3);
  club.clientExpecting(time3, name3);

  EXPECT_EQ(expectedclients.size(), 1);

  // Уходит 2 клиент и садится на его место 3 клиент
  EXPECT_EQ(club.clientLeaves("10:00", 4, name2), 0);

  EXPECT_EQ(avialableComp, 0);

  EXPECT_EQ(expectedclients.size(), 0);

  EXPECT_EQ(computers[numberTable2 - 1].name_, name3);
  EXPECT_EQ(computers[numberTable2 - 1].status_, false);
  EXPECT_EQ(computers[numberTable2 - 1].revenue_, 30);
  EXPECT_EQ(club.conversionToString(computers[numberTable2 - 1].worked),
            "00:40");

  EXPECT_EQ(clients.at(name3).numberComputer_, numberTable2);
  EXPECT_EQ(clients.at(name3).status_, true);
  EXPECT_EQ(club.conversionToString(clients.at(name3).satDownComp), "10:00");
}

// проверка когда клуб закрывается и все клиенты уходят
TEST(test_computer_club, func_kickingAllClients) {
  int number = 3;
  std::string begin = "09:00";
  std::string end = "18:00";
  int cost = 30;

  computerClub club(number, cost, begin, end);

  auto&& clients = club.getclients_();
  auto&& expectedClients = club.getexpectedClients_();
  auto&& computers = club.getcomputers_();

  // 1 клиент
  std::string time1 = "09:00";
  std::string name1 = "Client1";
  int numberTable1 = 1;

  club.clientArrived(time1, name1);
  club.clientSatDown(time1, name1, numberTable1);

  // 2 клиент
  std::string time2 = "09:00";
  std::string name2 = "Client2";
  int numberTable2 = 2;

  club.clientArrived(time2, name2);
  club.clientSatDown(time2, name2, numberTable2);

  // 3 клиент
  std::string time3 = "09:00";
  std::string name3 = "Client3";
  int numberTable3 = 3;

  club.clientArrived(time3, name3);
  club.clientSatDown(time3, name3, numberTable3);

  // 4 клиент
  std::string time4 = "09:00";
  std::string name4 = "Client4";

  club.clientArrived(time4, name4);
  club.clientExpecting(time4, name4);

  // 5 клиент
  std::string time5 = "09:00";
  std::string name5 = "Client5";

  club.clientArrived(time5, name5);
  club.clientExpecting(time5, name5);

  // 6 клиент
  std::string time6 = "09:00";
  std::string name6 = "Client6";

  club.clientArrived(time6, name6);
  club.clientExpecting(time6, name6);

  EXPECT_EQ(clients.size(), 6);
  EXPECT_EQ(expectedClients.size(), 3);

  club.kickingAllClients();

  EXPECT_EQ(clients.size(), 0);
  EXPECT_EQ(expectedClients.size(), 0);

  EXPECT_EQ(computers[numberTable1 - 1].name_, "");
  EXPECT_EQ(computers[numberTable1 - 1].status_, true);
  EXPECT_EQ(computers[numberTable1 - 1].revenue_, 9 * cost);
  EXPECT_EQ(club.conversionToString(computers[numberTable1 - 1].worked),
            "09:00");

  EXPECT_EQ(computers[numberTable2 - 1].name_, "");
  EXPECT_EQ(computers[numberTable2 - 1].status_, true);
  EXPECT_EQ(computers[numberTable2 - 1].revenue_, 9 * cost);
  EXPECT_EQ(club.conversionToString(computers[numberTable1 - 1].worked),
            "09:00");

  EXPECT_EQ(computers[numberTable3 - 1].name_, "");
  EXPECT_EQ(computers[numberTable3 - 1].status_, true);
  EXPECT_EQ(computers[numberTable3 - 1].revenue_, 9 * cost);
  EXPECT_EQ(club.conversionToString(computers[numberTable1 - 1].worked),
            "09:00");
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}