#ifndef SYNC_H
#define SYNC_H
#include"Include.h"
class Sync
{
private:
    GLsync sync;
public:
    Sync();
    bool IsComplete();
    ~Sync();
};

#endif // SYNC_H
