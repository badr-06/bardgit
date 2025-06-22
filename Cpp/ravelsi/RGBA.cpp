#include <iostream>
#include <cstdint>

class RGBA{
    std::uint8_t m_red;
    std::uint8_t m_green;
    std::uint8_t m_blue;
    std::uint8_t m_alpha;

public:
    RGBA(std::uint8_t r=0, std::uint8_t g=0, std::uint8_t b=0, std::uint8_t a=255) : m_red(r), m_green(g), m_blue(b), m_alpha(a) {};

    void print() {
        std::cout << "r=" << (int)m_red << " g=" << (int)m_green << " b=" << (int)m_blue << " a=" << (int)m_alpha << '\n';
    }

};


int main(){

	RGBA color(0, 135, 135);
	color.print();

    return 0;
}