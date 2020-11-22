//
// Created by shine on 11/3/2020.
//

#include "Game.h"

void Game::KeyAnalyse(HWND hWnd, WPARAM wParam, RECT windowRect) {
    States state = gameState.GetState();
    switch(wParam) {
        case VK_SHIFT: {
            if (state == SCORE || state == SHOP)
                ResetView(windowRect);
            scene.isActive = !scene.isActive;
            if (state != GAMELEVEL) {
                gameState.ChangeToGameLevel();
            }
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
        case VK_F1: {
            if (state == GAMELEVEL) return;
            gameState.ChangeToShop();
            break;
        }
        case VK_ESCAPE: {
            scene.isActive = false;
            ResetView(windowRect);
            gameState.ChangeToIntro();
            break;
        }
        case VK_F5: {
            scene.SetNewBackground(backgrounds[0]);
            break;
        }
        case VK_F6: {
            scene.SetNewBackground(backgrounds[1]);
            break;
        }
    }
    if (state == SHOP)
        scene.KeyAnalyse(hWnd, wParam, windowRect);
}

void Game::ResetView(RECT windowRect) {
    scene.ResetCounter();
    bird.UpdateXY(windowRect);
    Pipe::InitializePipes(scene.pipe.pipes, true);
    scene.pipe.updatePipesPosition(windowRect, scene.pipe.pipes, DEFAULT_WINDOW_WIDTH, true);
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


