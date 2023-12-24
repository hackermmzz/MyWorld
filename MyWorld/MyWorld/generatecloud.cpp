#include "generatecloud.h"

void GenerateCloud()
{
    static ComputeShader*cs;
    static bool init=0;
    static float  Time = 0;
    static float Speed =8000;
    static int LoadSize = 16;
    static int cloud_section_size = 32;
    static int cloud_fbm = 10;
    if(!init)
    {
        init=1;
        std::ifstream cs_file("Src/Shader/Cloud/CloudGenerator.comp");
        std::string code;
        int line=0;
        string temp;
        while(getline(cs_file,temp))
        {
            if(line==1)
                code+="const int FBM="+to_string(cloud_fbm)+";";
            else if(line==2)
                code+="const int SECTION_SIZE="+to_string(cloud_section_size)+";";
            else code+=temp;
            code+='\n';
                temp="";
             line++;
        }
        cs=new ComputeShader(code.data(),1);
        const Uint size=cloud_section_size*LoadSize;
        cloud=new Texture2DGeneral(size,size,GL_R16F,GL_RED,GL_FLOAT,0);
        cloud->wrap(GL_CLAMP_TO_BORDER);
        cloud->filter(GL_NEAREST);
        cloud->setBoarderColor({ 0 });
    }
    cs->bind();
    cs->setfloat("time",Time/Speed);
    Time += render_time;
    cs->setint("cloud",0);
    cloud->bind(0);
    cloud->bindImage(0,GL_R16F,GL_READ_WRITE);
    cs->run(LoadSize,1, LoadSize);
    cs->barrierImage();
}
