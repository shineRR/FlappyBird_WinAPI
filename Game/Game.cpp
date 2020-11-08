//
// Created by shine on 11/3/2020.
//

#include "Game.h"

void Game::KeyAnalyse(HWND hWnd, WPARAM wParam, RECT windowRect) {
    switch(wParam) {
        case VK_SHIFT: {
            scene.isActive = !scene.isActive;
            gameState.ChangeToGameLevel();
            break;
        }
        case VK_UP: {
            MoveBird(windowRect, upModifier);
            break;
        }
        case VK_DOWN: {
            MoveBird(windowRect, downModifier);
            break;
        }
        case VK_ESCAPE: {
            scene.isActive = !scene.isActive;
            gameState.ChangeToIntro();
            break;
        }
    }
//    scene.Render(hWnd);
}

void Game::MoveBird(RECT windowRect, double multiplierDirection) {
    if (!scene.isActive) return;
    bird.MoveVertical(windowRect, multiplierDirection);
}


void Game::Run(HWND hWnd) {
    RECT windowRect;
    GetClientRect(hWnd, &windowRect);
    int width = (windowRect.right - windowRect.left);
    int height = (windowRect.bottom - windowRect.top);
    int _x = width / 2 - 40;
    int _y = height / 2;
    bird.UpdateXY(_x, _y);
    scene.Render(hWnd);
}

void Game::Quit() {

}
