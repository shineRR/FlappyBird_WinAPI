//
// Created by shine on 11/3/2020.
//

#ifndef FLAPPYBIRD_WINAPI_GAME_H
#define FLAPPYBIRD_WINAPI_GAME_H

#include "algorithm"
#include "Scene.h"
#include "GameState.h"

class Game {
    private:
        const int downModifier = 1;
        const int upModifier = -1;
        int money = 0;

    public:
        Game() = default;
        GameState gameState = GameState(INTRO);
        Bird bird = Bird(L"C:\\Users\\shine\\Desktop\\Dev\\FlappyBird_WinAPI\\Assets\\redbird-midflap.png");
        Scene scene = Scene(&gameState, &bird);

        void KeyAnalyse(HWND hWnd, WPARAM wParam);
        void Run(HWND hWnd, WPARAM wParam);
        void Quit();
};


#endif //FLAPPYBIRD_WINAPI_GAME_H
