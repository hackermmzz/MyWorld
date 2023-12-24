#include "drawinfo.h"
void DrawInfo()
{
    static auto*Info=new Frame(OpenglWidget);
    static bool init=0;
    if(!init)
    {
        init=1;
        Info->setAttribute(Qt::WA_TransparentForMouseEvents);
        Info->move(0,0);
        Info->setStyleSheet("background-color: rgba(255,255,255,120);");
    }
    if(Show_Info)
    {
        auto&ui=Info->ui;
        /////////////////////////////////////////////////
        ui->FPSVAL->setText(to_string(fps).c_str());
        ui->POSVALX->setText(to_string(camera.position.x).c_str());
        ui->POSVALY->setText(to_string(camera.position.y).c_str());
        ui->POSVALZ->setText(to_string(camera.position.z).c_str());
        ui->RENDERTIMEVAL->setText(to_string(render_time).c_str());
        ui->RENDERFACESVAL->setText(to_string(Face_Render_Nums).c_str());
        ui->RENDERSECTIONSVAL->setText(to_string(Section_Render_Nums).c_str());
        ui->CURRENTTIMEVAL->setText(to_string(int(TimeOfDay*24/TimePerDay)).c_str());
        //////////////////////////////////////////////////
        float  relativeSize = 0.5;
        Info->resize(OpenglWidget->width()* relativeSize,OpenglWidget->height()* relativeSize);
        Info->show();
    }
    else
        Info->hide();
}
