#include "updatecameraubo.h"

void UpdateCameraUbo()
{
    //////////////////////////////////////////更新人物坐标和各种矩阵
    vec3 section_pos=(camera.position/SECTION_SIZE).floor()*SECTION_SIZE;
    camera_section=ivec3(int(section_pos.x),int(section_pos.y),int(section_pos.z));
    camera_chunk=ivec2(camera_section.x,camera_section.z);
    //////////////////////////////////////////更新摄像机
    UpdateCamera();
    //////////////////////////////////////////
    camera_ubo->bind();
    Matrix vp=camera_projection*camera_view;
    camera_ubo->setdata_arglist(0,vp,camera_projection,camera_view);
    //////////////////////////////////////////更新视锥体6个面
    UpdateCameraFace();
}

void UpdateCameraFace()
{
    ////////////////////////////////////////////////////////生成视锥矩阵的六个面
    //1生成8个点
    static float tan_half_theta=tan(CAMERA_PROJECTION_FOV*PI/360),
        half_height_fornt=tan_half_theta*CAMERA_PROJECTION_NEAR,
        half_height_back=tan_half_theta*CAMERA_PROJECTION_FAR;
    float  asp=window_width*1.0/window_height,
        half_width_front=asp*half_height_fornt,
        half_width_back=asp*half_height_back;
    vec3 point[8]={
        {-half_width_front,half_height_fornt,-CAMERA_PROJECTION_NEAR},
        {half_width_front,half_height_fornt,-CAMERA_PROJECTION_NEAR},
        {half_width_front,-half_height_fornt,-CAMERA_PROJECTION_NEAR},
        {-half_width_front,-half_height_fornt,-CAMERA_PROJECTION_NEAR},
        {-half_width_back,half_height_back,-CAMERA_PROJECTION_FAR},
        {half_width_back,half_height_back,-CAMERA_PROJECTION_FAR},
        {half_width_back,-half_height_back,-CAMERA_PROJECTION_FAR},
        {-half_width_back,-half_height_back,-CAMERA_PROJECTION_FAR}
    };
    for(int i=0;i<8;++i)
        point[i]=camera_view_inverse*vec4(point[i],1.0);
    vec3 line[]{
        point[6]-point[5],//0
        point[4]-point[5],//1
        point[1]-point[5],//2
        point[3]-point[7],//3
        point[4]-point[7],//4
        point[6]-point[7],//5
        point[1]-point[0],//6
        point[3]-point[0],//7
        point[5]-point[4],//8
        point[7]-point[4]//9
    };
    ////////////////////////////法线指向视锥体内部
    vec3 normal[]{
        line[2].cross(line[1]),
        line[3].cross(line[5]),
        line[6].cross(line[7]),
        line[9].cross(line[8]),
        line[4].cross(line[3]),
        line[0].cross(line[2])
    };
    //2生成六个面
    auto GenerateCameraFace=[&](int face_index,int i){
        auto&face=camera_face[face_index];
        face.vertex[0].position=point[i];
        face.vertex[0].normal=normal[face_index].normalize();
    };
    GenerateCameraFace(0,4);
    GenerateCameraFace(1,6);
    GenerateCameraFace(2,0);
    GenerateCameraFace(3,5);
    GenerateCameraFace(4,4);
    GenerateCameraFace(5,1);
    //////////////////////////////////////////
}

void UpdateCamera()
{
    //////////////////////////////////根据摄像机的模式来生成摄像机矩阵
    if (camera_mode == 0) {
      static float offset = 0.2;
      auto camera_pos = camera.position;
      camera.position +=camera.front*offset;
      camera_view= camera.getMatrix();
      camera.position= camera_pos;
    }
    else if (camera_mode == 1|| camera_mode == 2) {
        auto camera_pos = camera.position;
        auto finalPos = camera_pos;
        auto temp = real_camera_distance;
        for (;temp >= 0;temp -=1)
        {
            finalPos= camera_pos-camera.front * temp;
            if (!is_obstacle(world->GetBlock(floor(finalPos.x), floor(finalPos.y), floor(finalPos.z))))
                break;
        }
        if (temp>0)camera.position = finalPos;
        camera_view = camera.getMatrix();
        camera.position = camera_pos;
    }
    ///////////////////////////////////////
    camera_view_inverse = camera_view.inverse();
}


