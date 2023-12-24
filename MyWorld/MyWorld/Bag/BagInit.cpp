#include "BagInit.h"

void BagInit()
{
	///////////////初始化所有物品数量
	int ItemInitNum = 1;
	memset(BagItems, 0, sizeof(BagItems));
	for (int i = 1; i < ITEM_NUMS; ++i)
	{
		BagItems[i] = ItemInitNum;
	}
	///////////////获得转换表
	GenerateExchangeTable();
	/////////////////获得物品的图标
	GenerateAllBlockicons();
	////////////////初始化工作台
	WorkSpaceBoardInit();
	////////////////初始化物品框
	ItemBoardInit();
	///////////////初始化人物背包
	MyBagInit();
}

void GenerateExchangeTable()
{
	map<vector<int>, ivec2>table;
	//////////////////////////////////////
	table.insert({ vector<int>{CLOVER,DIRT},ivec2{GRASS,1000} });
	///////////////////////////////////////对转换表所有的元素重新排序
	for (auto itr = table.begin(); itr != table.end(); ++itr)
	{
		auto transition = itr->first;
		sort(transition.begin(), transition.end());
		TransitionTable.insert({ transition,itr->second });
	}
}

ivec2 FindExchangeTable(vector<int>& id)
{
	ivec2 res = { 0,0 };
	/////////////////////////////////////
	//排序所有的id
	sort(id.begin(), id.end());
	//从转换表里面查找对于的转换
	auto itr = TransitionTable.find(id);
	if (itr != TransitionTable.end())res = itr->second;
	////////////////////////////////////
	return res;
}

bool operator<(vector<int>& v1, vector<int>& v2)
{
	int s1 = v1.size(), s2 = v2.size();
	for (int i = 0; i < s1 && i < s2; ++i)
	{
		if (v1[i] < v2[i])return 1;
		else if (v1[i] > v2[i])return 0;
	}
	return s1 < s2;
}

void GenerateAllBlockicons()
{
	QImage blocks("Src/Img/block/terrain.png");
	ItemIcons=decltype(ItemIcons)(BagRow * BagColumn, 0);
	int image_width = blocks.width(), image_height = blocks.height();
	int itemWidth = image_width / BagColumn;
	int itemHeight = image_height / BagRow;
	for (int i = 0; i < ITEM_NUMS; ++i)
	{
		auto& block_uv = ITEM_UV[i];
		ivec2 pos;
		if (is_Distinguish_Front(i))pos = block_uv[2];
		else if (is_NotBlock(i))pos = block_uv[0];
		else pos = block_uv[0];
		int x = pos.x * image_width / BagColumn, y = (BagRow - pos.y - 1) * image_height / BagRow;
		auto itmePicture = blocks.copy(x, y, itemWidth, itemHeight);
		ItemIcons[i] = new QIcon(QPixmap::fromImage(itmePicture));
	}
}

