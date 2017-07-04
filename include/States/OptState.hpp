#ifndef OPTSTATE_HPP
# define OPTSTATE_HPP

#include <States/AppState.hpp>

class OptState : public AppState {
public:
    OptState();

    DECLARE_APPSTATE_CLASS(OptState)

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
};

#endif /* OPTSTATE_HPP */
