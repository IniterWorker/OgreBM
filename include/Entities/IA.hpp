//
//-----------------------------------------------------------------------------
//Filename:    IA.hpp
//-----------------------------------------------------------------------------
//
// Created by bonett_w on 7/3/17.
//-----------------------------------------------------------------------------
//

#ifndef OGREBM_IA_HPP
#define OGREBM_IA_HPP

#include "Body.hpp"

extern "C" {
#include <lua5.1/lualib.h>
#include <lua5.1/lauxlib.h>
#include <lua5.1/lua.h>
}

#include <luabind/luabind.hpp>
#include <luabind/function.hpp>

class IA : public Body {
public:
  IA(Ogre::SceneManager *sceneManager, const std::string &name, const std::string &scriptPath, int id);

    virtual ~IA();

    void update(Ogre::Real elapsedTime) override;

    int getX() const;

    int getY() const;

    bool getLastAction(ActionPlayer &action) override;

private:

    bool loadIA(const std::string &path);

    void RegisterIAWithLua(lua_State *pLua);

    lua_State *_pLua;
};


#endif //OGREBM_IA_HPP
