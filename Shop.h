#ifndef SHOP_H
#define SHOP_H
#include "game.h"
extern bool paused,clicked;
extern SDL_Surface *shop,*cursor;
extern int cursorState;
void LoadShopAssets();
void RenderShop();
void UpdateShop();
int ProcessingCursorLocation(int mouseX, int mouseY);
void HandleShopEvent();
#endif