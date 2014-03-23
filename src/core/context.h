#ifndef H_CONTEXT_INCLUDED
#define H_CONTEXT_INCLUDED

#include <SDL2/SDL.h>

typedef enum {
    BTN_STATE_NONE,
    BTN_STATE_PRESSED,
    BTN_STATE_CLICKED,
    BTN_STATE_RELEASED = BTN_STATE_CLICKED,
    BTN_STATE_HOVER,
    BTN_STATE_COUNT
} buttonstate_e;

typedef enum {
    MOUSE_BTN_L = SDL_BUTTON_LEFT,
    MOUSE_BTN_R = SDL_BUTTON_RIGHT,
    MOUSE_BTN_M = SDL_BUTTON_MIDDLE,
    MOUSE_BTN_COUNT = 5
} mousebutton_e;

typedef enum {
    EVENT_NONE = 0,
    EVENT_USE_MOUSE = 0x1,
    EVENT_USE_KEYBOARD = 0x2
} eventflag_t;

char InitializeSDLContext(int w, int h, char const * title);

void DestroySDLContext(void);

char UpdateSDLContext(void);

buttonstate_e GetMouseState(mousebutton_e btn, int * x, int * y);

buttonstate_e GetKeyState(SDL_Scancode key);

void SetContextEvent(eventflag_t flags);

SDL_Window * GetSDLContextWindow(void);

void Message(char const * text);

#endif /* H_CONTEXT_INCLUDED */
