//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_GAME_H
#define FLAPPYBIRD_WINAPI_GAME_H

#include "algorithm"
#include "Scene/Scene.h"
#include "GameState.h"

class Game {
    private:
        const int downModifier = 1;
        const int upModifier = -1;
        WCHAR backgrounds[2][255] = {L"background-day.png",
                                     L"background-night.png"};
        void ResetView(RECT windowRect);
    public:
        Game() = default;
        GameState gameState = GameState(INTRO);
        Bird bird = Bird(L"redbird-midflap.png");
        Scene scene = Scene(&gameState, &bird);
        void MoveBird(RECT windowRect, double multiplierDirection);
        void KeyAnalyse(HWND hWnd, WPARAM wParam, RECT windowRect);
        int GetCoins();
        void Run(HWND hWnd);
        void Quit();
};


#endif //FLAPPYBIRD_WINAPI_GAME_H
