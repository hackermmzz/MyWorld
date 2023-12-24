#include "DrawSection.h"
void DrawSection(vector<Section*>& sections)
{
    Face_Render_Nums = 0;
    Section_Render_Nums= sections.size();
    //////////////////////绘制实体方块
    DrawCube(sections);
}

void DrawCube(vector<Section*>& sections)
{
    api->glEnable(GL_CULL_FACE);
    api->glCullFace(GL_BACK);
    api->glFrontFace(GL_CW);
    ////////////////////////////////////
    BlockRenderProgram->bind();
    BlockRenderProgram->setint("sampler", 0);
    BlockRenderProgram->setvec3("eye", camera.position);
    BLOCK_TEXTURE->bind(0);
    for (auto&section:sections)
    {
        if (section->face.size()==0)continue;
        /////////////////////////////////////////
        auto* a = section;
        section->vao->bind();
        Face_Render_Nums += section->face.size();
        api->glDrawElements(GL_TRIANGLES, 6 * section->face.size(), GL_UNSIGNED_INT, 0);
}
    //////////////////////////////
    api->glDisable(GL_CULL_FACE);
}
