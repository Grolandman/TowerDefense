#include "font.h"
#include <string.h>
#include <stdio.h>

struct bitmapfont_t {
    SDL_Texture * tex;
    SDL_Rect * glyphs;
    Uint32 space;
    Uint32 newline;
    char begin;
};

static Uint32 peekColor(SDL_Surface * surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            return *p;
            break;
        case 2:
            return *(Uint16 *)p;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;
        case 4:
            return *(Uint32 *)p;
            break;
        default:
            return 0;
    }
}

bitmapfont_t * NewBitmapFont(char const * bmp, Uint32 bckgd, char begin,
                             char end)
{
    bitmapfont_t * out = NULL;

    if (bmp) {
        out = malloc(sizeof(bitmapfont_t));
        if (out) {
            char fail = 1;
            SDL_Surface * tmp = SDL_LoadBMP(bmp);
            out->glyphs = NULL;
            out->tex = NULL;
            if (tmp) {
                int n = (end - begin)+1;
                int gw = tmp->w / n;
                out->glyphs = calloc(n,sizeof(SDL_Rect));
                if (out->glyphs) {
                    int i;
                    for (i=0 ; i<n ; i++) {
                        int x,y,start=0,end=gw;

                        out->glyphs[i].y = 0;
                        out->glyphs[i].h = tmp->h;
                        out->glyphs[i].w = gw;
                        out->glyphs[i].x = i * gw;

                        /* FIND START */
                        for (x=0 ; x<gw ; x++) {
                            start = i * gw + x;
                            for (y=0 ; y<tmp->h ; y++) {
                                if (peekColor(tmp,start,y) != bckgd) {
                                    out->glyphs[i].x = start;
                                    x = gw;
                                    y = tmp->h;
                                }
                            }
                        }

                        /* FIND END */
                        for (x=gw-1 ; x>=0 ; x--) {
                            for (y=0 ; y<tmp->h ; y++) {
                                end = i * gw + x;
                                if (peekColor(tmp,end,y) != bckgd) {
                                    out->glyphs[i].w = end - start + 1;
                                    x = -1;
                                    y = tmp->h;
                                }
                            }
                        }
                    }

                    SDL_SetColorKey(tmp,SDL_TRUE,bckgd);
                    out->tex = LoadTextureSurface(tmp);
                    SDL_FreeSurface(tmp);
                    if (out->tex) {
                        fail = 0;
                        out->begin = begin;
                        out->newline = 0;
                        out->space = 1;
                    }
                }

            }

            if (fail) {
                DeleteBitmapFont(out);
                out = NULL;
            }
        }
    }

    return out;
}

void DeleteBitmapFont(bitmapfont_t * font)
{
    if (font) {
        SDL_DestroyTexture(font->tex);
        free(font->glyphs);
        free(font);
    }
}

void RenderGlyph(bitmapfont_t * font, int x, int y, char glyph)
{
    if (font) {
        SDL_Rect * tmp = &font->glyphs[glyph - font->begin];
        SDL_Rect dst = *tmp;
        dst.x = x;
        dst.y = y;
        RenderTexture(font->tex,tmp,&dst);
    }
}

void RenderText(bitmapfont_t * font, int x, int y, char const * text)
{
    if (font && text) {
        int i, n = strlen(text);
        int dx = x;
        for (i=0 ; i<n ; i++) {
            if (text[i] == '\n') {
                y += font->glyphs[0].h + font->newline;
                dx = x;
            } else {
                RenderGlyph(font,dx,y,text[i]);
                dx += font->glyphs[text[i]-font->begin].w + font->space;
            }
        }
    }
}

void SetBitmapFontSpace(bitmapfont_t * font, int space)
{
    if (font) {
        font->space = space;
    }
}

void SetBitmapFontNewLine(bitmapfont_t * font, int newline)
{
    if (font) {
        font->newline = newline;
    }
}

void GetBitmapFontAttrib(bitmapfont_t * font, int * space, int * newline)
{
    if (font) {
        if (space) {
            *space = font->space;
        }
        if (newline) {
            *newline = font->newline;
        }
    }
}

void GetTextSize(bitmapfont_t * font, char const * text, int * w, int * h)
{
    if (font && text) {
        int ww = 0, hh = 0;
        int i, l=0, n = strlen(text);

        if (n) {
            hh = font->glyphs[0].h;
        }

        for (i=0 ; i<n ; i++) {
            if (text[i] == '\n') {
                if (l > ww) { ww = l; }
                l = 0;
                hh += font->glyphs[0].h + font->newline;
            } else {
                int len = font->glyphs[text[i]-font->begin].w;
                l += len + font->space;
            }
        }

        ww = (l > ww) ? l : ww;

        if (w) { *w = ww; }
        if (h) { *h = hh; }
    }
}

