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
    //设置opengl渲染控件与窗口同等大小
    auto& openglwidget = ui.openGLWidget;
    openglwidget->move(0, 0);
    openglwidget->resize(width(), height());
}
