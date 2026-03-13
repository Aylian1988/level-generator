#include "LevelBuilder.hpp"

using namespace geode::prelude;

float LevelBuilder::bpmSpacing(int bpm){

    float beat = 60.0f / bpm;
    return beat * 240;
}

void LevelBuilder::backgroundDecoration(LevelEditorLayer* editor,float x){

    auto bg = GameObject::createWithKey(579);
    bg->setPosition({x,260});
    editor->addObject(bg);
}

void LevelBuilder::movingDecoration(LevelEditorLayer* editor,float x){

    auto deco = GameObject::createWithKey(1615);
    deco->setPosition({x,200});
    editor->addObject(deco);

    auto move = GameObject::createWithKey(901);
    move->setPosition({x,300});
    editor->addObject(move);
}

void LevelBuilder::colorTrigger(LevelEditorLayer* editor,float x){

    auto trigger = GameObject::createWithKey(899);
    trigger->setPosition({x,320});
    editor->addObject(trigger);
}

void LevelBuilder::buildStructure(LevelEditorLayer* editor,float x){

    auto block1 = GameObject::createWithKey(1);
    block1->setPosition({x,150});
    editor->addObject(block1);

    auto block2 = GameObject::createWithKey(1);
    block2->setPosition({x+30,180});
    editor->addObject(block2);

    auto glow = GameObject::createWithKey(1006);
    glow->setPosition({x+15,210});
    editor->addObject(glow);

    backgroundDecoration(editor,x);
    movingDecoration(editor,x);
}

void LevelBuilder::cubeSection(LevelEditorLayer* editor,float& x,int bpm){

    float spacing = bpmSpacing(bpm);

    for(int i=0;i<15;i++){

        auto block = GameObject::createWithKey(1);
        block->setPosition({x,100});
        editor->addObject(block);

        if(rand()%2==0){

            auto spike = GameObject::createWithKey(8);
            spike->setPosition({x+30,130});
            editor->addObject(spike);
        }

        buildStructure(editor,x);

        if(rand()%5==0)
            colorTrigger(editor,x);

        x += spacing;
    }
}

void LevelBuilder::shipSection(LevelEditorLayer* editor,float& x,int bpm){

    auto portal = GameObject::createWithKey(13);
    portal->setPosition({x,100});
    editor->addObject(portal);

    float spacing = bpmSpacing(bpm);

    for(int i=0;i<12;i++){

        auto top = GameObject::createWithKey(1);
        top->setPosition({x,220});
        editor->addObject(top);

        auto bottom = GameObject::createWithKey(1);
        bottom->setPosition({x,40});
        editor->addObject(bottom);

        buildStructure(editor,x);

        x += spacing;
    }
}

void LevelBuilder::waveSection(LevelEditorLayer* editor,float& x,int bpm){

    auto portal = GameObject::createWithKey(660);
    portal->setPosition({x,100});
    editor->addObject(portal);

    float spacing = bpmSpacing(bpm);

    for(int i=0;i<16;i++){

        auto spikeTop = GameObject::createWithKey(8);
        spikeTop->setPosition({x,230});
        editor->addObject(spikeTop);

        auto spikeBottom = GameObject::createWithKey(8);
        spikeBottom->setPosition({x,30});
        editor->addObject(spikeBottom);

        buildStructure(editor,x);

        x += spacing;
    }
}

void LevelBuilder::dualSection(LevelEditorLayer* editor,float& x,int bpm){

    auto portal = GameObject::createWithKey(286);
    portal->setPosition({x,100});
    editor->addObject(portal);

    float spacing = bpmSpacing(bpm);

    for(int i=0;i<14;i++){

        auto blockTop = GameObject::createWithKey(1);
        blockTop->setPosition({x,200});
        editor->addObject(blockTop);

        auto blockBottom = GameObject::createWithKey(1);
        blockBottom->setPosition({x,60});
        editor->addObject(blockBottom);

        buildStructure(editor,x);

        x += spacing;
    }
}

void LevelBuilder::generate(std::string name,int musicID){

    srand(time(0));

    auto level = GJGameLevel::create();

    level->m_levelName = name;
    level->m_songID = musicID;

    auto editor = LevelEditorLayer::create(level);

    float x = 0;
    int bpm = 140;
    int sections = 60;

    for(int i=0;i<sections;i++){

        int type = rand()%4;

        if(type==0)
            cubeSection(editor,x,bpm);

        if(type==1)
            shipSection(editor,x,bpm);

        if(type==2)
            waveSection(editor,x,bpm);

        if(type==3)
            dualSection(editor,x,bpm);
    }

    CCDirector::sharedDirector()->replaceScene(
        CCTransitionFade::create(0.5,editor)
    );
}

void LevelBuilder::generateRandom(){

    generate("Random Level", rand()%200000);
}