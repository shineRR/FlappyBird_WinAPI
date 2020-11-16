//
// Created by shine on 04.11.2020.
//

#ifndef FLAPPYBIRD_WINAPI_GAMESTATE_H
#define FLAPPYBIRD_WINAPI_GAMESTATE_H

enum States {
    INTRO = 0,
    GAMELEVEL,
    SCORE,
    SHOP,
};

class GameState {
    private:
        States state;
    public:
        GameState();
        explicit GameState(States _state);
        States GetState();
        void ChangeToIntro();
        void ChangeToGameLevel();
        void ChangeToScore();
        void ChangeToShop();
};


#endif //FLAPPYBIRD_WINAPI_GAMESTATE_H
