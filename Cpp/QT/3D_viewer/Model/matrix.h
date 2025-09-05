#pragma once

#include <cmath>
#include <vector>

namespace s21 {

// Матрица преобразования
struct TransMatrix {
    float m[4][4];
    
    TransMatrix();
    TransMatrix operator*(const TransMatrix& other) const;

    // Единичная матрица
    static TransMatrix identity();
    // Матрица переноса
    static TransMatrix translation(float dx, float dy, float dz);
    // Матрица масштабирования
    static TransMatrix scaling(float sx, float sy, float sz);
    // Матрица вращения
    static TransMatrix rotation(float angle, float x, float y, float z);
};

// Координаты вершин
struct Vector3D {
    float x, y, z;

    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    // Длина вектора
    float length() const;

    // Преобразование вектора с помощью матрицы
    Vector3D& operator*=(const TransMatrix& transMatrix);
    Vector3D operator*(const TransMatrix& transMatrix) const;

    void push_back(std::vector<int>&& v);
};

// Ребро
struct Edge {

    Edge() : from(0), to(0) {}
    Edge(unsigned int from_, unsigned int to_) : from(from_), to(to_) {}

    // Индексы вершин
    unsigned int from, to;
};

} // namespace s21
