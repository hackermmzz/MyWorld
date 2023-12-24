#ifndef CUBE_H
#define CUBE_H
#include"Include.h"
#include"program.h"
#include"vao.h"
#include"vbo.h"
#include"ebo.h"
#include"matrix.h"
#include<vector>
#include"texture2dgeneral.h"
#include<string.h>
using namespace  std;
class Cube:public Texture2DGeneral
{
private:
    void LoadTexture(vector<const char*>&file);
public:
    Cube(const char*positive_x_file,const char*nagative_x_file,const char*positive_y_file,const char*nagative_y_file,const char*positive_z_file,const char*nagative_z_file);
    Cube(const char*file_path,const char*image_format);
    void Draw(Matrix&projection,Matrix&view);
    ~Cube();
};

#endif // CUBE_H
