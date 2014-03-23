#ifndef H_WIDGET_INCLUDED
#define H_WIDGET_INCLUDED

#include "../core/context.h"
#include "../core/list.h"

typedef struct widget_t widget_t;
struct widget_t {
    void * that;
    void (*update)(widget_t * that);
    void (*render)(widget_t * that);
    void (*remove)(widget_t * that);
    widget_t * parent;
    list_t * children;

    SDL_Rect rect;
    #define WIDGET_INACTIVE 0x0
    #define WIDGET_VISIBLE  0x1
    #define WIDGET_ACTIVE   0x3
    int state;
};

widget_t * NewWidget(widget_t * parent);

char SetWidgetParent(widget_t * wid, widget_t * parent);

void ShowWidget(widget_t * wid);

void DeleteWidget(widget_t * wid);

void SetWidgetState(widget_t * wid, int state);

void SetWidgetPosition(widget_t * wid, int x, int y);

#endif /* H_WIDGET_INCLUDED */
