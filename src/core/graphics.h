#ifndef H_GRAPHICS_INCLUDED
#define H_GRAPHICS_INCLUDED

#include "context.h"
#include "list.h"

typedef struct {
    SDL_Point center;
    SDL_Rect rect;
    SDL_Rect sub;
    float angle;
    SDL_Texture * tex;
} sprite_t;

typedef enum {
    ANIM_TYPE_NORMAL,
    ANIM_TYPE_REVERSE,
    ANIM_TYPE_LOOP,
    ANIM_TYPE_LOOPREVERSE,
    ANIM_TYPE_COUNT
} animtype_e;

typedef struct {
    list_t * frames;
    int time;
    int delay;
    int frame;
    animtype_e type;
    char rev, loop;
} anim_t;

char LoadRenderer(void);

void DestroyRenderer(void);

void UpdateRenderer(void);


void RenderRect(SDL_Rect * rect, char filled);

void SetRenderDrawColor(unsigned r, unsigned g, unsigned b, unsigned a);


SDL_Texture * LoadTextureBMP(char const * file, Uint32 colorkey);

SDL_Texture * LoadTextureSurface(SDL_Surface * src);

void RenderTexture(SDL_Texture * tex, SDL_Rect * sub, SDL_Rect * rect);


void SetSpriteTexture(sprite_t * spr, SDL_Texture * tex);

void RenderSprite(sprite_t * spr);


anim_t * NewAnimation(animtype_e type, int delay);

void DeleteAnimation(anim_t * anim);

char AddAnimFrame(anim_t * anim, sprite_t * frame);

void ShowAnimation(anim_t * anim);

#endif /* H_GRAPHICS_INCLUDED */
