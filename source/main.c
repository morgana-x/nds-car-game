// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2008-2024
//
// This file is part of Nitro Engine

#include <NEMain.h>

#include <filesystem.h>

#include <math.h>

#include "resource.h"

#include "scene.h"

int main(int argc, char *argv[])
{
    SceneData Scene = { 0 };

    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    // Init Nitro Engine in normal 3D mode
    NE_Init3D();

    // libnds uses VRAM_C for the text console, reserve A and B only
    NE_TextureSystemReset(0, 0, NE_VRAM_AB);
    // Init console in non-3D screen
    consoleDemoInit();

    if (!nitroFSInit(NULL))
    {
        printf("nitroFSInit failed.\nPress START to exit");
        while (1)
        {
            NE_WaitForVBL(0);

            scanKeys();
            if (keysHeld() & KEY_START)
                return 0;
        }
    }
    Resource_Init();
    Scene_Init(&Scene);

    while (1)
    {
        // Wait for next frame
        NE_WaitForVBL(0);

        //printf("\x1b[0;0HPad: Rotate.\n");
        
        Scene_Tick(&Scene);
             // Draw scene
        NE_ProcessArg(Scene_Draw3d, &Scene);
    }

    return 0;
}
