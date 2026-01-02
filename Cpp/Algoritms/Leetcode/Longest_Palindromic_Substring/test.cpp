#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

struct Point_2 {
    double x;
    double y;
};

struct LineSegment {
    Point_2 start;
    Point_2 end;
    
    bool isValid() const {
        return !(start.x == end.x && start.y == end.y);
    }
};

// Функция пересечения двух прямых
Point_2 findLineIntersection(const Point_2& normal, double offset, 
                            const Point_2& p1, const Point_2& p2) {
    double A1 = normal.x;
    double B1 = normal.y;
    double C1 = offset;
    
    double A2 = p2.y - p1.y;
    double B2 = p1.x - p2.x;
    double C2 = A2 * p1.x + B2 * p1.y;
    
    double det = A1 * B2 - A2 * B1;
    
    if (std::abs(det) < 1e-10) {
        return Point_2{NAN, NAN};
    }
    
    double x = (C1 * B2 - C2 * B1) / det;
    double y = (A1 * C2 - A2 * C1) / det;
    
    return Point_2{x, y};
}

// Проверка что точка лежит на отрезке
bool pointOnSegment(const Point_2& point, const Point_2& segStart, const Point_2& segEnd, 
                   double epsilon = 1e-10) {
    if (std::isnan(point.x) || std::isnan(point.y)) {
        return false;
    }
    
    // Проверка bounding box
    double minX = std::min(segStart.x, segEnd.x) - epsilon;
    double maxX = std::max(segStart.x, segEnd.x) + epsilon;
    double minY = std::min(segStart.y, segEnd.y) - epsilon;
    double maxY = std::max(segStart.y, segEnd.y) + epsilon;
    
    if (point.x < minX || point.x > maxX || point.y < minY || point.y > maxY) {
        return false;
    }
    
    // Проверка коллинеарности
    double cross = (point.x - segStart.x) * (segEnd.y - segStart.y) 
                 - (point.y - segStart.y) * (segEnd.x - segStart.x);
    
    return std::abs(cross) <= epsilon;
}

// Нахождение отрезка внутри контура для заданной линии
LineSegment findSegmentInsideContour(const std::vector<Point_2>& contour, 
                                   const Point_2& normal, double offset) {
    std::vector<Point_2> intersection_points;
    
    // Находим все пересечения линии с контуром
    for (size_t i = 0; i < contour.size(); i++) {
        Point_2 p1 = contour[i];
        Point_2 p2 = contour[(i + 1) % contour.size()];
        
        Point_2 intersection = findLineIntersection(normal, offset, p1, p2);
        
        if (pointOnSegment(intersection, p1, p2)) {
            // Проверяем на дубликаты (из-за погрешностей вычислений)
            bool isDuplicate = false;
            for (const auto& existing : intersection_points) {
                if (std::abs(existing.x - intersection.x) < 1e-10 &&
                    std::abs(existing.y - intersection.y) < 1e-10) {
                    isDuplicate = true;
                    break;
                }
            }
            
            if (!isDuplicate) {
                intersection_points.push_back(intersection);
            }
        }
    }
    
    // Для выпуклого многоугольника должно быть ровно 2 точки
    if (intersection_points.size() == 2) {
        return LineSegment{intersection_points[0], intersection_points[1]};
    }
    
    return LineSegment{}; // Невалидный отрезок
}

// Основная функция генерации штриховки
std::vector<LineSegment> generateHatching(const std::vector<Point_2>& contour, 
                                        double angle_degrees, double step) {
    std::vector<LineSegment> hatching_lines;
    
    // Преобразуем угол в радианы
    double angle_rad = angle_degrees * M_PI / 180.0;
    
    // Вычисляем нормаль (перпендикуляр к направлению штриховки)
    Point_2 normal{-sin(angle_rad), cos(angle_rad)};
    
    // Находим проекции всех вершин контура на нормаль
    std::vector<double> projections;
    for (const auto& point : contour) {
        double proj = point.x * normal.x + point.y * normal.y;
        projections.push_back(proj);
    }
    
    // Находим минимальную и максимальную проекцию
    auto min_max = std::minmax_element(projections.begin(), projections.end());
    double min_proj = *min_max.first;
    double max_proj = *min_max.second;
    
    // Определяем диапазон линий
    int n_min = std::ceil(min_proj / step);
    int n_max = std::floor(max_proj / step);
    
    std::cout << "Angle: " << angle_degrees << "°" << std::endl;
    std::cout << "Normal: (" << normal.x << ", " << normal.y << ")" << std::endl;
    std::cout << "Projections range: " << min_proj << " to " << max_proj << std::endl;
    std::cout << "Lines count: " << (n_max - n_min + 1) << std::endl;
    
    // Генерируем линии
    for (int n = n_min; n <= n_max; ++n) {
        double offset = n * step;
        LineSegment segment = findSegmentInsideContour(contour, normal, offset);
        
        if (segment.isValid()) {
            hatching_lines.push_back(segment);
        }
    }
    
    return hatching_lines;
}

// Функция для красивого вывода
void printResults(const std::vector<LineSegment>& lines) {
    for (size_t i = 0; i < lines.size(); ++i) {
        std::cout << "Line " << i << ": (" 
                  << lines[i].start.x << "," << lines[i].start.y << ") -> (" 
                  << lines[i].end.x << "," << lines[i].end.y << ")" << std::endl;
    }
}

int main() {
    // Примеры тестирования для разных углов
    
    // Прямоугольник
    std::vector<Point_2> rectangle = {
        {0, 0}, {10, 0}, {10, 10}, {0, 10}
    };
    
    std::cout << "=== Testing different angles ===" << std::endl;
    
    // Тест 1: 0° (горизонтальные линии)
    std::cout << "\n--- Angle 0° ---" << std::endl;
    auto lines0 = generateHatching(rectangle, 0, 1);
    printResults(lines0);
    
    // Тест 2: 45° (диагональные линии)
    std::cout << "\n--- Angle 45° ---" << std::endl;
    auto lines45 = generateHatching(rectangle, 45, 1);
    printResults(lines45);
    
    // Тест 3: 90° (вертикальные линии)
    std::cout << "\n--- Angle 90° ---" << std::endl;
    auto lines90 = generateHatching(rectangle, 90, 1);
    printResults(lines90);
    
    // Тест 4: 30° (произвольный угол)
    std::cout << "\n--- Angle 30° ---" << std::endl;
    auto lines30 = generateHatching(rectangle, 30, 1);
    printResults(lines30);
    
    // Тест 5: 135° (тупой угол)
    std::cout << "\n--- Angle 135° ---" << std::endl;
    auto lines135 = generateHatching(rectangle, 135, 1);
    printResults(lines135);
    
    return 0;
}