//
// Created by Dillon Yao on 4/11/18.
//

#include <iostream>
#include "app.h"
#include "../states/view-state.h"
#include "input.h"
#include "../util/util.h"
#include "../common.h"

bool init_msg(const char *name) {
    scoped_msg(name, "initializaing...", 1);
    return true;
}

bool end_init_msg() {
    std::cout << "\tdone." << std::endl;
    return true;
}

bool App::init() {
    scoped_msg(">>", "begin service init\n");
    if (!init_services(_state)) {
        std::cerr << "failed to initialize services" << std::endl;
        return false;
    }
    level_msg("done.", 1, true);

    _stack.push(new ViewState);
    scoped_msg("--", "end init\n");
    return true;
}

void App::begin() {
    double sys_last = glfwGetTime();
    double accumulator = 0;
    double sys_curr, dt;
    while (!_state.common.terminate) {
        sys_curr = glfwGetTime();
        dt = sys_curr - sys_last;
        sys_last = sys_curr;
        accumulator += dt;

        glfwPollEvents();
        while (accumulator >= TIMESTEP) {
            accumulator -= TIMESTEP;
            update_state(TIMESTEP);
        }

        render_state();
        _view.swap_buffers();

        if (_view.should_close() || _stack.top()->should_terminate()) {
            _state.common.terminate = true;
        }
    }
}

bool App::init_services(AppConfig &state) {
    return init_msg("view")
           && _view.init(state.view)
           && end_init_msg()
           && init_msg("input")
           && Input::get()->init(this, &_view)
           && end_init_msg();
}

void App::update_state(double dt) {
    _stack.top()->handle_input();
    _stack.top()->update(dt);
}

void App::render_state() {
    _stack.top()->render();
}
