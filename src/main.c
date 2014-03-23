#include "gui.h"

int main(int argc, char *argv[])
{
    InitializeSDLContext(640,480,"Tower Denfense");
    SetContextEvent(EVENT_USE_MOUSE);
    LoadRenderer();

    UpdateRenderer();

    SDL_Delay(2000);

    DestroyRenderer();

    return 0;
}
