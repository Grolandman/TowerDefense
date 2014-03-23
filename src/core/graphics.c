#include "graphics.h"

static SDL_Renderer * s_renderer = NULL;

SDL_Texture * LoadTextureSurface(SDL_Surface * src)
{
    return (src) ? SDL_CreateTextureFromSurface(s_renderer,src) : NULL;
}

void RenderTexture(SDL_Texture * tex, SDL_Rect * sub, SDL_Rect * rect)
{
    if (s_renderer) {
        SDL_RenderCopy(s_renderer,tex,sub,rect);
    }
}

char LoadRenderer(void)
{
    char flags = (SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    s_renderer = SDL_CreateRenderer(GetSDLContextWindow(),-1,flags);

    return (s_renderer) ? 1 : 0;
}

void DestroyRenderer(void)
{
    SDL_DestroyRenderer(s_renderer);
}

void UpdateRenderer(void)
{
    SDL_RenderPresent(s_renderer);

    SDL_SetRenderDrawColor(s_renderer,0,0,0,255);
    SDL_RenderClear(s_renderer);
}

void RenderRect(SDL_Rect * rect, char filled)
{
    if (filled) {
        SDL_RenderFillRect(s_renderer,rect);
    } else {
        SDL_RenderDrawRect(s_renderer,rect);
    }
}

anim_t * NewAnimation(animtype_e type, int delay)
{
    anim_t * out = malloc(sizeof(anim_t));

    if (out) {
        out->type = type;
        out->frame = 0;
        out->delay = delay;
        out->rev = 0;
        out->frames = NewList();
        if (!out->frames) {
            free(out);
            out = NULL;
        }
    }

    return out;
}

void DeleteAnimation(anim_t * anim)
{
    if (anim) {
        DelList(anim->frames);
        free(anim);
    }
}

char AddAnimFrame(anim_t * anim, sprite_t * frame)
{
    char out = 0;

    if (anim && frame) {
        if (PushBackListData(anim->frames,frame)) {
            out = 1;
        }
    }

    return out;
}

static void UpdateAnim_Normal(anim_t * anim)
{
    if (anim->frame < ListSize(anim->frames)) {
        anim->frame++;
    }
}

static void UpdateAnim_Reverse(anim_t * anim)
{
    if (anim->frame == ListSize(anim->frames)) {
        anim->rev = 1;
    } else if (anim->frame == 0 && anim->rev) {
        return;
    }

    anim->frame += (anim->rev) ? -1 : 1;
}

static void UpdateAnim_Loop(anim_t * anim)
{
    if (anim->frame == ListSize(anim->frames)) {
        anim->frame = 0;
    } else {
        anim->frame++;
    }
}

static void UpdateAnim_LoopReverse(anim_t * anim)
{
    if (anim->frame == ListSize(anim->frames)) {
        anim->rev = 1;
    } else if (anim->frame == 0 && anim->rev) {
        anim->rev = 0;
    }

    anim->frame += (anim->rev) ? -1 : 1;
}

static void (*UpdateAnimFunc[ANIM_TYPE_COUNT])(anim_t * anim) = {
    UpdateAnim_Normal,
    UpdateAnim_Reverse,
    UpdateAnim_Loop,
    UpdateAnim_LoopReverse
};

void ShowAnimation(anim_t * anim)
{
    if (anim) {
        RenderSprite(ListAt(anim->frames,anim->frame));

        if (SDL_GetTicks() - anim->time > anim->delay) {
            UpdateAnimFunc[anim->type](anim);
        }
    }
}

SDL_Texture * LoadTextureBMP(char const * file, Uint32 colorkey)
{
    SDL_Texture * out = NULL;
    SDL_Surface * tmp = SDL_LoadBMP(file);
    if (tmp) {
        SDL_SetColorKey(tmp,SDL_TRUE,colorkey);
        out = SDL_CreateTextureFromSurface(s_renderer,tmp);
        SDL_FreeSurface(tmp);
    }

    return out;
}

void SetSpriteTexture(sprite_t * spr, SDL_Texture * tex)
{
    if (spr) {
        if (tex) {
            SDL_QueryTexture(tex,NULL,NULL,&spr->rect.w,&spr->rect.h);
            spr->center.x = spr->rect.w * .5f - 1;
            spr->center.y = spr->rect.h * .5f - 1;
            spr->angle = 0.f;
            spr->sub.x = spr->sub.y = 0;
            spr->sub.w = spr->rect.w;
            spr->sub.h = spr->rect.h;
        } else {
            memset(spr,0,sizeof(sprite_t));
        }

        spr->tex = tex;
    }
}

void RenderSprite(sprite_t * spr)
{
    if (spr) {
        if (spr->tex) {
            SDL_RenderCopyEx(s_renderer,spr->tex,&spr->rect,&spr->sub,
                             spr->angle,&spr->center,SDL_FLIP_NONE);
        }
    }
}

void SetRenderDrawColor(unsigned r, unsigned g, unsigned b, unsigned a)
{
    SDL_SetRenderDrawColor(s_renderer,r,g,b,a);
}
