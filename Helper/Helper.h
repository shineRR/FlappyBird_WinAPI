//
// Created by shine on 11/16/2020.
//

#ifndef FLAPPYBIRD_WINAPI_HELPER_H
#define FLAPPYBIRD_WINAPI_HELPER_H

#define GetCurrentDir _getcwd
#include <string>
#include "gdiplus.h"
#include "windows.h"
#include <dirent.h>

struct BirdProperties {
    WCHAR name[255];
    int price;
};

class Helper {
    public:
        static WCHAR * GetWCHAR(std::string text);
        static void DrawTextZ(Gdiplus::Graphics &graphics, std::string text, Gdiplus::RectF rectF);
        static std::string GetAssetsDir();
};


#endif //FLAPPYBIRD_WINAPI_HELPER_H
