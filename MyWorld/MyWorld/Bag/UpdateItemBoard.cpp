#include "UpdateItemBoard.h"

void UpdateItemBoard()
{
	auto& items = itemBoard->ui->item;
	auto& nums = itemBoard->ui->num;
	for (int i = 0; i < 9; ++i)
	{
		int&item_nums = BagItems[items[i]->id];
		if (item_nums == 0)
			items[i]->setIcon(ItemIcons[0], 0);
		nums[i]->setText(to_string(item_nums).c_str());	
	}
}
