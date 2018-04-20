//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_STATE_H
#define F2_STATE_H

#include <vector>
#include "../util/util.h"

class App;

class AppState {
public:
    virtual const char *name() { return ""; };
    virtual void init() {};
    virtual void handle_input() {};
    virtual void update(double dt) {};
    virtual void render() {};
    virtual inline bool should_terminate() {
        return true;
    };
    inline void set_app(App* app) {
        _app = app;
    }

private:
    App *_app;
};

class StateStack {
public:
    void setApp(App *app) {
        _app = app;
    }

    void push(AppState *state) {
        state->set_app(_app);
        _stack.push_back(state);
        scoped_msg(">>", "begin state init\n");
        state->init();
        level_msg("done.", 1, true);
    }

    void pop() {
        if (_stack.size())
            _stack.pop_back();
    }

    void swap(AppState *state) {
        pop();
        push(state);
    }

    AppState *top() {
        return _stack.back();
    }

private:
    App *_app;
    std::vector<AppState *> _stack;
};

#endif //F2_STATE_H
