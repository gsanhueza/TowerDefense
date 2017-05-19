#include <Ogre.h>
#include <OgreApplicationContext.h>

class Base : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    Base();
    void setup();

    // I/O
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
    bool keyReleased(const OgreBites::KeyboardEvent& evt);
    bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
    bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);
    bool mousePressed(const OgreBites::MouseButtonEvent& evt);
    bool mouseReleased(const OgreBites::MouseButtonEvent& evt);
};
