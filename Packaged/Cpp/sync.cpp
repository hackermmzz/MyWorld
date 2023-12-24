#include "Include/sync.h"

Sync::Sync()
{
    sync=api->glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
}

bool Sync::IsComplete()
{
    auto state=api->glClientWaitSync(sync,0,GL_TIMEOUT_IGNORED);
    return state==GL_ALREADY_SIGNALED||state==GL_CONDITION_SATISFIED;
}

Sync::~Sync()
{
    if(sync)api->glDeleteSync(sync);
}
