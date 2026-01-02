#include <iostream>
#include <vector>

int main() {


    double a, b, c, v1, v2, v3;
    std::cin >> a >> b >> c >> v1 >> v2 >> v3;

    

    double var = a/v1 + c/v2 + b/v3;
    double res = var;

    var = b/v1 + c/v2 + a/v3;
    res = std::min(res, var);

    var = a/v1 + a/v2 + b/v1 + b/v2;
    res = std::min(res, var);

    var = b/v1 + b/v2 + a/v1 + a/v2;
    res = std::min(res, var);

    var = a/v1 + c/v1 + c/v2 + a/v3;
    res = std::min(res, var);

    var = b/v1 + c/v1 + c/v2 + b/v3;
    res = std::min(res, var);

    var = a/v1 + c/v1 + c/v2 + a/v2 + a/v1 + a/v2;
    res = std::min(res, var);

    var = b/v1 + c/v1 + c/v2 + b/v2 + b/v1 + b/v2;
    res = std::min(res, var);

    var = a/v1 + a/v2 + a/v1 + c/v1 + c/v2 + a/v2;
    res = std::min(res, var);

    var = b/v1 + b/v2 + b/v1 + c/v1 + c/v2 + b/v2;
    res = std::min(res, var);

    var = a/v1 + c/v2 + c/v3 + a/v3;
    res = std::min(res, var);

    var = b/v1 + c/v2 + c/v3 + b/v3;
    res = std::min(res, var);

    std::cout << res << '\n';

    return 0;
}