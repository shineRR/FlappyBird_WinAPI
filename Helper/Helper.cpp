//
// Created by shine on 11/16/2020.
//

#include "Helper.h"

#include <utility>

void Helper::DrawTextZ(Gdiplus::Graphics &graphics, std::string text, Gdiplus::RectF rectF) {
    Gdiplus::FontFamily   fontFamily(L"Arial");
    Gdiplus::Font         font(&fontFamily, 12, Gdiplus::FontStyleBold, Gdiplus::UnitPoint);
    Gdiplus::SolidBrush   solidBrush(Gdiplus::Color(255, 255, 255, 255));
    graphics.DrawString(GetWCHAR(std::move(text)), -1, &font, rectF, nullptr, &solidBrush);
}

WCHAR * Helper::GetWCHAR(std::string text) {
    std::wstring wide_string = std::wstring(text.begin(), text.end());
    const wchar_t* result = wide_string.c_str();
    auto * wchar = new WCHAR[255];
    wcscpy(wchar, result);
    return wchar;
}

std::string Helper::GetAssetsDir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX );
    std::string currDir(buff);
    std::size_t pos = currDir.find_last_of('\\');      // position of "live" in str
    std::string assetDir = currDir.substr(0, pos).append("\\Assets\\");     // get from "live" to the end
    return assetDir;
}
