#pragma once
#include <QApplication>
#include <QPushButton>
#include <QIcon>
#include <QPainter>
class BagButton : public QPushButton {
public:
    QIcon* icon_;
    size_t id;
    BagButton(QWidget* parent = nullptr);
    void setIcon(QIcon*icon,int id=0);
protected:
    void paintEvent(QPaintEvent* event) override;

};

