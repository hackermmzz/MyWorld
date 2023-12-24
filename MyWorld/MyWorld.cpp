#include "MyWorld.h"

MyWorld::MyWorld(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle("MyWorld");
    setWindowIcon(QIcon("Src/Icon/icon.jpg"));
}

MyWorld::~MyWorld()
{
   
}

void MyWorld::resizeEvent(QResizeEvent* e)
{
    //����opengl��Ⱦ�ؼ��봰��ͬ�ȴ�С
    auto& openglwidget = ui.openGLWidget;
    openglwidget->move(0, 0);
    openglwidget->resize(width(), height());
}
