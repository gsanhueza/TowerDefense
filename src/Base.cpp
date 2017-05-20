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

void Base::getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
    img.load("terrain.jpg", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

    if (flipX)
        img.flipAroundY();
    if (flipY)
        img.flipAroundX();
}


void Base::defineTerrain(long x, long y)
{
    Ogre::String filename = mTerrainGroup->generateFilename(x, y);

    bool exists =
            Ogre::ResourceGroupManager::getSingleton().resourceExists(
                    mTerrainGroup->getResourceGroup(),
                    filename);
    if (exists)
        mTerrainGroup->defineTerrain(x, y);
    else
    {
        Ogre::Image img;
        getTerrainImage(x % 2 != 0, y % 2 != 0, img);
        mTerrainGroup->defineTerrain(x, y, &img);

        mTerrainsImported = true;
    }
}

void Base::initBlendMaps(Ogre::Terrain* terrain)
{
    Ogre::Real minHeight0 = 70;
    Ogre::Real fadeDist0 = 40;
    Ogre::Real minHeight1 = 70;
    Ogre::Real fadeDist1 = 15;

    Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

    float* pBlend0 = blendMap0->getBlendPointer();
    float* pBlend1 = blendMap1->getBlendPointer();

    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;

            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend0++ = val;

            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }

    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}

void Base::configureTerrainDefaults(Ogre::Light* light, Ogre::SceneManager* scnMgr)
{
    mTerrainGlobals->setMaxPixelError(8);
    mTerrainGlobals->setCompositeMapDistance(3000);

    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(scnMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

    Ogre::Terrain::ImportData& importData = mTerrainGroup->getDefaultImportSettings();
    importData.terrainSize = 513;
    importData.worldSize = 12000.0;
    importData.inputScale = 600;
    importData.minBatchSize = 33;
    importData.maxBatchSize = 65;

    importData.layerList.resize(3);

    importData.layerList[0].worldSize = 100;
    importData.layerList[0].textureNames.push_back(
            "dirt_grayrocky_diffusespecular.dds");
    importData.layerList[0].textureNames.push_back(
            "dirt_grayrocky_normalheight.dds");
    importData.layerList[1].worldSize = 30;
    importData.layerList[1].textureNames.push_back(
            "grass_green-01_diffusespecular.dds");
    importData.layerList[1].textureNames.push_back(
            "grass_green-01_normalheight.dds");
    importData.layerList[2].worldSize = 200;
    importData.layerList[2].textureNames.push_back(
            "growth_weirdfungus-03_diffusespecular.dds");
    importData.layerList[2].textureNames.push_back(
            "growth_weirdfungus-03_normalheight.dds");
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
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
    light->setPosition(0, 10, 15);

    // also need to tell where we are
    Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode("CamNode");
    std::cout << camNode->getName() << std::endl;
    camNode->setPosition(Ogre::Vector3(0, 0, 0));
    camNode->lookAt(Ogre::Vector3(1963, 50, 1660), Ogre::Node::TS_PARENT);

    // create the camera
    Ogre::Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5);                            // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
    mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(
            scnMgr,
            Ogre::Terrain::ALIGN_X_Z,
            513, 12000.0);
    mTerrainGroup->setFilenameConvention(Ogre::String("terrain"), Ogre::String("dat"));
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

    configureTerrainDefaults(light, scnMgr);

    for (long x = 0; x <= 0; ++x)
        for (long y = 0; y <= 0; ++y)
            defineTerrain(x, y);

    mTerrainGroup->loadAllTerrains(true);

    if (mTerrainsImported)
    {
        Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();

        while (ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;
            initBlendMaps(t);
        }
    }

    mTerrainGroup->freeTemporaryResources();



    // finally something to render
    Ogre::Entity* ent = scnMgr->createEntity("ogrehead.mesh");
    Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
}
