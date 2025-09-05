#include "matrix.h"


namespace s21 {

class Figure {
    std::vector<Vector3D> vertices_;
    std::vector<Edge> edges_;

    float maxX_ = -INFINITY;
    float minX_ = INFINITY;

    float maxY_ = -INFINITY;
    float minY_ = INFINITY;

    float maxZ_ = -INFINITY;
    float minZ_ = INFINITY;
public:
    Figure();

    Figure* getFigure() { return this; }

    // Список вершин
    const std::vector<Vector3D>& vertices() const;
    // Список рёбер
    const std::vector<Edge>& edges() const; 
    // Список вершин
    std::vector<Vector3D>& vertices();
    // Список рёбер
    std::vector<Edge>& edges();

    // Плоский массив вершин
    const float* flatVertices() const;
    // Плоский массив рёбер
    const unsigned int* flatEdges() const;

    // Добавить вершину
    void addVertex(float x, float y, float z);
    // Добавить ребро
    void addEdge(int v1, int v2);
    // Сбросить фигуру
    void clear();

    // Радиус фигуры
    float radius() const;
    // Центр фигуры
    const s21::Vector3D center() const;

    // Масштабировать и вернуть результат
    Figure& scale(float sx, float sy, float sz);
    // Переместить и вернуть результат
    Figure& move(float dx, float dy, float dz);
    // Повернуть и вернуть результат
    Figure& rotate(float angle, float x, float y, float z);
    // Проеряеят массивы для вершин и грани на пустоту, перед парсером
    void checkQvectors();
    void select_size(int V, int F);
};

} // namespace s21
