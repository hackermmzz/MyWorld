#include "roleFunctionBlock.h"

void RoleFunctionBlock::Enter()
{
}

void RoleFunctionBlock::Execute()
{
	static int MAX_HEIGHT = CHUNK_SIZE * SECTION_SIZE - 1;
	////////////////////一直射到一个方块为止或者超出射程
	Block* BlockHit = 0;
	ivec3 BlockPos;
	for (RayMatch ray(camera.position, camera.front); ray.Distance() < BLOCK_TARGET_MAX_DISTANCE; ray.Step(0.1))
	{
		vec3 pos = ray.GetRay();
		pos = pos.floor();
		/////////////////////////约束范围
		if (pos.y > MAX_HEIGHT || pos.y < 0)continue;
		//////////////////////////
		ivec3 pos_ = ivec3(pos.x, pos.y, pos.z);
		Block& block = world->GetBlock(pos_.x, pos_.y, pos_.z);
		////////////////////////////////////////
		if (block.id == WATER)continue;
		if (block.id == 0)
		{
			if (CheckAroundExistBlock(pos_))
			{
				BlockPos = pos_;
				BlockHit = &block;
			}
		}
		else if(is_functionalBlock(block.id))
		{
			if (DealWithFunctionalBlock(pos_, block)) {
				SwitchState(STOP);
				return;
			}
		}
	}
	/////////////////////////////////////////////
	if (BlockHit) BlockHit_Function(*BlockHit,BlockPos);
	////////////////////////////////////////////
	SwitchState(STOP);
}

void RoleFunctionBlock::Exit()
{
}

bool CheckAroundExistBlock(const ivec3& pos)
{
	static ivec3 direction[6] = { {0,0,1},{0,0,-1},{0,1,0},{0,-1,0},{1,0,0},{-1,0,0} };
	for (auto&dir: direction)
	{
		ivec3 pos_ = pos + dir;
		auto& block = world->GetBlock(pos_.x, pos_.y, pos_.z);
		if (block.id&&block.id!=WATER)return 1;
	}
	return 0;
}

bool DealWithFunctionalBlock(const ivec3&pos,Block& block)
{
	switch (block.id)
	{
	case TNT:
		return TNT_Function(pos);
	case WORKSPACE:
		return WORKSPACE_Function();
	}
	return 0;
}

bool TNT_Function(const ivec3& pos)
{
	static int shift = Get_2_N_POW(SECTION_SIZE);
	static int MAX_HEIGHT = SECTION_SIZE * CHUNK_SIZE - 1;
	////////////////////////////////////////判断当前所持item是否为火把
	if (itemBoard->ui->item[ItemBoardCurrentSelectedItem]->id != TORCH)return 0;
	////////////////////////////////////////
	auto DestroyedBlock = TNT_BOOM(pos);
	set<ivec3>SectionNeedUpdate;
	////////////////////////////////////////先获取所有需要更新的section
	for (auto& pos : DestroyedBlock)
	{
		auto sectionPos = ivec3(pos.x >> shift << shift, pos.y >> shift << shift, pos.z >> shift << shift);
		SectionNeedUpdate.insert(sectionPos);
		//上
		if (sectionPos.y + SECTION_SIZE < MAX_HEIGHT && pos.y % (SECTION_SIZE - 1) == 0)SectionNeedUpdate.insert(sectionPos+ ivec3{ 0,SECTION_SIZE,0 });
		//下
		if (sectionPos.y - SECTION_SIZE >= 0 && pos.y % SECTION_SIZE == 0)SectionNeedUpdate.insert(sectionPos - ivec3{ 0,SECTION_SIZE,0 });
		//前
		if (pos.z % (SECTION_SIZE - 1) == 0)SectionNeedUpdate.insert(sectionPos + ivec3{ 0,0,SECTION_SIZE });
		//后
		if (pos.z % (SECTION_SIZE) == 0)SectionNeedUpdate.insert(sectionPos - ivec3{ 0,0,SECTION_SIZE });
		//左
		if (pos.x % SECTION_SIZE == 0)SectionNeedUpdate.insert(sectionPos - ivec3{ SECTION_SIZE,0,0 });
		//右
		if (pos.x % (SECTION_SIZE - 1) == 0)SectionNeedUpdate.insert(sectionPos + ivec3{ SECTION_SIZE,0,0 });
	}
	//////////////////////////////////////////////////////
	for (auto& sectionPos : SectionNeedUpdate)
	{
		auto* section = world->getSection(sectionPos);
		if (section == 0)continue;
		GenerateFace(section, GetChunkNearChunks((Chunk*)(section->Chunk)));
		section->PossDataToGpu();
	}
	//////////////////////////////////////////
	return 1;
}

