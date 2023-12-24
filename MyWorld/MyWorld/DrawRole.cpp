#include "DrawRole.h"

void DrawRole()
{
	static bool init = 0;
	static Program* program;
	static Model* model;
	if (!init)
	{
		init = 1;
		program = new Program("Src/Shader/Role/Role.vert", "Src/Shader/Role/Role.frag");
		program->setuniformblock("VP", CAMERA_UBO_BINDING);
		model = new Model("Src/Model/nxd/nxd.pmx",ANIMATION_ALL);
	}
	///////////////////如果是第一人称就不会绘制
	if (camera_mode == 0)return;
	Matrix roleMatrix;
	auto& camera_pos = camera.position;
	int offset = camera_mode == 1 ? -90 : 90;
	roleMatrix.scale(vec3(0.13, 0.13, 0.13));
	roleMatrix.rotate(vec3(0, 1, 0), -int(camera.yaw)%360+offset);
	roleMatrix.translate(vec3(camera_pos.x,camera_pos.y-RoleBox.h,camera_pos.z));
	program->bind();
	program->setmat4("model", roleMatrix);
	model->Draw(*program);
}
