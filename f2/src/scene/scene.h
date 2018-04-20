//
// Created by Dillon Yao on 4/12/18.
//

#ifndef F2_SCENE_H
#define F2_SCENE_H

#include <vector>
#include "thing.h"
#include "camera.h"

class Scene {
public:
    Scene();

    void add_thing(Thing *t) {
        _things.push_back(t);
        t->_scene = this;
        if (t->_is_collidable)
            _collidables.push_back(t);
    }

    void render(Camera &camera) {
        for (Thing *t : _things) {
            t->render(camera);
        }
    }

    std::vector<Thing *> &get_collidables() {
        return _collidables;
    }

private:
    std::vector<Thing *> _things;
    std::vector<Thing *> _collidables;
};

#endif //F2_SCENE_H
