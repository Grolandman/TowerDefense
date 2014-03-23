#include "button.h"
#include "../core/colision.h"

button_t * NewButton(SDL_Rect rect)
{
    button_t * out = malloc(sizeof(button_t));

    if (out) {
        out->widget = NewWidget(NULL);
        if (out->widget) {
            out->widget->rect = rect;
            out->state = BTN_STATE_NONE;
            out->widget->remove = RemoveButton;
            out->widget->update = UpdateButton;
            out->widget->that = out;
        } else {
            free(out);
            out = NULL;
        }
    }

    return out;
}

void RemoveButton(widget_t * wid)
{
    free(wid->that);
    wid->that = NULL;
}

void UpdateButton(widget_t * wid)
{
    int x, y, n = GetMouseState(MOUSE_BTN_L,&x,&y);
    button_t * btn = wid->that;

    if (ColisionPointBox(wid->rect,x,y)) {
        btn->state = (n == BTN_STATE_NONE) ? BTN_STATE_HOVER : n;
    } else {
        btn->state = BTN_STATE_NONE;
    }
}

void DeleteButton(button_t * btn)
{
    if (btn) {
        DeleteWidget(btn->widget);
    }
}

void ShowButton(button_t * btn)
{
    if (btn) {
        ShowWidget(btn->widget);
    }
}

void SetButtonText(button_t * btn,  statictext_t * text)
{
    if (btn && text) {
        if (SetWidgetParent(text->wid,btn->widget)) {
            int w, h, x, y;
            GetStaticTextSize(text,&w,&h);
            x = btn->widget->rect.x + btn->widget->rect.w * .5f - w * .5f;
            y = btn->widget->rect.y + btn->widget->rect.h * .5f - h * .5f;
            SetStaticTextPosition(text,x,y);
        }
    }
}

void SetButtonImage(button_t * btn, image_t * img)
{
    if (btn && img) {
        if (SetWidgetParent(img->wid,btn->widget)) {
            SDL_Rect * tmp = &btn->widget->rect;
            SetImageSize(img,tmp->w,tmp->h);
            SetImagePosition(img,tmp->x,tmp->y);
        }
    }
}
