#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

    struct infoClient
    {
        bool status_ = false; // false означает что клиент не за компьютером
        int numberComputer_ = 0; // номер стола компьютера за которым сидит
        int satDownComp;
    };

    struct infoComputer
    {
        bool status_ = true; // true означает компьютер свободен
        std::string name_; // имя клиента который занял
        int worked; // время которое он проработал в день
        int revenue_; // выручка

    };

class computerClub 
{
    unsigned int numberOfComputers_; // количество комп
    unsigned int numbAvailableComp_; // количество доступных компьютеров
    int beginWorkDay_; // начало рабочего дня
    int endWorkDay_; // конец рабочего длня
    unsigned int costHour_; // стоимость за час
    
    std::map<std::string, infoClient> clients_; // имена и статус клиентов
    std::vector<infoComputer> computers_; // информация о компьютерах
    std::set<std::string> expectedClients_; // клиенты которые ожидают

public:
    computerClub() noexcept : numberOfComputers_(0), numbAvailableComp_(0), beginWorkDay_(0), endWorkDay_(0), costHour_(0) {}
    computerClub(int number, int cost, std::string begin, std::string end) noexcept;

    auto conversionToMinutes(std::string str) -> int;
    auto conversionToString(int minutes) -> std::string;
    auto calculatingRevenue(int timeWhenStandUp, int timeWhenSatDown) -> int;
    void kickingAllClients();

    auto clientArrived(const std::string time, const std::string& name) -> int;
    auto clientSatDown(std::string time, const std::string& name, const int number) -> int;
    auto clientExpecting( const std::string time, const std::string& name) -> int;
    auto clientLeaves(std::string time, const int id, const std::string& name) -> int;
   
    void printRevenu();

    const unsigned int& getnumberOfComputers(){
        return numberOfComputers_;
    }
    const unsigned int& getnumbAvailableComp(){
        return numbAvailableComp_;
    }
    std::string getbeginWorkDay(){
        return conversionToString(beginWorkDay_);
    }
    std::string getendWorkDay(){
        return conversionToString(endWorkDay_);
    }
    const unsigned int& getcostHour(){
        return costHour_;
    }

    const std::map<std::string, infoClient>& getclients_(){
        return clients_;
    }
    const std::vector<infoComputer>& getcomputers_() {
        return computers_;
    };
    const std::set<std::string>& getexpectedClients_(){
        return expectedClients_;
    };

};