#include "frustumcull.h"
WorldNode* WorldRoot;
vector<Section*> &FrustumCull()
{
    static int HALF_CHUNK_RENDER_SIZE = CHUNK_RENDER_SIZE / 2;
    /////////////////////////////初始化WorldRoot
    static bool init = 0;
    if (!init) {
        init = 1;
        WorldRoot= BuildWorldNode(-HALF_CHUNK_RENDER_SIZE, HALF_CHUNK_RENDER_SIZE,0, CHUNK_SIZE,-HALF_CHUNK_RENDER_SIZE, HALF_CHUNK_RENDER_SIZE);
    }
    /////////////////////////////
    static vector<Section*> visible;
    visible.clear();
    //////////////////////////////////////
    Canculate(WorldRoot, visible);
    //////////////////////////////////////
    return visible;
}
int JudgeBoxIsInSamePlane(const vec3 *point, Face &face)
{
    bool flag_pos1=0,flag_pos2=0;
    float temp;
    vec3 dir;
    for(int i=0;i<8;++i)
    {
        auto&pos=point[i];
        dir=pos-face.vertex[0].position;
        temp=dir.dot(face.vertex[0].normal);
        if(temp<=0)flag_pos1=1;
        else flag_pos2=1;
        if(flag_pos1&&flag_pos2)return 0;
    }
    if(flag_pos1)return -1;
    else return 1;
}

WorldNode* BuildWorldNode(int x_start, int x_end, int y_start, int y_end, int z_start, int z_end)
{
    if (x_start >= x_end||y_start >= y_end||z_start >= z_end)return 0;
    WorldNode* node = new WorldNode;
    node->point[0] = ivec3(x_start * SECTION_SIZE, y_end * SECTION_SIZE, z_start * SECTION_SIZE);
    node->point[1]= ivec3(x_end * SECTION_SIZE, y_end * SECTION_SIZE, z_start * SECTION_SIZE);
    node->point[2]= ivec3(x_end * SECTION_SIZE, y_end * SECTION_SIZE, z_end * SECTION_SIZE);
    node->point[3] = ivec3(x_start * SECTION_SIZE, y_end * SECTION_SIZE, z_end * SECTION_SIZE);
    node->point[4] = ivec3(x_start * SECTION_SIZE, y_start * SECTION_SIZE, z_start * SECTION_SIZE);
    node->point[5] = ivec3(x_end * SECTION_SIZE, y_start * SECTION_SIZE, z_start * SECTION_SIZE);
    node->point[6] = ivec3(x_end * SECTION_SIZE, y_start * SECTION_SIZE, z_end * SECTION_SIZE);
    node->point[7] = ivec3(x_start * SECTION_SIZE, y_start * SECTION_SIZE, z_end * SECTION_SIZE);
    if (x_start + 1 == x_end && y_start + 1 == y_end && z_start + 1 == z_end)
    {
        for (auto& ele : node->child)ele = 0;
        return node;
    }
    int x_point[] = { x_start,floor((x_start + x_end)/2),x_end };
    int y_point[] = { y_start,floor((y_start + y_end)/2),y_end };
    int z_point[] = { z_start,floor((z_start + z_end)/2),z_end };
    int index = 0;
    for (int x = 0; x < 2; ++x)
    {
        for (int y = 0; y < 2; ++y)
        {
            for (int z = 0; z < 2; ++z)
            {
                node->child[index++] = BuildWorldNode(x_point[x],x_point[x + 1], y_point[y], y_point[y + 1], z_point[z], z_point[z + 1]);

            }
        }
    }
    return node;
}

void Canculate(WorldNode* node, vector<Section*>&store)
{
    bool flag = 1;
    vec3 offset = vec3(camera_chunk.x, 0, camera_chunk.y);
    for (auto& child:node->child)
    {
        if (!child)continue;
        flag = 0;
        ////////////////////////////////////////////////开始计算
        static vec3 points[8];
        ////////////////////////////////生成包围盒8个顶点
        for (int i = 0; i < 8; ++i)
        {
            auto& point = child->point[i];
            points[i] = vec3(point.x,point.y,point.z) + offset;
        }
        ////////////////////////////////
        bool flag2 = 1;
        for (int i = 0; i < 6; ++i)
        {
            if (JudgeBoxIsInSamePlane(points, camera_face[i]) == -1)
            {
                flag2 = 0;
                break;
            }
        }
        if (flag2)
            Canculate(child, store);
        ////////////////////////////////////////////////
    }
    if (flag)
    {
        //如果面还没产生或者压根没有面能被看到那就不渲染
        ivec3 pos = node->point[4];
        pos.x += camera_chunk.x;
        pos.z += camera_chunk.y;
        auto* section = world->getSection(pos);
        if (section == 0)return;
        if (section->IsFaceGenerateComplete==0||(section->face.size()==0 && section->waterFace.size() == 0))return;
        if (section->IsFaceLoadToGpu == 0)//如果还没把面加载到显存那就立刻加载
            section->PossDataToGpu();
        store.push_back(section);
    }
}