void WorkSpaceBoardInit()
{
	workSpaceBoard = new WorkSpaceBoard(OpenglWidget);
	workSpaceBoard->setStyleSheet("background-color: rgba(255,255,255,120);");
	workSpaceBoard->focusWidget();
	workSpaceBoard->hide();
	////////////////////////////////////
	auto& ui = *workSpaceBoard->ui;
	////////////////绑定退出事件
	auto& exitRadioButton = ui.exit;
	QApplication::connect(ui.exit, &QRadioButton::clicked, [&]() {
		exitRadioButton->setChecked(0);
		workSpaceBoard->hide();
		EventQueue.push(ESCAPE_PRESS);
		});
	///////////////////绑定target按钮
	auto&targetButton = ui.target;
	targetButton->setIcon(ItemIcons[0], 0);
	QApplication::connect(targetButton, &BagButton::clicked, [&]() {
		auto* numberLabel = ui.number;
		int id = targetButton->id;
		if (id== 0)return;
		int r = id / BagColumn, c = id % BagColumn;
		auto* widget = ui.Bag->cellWidget(r, c);
		auto* child = widget->findChild<QLabel*>(QString("number"));
		int nums = child->text().toInt();
		int bonus = numberLabel->text().toInt();
		//////////////////////////////
		BagItems[id] += bonus;
		//////////////////////////////
		child->setText(to_string(nums + bonus).c_str());
		targetButton->setIcon(ItemIcons[0], 0);
		numberLabel->setText(to_string(0).c_str());
		////////////////////////////////
		////////////////清空source
		for (auto& source : ui.source)
		{
			int id = source->id;
			if (id == 0)continue;
			BagItems[id]--;
			source->setIcon(ItemIcons[0], 0);
		}
		});
	//////////////////设置target的图标和数量
	static auto setTaregtInfo = [&]() {
		static auto& icons = ItemIcons;
		vector<int>id;
		for (auto& source : ui.source)
		{
			if (source->id == 0)break;
			id.push_back(source->id);
		}
		auto data = FindExchangeTable(id);
		ui.target->setIcon(icons[data.x], data.x);
		ui.number->setText(to_string(data.y).c_str());
		};
	//////////////////设置source按钮
	auto& source = ui.source;
	int index = 0;
	for (auto& ele : source)
	{
		ele->setIcon(ItemIcons[0], 0);
		QApplication::connect(ele, &BagButton::clicked, [=]() {
			static auto* icons = &ItemIcons;
			if (ele->id == 0)return;
			int r = ele->id / BagRow, c = ele->id % BagColumn;
			auto* widget = ui.Bag->cellWidget(r, c);
			auto* child = widget->findChild<QLabel*>(QString("number"));
			int nums = child->text().toInt();
			child->setText(to_string(nums + 1).c_str());
			ele->setIcon((*icons)[0], 0);
			//////////////////设置target
			setTaregtInfo();
			});

	}
	////////////////设置物品的图片
	auto& Bag = ui.Bag;
	Bag->setSelectionMode(QAbstractItemView::SingleSelection);
	Bag->verticalHeader()->hide();
	Bag->horizontalHeader()->hide();
	Bag->setRowCount(BagRow);
	Bag->setColumnCount(BagColumn);
	for (int row = 0; row < BagRow; ++row)
	{
		for (int column = 0; column < BagColumn; ++column)
		{
			QWidget* widget = new QWidget(Bag);
			QVBoxLayout* layout = new QVBoxLayout(widget);
			widget->setLayout(layout);
			/////////////////////////
			int index = row * BagColumn + column;
			BagButton* image = new BagButton();
			QLabel* NumbersLabel = new QLabel(to_string(BagItems[index]).c_str());
			image->setObjectName(QString("icon"));
			NumbersLabel->setObjectName(QString("number"));
			image->setIcon(ItemIcons[0], 0);
			if (index < ITEM_NUMS)image->setIcon(ItemIcons[index], index);
			layout->addWidget(image);
			layout->addWidget(NumbersLabel);
			Bag->setCellWidget(row, column, widget);
			auto item = Bag->item(row, column);
			QApplication::connect(image, &BagButton::clicked, [&,image, NumbersLabel]() {
				int id = image->id;
				int nums = BagItems[id];
				if (nums == 0)return;
				for (auto& source : ui.source)
				{
					if (source->id == 0)
					{
						source->setIcon(ItemIcons[id],id);
						NumbersLabel->setText(to_string(nums - 1).c_str());
						break;
					}
				}
				////////////////////检测是否有对应的替换
				setTaregtInfo();
				});
		}
	}
	///////////////////////////////////
}

void ItemBoardInit()
{
	itemBoard = new ItemBoard(OpenglWidget);
	itemBoard->setStyleSheet("background-color: rgba(255,255,255,120);");
	itemBoard->setFocusPolicy(Qt::NoFocus);
	///////////////////////////
	auto& items = itemBoard->ui->item;
	auto& nums = itemBoard->ui->num;
	for (int i=0;i<9;++i)
	{
		auto& item = items[i];
		auto& num = nums[i];
		item->setIcon(ItemIcons[0], 0);
		num->setText("0");
		QApplication::connect(item, &BagButton::clicked,[&](){
		item->setIcon(ItemIcons[MyBagCurrentSelectedItem], MyBagCurrentSelectedItem);
		num->setText(to_string(BagItems[MyBagCurrentSelectedItem]).c_str());
		});
	}
	//第一个物品为工作台
	items[0]->setIcon(ItemIcons[WORKSPACE],WORKSPACE);
	items[0]->setStyleSheet("QPushButton { border: 2px solid black; }");
	nums[0]->setText(to_string(BagItems[WORKSPACE]).c_str());
	/////////////////////////
}

void MyBagInit()
{
	MyBag = new Bag(OpenglWidget);
	MyBag->setStyleSheet("background-color: rgba(255,255,255,120);");
	MyBag->setFocusPolicy(Qt::NoFocus);
	MyBag->hide();
	/////////////////////////////
	auto& bag = MyBag->ui->bag;
	bag->setRowCount(BagRow);
	bag->setColumnCount(BagColumn);
	////////////////////////////
	for (int r = 0; r < BagRow; ++r)
	{
		for (int c = 0; c < BagColumn; ++c)
		{
			QWidget* widget = new QWidget();
			QVBoxLayout* layout = new QVBoxLayout();
			BagButton* bagbutton = new BagButton;
			QLabel* label = new QLabel;
			widget->setLayout(layout);
			layout->addWidget(bagbutton);
			layout->addWidget(label);
			bag->setCellWidget(r,c,widget);
			bagbutton->setObjectName(QString("icon"));
			label->setObjectName(QString("num"));
			int id = r * BagColumn + c;
			id = id >= ITEM_NUMS?0:id;
			label->setText(to_string(BagItems[id]).c_str());
			bagbutton->setIcon(ItemIcons[id], id);
			////////////////绑定点击事件
			QApplication::connect(bagbutton, &BagButton::clicked, [&,bagbutton](){
				MyBagCurrentSelectedItem = bagbutton->id;
			});
		}
	}
}
