#ifndef H_TEXT_INCLUDED
#define H_TEXT_INCLUDED

#include "widget.h"
#include "../core/string.h"
#include "../core/font.h"

typedef struct {
    widget_t * wid;
    string_t * str;
    bitmapfont_t * font;
} statictext_t;

statictext_t * NewStaticText(void);

void DeleteStaticText(statictext_t * text);

void RemoveStaticText(widget_t * wid);

void RenderStaticText(widget_t * wid);

void ShowStaticText(statictext_t * text);

void SetStaticTextFont(statictext_t * text, bitmapfont_t * font);

void SetStaticText(statictext_t * text, char const * str);

void SetStaticTextPosition(statictext_t * text, int x, int y);

void GetStaticTextSize(statictext_t * text, int * w, int * h);

#endif /* H_TEXT_INCLUDED */