vector<ivec3> TNT_BOOM(const ivec3& pos)
{
	static int DISTANCE_2 = TNT_BOOM_RANGE * TNT_BOOM_RANGE;
	static int MAX_HEIGHT = SECTION_SIZE * CHUNK_SIZE - 1;
	///////////////////////////////////
	vector<ivec3>DestroyedBlock;
	//////////////////////////////////////先将自身改成0
	world->SetBlock(pos.x, pos.y, pos.z, 0, 0);
	//////////////////////////////////////
	for (int x = pos.x - TNT_BOOM_RANGE; x <= pos.x + TNT_BOOM_RANGE; ++x)
	{
		for (int y = pos.y - TNT_BOOM_RANGE; y <= pos.y + TNT_BOOM_RANGE; ++y)
		{
			for (int z = pos.z - TNT_BOOM_RANGE; z <= pos.z + TNT_BOOM_RANGE; ++z)
			{
				int ox, oy, oz;
				ox = x - pos.x, oy = y - pos.y, oz = z - pos.z;
				float distance = ox * ox + oy * oy + oz * oz;
				if (distance > DISTANCE_2 || y > MAX_HEIGHT || y < 0)continue;
				//////////////////////////////////////////
				auto pos = ivec3{ x, y, z };
				auto& block = world->GetBlock(x, y, z);
				//////////////////////如果所炸方块为TNT,则引爆该TNT
				if (block.id == TNT)
				{
					auto DestroyedBlock_ = TNT_BOOM(pos);
					for (auto& itr : DestroyedBlock_)DestroyedBlock.push_back(itr);
					}
				/////////////////////
				else if (is_destructable(block.id)) {
					BagItems[block.id]++;
					block.id = 0;
				}
				UpdateBlockChangedMap(pos, block);
				DestroyedBlock.emplace_back(pos);
				//////////////////////////////////////////
			}
		}
	}
	//////////////////////////////////////////////////
	return DestroyedBlock;
}

void BlockHit_Function(Block& block, const ivec3& pos)
{
	///////////////////////
	auto&id = itemBoard->ui->item[ItemBoardCurrentSelectedItem]->id;
	if (BagItems[id]==0)return;
	///////////////////////检测所放位置是否已经和人物位置冲突
	vec3 center = vec3(camera.position.x, camera.position.y - RoleBox.h/2, camera.position.z);
	AABB roleBoxAABB(center, vec3(RoleBox.r * 2), 1);
	AABB blockAABB(vec3(pos.x, pos.y, pos.z) + vec3(0.5, 0.5, 0.5), vec3(1), 1);
	if (roleBoxAABB.IsCollide(blockAABB))return;
	////////////////////////////
	BagItems[id]--;
	block.id = id;
	SetBlockFaceDir(block);//设置面朝向
	//////////////////////
	UpdateBlockChangedMap(pos, block);
	//////////////////////
	UpdateSectionFaceNearBlock(pos.x,pos.y,pos.z);
}

void SetBlockFaceDir(Block& block)
{
	if (is_NotBlock(block.id))return;
	////////////////////////////////////
	auto& dir = camera.front;
	if (abs(dir.x) > abs(dir.z))
	{
		block.meta = dir.x < 0 ? 5 : 4;
	}
	else
	{
		block.meta = dir.z < 0 ? 2 : 3;
	}
}

bool WORKSPACE_Function()
{
	//////////////释放鼠标
	EventQueue.push(ESCAPE_PRESS);
	//////////////重置工作台
	UpdateWorkSpace();
	//////////////
	workSpaceBoard->show();
	//////////////
	return 1;
}

void UpdateBagItem(int id, int nums)
{

}









