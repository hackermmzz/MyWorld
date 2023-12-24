#ifndef WORKSPACEBOARD_H
#define WORKSPACEBOARD_H

#include <QFrame>
#include"ui_workspaceboard.h"
namespace Ui {
class WorkSpaceBoard;
}

class WorkSpaceBoard : public QFrame
{
    Q_OBJECT

public:
    explicit WorkSpaceBoard(QWidget *parent = nullptr);
    ~WorkSpaceBoard();
    Ui::WorkSpaceBoard *ui;

};

#endif // WORKSPACEBOARD_H
