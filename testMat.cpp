#include <iostream>
#include "Matrix.h"
int main() {
    float * f = new float[8] {1.0f, 2.0f, 3.0f, 4.0f, 1.0f, 2.0f, 3.0f, 4.0f};
    Matrix mat("A" ,f, 8, 4, 2);
    Matrix mat2(mat);
    Matrix mat3("B",2,3);
    std::cout << mat2 << 2 * mat << mat;
}
