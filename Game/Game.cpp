//
// Created by shine on 11/3/2020.
//

#include "Game.h"

void Game::KeyAnalyse(HWND hWnd, WPARAM wParam) {
    switch(wParam) {
        case VK_SHIFT: {
            gameState.ChangeToGameLevel();
            break;
        }
    }
    scene.Render(hWnd);
}

void Game::Run(HWND hWnd, WPARAM wParam) {
    scene.Render(hWnd);
}

void Game::Quit() {

}