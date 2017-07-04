//
//-----------------------------------------------------------------------------
//Filename:    IA.cpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#include "Entities/IA.hpp"

IA::IA(Map *map, Ogre::SceneManager *sceneManager, const std::string &name, const std::string &scriptPath, int id)
        : Body(map, sceneManager, name, id), _pLua(nullptr), timer(0) {
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

    timer += elapsedTime;

    if (timer > 1.0f) {
        timer = 0;
        CaseSearch st;

        st = lookFast();

        bool action = false;
        for (int i = 0; i < 4; ++i) {
            switch ((Map::Bloc)st.data[i]) {
                case Map::Bloc::EMPTY:break;
                case Map::Bloc::WALL:break;
                case Map::Bloc::EXPLOSION:break;
                case Map::Bloc::BREAKABLE:
                    setWantBomb(true);
                    action = true;
                    break;
            }
            if (action) {
                break;
            }
        }

        if (!action)
            setDir({(rand() % 2) ? -1 : 1, (rand() % 2) ? -1 : 1});
    }
}

IA::~IA() {
    if (_pLua)
        lua_close(_pLua);
}
