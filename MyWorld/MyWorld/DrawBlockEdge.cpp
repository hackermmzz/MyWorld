#include "DrawBlockEdge.h"
void DrawBlockEdge()
{
	static bool init = 0;
	static Program* program;
	static Vao* vao;
	static Vbo* vbo;
	static Ebo* ebo;
	if (!init)
	{
		init = 1;
		program = new Program("Src/Shader/BlockEdge/BlockEdge.vert","Src/Shader/BlockEdge/BlockEdge.frag");
		program->setuniformblock("VP", CAMERA_UBO_BINDING);
		vao = new Vao;
		vec3 pos[]{
			{0,1,0},{1,1,0},{1,1,1},{0,1,1},
			{0,0,0},{1,0,0},{1,0,1},{0,0,1}
		};
		GLuint indices[]{
		0,1,1,2,2,3,3,0,
		4,5,5,6,6,7,7,4,
		3,7,2,6,
		0,4,1,5,
		};
		vbo = new Vbo(sizeof(pos),pos);
		vbo->setpoint(0, GL_FLOAT, 3, sizeof(GLfloat)*3, 0);
		ebo = new Ebo(sizeof(indices) / sizeof(GLuint), indices);
		vao->unbind();
	}
	//////////////////////////////////////////根据摄像机得到目标
	static ivec3 blockOffset[]{
		{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}
	};
	vec3 pos;
	bool flag = 0;
	for (RayMatch ray(camera.position, camera.front); ray.Distance() < BLOCK_TARGET_MAX_DISTANCE; ray.Step(0.1))
	{
		pos = ray.GetRay();
		pos = pos.floor();
		//////////////////////判断是否比最高高度还高
		static int MAX_HEIGHT = CHUNK_SIZE * SECTION_SIZE-1;
		if (pos.y > MAX_HEIGHT)continue;
		////////////////////
		Block& block = world->GetBlock(pos.x,pos.y,pos.z);
		/////////////////////////////////判断是否是水
		if (block.id&&block.id!=WATER)
			flag = 1;
		if (flag)break;
	}
	//////////////////////////////////////////
	if (!flag)return;
	api->glEnable(GL_DEPTH_TEST);
	api->glLineWidth(8.0);
	vao->bind();
	program->bind();
	program->setvec3("offset", pos);
	api->glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
	api->glLineWidth(2.0);
}
