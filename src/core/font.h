#ifndef H_FONT_INCLUDED
#define H_FONT_INCLUDED

#include "graphics.h"

typedef struct bitmapfont_t bitmapfont_t;

bitmapfont_t * NewBitmapFont(char const * bmp, Uint32 bckgd, char begin,
                             char end);

void DeleteBitmapFont(bitmapfont_t * font);

void RenderText(bitmapfont_t * font, int x, int y, char const * text);

void SetBitmapFontSpace(bitmapfont_t * font, int space);

void SetBitmapFontNewLine(bitmapfont_t * font, int newline);

void GetBitmapFontAttrib(bitmapfont_t * font, int * space, int * newline);

void GetTextSize(bitmapfont_t * font, char const * text, int * w, int * h);

void RenderGlyph(bitmapfont_t * font, int x, int y, char glyph);

#endif /* H_FONT_INCLUDED */
