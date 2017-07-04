//
//-----------------------------------------------------------------------------
//Filename:    IA.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Entities/IA.hpp"

IA::IA(Ogre::SceneManager *sceneManager, const std::string &name, const std::string &scriptPath) : Body(sceneManager,
                                                                                                        name),
                                                                                                   _pLua(nullptr) {
    if (!loadIA(scriptPath))
        _pLua = nullptr;
}

void IA::RegisterIAWithLua(lua_State *pLua) {
    luabind::module(pLua)
    [
            luabind::def("GetPosX", (int(*)())&IA::getX),
            luabind::def("GetPosY", (int(*)())&IA::getY)
    ];
}

int IA::getX() const {
    return (int) _pos.x;
}

int IA::getY() const {
    return (int) _pos.y;
}

bool IA::loadIA(const std::string &path) {
    _pLua = lua_open();

    luaL_openlibs(_pLua);
    if (luaL_dofile(_pLua, path.c_str())) {
        OgreFramework::getSingletonPtr()->_log->logMessage(
                std::string("Couldn't load file: ") + lua_tostring(_pLua, -1));
        return false;
    }

    luabind::open(_pLua);
    RegisterIAWithLua(_pLua);

    return true;
}

void IA::update(Ogre::Real elapsedTime) {
    Body::update(elapsedTime);

    if (_pLua)
    {
        int value = luabind::call_function<int>(_pLua, "run");
        switch ((ActionPlayer)value) {
            case ActionPlayer::GO_UP:
                moveUp();
                break;
            case ActionPlayer::GO_DOWN:
                moveDown();
                break;
            case ActionPlayer::GO_LEFT:
                moveLeft();
                break;
            case ActionPlayer::GO_RIGHT:
                moveRight();
                break;
            case ActionPlayer::PUT_BOMB:
                putBomb();
                break;
            case ActionPlayer::HIT_BOMB:
                hitBomb();
                break;
        }
    }
}

IA::~IA() {
    if (_pLua)
        lua_close(_pLua);
}

bool IA::getLastAction(InputController::ActionPlayer &action) {
    const bool ret = InputController::getLastAction(action);
    if (_qInput.size())
        _qInput.pop();
    return ret;
}
