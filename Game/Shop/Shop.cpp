//
// Created by shine on 11/16/2020.
//

#include "Shop.h"

void Shop::DrawShop(HDC &memDC, RECT windowRect) {
    std::string assets = Helper::GetAssetsDir();
    double width = windowRect.right - windowRect.left;
    double height = windowRect.bottom - windowRect.top;
    double coefX = width / DEFAULT_WINDOW_WIDTH;
    double coefY = height / DEFAULT_WINDOW_HEIGHT;

    int shopWidth = int(width / 12 * coefX);
    int shopHeight = int(height / 12 * coefY);
    int shopX = int((width - shopWidth) / 8 * coefX);
    int shopY = int((height - shopHeight) / 8 * coefY) ;

    Gdiplus::Graphics graphics(memDC);
    for (int i = 0; i < 3; i++) {
        Gdiplus::Rect destRect(shopX, shopY, shopWidth, shopHeight);
        WCHAR * imageName = new WCHAR[255];
        wcscpy(imageName, Helper::GetWCHAR(assets));
        wcscat(imageName, itemProperties[i].name);
        Gdiplus::Image image(imageName);
        graphics.DrawImage(&image, destRect);
        Gdiplus::RectF rectF(shopX + 10, shopY + shopHeight + 20, 100 * coefX, 50 * coefY);
        std::string text(std::to_string(itemProperties[i].price));
        text += " GRIVNI";
        Helper::DrawTextZ(graphics, text, rectF);
        shopX += int(150 * coefX);
    }
    Gdiplus::RectF rectF(windowRect.right - 120 * coefX, 10.0f, 120 * coefX, 60 * coefY);
    std::string text("Esc to Menu");
    Helper::DrawTextZ(graphics, text, rectF);
}

Shop::Shop(Bird * _bird) {
    bird = _bird;
}

int Shop::BuyItem(int i, int coins) {
    if (i < 1 || i > sizeof(itemProperties)) return 0;
    std::string assets = Helper::GetAssetsDir();
    ItemProperties item = itemProperties[i - 1];
    if (coins >= item.price)
    {
        WCHAR * wchar = new WCHAR[255];
        wcscpy(wchar, Helper::GetWCHAR(assets));
        wcscat(wchar, item.name);
        bird->SetNewBird(wchar);
        return item.price;
    }
    return 0;
}
