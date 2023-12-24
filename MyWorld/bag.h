#ifndef BAG_H
#define BAG_H

#include <QFrame>
#include"ui_bag.h"
namespace Ui {
class Bag;
}

class Bag : public QFrame
{
    Q_OBJECT

public:
    explicit Bag(QWidget *parent = nullptr);
    ~Bag();
    Ui::Bag *ui;

};

#endif // BAG_H
