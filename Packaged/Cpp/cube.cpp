#include "Include/cube.h"
void Cube::LoadTexture(vector<const char *>&file)
{
    height = new GLuint[6];
    width = new GLuint[6];
    for(int i=0;i<6;++i)
    {
        auto img=QImage(file[i]).convertToFormat(QImage::Format_RGBA8888);
        width[i] = img.width();
        height[i] = img.height();
        api->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGBA,img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits());
    }
    wrap(GL_CLAMP_TO_EDGE);
    filter(GL_LINEAR);
}

Cube::Cube(const char *positive_x_file, const char *nagative_x_file, const char *positive_y_file, const char *nagative_y_file, const char *positive_z_file, const char *nagative_z_file)
:Texture2DGeneral(CUBE)
{
    ////////////////////////////////////////////////
    vector<const char*>file(6);
    file[0]=positive_x_file,file[1]=nagative_x_file,
    file[2]=positive_y_file,file[3]=nagative_y_file,
    file[4]=positive_z_file,file[5]=nagative_z_file;
    ///////////////////////////////////////////////
    LoadTexture(file);

}

Cube::Cube(const char*file_path,const char*image_format)
:Texture2DGeneral(CUBE)
{
   vector<string>file(6);
    string path=file_path;
    path+="/";
    file[0]=path+CUBE_POSITIVE_X_NAME+"."+image_format;
    file[1]=path+CUBE_NAGATIVE_X_NAME+"."+image_format;
    file[2]=path+CUBE_POSITIVE_Y_NAME+"."+image_format;
    file[3]=path+CUBE_NAGATIVE_Y_NAME+"."+image_format;
    file[4]=path+CUBE_POSITIVE_Z_NAME+"."+image_format;
    file[5]=path+CUBE_NAGATIVE_Z_NAME+"."+image_format;
   vector<const char*>file_(6);
    for(int i=0;i<6;++i)file_[i]=file[i].c_str();
    LoadTexture(file_);
}


void Cube::Draw(Matrix &projection, Matrix &view)
{
    static bool init=0;
    static Program*program;
    static Vao*vao;
    static Vbo*vbo;
    static Ebo*ebo;
    if(!init)
    {
        init=1;
        //////////////////////////////生成program
        const char*vertex_code="#version 330 core\n"
         "layout (location=0) in vec3 aPos;\n"
        "out vec3 TexCoords;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 view;\n"
        "void main(){\n"
        "TexCoords =aPos;\n"
        "vec4 pos = projection*view*vec4(aPos, 1.0);\n"
        "gl_Position = pos.xyww;}";
        const char*frag_code="#version 330 core\n"
        "precision highp float;\n"
        "in vec3 TexCoords;\n"
        "uniform samplerCube sampler;\n"
        "void main(){\n"
        "gl_FragColor =texture(sampler,TexCoords);}\n";
        program=new Program(vertex_code,frag_code,1);
        //////////////////////////////
        float skyboxVertices[] = {
            1,1,1,
            1,1,-1,
            -1,1,-1,
            -1,1,1,
            1,-1,1,
            1,-1,-1,
            -1,-1,-1,
            -1,-1,1
        };
        GLuint indices[]={
        0,1,2,0,2,3,
        0,1,5,0,5,4,
        0,4,7,0,3,7,
        6,2,3,6,3,7,
        6,7,4,6,4,5,
        6,2,1,6,1,5
        };
        vao=new Vao();
        vbo=new Vbo(sizeof(skyboxVertices),skyboxVertices);
        vbo->setpoint(0,GL_FLOAT,3,sizeof(float)*3);
        ebo=new Ebo(36,indices);
        vao->unbind();
        //////////////////////////////
    }
    api->glDepthFunc(GL_LEQUAL);
    program->bind();
    vao->bind();
    bind();
    auto view_=view.ToMat3();
    program->setint("sampler",0);
    program->setmat4("view",view_);
    program->setmat4("projection",projection);
    api->glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
    api->glDepthFunc(GL_LESS);
}
Cube::~Cube()
{
}
