#ifndef MATRIX_H
#define MATRIX_H
#include"vec.hpp"
#include"Include.h"
#include<vector>
using  std::vector;
class Matrix {
private:
  vec4 row[4];
public:
 Matrix();
Matrix(const Matrix &mat);
 void translate(const vec3 &vec);
 void rtranslate(const vec3 &vec);
void scale(const vec3 &vec);
 void rscale(const vec3 &vec);
 void rotate(const vec3 &vec, float degree);
 void rrotate(const vec3 &vec, float degree);
 Matrix transpose();
 Matrix inverse();
 float det4_value();
static float det3_value(const vec3 &a, const vec3 &b,
                          const vec3 &c);
 void operator=(const Matrix &mat);
 void operator*=(const Matrix &mat);
 vec4 &operator[](int index);
 Matrix operator/(float div);
 vec4 get(int index);
 float *value_ptr();
 Matrix ToMat3();
 Matrix operator*(const Matrix &mat)const;
 vec4 operator*(const vec4 &v);
 static Matrix perspective(double fov, double asp, double near_, double far_);
 static Matrix ortho(double left,double right,double bottom,double top,double near_,double far_);
 static Matrix camera(const vec3 &eye, const vec3 &target, const vec3 &up);
 static Matrix ConvertToColumnFormat(const float*data);
 static Matrix ConvertQuaternionToMat4(const vec4&quaternion);
 ~Matrix();
};
///////////
#endif // MATRIX_H
