#pragma once
#include"rolecontrollersource.h"
#include"../../BagButton.h"
#include"../Bag/BagGlobalSource.h"
#include"qmessagebox.h"
#include"../Bag/BagInit.h"
#include"../EventProcess.h"
#include"../Bag/UpdateWorkSpace.h"
struct RoleFunctionBlock:RoleAction
{
	// 通过 FSMAction 继承
	void Enter() override;
	void Execute() override;
	void Exit() override;
};
bool CheckAroundExistBlock(const ivec3& pos);
bool DealWithFunctionalBlock(const ivec3&pos,Block& block);
bool TNT_Function(const ivec3&pos);
bool WORKSPACE_Function();
void UpdateBagItem(int id,int nums);
vector<ivec3> TNT_BOOM(const ivec3& pos);//返回会被更新的section坐标
void BlockHit_Function(Block&block,const ivec3&pos);
void SetBlockFaceDir(Block& block);

