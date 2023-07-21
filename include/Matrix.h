#pragma once
#include "Point3D.h"
#include <array>

std::array<std::array<float, 4>, 4> matrixMultiplication(const std::array<std::array<float, 4>, 4>& matrixA, const std::array<std::array<float, 4>, 4>& matrixB);
std::array<std::array<float, 4>, 4> createRotationMatrixX(float alfa);
std::array<std::array<float, 4>, 4> createRotationMatrixY(float beta);
std::array<std::array<float, 4>, 4> createRotationMatrixZ(float gamma);
std::array<std::array<float, 4>, 4> createRotationMatrix(const Point3D& vector);
std::array<std::array<float, 4>, 4> createTranslationMatrix(Point3D& translationVector);
std::array<std::array<float, 4>, 4> createInverseTransformationMatrix(const std::array<std::array<float, 4>, 4>& transformationMatrix);