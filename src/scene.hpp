#ifndef SCENE_H
#define SCENE_H

#include "scene_interface.h"
#include "gui.h"

class Scene : public SceneInterface{
    public:
        Gui *gui;
};

#endif