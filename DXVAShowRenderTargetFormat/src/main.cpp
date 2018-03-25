#include "DirectXManager.h"
#include "RenderTargetMap.h"

int main()
{
    DirectXManager directXManager;

    if (!directXManager.Init())
        return -1;

    auto device = directXManager.GetDevice();
    if (!device)
        return -1;

    RenderTargetMap rtm;

    rtm.Create(device);

    RenderTargetMap::PrintRTM(rtm.GetMap());

    directXManager.Deinit();

    return 0;
}

