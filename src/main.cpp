#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "GeneratorLayer.hpp"

using namespace geode::prelude;

class $modify(MenuLayer) {

    bool init() {

        if(!MenuLayer::init())
            return false;

        auto sprite = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");

        auto button = CCMenuItemSpriteExtra::create(
            sprite,
            this,
            menu_selector(MenuLayer::openGenerator)
        );

        button->setPosition({200, -100});

        auto menu = this->getChildByType<CCMenu>(0);

        if(menu)
            menu->addChild(button);

        return true;
    }

    void openGenerator(CCObject*) {

        auto layer = GeneratorLayer::create();

        CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
    }
};