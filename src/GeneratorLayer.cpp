#include "GeneratorLayer.hpp"
#include "LevelBuilder.hpp"

using namespace geode::prelude;

GeneratorLayer* GeneratorLayer::create() {

    auto ret = new GeneratorLayer();

    if(ret && ret->init()) {

        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool GeneratorLayer::init() {

    auto win = CCDirector::sharedDirector()->getWinSize();

    auto bg = CCLayerColor::create({0,0,0,180});
    this->addChild(bg);

    auto title = CCLabelBMFont::create("LEVEL GENERATOR","bigFont.fnt");
    title->setPosition({win.width/2, win.height - 80});
    addChild(title);

    levelName = TextInput::create(220,"Level Name");
    levelName->setPosition({win.width/2, win.height - 140});
    addChild(levelName);

    musicID = TextInput::create(220,"Music ID");
    musicID->setPosition({win.width/2, win.height - 190});
    addChild(musicID);

    auto preview = CCMenuItemFont::create(
        "PREVIEW",
        this,
        menu_selector(GeneratorLayer::onPreview)
    );

    auto random = CCMenuItemFont::create(
        "RANDOM GENERATE",
        this,
        menu_selector(GeneratorLayer::onRandom)
    );

    auto generate = CCMenuItemFont::create(
        "GENERATE",
        this,
        menu_selector(GeneratorLayer::onGenerate)
    );

    auto menu = CCMenu::create(preview, random, generate, nullptr);

    preview->setPosition({0,-20});
    random->setPosition({0,-60});
    generate->setPosition({0,-100});

    menu->setPosition({win.width/2, win.height/2});
    addChild(menu);

    return true;
}

void GeneratorLayer::onPreview(CCObject*) {

    std::string text =
        "Name: " + levelName->getString() +
        "\nMusic ID: " + musicID->getString();

    FLAlertLayer::create(
        "Preview",
        text.c_str(),
        "Generate",
        "Cancel"
    )->show();
}

void GeneratorLayer::onRandom(CCObject*) {

    LevelBuilder::generateRandom();
}

void GeneratorLayer::onGenerate(CCObject*) {

    int id = 0;

    try {
        id = std::stoi(musicID->getString());
    }
    catch (...) {
        id = 0;
    }

    LevelBuilder::generate(
        levelName->getString(),
        id
    );
}