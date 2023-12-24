#include "roledestroyblock.h"
void RoleChangeBlock::Enter()
{

}

void RoleChangeBlock::Execute()
{
	static ivec3 blockOffset[]{
		{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}
		};
	static int shift = Get_2_N_POW(SECTION_SIZE);
	for (RayMatch ray(camera.position, camera.front); ray.Distance() < BLOCK_TARGET_MAX_DISTANCE; ray.Step(0.1))
	{
		vec3 pos = ray.GetRay();
		pos = pos.floor();
		ivec3 pos_ = ivec3(pos.x, pos.y, pos.z);
		Block& block = world->GetBlock(pos_.x, pos_.y,pos_.z);
		//////////////////////////////////
		if (block.id == 0 || block.id == WATER||!is_destructable(block.id))continue;
		/////////////////////////////////
		BagItems[block.id]++;//放入背包
		////////////////检测该方块四周是否有水
		if (CheckBlockAroundIsWater(pos_)) {
			vector<ivec3>UpdatedsectionPos;
			ivec3 sectionPos = { pos_.x >> shift << shift,pos_.y >> shift << shift,pos_.z >> shift << shift };
			UpdatedsectionPos.push_back(sectionPos);
			block.id = WATER;
			FillWaterAroundWithWater(pos_,UpdatedsectionPos);
			for (auto& pos : UpdatedsectionPos)
			{
				if (!pos.equal(sectionPos))
				{
					auto* section = world->getSection(pos);
					GenerateFace(section, GetChunkNearChunks((Chunk*)section->Chunk));
					section->PossDataToGpu();
				}
			}
		}
		else block.id = 0;
		////////////////////////////////更新BlockcChanged
		UpdateBlockChangedMap(pos_, block);
		//////////////////////////////算出block所在的section以及其临近的section都将被更新
		UpdateSectionFaceNearBlock(pos_.x,pos_.y,pos_.z);
		break;
	}
    SwitchState(STOP);
}

void RoleChangeBlock::Exit()
{

}

bool CheckBlockAroundIsWater(const ivec3& pos_)
{
	if (world->GetBlock(pos_.x + 1, pos_.y, pos_.z).id == WATER ||
		world->GetBlock(pos_.x - 1, pos_.y, pos_.z).id == WATER ||
		world->GetBlock(pos_.x, pos_.y, pos_.z + 1).id == WATER ||
		world->GetBlock(pos_.x, pos_.y, pos_.z - 1).id == WATER
		)
		return 1;
	return 0;
}

void FillWaterAroundWithWater(ivec3& pos,vector<ivec3>& UpdatedSection)
{
	static int shift = Get_2_N_POW(SECTION_SIZE);
	static ivec2 offsets[] = { {1,0},{-1,0},{0,1},{0,-1} };
	for (auto& offset : offsets)
	{
		ivec3 pos_ = ivec3{ pos.x + offset.x,pos.y,pos.z + offset.y };
		auto& block = world->GetBlock(pos_.x, pos_.y, pos_.z);
		if (block.id == EMPTY)
		{
			block.id = WATER;
			UpdateBlockChangedMap(pos_,block);
			ivec3 sectionPos = ivec3{pos_.x>>shift<<shift,pos_.y>>shift<<shift,pos_.z>>shift<<shift};
			if (UpdatedSection.end() == find(UpdatedSection.begin(), UpdatedSection.end(),sectionPos))
				UpdatedSection.push_back(sectionPos);
			FillWaterAroundWithWater(pos_,UpdatedSection);
		}
	}
}
