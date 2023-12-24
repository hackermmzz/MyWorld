#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MyWorld.h"

class MyWorld : public QMainWindow
{
    Q_OBJECT

public:
    MyWorld(QWidget *parent = nullptr);
    ~MyWorld();
protected:
    void resizeEvent(QResizeEvent* e);
private:
    Ui::MyWorldClass ui;
};
