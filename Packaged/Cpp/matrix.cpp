#include "Include/matrix.h"

Matrix::Matrix(const Matrix &mat) { *this = mat; }

vec4 &Matrix::operator[](int index) { return row[index]; }

vec4 Matrix::get(int index) { return row[index]; }

Matrix::Matrix() {
  row[0] = row[1] = row[2] =row[3] = vec4(0.0f);
  row[0][0] = row[1][1] = row[2][2] = row[3][3] = 1;
}
//////
Matrix::~Matrix() {

}
///////
void Matrix::rotate(const vec3 &vec, float degree){
  degree = degree * PI/ 180.0;
  double Cos = cosf(degree);
  double Sin = sinf(degree);
  float a = vec.get(0), b = vec.get(1), c = vec.get(2);
  double aa = a * a, bb = b * b, cc = c * c;
  double rr = aa + bb + cc;
  double r = sqrt(rr);
  Matrix mat;
  mat[0][0] = ((bb + cc) * Cos + aa) / rr;
  mat[1][0] = (a * b * (1 - Cos) - c * r * Sin) / rr;
  mat[2][0] = (a * c * (1 - Cos) + b * r * Sin) / rr;
  mat[0][1] = (a * b * (1 - Cos) + c * r * Sin) / rr;
  mat[1][1] = ((aa + cc) * Cos + bb) / rr;
  mat[2][1] = (b * c * (1 - Cos) - a * r * Sin) / rr;
  mat[0][2] = (a * c * (1 - Cos) - b * r * Sin) / rr;
  mat[1][2] = (b * c * (1 - Cos) + a * r * Sin) / rr;
  mat[2][2] = ((aa + bb) * Cos + cc) / rr;
  mat *= (*this);
  *this = mat;
}
///////
void Matrix::rrotate(const vec3 &vec, float degree) {
  Matrix mat;
  mat.rotate(vec, degree);
  (*this) *= mat;
}
////////
void Matrix::translate(const vec3 &vec) {
 for (int c = 0; c < 3; c++)
    for (int r = 0; r < 4; r++)
      row[r][c] += vec.get(c) * row[r][3];
}
//////
void Matrix::rtranslate(const vec3 &vec) {
for (int c = 0; c < 4; c++) {
    float temp = 0;
    for (int i = 0; i < 3; i++)
      temp += row[i][c] * vec.get(i);
    row[3][c] += temp;
  }
}
////////
void Matrix::scale(const vec3 &vec) {
  for (int c = 0; c < 3; c++)
    for (int r = 0; r < 4; r++)
      row[r][c] *= vec.get(c);
}
/////
void Matrix::rscale(const vec3 &vec) {
  for (int c = 0; c < 4; c++) {
    for (int r = 0; r < 3; r++)
      row[r][c] *= vec.get(r);
  }
}
//////
Matrix Matrix::transpose() {
  Matrix res;
  for (int c = 0; c < 4; c++)
    for (int r = 0; r < 4; r++)
      res.row[r][c] = row[c][r];
  return res;
}
///////
float Matrix::det4_value() {
  auto &a = row[0];
  auto &b = row[1];
  auto &c = row[2];
  auto &d = row[3];
  return (a[0] * b[1] - a[1] * b[0]) * (c[2] * d[3] - c[3] * d[2]) -
         (a[0] * b[2] - a[2] * b[0]) * (c[1] * d[3] - c[3] * d[1]) +
         (a[0] * b[3] - a[3] * b[0]) * (c[1] * d[2] - c[2] * d[1]) +
         (a[1] * b[2] - a[2] * b[1]) * (c[0] * d[3] - c[3] * d[0]) -
         (a[1] * b[3] - a[3] * b[1]) * (c[0] * d[2] - c[2] * d[0]) +
         (a[2] * b[3] - a[3] * b[2]) * (c[0] * d[1] - c[1] * d[0]);
}
//////
float Matrix::det3_value(const vec3 &a, const vec3 &b, const vec3 &c) {
  return a.get(0) * b.get(1) * c.get(2) + a.get(1) * b.get(2) * c.get(0) +
         a.get(2) * b.get(0) * c.get(1) - a.get(2) * b.get(1) * c.get(0) -
         a.get(0) * b.get(2) * c.get(1) - a.get(1) * b.get(0) * c.get(2);
}
//////
Matrix Matrix::inverse() {
  Matrix res;

  float div = det4_value();

  if (div == 0.0)
    return res;

  vec3 A[3];
  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      //
      int index1 = 0, index2 = 0;
      for (int R = 0; R < 4; R++) {
        if (R == r)
          continue;
        for (int C = 0; C < 4; C++) {
          if (C == c)
            continue;
          A[index1][index2++] = row[R][C];
        }
        index1++;
        index2 = 0;
      }
      //
      res[c][r] = (((r + c) & 1) ? -1.0 : 1.0) * det3_value(A[0], A[1], A[2]);
    }
  }
  return res / div;
}
///////
float *Matrix::value_ptr() {
return &row[0][0];
}
////
Matrix Matrix::ToMat3(){
  Matrix res;
 for(int r=0;r<3;r++)
 for(int c=0;c<4;c++)
   res.row[r][c] =row[r][c];
 return res;
    }
