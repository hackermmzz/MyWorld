#include "DrawBag.h"
void DrawBag(bool isdraw)
{
	if (isdraw)
	{
		////////////////////////////设置表格里面的元素
		for (int i = 1; i < ITEM_NUMS; ++i)
		{
			int r = i / BagColumn, c = i % BagColumn;
			auto* widget = MyBag->ui->bag->cellWidget(r, c);
			auto* NumLabel = widget->findChild<QLabel*>("num");
			NumLabel->setText(to_string(BagItems[i]).c_str());
		}
		///////////////////////////
		EventQueue.push(3);
		MyBag->show();
	}
	else
	{
		EventQueue.push(3);
		MyBag->hide();
	}
}
