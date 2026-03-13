#pragma once
#include <Geode/Geode.hpp>

class LevelBuilder {

public:

    static void generate(std::string name,int musicID);
    static void generateRandom();

private:

    static float bpmSpacing(int bpm);

    static void cubeSection(LevelEditorLayer* editor,float& x,int bpm);
    static void shipSection(LevelEditorLayer* editor,float& x,int bpm);
    static void waveSection(LevelEditorLayer* editor,float& x,int bpm);
    static void dualSection(LevelEditorLayer* editor,float& x,int bpm);

    static void buildStructure(LevelEditorLayer* editor,float x);
    static void backgroundDecoration(LevelEditorLayer* editor,float x);
    static void movingDecoration(LevelEditorLayer* editor,float x);
    static void colorTrigger(LevelEditorLayer* editor,float x);
};