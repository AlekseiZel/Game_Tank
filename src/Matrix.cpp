
#include "Update.h"
#include "Matrix.h"
#include "Point3D.h"
#include "Tank.h"
#include "Engine.h"
#include "Segment3D.h"
#include "Snowflake.h"
#include <vector>
#include <cmath>
#include <array>


std::array<std::array<float, 4>, 4> matrixMultiplication(const std::array<std::array<float, 4>, 4>& matrixA, const std::array<std::array<float, 4>, 4>& matrixB) {
    std::array<std::array<float, 4>, 4> result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return result;
}


std::array<std::array<float, 4>, 4> createTranslationMatrix(Point3D& translationVector) {
    std::array<std::array<float, 4>, 4> translationMatrix;

    translationMatrix[0] = { 1.0f, 0.0f, 0.0f, translationVector.x };
    translationMatrix[1] = { 0.0f, 1.0f, 0.0f, translationVector.y };
    translationMatrix[2] = { 0.0f, 0.0f, 1.0f, translationVector.z };
    translationMatrix[3] = { 0.0f, 0.0f, 0.0f, 1.0f };

    return translationMatrix;
}



std::array<std::array<float, 4>, 4> createRotationMatrixX(float alpha) {
    float cosAlpha = std::cos(alpha);
    float sinAlpha = std::sin(alpha);

    std::array<std::array<float, 4>, 4> rotationMatrixX;

    // Матрица поворота вокруг оси X (угол alpha)
    rotationMatrixX[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
    rotationMatrixX[1] = { 0.0f, cosAlpha, -sinAlpha, 0.0f };
    rotationMatrixX[2] = { 0.0f, sinAlpha,  cosAlpha, 0.0f };
    rotationMatrixX[3] = { 0.0f, 0.0f,      0.0f,      1.0f };

    return rotationMatrixX;
}

std::array<std::array<float, 4>, 4> createRotationMatrixY(float beta) {
    float cosBeta = std::cos(beta);
    float sinBeta = std::sin(beta);

    // Матрица поворота вокруг оси Y (угол beta)
    std::array<std::array<float, 4>, 4> rotationMatrixY;
    rotationMatrixY[0] = { cosBeta, 0.0f, sinBeta, 0.0f };
    rotationMatrixY[1] = { 0.0f,    1.0f, 0.0f,    0.0f };
    rotationMatrixY[2] = { -sinBeta, 0.0f, cosBeta, 0.0f };
    rotationMatrixY[3] = { 0.0f,    0.0f, 0.0f,    1.0f };
  
    return rotationMatrixY;
}

std::array<std::array<float, 4>, 4> createRotationMatrixZ(float gamma) {

    float cosGamma = std::cos(gamma);
    float sinGamma = std::sin(gamma);

    // Матрица поворота вокруг оси Z (угол gamma)
    std::array<std::array<float, 4>, 4> rotationMatrixZ;
    rotationMatrixZ[0] = { cosGamma, -sinGamma, 0.0f, 0.0f };
    rotationMatrixZ[1] = { sinGamma, cosGamma,  0.0f, 0.0f };
    rotationMatrixZ[2] = { 0.0f,     0.0f,      1.0f, 0.0f };
    rotationMatrixZ[3] = { 0.0f,     0.0f,      0.0f, 1.0f };
   

    return rotationMatrixZ;
}


std::array<std::array<float, 4>, 4> createRotationMatrix(const Point3D & vector) {
    std::array<float, 3> axis;
    axis[0] = vector.x;
    axis[1] = vector.y;
    axis[2] = vector.z;

    // Нормализуем вектор
    float length = std::sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
    float x = axis[0] / length;
    float y = axis[1] / length;
    float z = axis[2] / length;

    // Вычисляем углы поворота вокруг осей X, Y и Z
    float alpha = std::atan2(y, z);
    float beta = std::atan2(-x, std::sqrt(y * y + z * z));
    float gamma = std::atan2(std::sin(alpha) * z - std::cos(alpha) * y, std::cos(alpha) * x - std::sin(alpha) * y);

    // Вычисляем синусы и косинусы углов
    float cosAlpha = std::cos(alpha);
    float sinAlpha = std::sin(alpha);
    float cosBeta = std::cos(beta);
    float sinBeta = std::sin(beta);
    float cosGamma = std::cos(gamma);
    float sinGamma = std::sin(gamma);

    // Создаем матрицу поворота
    std::array<std::array<float, 4>, 4> rotationMatrix;
    rotationMatrix[0] = { cosBeta * cosGamma, cosAlpha * sinGamma + sinAlpha * sinBeta * cosGamma, sinAlpha * sinGamma - cosAlpha * sinBeta * cosGamma, 0.0f };
    rotationMatrix[1] = { -cosBeta * sinGamma, cosAlpha * cosGamma - sinAlpha * sinBeta * sinGamma, sinAlpha * cosGamma + cosAlpha * sinBeta * sinGamma, 0.0f };
    rotationMatrix[2] = { sinBeta, -sinAlpha * cosBeta, cosAlpha * cosBeta, 0.0f };
    rotationMatrix[3] = { 0.0f, 0.0f, 0.0f, 1.0f };

    return rotationMatrix;
}


std::array<std::array<float, 4>, 4> createInverseTransformationMatrix(const std::array<std::array<float, 4>, 4>& transformationMatrix) {
    // Разбиваем комбинированную матрицу на матрицу поворота и матрицу трансляции
    std::array<std::array<float, 3>, 3> rotationMatrix = { {
        {transformationMatrix[0][0], transformationMatrix[0][1], transformationMatrix[0][2]},
        {transformationMatrix[1][0], transformationMatrix[1][1], transformationMatrix[1][2]},
        {transformationMatrix[2][0], transformationMatrix[2][1], transformationMatrix[2][2]}
    } };

    std::array<float, 3> translationVector = {
        transformationMatrix[0][3],
        transformationMatrix[1][3],
        transformationMatrix[2][3]
    };

    // Находим транспонированную матрицу поворота
    std::array<std::array<float, 3>, 3> inverseRotationMatrix;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverseRotationMatrix[i][j] = rotationMatrix[j][i];
        }
    }

    // Вычисляем обратный вектор трансляции
    std::array<float, 3> inverseTranslationVector = {
        -(inverseRotationMatrix[0][0] * translationVector[0] + inverseRotationMatrix[0][1] * translationVector[1] + inverseRotationMatrix[0][2] * translationVector[2]),
        -(inverseRotationMatrix[1][0] * translationVector[0] + inverseRotationMatrix[1][1] * translationVector[1] + inverseRotationMatrix[1][2] * translationVector[2]),
        -(inverseRotationMatrix[2][0] * translationVector[0] + inverseRotationMatrix[2][1] * translationVector[1] + inverseRotationMatrix[2][2] * translationVector[2])
    };

    // Вычисляем обратную комбинированную матрицу
    std::array<std::array<float, 4>, 4> inverseTransformationMatrix;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            inverseTransformationMatrix[i][j] = inverseRotationMatrix[i][j];
        }
        inverseTransformationMatrix[i][3] = inverseTranslationVector[i];
    }
    inverseTransformationMatrix[3] = { 0.0f, 0.0f, 0.0f, 1.0f };

    return inverseTransformationMatrix;
}