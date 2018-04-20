//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_APP_H
#define F2_APP_H

#include "view.h"
#include "state.h"

class App {
public:
    bool init();
    void begin();

private:
    bool init_services(AppConfig &config);
    void update_state(double dt);
    void render_state();
//    bool load_config(AppConfig &config);

    AppConfig _state;
    View _view;
    StateStack _stack;
};

#endif //F2_APP_H
