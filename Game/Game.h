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

    public:
        Game() = default;
        GameState gameState = GameState(INTRO);
        Scene scene = Scene(&gameState);

        void KeyAnalyse(HWND hWnd, WPARAM wParam);
        void Run(HWND hWnd, WPARAM wParam);
        void Quit();
};


#endif //FLAPPYBIRD_WINAPI_GAME_H
