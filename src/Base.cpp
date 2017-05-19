#include "Base.h"
#include <iostream>

Base::Base() : OgreBites::ApplicationContext("TowerDefense")
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
    std::cout << evt.xrel << std::endl;
    std::cout << evt.yrel << std::endl;
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
    Ogre::SceneManager* scnMgr = root->createSceneManager(Ogre::ST_GENERIC);

    // register our scene with the RTSS
    Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // without light we would just get a black screen
    Ogre::Light* light = scnMgr->createLight("MainLight");
    light->setPosition(20, 80, 50);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(0, 47, 222);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);                            // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    // finally something to render
    Ogre::Entity* ent1 = scnMgr->createEntity("ogrehead.mesh");
    Ogre::Entity* ent2 = scnMgr->createEntity("ogrehead.mesh");
    Ogre::Entity* ent3 = scnMgr->createEntity("ogrehead.mesh");
    Ogre::Entity* ent4 = scnMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode* node1 = scnMgr->getRootSceneNode()->createChildSceneNode();
    Ogre::SceneNode* node2 = scnMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(84, 48, 0));

    Ogre::SceneNode* node3 = scnMgr->getRootSceneNode()->createChildSceneNode();
    node3->setPosition(0, 104, 0);
    node3->setScale(2, 1.2, 1);

    Ogre::SceneNode* node4 = scnMgr->getRootSceneNode()->createChildSceneNode();
    node4->setPosition(-84, 48, 0);
    node4->roll(Ogre::Degree(-90));

    node1->attachObject(ent1);
    node2->attachObject(ent2);
    node3->attachObject(ent3);
    node4->attachObject(ent4);
}
