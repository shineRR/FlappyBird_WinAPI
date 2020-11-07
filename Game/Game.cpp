//
// Created by shine on 11/3/2020.
//

#include "Game.h"

void Game::KeyAnalyse(HWND hWnd, WPARAM wParam) {
    RECT windowRect;
    GetClientRect(hWnd, &windowRect);
    switch(wParam) {
        case VK_SHIFT: {
            gameState.ChangeToGameLevel();
            break;
        }
        case VK_UP: {
            bird.MoveVertical(windowRect, upModifier);
            break;
        }
        case VK_DOWN: {
            bird.MoveVertical(windowRect, downModifier);
            break;
        }
        case VK_ESCAPE: {
            gameState.ChangeToIntro();
            break;
        }
    }
    scene.Render(hWnd);
}

void Game::Run(HWND hWnd, WPARAM wParam) {
    RECT windowRect;
    GetClientRect(hWnd, &windowRect);
    int _x = (windowRect.right - windowRect.left) / 2 - 40;
    int _y = (windowRect.bottom - windowRect.top) / 2;
    bird.UpdateXY(_x, _y);
    scene.Render(hWnd);
}

void Game::Quit() {

}