//////
void Matrix::operator=(const Matrix &mat) {
  row[0] = mat.row[0];
  row[1] = mat.row[1];
  row[2] = mat.row[2];
  row[3] = mat.row[3];
}
//////
Matrix Matrix::operator/(float div) {
  Matrix res = *this;
  for (int r = 0; r < 4; r++)
    for (int c = 0; c < 4; c++)
      res.row[r][c] /= div;
  return res;
}
////
//////
Matrix Matrix::operator*(const Matrix &mat)const {
  Matrix res;
  for (int c = 0; c < 4; c++)
    for (int r = 0; r < 4; r++) {
      float temp = 0;
      for (int s = 0; s < 4; s++)
        temp += row[s].get(c) * mat.row[r].get(s);
      res[r][c] = temp;
    }
  return res;
}
//////
vec4 Matrix:: operator*(const vec4 &v){
  vec4 res(0);
    for (int c = 0; c < 4; c++){
      for (int r = 0; r < 4; r++)
        res[c] += row[r][c] * v.get(r);
      }
      return res;
    }
/////
void Matrix::operator*=(const Matrix &mat) {
  vec4 temp_v;
  for (int c = 0; c < 4; c++) {
    for (int r = 0; r < 4; r++) {
      float temp = 0;
      for (int s = 0; s < 4; s++)
        temp += row[s].get(c) * mat.row[r].get(s);
      temp_v[r] = temp;
    }
    for (int s = 0; s < 4; s++)
      row[s][c] = temp_v[s];
  }
}
///////
Matrix Matrix::perspective(double fov, double asp, double Near, double Far) {
  Matrix res;
  double TAN = tan(fov*PI/360.0);
  double v1 = 1 / (TAN * asp);
  double v2 = 1 / TAN;
  double v3 = (Near+Far)/(Near-Far);
  double v4 = (2* Near * Far)/(Near - Far);
  res.row[0][0] = v1;
  res.row[1][1] = v2;
  res.row[2][2] = v3;
  res.row[3][2] = v4;
  res.row[2][3] = -1;
  res.row[3][3] = 0;
  return res;

}

Matrix Matrix::ortho(double left, double right, double bottom, double top,double near_,double far_)
{
  Matrix res;
  auto&row=res.row;
  row[0][0]=2.0/(right-left);
  row[1][1]=2.0/(top-bottom);
  row[2][2]=-2.0/(far_-near_);
  row[3][0]= - (right + left)/(right - left);
  row[3][1] = -(top + bottom)/(top - bottom);
  row[3][2] = - (far_+near_)/(far_- near_);
  return res;
}
//////
Matrix Matrix:: camera(const vec3 &eye, const vec3 &target, const vec3 &up) {
  ///////////////
  vec3 f = (target - eye).normalize();
  vec3 s = (f.cross(up)).normalize();
  vec3 u = s.cross(f);
  Matrix res;
  auto &row_ = res.row;
  row_[0][0] = s[0];
  row_[1][0] = s[1];
  row_[2][0] = s[2];
  row_[0][1] = u[0];
  row_[1][1] = u[1];
  row_[2][1] = u[2];
  row_[0][2] = -f[0];
  row_[1][2] = -f[1];
  row_[2][2] = -f[2];
  row_[3][0] = -s.dot(eye);
  row_[3][1] = -u.dot(eye);
  row_[3][2] = f.dot(eye);
  return res;
}

Matrix Matrix::ConvertToColumnFormat(const float*data)
{
  Matrix res;
  for(Uint r=0;r<4;++r)
  {
    for(Uint c=0;c<4;++c)
    {
      res[r][c]=data[c*4+r];
    }
  }
  return res;
}

Matrix Matrix::ConvertQuaternionToMat4(const vec4 &q)
{
  Matrix Result;
  float qxx(q.x * q.x);
  float qyy(q.y * q.y);
  float qzz(q.z * q.z);
  float qxz(q.x * q.z);
  float qxy(q.x * q.y);
  float qyz(q.y * q.z);
  float qwx(q.w * q.x);
  float qwy(q.w * q.y);
  float qwz(q.w * q.z);
  Result[0][0] = 1.0f -2.0f* (qyy +  qzz);
  Result[0][1] = 2.0f * (qxy + qwz);
  Result[0][2] = 2.0f * (qxz - qwy);

  Result[1][0] = 2.0f * (qxy - qwz);
  Result[1][1] = 1.0f-2.0f* (qxx +  qzz);
  Result[1][2] = 2.0f* (qyz + qwx);

  Result[2][0] = 2.0f * (qxz + qwy);
  Result[2][1] = 2.0f * (qyz - qwx);
  Result[2][2] = 1.0f - 2.0f * (qxx +  qyy);
  return Result;
}

