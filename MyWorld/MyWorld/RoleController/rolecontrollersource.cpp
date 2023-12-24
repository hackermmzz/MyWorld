#include "rolecontrollersource.h"
FSM<RoleState>*RoleJDFsm;
FSM<RoleState>* RoleMVFsm;
RoleFSM* RoleBuildFsm;
size_t RoleMoveDirection=0;
Cylinder RoleBox = { 0.4,1.8};
float RoleMoveSpeed = 4;
float RoleJumpSpeed = 5;


void UpdateSectionFaceNearBlock(int x, int y, int z)
{
	auto* chunk = world->getChunk(ivec2{ x,z }, 1);
	int sectionID = y / SECTION_SIZE;
	//本section
	auto* section = chunk->section[sectionID];
	auto cnc = GetChunkNearChunks(chunk);
	GenerateFace(section, cnc);
	section->PossDataToGpu();
	//上
	if ((y%(SECTION_SIZE - 1) == 0) && sectionID + 1 < CHUNK_SIZE)
	{
		auto* section = chunk->section[sectionID + 1];
		GenerateFace(section,cnc);
		section->PossDataToGpu();
	}
	//下
	if ((y % SECTION_SIZE == 0) && sectionID - 1 > 0)
	{
	auto* section = chunk->section[sectionID - 1];
	GenerateFace(section, cnc);
	section->PossDataToGpu();
	}
	//左
	if (x % SECTION_SIZE == 0)
	{
		auto* chunk = cnc.left;
		auto* section = chunk->section[sectionID];
		GenerateFace(section, GetChunkNearChunks(chunk));
		section->PossDataToGpu();
	}
	//右
	if (x % (SECTION_SIZE - 1) == 0)
	{
		auto* chunk = cnc.right;
		auto* section = chunk->section[sectionID];
		GenerateFace(section, GetChunkNearChunks(chunk));
		section->PossDataToGpu();	
	}
	//前
	if (z % (SECTION_SIZE - 1) == 0)
	{
		auto* chunk = cnc.front;
		auto* section = chunk->section[sectionID];
		GenerateFace(section, GetChunkNearChunks(chunk));
		section->PossDataToGpu();
	}
	//后
	if (z % SECTION_SIZE == 0)
	{
		auto* chunk = cnc.back;
		auto* section = chunk->section[sectionID];
		GenerateFace(section,GetChunkNearChunks(chunk));
		section->PossDataToGpu();
	}
}

void UpdateBlockChangedMap(const ivec3& pos, Block& block)
{
	////////////////////////////////////
	auto itr=BlockChanged.find(pos);
	if (itr == BlockChanged.end())
	{
		BlockChanged.insert({ pos,block });
	}
	else
	{
		itr->second = block;
	}
	/////////////////////////////////////如果是发光方块
	bool lightable = is_Lightable(block.id);
	if (block.id != EMPTY && !lightable)return;
	auto itr2 = LightBlock.find(pos);
	if (itr2==LightBlock.end()) {
		if (lightable)
			LightBlock.insert({ pos,block });
	}
	else LightBlock.erase(itr2);
}
