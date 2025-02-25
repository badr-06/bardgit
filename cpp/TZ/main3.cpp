#include <iostream>
#include <vector>
#include <algorithm>

struct Taxi {
    long long timestamp;
    int taxi_id;
    int taxi_position;
};

struct Order {
    long long timestamp;
    int order_id;
    int order_position;
    int order_time;
};

void processOrder(const std::vector<Taxi>& taxies, const Order& order, int L, int S, std::vector<std::vector<int>>& result) {
    std::vector<int> suitable_taxis;

    for (const auto& taxi : taxies) {
        long long time_diff = order.timestamp - taxi.timestamp;
        int min_distance = 0;
        int max_distance = S * time_diff;

        int min_position = (taxi.taxi_position + min_distance) % L;
        int max_position = (taxi.taxi_position + max_distance) % L;

        int distance;
        if (min_position <= order.order_position && order.order_position <= max_position) {
            distance = 0;
        } else {
            distance = (order.order_position - max_position + L) % L;
        }
        bool flag = true;


        if (distance <= order.order_time * S) {
        
        for(int to : suitable_taxis){
            if(to == taxi.taxi_id) flag = false;
        }            
        
        if(flag) suitable_taxis.push_back(taxi.taxi_id);
        
        }
    }

    bool flag = false;
    if (suitable_taxis.empty()) {
        result.push_back({-1});
    } else {
        if (suitable_taxis.size() > 5) {
            suitable_taxis.resize(5);
        }
        result.push_back(suitable_taxis);
    }
}

int main() {
    int N, L, S;
    std::cin >> N >> L >> S;

    if(N < 1) return 1;

    std::vector<Taxi> taxies;
    std::vector<Order> orders;
    std::vector<std::vector<int>> result;

    for (int i = 0; i < N; ++i) {
        std::string command;
        std::cin >> command;

        if (command == "TAXI") {
            Taxi taxi;
            std::cin >> taxi.timestamp >> taxi.taxi_id >> taxi.taxi_position;
            taxies.push_back(taxi);
        } else if (command == "ORDER") {
            Order order;
            std::cin >> order.timestamp >> order.order_id >> order.order_position >> order.order_time;
            processOrder(taxies, order, L, S, result);
        }
    }

    for (const auto& res : result) {
        for (int id : res) {
            std::cout << id << " ";
        }
        std::cout << '\n';
    }

    return 0;
}