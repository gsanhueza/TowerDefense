#include <Ogre.h>
#include <OgreApplicationContext.h>

class Base : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    Base();
    void setup();
    bool keyPressed(const OgreBites::KeyboardEvent& evt);
};
