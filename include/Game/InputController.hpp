//
//-----------------------------------------------------------------------------
//Filename:    InputPlayer.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#ifndef OGREBM_INPUTPLAYER_HPP
#define OGREBM_INPUTPLAYER_HPP


#include <OIS.h>
#include <queue>

class InputController {
public:
    enum class ActionPlayer {
        GO_UP,
        GO_DOWN,
        GO_LEFT,
        GO_RIGHT,
        PUT_BOMB,
        HIT_BOMB
    };
protected:
    std::queue<ActionPlayer> _qInput;

public:
    InputController();

    virtual ~InputController();

    bool getLastAction(ActionPlayer &action);

protected:
    void moveUp();

    void moveDown();

    void moveRight();

    void moveLeft();

    void putBomb();

    void hitBomb();
};


#endif //OGREBM_INPUTPLAYER_HPP
