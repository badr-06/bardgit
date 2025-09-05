#include "figure.h"


using namespace s21;

Figure::Figure() : vertices_(), edges_() {}

// Список вершин
const std::vector<Vector3D>& Figure::vertices() const {
    return vertices_;
}

// Список рёбер
const std::vector<Edge>& Figure::edges() const {
    return edges_;
}
// Список вершин
std::vector<Vector3D>& Figure::vertices() {
    return vertices_;
}

// Список рёбер
std::vector<Edge>& Figure::edges() {
    return edges_;
}

// Плоский массив вершин
// Так как используется своя структура, мы можем гарантировать,
// что все данные храняться в памяти последовательно
// из-за чего достаточно просто привести тип сырого указателя на массив структур к float*
const float* Figure::flatVertices() const {
    return reinterpret_cast<const float*>(vertices_.data());
}

// Плоский массив рёбер
// По той же причине здесь используется своя структура а не std::pair<int, int>
const unsigned int* Figure::flatEdges() const {
    return reinterpret_cast<const unsigned int*>(edges_.data());
}

// Добавить вершину
void Figure::addVertex(float x, float y, float z) {
    vertices_.emplace_back(x, y, z);
    
    maxX_ = std::max(maxX_, x);
    minX_ = std::min(minX_, x);
    maxY_ = std::max(maxY_, y);
    minY_ = std::min(minY_, y);
    maxZ_ = std::max(maxZ_, z);
    minZ_ = std::min(minZ_, z);
}

// Добавить ребро
void Figure::addEdge(int v1, int v2) {
    edges_.emplace_back(v1, v2);
}

// Сбросить фигуру
void Figure::clear() {
    vertices_.clear();
    edges_.clear();
    maxX_ = -INFINITY;
    minX_ = INFINITY;
    maxY_ = -INFINITY;
    minY_ = INFINITY;
    maxZ_ = -INFINITY;
    minZ_ = INFINITY;
}

// Радиус фигуры
float Figure::radius() const {
    float x = maxX_ - minX_;
    float y = maxY_ - minY_;
    float z = maxZ_ - minZ_;
    return Vector3D{x, y, z}.length() / 2;
}

// Центр фигуры
const s21::Vector3D Figure::center() const {
    float centerX = (minX_ + maxX_) / 2;
    float centerY = (minY_ + maxY_) / 2;
    float centerZ = (minZ_ + maxZ_) / 2;
    return Vector3D{centerX, centerY, centerZ};
}

// Масштабировать и вернуть результат
Figure& Figure::scale(float sx, float sy, float sz) {
    TransMatrix scaleMatrix = TransMatrix::scaling(sx, sy, sz);
    for (Vector3D& vertex : vertices_) {
        vertex *= scaleMatrix;
    }
    return *this;
}

// Переместить и вернуть результат
Figure& Figure::move(float dx, float dy, float dz) {
    TransMatrix moveMatrix = TransMatrix::translation(dx, dy, dz);
    for (Vector3D& vertex : vertices_) {
        vertex *= moveMatrix;
    }
    return *this;
}

// Повернуть и вернуть результат
Figure& Figure::rotate(float angle, float x, float y, float z) {
    TransMatrix rotateMatrix = TransMatrix::rotation(angle, x, y, z);
    for (Vector3D& vertex : vertices_) {
        vertex *= rotateMatrix;
    }
    return *this;
}

void Figure::checkQvectors()
{
    if(!vertices_.empty() || !edges_.empty()) this->clear();
}


void Figure::select_size(int V, int F)
{
    vertices_.reserve(V + 1);
    edges_.reserve(F * 4 + 1);
}