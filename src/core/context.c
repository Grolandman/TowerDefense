#include "context.h"
#include <string.h>

struct context_t {
    SDL_Window * win;
    int eventflags;
    char keys[SDL_NUM_SCANCODES];
    struct {
        int x, y;
        char btn[MOUSE_BTN_COUNT];
    } mouse;
} s_context;

char InitializeSDLContext(int w, int h, char const * title)
{
    char out = 0;

    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
        #define CENTERED SDL_WINDOWPOS_CENTERED
        s_context.win = SDL_CreateWindow(title,CENTERED,CENTERED,w,h,0);
        #undef  CENTERED
        if (s_context.win) {
            memset(s_context.keys,0,SDL_NUM_SCANCODES);
            memset(&s_context.mouse,0,MOUSE_BTN_COUNT+2*sizeof(int));
            s_context.eventflags = EVENT_USE_KEYBOARD | EVENT_USE_MOUSE;
            out = 1;
        }
    }

    return out;
}

void DestroySDLContext(void)
{
    SDL_DestroyWindow(s_context.win);
    SDL_Quit();
}

char UpdateSDLContext(void)
{
    SDL_Event event;
    char out = 1;
    char k = s_context.eventflags & EVENT_USE_KEYBOARD;
    char m = s_context.eventflags & EVENT_USE_MOUSE;

    if (k) { memset(s_context.keys,BTN_STATE_NONE,SDL_NUM_SCANCODES); }
    if (m) { memset(s_context.mouse.btn,BTN_STATE_NONE,MOUSE_BTN_COUNT); }

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (k) {
                    s_context.keys[event.key.keysym.scancode]
                        = BTN_STATE_PRESSED;
                } break;
            case SDL_KEYUP:
                if (k) {
                    s_context.keys[event.key.keysym.scancode]
                        = BTN_STATE_RELEASED;
                } break;
            case SDL_MOUSEBUTTONDOWN:
                if (m) {
                    s_context.mouse.btn[event.button.button]
                        = BTN_STATE_PRESSED;
                } break;
            case SDL_MOUSEBUTTONUP:
                if (m) {
                    s_context.mouse.btn[event.button.button]
                        = BTN_STATE_CLICKED;
                } break;
            case SDL_MOUSEMOTION:
                if (m) {
                    s_context.mouse.x = event.motion.x;
                    s_context.mouse.y = event.motion.y;
                }
                break;
            case SDL_QUIT:
                out = 0;
            default:
                break;
        }
    }

    return out;
}

buttonstate_e GetMouseState(mousebutton_e btn, int * x, int * y)
{
    if (x) { *x = s_context.mouse.x; }
    if (y) { *y = s_context.mouse.y; }

    return s_context.mouse.btn[btn];
}

buttonstate_e GetKeyState(SDL_Scancode key)
{
    return s_context.keys[key];
}

void SetContextEvent(eventflag_t flags)
{
    s_context.eventflags = flags;
}


SDL_Window * GetSDLContextWindow(void)
{
    return s_context.win;
}

void Message(char const * text)
{
    SDL_ShowSimpleMessageBox(0,"",text,s_context.win);
}

