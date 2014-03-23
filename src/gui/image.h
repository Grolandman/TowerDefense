#ifndef H_IMAGE_INCLUDED
#define H_IMAGE_INCLUDED

#include "widget.h"
#include "../core/graphics.h"

typedef struct {
    widget_t * wid;
    sprite_t spr;
} image_t;

image_t * NewImage(void);

void DeleteImage(image_t * img);

void RemoveImage(widget_t * wid);

void RenderImage(widget_t * wid);

void ShowImage(image_t * img);

void SetImageSprite(image_t * img, sprite_t * spr);

void SetImageSize(image_t * img, int w, int h);

void SetImagePosition(image_t * img, int x, int y);

#endif /* H_IMAGE_INCLUDED */
