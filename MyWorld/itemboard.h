#ifndef ITEMBOARD_H
#define ITEMBOARD_H
#include <QFrame>
#include"ui_itemboard.h"
#include"qevent.h"
namespace Ui {
class ItemBoard;
}

class ItemBoard : public QFrame
{
    Q_OBJECT

public:
    explicit ItemBoard(QWidget *parent = nullptr);
    ~ItemBoard();
    Ui::ItemBoard* ui;
};

#endif // ITEMBOARD_H
