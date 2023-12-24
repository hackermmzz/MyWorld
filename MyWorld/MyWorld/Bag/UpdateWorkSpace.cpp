#include "UpdateWorkSpace.h"

void UpdateWorkSpace()
{
	auto* Bag = workSpaceBoard->ui->Bag;
	for (int i = 0; i < ITEM_NUMS; ++i)
	{
		int r = i / BagColumn, c = i % BagColumn;
		auto* widget = Bag->cellWidget(r, c);
		auto* num = widget->findChild<QLabel*>("number");
		num->setText(to_string(BagItems[i]).c_str());
	}
	for (auto& source : workSpaceBoard->ui->source)
	{
		source->setIcon(ItemIcons[0], 0);
	}
	workSpaceBoard->ui->target->setIcon(ItemIcons[0], 0);
}
