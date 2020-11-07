//
// Created by shine on 04.11.2020.
//

#include "GameState.h"
#include <iostream>

States GameState::GetState() {
    return state;
}

GameState::GameState(States _state) {
    state = _state;
}

void GameState::ChangeToGameLevel() {
    state = GAMELEVEL;
}

void GameState::ChangeToScore() {
    state = SCORE;
}

void GameState::ChangeToIntro() {
    state = INTRO;
}

GameState::GameState() = default;
