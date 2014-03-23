#include "widget.h"

static void updateWidget(widget_t * wid)
{
    (void)wid;
}

static void renderWidget(widget_t * wid)
{
    (void)wid;
}

static void removeWidget(widget_t * wid)
{
    int i, n = ListSize(wid->children);
    for (i=0 ; i<n ; i++) {
        widget_t * tmp = ListAt(wid->children,i);
        tmp->remove(tmp);
        removeWidget(tmp);
    }

    DelList(wid->children);
    free(wid);
}

widget_t * NewWidget(widget_t * parent)
{
    widget_t * out = malloc(sizeof(widget_t));

    if (out) {
        out->children = NewList();
        if (out->children) {
            memset(&out->rect,0,sizeof(SDL_Rect));
            out->that = NULL;
            out->parent = NULL;
            out->state = WIDGET_ACTIVE;

            out->remove = removeWidget;
            out->render = renderWidget;
            out->update = updateWidget;
        } else {
            free(out);
            out = NULL;
        }
    }

    return out;
}

char SetWidgetParent(widget_t * wid, widget_t * parent)
{
    char out = 0;

    if (wid) {
        wid->parent = parent;
        if (parent) {
            /* check if not already linked */
            int i, n = ListSize(parent->children);
            for (i=0 ; i<n ; i++) {
                if (ListAt(parent->children,i) == wid) {
                    return (out = 1);
                }
            }
            /* if not, links the two widgets */
            if (PushBackListData(parent->children,wid)) {
                out = 1;
            }
        }
    }

    return out;
}

void ShowWidget(widget_t * wid)
{
    if (wid) {
        int i, n = ListSize(wid->children);
        if (wid->state & WIDGET_VISIBLE) {
            if (wid->state == WIDGET_ACTIVE) {
                wid->update(wid);
            }

            wid->render(wid);
        }

        for (i=0 ; i<n ; i++) {
            widget_t * tmp = ListAt(wid->children,i);
            ShowWidget(tmp);
        }
    }
}

void DeleteWidget(widget_t * wid)
{
    if (wid) {
        if (wid->that) {
            wid->remove(wid);
        }
        removeWidget(wid);
    }
}

void SetWidgetState(widget_t * wid, int state)
{
    if (wid) {
        wid->state = state;
        if (state == WIDGET_INACTIVE || state == WIDGET_VISIBLE) {
            int i, n = ListSize(wid->children);
            for (i=0 ; i<n ; i++) {
                widget_t * tmp = ListAt(wid->children,i);
                if (tmp) {
                    if (tmp->state != WIDGET_INACTIVE) {
                        tmp->state = state;
                    }
                }
            }
        }
    }
}

void SetWidgetPosition(widget_t * wid, int x, int y)
{
    if (wid) {
        wid->rect.x = x;
        wid->rect.y = y;
    }
}

