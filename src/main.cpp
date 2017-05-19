#include <Ogre.h>
#include <OgreApplicationContext.h>
#include "Base.h"

int main(void)
{
    Base app;
    app.initApp();
    app.getRoot()->startRendering();
    app.closeApp();
}
