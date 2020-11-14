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
            scene.isActive = false;
            scene.ResetCounter();
            gameState.ChangeToIntro();
            bird.UpdateXY(windowRect);
            Pipe::InitializePipes(scene.pipe.pipes, true);
            scene.pipe.updatePipesPosition(windowRect, scene.pipe.pipes, DEFAULT_WINDOW_WIDTH, true);
            break;
        }
    }
}

void Game::MoveBird(RECT windowRect, double multiplierDirection) {
    if (!scene.isActive) return;
    bird.MoveVertical(windowRect, multiplierDirection);
}


void Game::Run(HWND hWnd) {
    RECT windowRect;
    GetClientRect(hWnd, &windowRect);
    bird.UpdateXY(windowRect);
    scene.Render(hWnd);
}

int Game::GetCoins() {
    return scene.coins;
}

void Game::Quit() {

}

