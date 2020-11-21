//
// Created by shine on 11/16/2020.
//

#ifndef FLAPPYBIRD_WINAPI_SHOP_H
#define FLAPPYBIRD_WINAPI_SHOP_H

#include "../../Bird/Bird.h"
#include "../../Helper/Helper.h"
#include "../../Pipe/Pipe.h"

class Shop {
    private:
        Bird* bird;
        Pipe* pipe;
        ItemProperties itemProperties[5] = {{0, L"redbird-midflap.png",    2},
                                            {0, L"yellowbird-midflap.png", 5},
                                            {0, L"bluebird-midflap.png",   10},
                                            {1, L"pipe-red.png", 50},
                                            {1, L"pipe-green.png", 50}};
    public:
        Shop(Bird * _bird, Pipe* _pipe);
        Shop() = default;
        void DrawShop(HDC &memDC, RECT windowRect);
        int BuyItem(int i, int coins);
};


#endif //FLAPPYBIRD_WINAPI_SHOP_H
