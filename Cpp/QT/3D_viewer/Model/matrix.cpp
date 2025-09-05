#include "matrix.h"


using namespace s21;

TransMatrix::TransMatrix() {
    *this = identity();
}

TransMatrix TransMatrix::operator*(const TransMatrix& other) const {
    TransMatrix result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

// Единичная матрица
TransMatrix TransMatrix::identity() {
    TransMatrix matrix;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
    return matrix;
}

// Матрица переноса
TransMatrix TransMatrix::translation(float dx, float dy, float dz) {
    TransMatrix matrix = TransMatrix();
    matrix.m[0][3] = dx;
    matrix.m[1][3] = dy;
    matrix.m[2][3] = dz;
    return matrix;
}

// Матрица масштабирования
TransMatrix TransMatrix::scaling(float sx, float sy, float sz) {
    TransMatrix matrix = TransMatrix();
    matrix.m[0][0] = sx;
    matrix.m[1][1] = sy;
    matrix.m[2][2] = sz;
    return matrix;
}

// Матрица вращения
TransMatrix TransMatrix::rotation(float angle, float x, float y, float z) {
    TransMatrix matrix = TransMatrix();
    float rad = angle * M_PI / 180.0;
    float cosA = cos(rad);
    float sinA = sin(rad);
    matrix.m[0][0] = cosA + (1 - cosA) * x * x;
    matrix.m[0][1] = (1 - cosA) * x * y - sinA * z;
    matrix.m[0][2] = (1 - cosA) * x * z + sinA * y;
    matrix.m[1][0] = (1 - cosA) * y * x + sinA * z;
    matrix.m[1][1] = cosA + (1 - cosA) * y * y;
    matrix.m[1][2] = (1 - cosA) * y * z - sinA * x;
    matrix.m[2][0] = (1 - cosA) * z * x - sinA * y;
    matrix.m[2][1] = (1 - cosA) * z * y + sinA * x;
    matrix.m[2][2] = cosA + (1 - cosA) * z * z;
    return matrix;
}


// Длина вектора
float Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Преобразование вектора с помощью матрицы
Vector3D &Vector3D::operator*=(const TransMatrix &transMatrix) {
    float newX = transMatrix.m[0][0] * x + transMatrix.m[0][1] * y + transMatrix.m[0][2] * z + transMatrix.m[0][3];
    float newY = transMatrix.m[1][0] * x + transMatrix.m[1][1] * y + transMatrix.m[1][2] * z + transMatrix.m[1][3];
    float newZ = transMatrix.m[2][0] * x + transMatrix.m[2][1] * y + transMatrix.m[2][2] * z + transMatrix.m[2][3];
    x = newX;
    y = newY;
    z = newZ;
    return *this;
}

Vector3D Vector3D::operator*(const TransMatrix &transMatrix) const {
    Vector3D result = *this;
    result *= transMatrix;
    return result;
}

void s21::Vector3D::push_back(std::vector<int>&& v)
{
    this->x = v[0];
    this->y = v[1];
    this->z = v[2];
}
