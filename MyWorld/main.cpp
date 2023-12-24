#pragma once
#include "MyWorld.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    QApplication a(argc, argv);
    MyWorld w;
    w.show();
    return a.exec();
}
