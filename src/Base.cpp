#include "Base.h"
#include <iostream>

Base::Base() : OgreBites::ApplicationContext("Base")
{
    addInputListener(this);
}

bool Base::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    std::cout << "Pressed (KBD)!" << std::endl;
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    else if (evt.keysym.sym == SDLK_d)
    {
        getRoot()->getSceneManager("TowerDefense")->getSceneNode("CamNode")->translate(Ogre::Vector3(1, 0, 0));
    }
    else if (evt.keysym.sym == SDLK_a)
    {
        getRoot()->getSceneManager("TowerDefense")->getSceneNode("CamNode")->translate(Ogre::Vector3(-1, 0, 0));
    }
    else if (evt.keysym.sym == SDLK_w)
    {
        getRoot()->getSceneManager("TowerDefense")->getSceneNode("CamNode")->translate(Ogre::Vector3(0, 0, -1));
    }
    else if (evt.keysym.sym == SDLK_s)
    {
        getRoot()->getSceneManager("TowerDefense")->getSceneNode("CamNode")->translate(Ogre::Vector3(0, 0, 1));
    }
    else if (evt.keysym.sym == SDLK_q)
    {
        getRoot()->getSceneManager("TowerDefense")->getSceneNode("CamNode")->roll(Ogre::Radian(-0.1));
    }
    else if (evt.keysym.sym == SDLK_e)
    {
        getRoot()->getSceneManager("TowerDefense")->getSceneNode("CamNode")->roll(Ogre::Radian(0.1));
    }
    return true;
}

bool Base::keyReleased(const OgreBites::KeyboardEvent& evt)
{
    std::cout << "Released (KBD)!" << std::endl;

    return true;
}

bool Base::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
    std::cout << "Moved!" << std::endl;
    getRoot()->getSceneManager("TowerDefense")->getSceneNode("CamNode")->yaw(Ogre::Degree(-0.1 * evt.xrel));
    getRoot()->getSceneManager("TowerDefense")->getSceneNode("CamNode")->pitch(Ogre::Degree(-0.1 * evt.yrel));

    return true;
}

bool Base::mousePressed(const OgreBites::MouseButtonEvent& evt)
{
    std::cout << "Pressed!" << std::endl;
    return true;
}

bool Base::mouseWheelRolled(const OgreBites::MouseWheelEvent& evt)
{
    std::cout << "Rolled!" << std::endl;
    return true;
}

bool Base::mouseReleased(const OgreBites::MouseButtonEvent& evt)
{
    std::cout << "Released (Mouse)!" << std::endl;
    return true;
}

void Base::setup(void)
{
    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // get a pointer to the already created root
    Ogre::Root* root = getRoot();
    Ogre::SceneManager* scnMgr = root->createSceneManager(Ogre::ST_GENERIC, "TowerDefense");

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen
    Ogre::Light* light = scnMgr->createLight("MainLight");
    light->setPosition(0, 10, 15);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode("CamNode");
    std::cout << camNode->getName() << std::endl;
    camNode->setPosition(30, 0, 100);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);                            // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    // finally something to render
    Ogre::Entity* ent = scnMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
}
