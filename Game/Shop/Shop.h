//
// Created by shine on 11/16/2020.
//

#ifndef FLAPPYBIRD_WINAPI_SHOP_H
#define FLAPPYBIRD_WINAPI_SHOP_H

#include "../../Bird/Bird.h"
#include "../../Helper/Helper.h"

class Shop {
    private:
        Bird* bird;
        ItemProperties itemProperties[3] = {{L"redbird-midflap.png",    2},
                                            {L"yellowbird-midflap.png", 5},
                                            {L"bluebird-midflap.png",   10}};
        int price[3] = {1, 1, 1};
    public:
        Shop(Bird * _bird);
        Shop() = default;
        void DrawShop(HDC &memDC, RECT windowRect);
        int BuyItem(int i, int coins);
};


#endif //FLAPPYBIRD_WINAPI_SHOP_H
