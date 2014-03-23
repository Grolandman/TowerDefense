#include "text.h"

statictext_t * NewStaticText(void)
{
    statictext_t * out = malloc(sizeof(statictext_t));

    if (out) {
        out->wid = NewWidget(NULL);
        if (out->wid) {
            out->str = NewString();
            if (out->str) {
                out->wid->remove = RemoveStaticText;
                out->wid->render = RenderStaticText;
                out->wid->that = out;
            } else {
                DeleteWidget(out->wid);
            }
        } else {
            free(out);
        }
    }

    return out;
}

void RemoveStaticText(widget_t * wid)
{
    if (wid) {
        statictext_t * tmp = wid->that;
        if (tmp) {
            DelString(tmp->str);
            free(tmp);
        }
    }
}

void DeleteStaticText(statictext_t * text)
{
    if (text) {
        DeleteWidget(text->wid);
    }
}

void RenderStaticText(widget_t * wid)
{
    if (wid) {
        statictext_t * tmp = wid->that;
        if (tmp) {
            char * t = StringCStr(tmp->str);
            RenderText(tmp->font,wid->rect.x,wid->rect.y,t);
        }
    }
}

void SetStaticText(statictext_t * text, char const * str)
{
    if (text) {
        if (text->wid) {
            GetTextSize(text->font,str,&text->wid->rect.w,&text->wid->rect.w);
        }

        SetStringStr(text->str,str);
    }
}

void SetStaticTextFont(statictext_t * text, bitmapfont_t * font)
{
    if (text) {
        text->font = font;
        if (font && text->wid) {
            int * w = &text->wid->rect.w;
            int * h = &text->wid->rect.h;
            GetTextSize(font,StringCStr(text->str),w,h);
        }
    }
}

void SetStaticTextPosition(statictext_t * text, int x, int y)
{
    if (text) {
        if (text->wid) {
            text->wid->rect.x = x;
            text->wid->rect.y = y;
        }
    }
}

void ShowStaticText(statictext_t * text)
{
    if (text) {
        ShowWidget(text->wid);
    }
}

void GetStaticTextSize(statictext_t * text, int * w, int * h)
{
    if (text) {
        if (w) *w = text->wid->rect.w;
        if (h) *h = text->wid->rect.h;
    }
}

