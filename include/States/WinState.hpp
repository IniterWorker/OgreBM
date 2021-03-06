#ifndef WINSTATE_HPP
# define WINSTATE_HPP

#include <OGRE/OgreSceneManager.h>
#include <States/AppState.hpp>

class WinState : public AppState {
public:
    WinState();

    DECLARE_APPSTATE_CLASS(WinState)

    void enter();

    void createScene();

    void exit();

    bool keyPressed(const OIS::KeyEvent &keyEventRef);

    bool keyReleased(const OIS::KeyEvent &keyEventRef);

    bool mouseMoved(const OIS::MouseEvent &evt);

    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

    void buttonHit(OgreBites::Button *button);

    void update(Ogre::Real timeSinceLastFrame);

private:
    bool _isQuit;
    Ogre::SceneManager *_sceneManager;
    Ogre::Camera *_camera;
    Ogre::Real _time;
    Ogre::Real _awaitingTime;
    Ogre::TextureUnitState *tex;
};

#endif /* WINSTATE_HPP */
