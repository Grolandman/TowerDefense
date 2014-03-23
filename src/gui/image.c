#include "image.h"
#include <string.h>

image_t * NewImage(void)
{
    image_t * out = malloc(sizeof(image_t));

    if (out) {
        out->wid = NewWidget(NULL);
        if (out->wid) {
            SetImageSprite(out,NULL);
            out->wid->render = RenderImage;
            out->wid->that = out;
        }
    }

    return out;
}

void DeleteImage(image_t * img)
{
    if (img) {
        DeleteWidget(img->wid);
    }
}

void RemoveImage(widget_t * wid)
{
    if (wid) {
        free(wid->that);
    }
}

void RenderImage(widget_t * wid)
{
    if (wid) {
        image_t * tmp = wid->that;
        if (tmp) {
            RenderSprite(&tmp->spr);
        }
    }
}

void ShowImage(image_t * img)
{
    if (img) {
        ShowWidget(img->wid);
    }
}

void SetImageSprite(image_t * img, sprite_t * spr)
{
    if (img) {
        if (spr) {
            img->spr = *spr;
        } else {
            SetSpriteTexture(&img->spr,NULL);
        }

        img->wid->rect = spr->rect;
    }
}

void SetImageSize(image_t * img, int w, int h)
{
    if (img) {
        if (w > 0) img->wid->rect.w = w;
        if (h > 0) img->wid->rect.h = h;
        img->spr.rect.w = img->wid->rect.w;
        img->spr.rect.h = img->wid->rect.h;
    }
}

void SetImagePosition(image_t * img, int x, int y)
{
    if (img) {
        img->wid->rect.x = x;
        img->wid->rect.y = y;
        img->spr.rect.x = x;
        img->spr.rect.y = y;
    }
}
