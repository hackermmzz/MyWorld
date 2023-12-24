#include "BagButton.h"

BagButton::BagButton(QWidget* parent):QPushButton(parent)
{
    icon_ = 0;
    id = 0;
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void BagButton::setIcon(QIcon*icon,int id_)
{
    icon_ = icon;
    id = id_;
}


 void BagButton::paintEvent(QPaintEvent* event) {
    QPushButton::paintEvent(event);
    if (icon_ == 0)return;
    // ��ȡ��ť�ľ�������
    QRect rect = this->rect();
    // ����������
    QPainter painter(this);
    // ��ͼ����Ƶ���ť�У�ʹ�����������ť
   icon_->paint(&painter, rect, Qt::AlignCenter, QIcon::Normal, QIcon::On);
}
