#ifndef H_BUTTON_INCLUDED
#define H_BUTTON_INCLUDED

#include "widget.h"
#include "image.h"
#include "text.h"

typedef struct {
    widget_t * widget;
    buttonstate_e state;
} button_t;

button_t * NewButton(SDL_Rect rect);

void DeleteButton(button_t * btn);

void ShowButton(button_t * btn);

void UpdateButton(widget_t * wid);

void RemoveButton(widget_t * wid);

void SetButtonText(button_t * btn,  statictext_t * text);

void SetButtonImage(button_t * btn, image_t * img);

#endif /* H_BUTTON_INCLUDED */
