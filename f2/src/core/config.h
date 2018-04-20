//
// Created by Dillon Yao on 4/11/18.
//

#ifndef F2_CONFIG_H
#define F2_CONFIG_H

struct CommonState {
    bool terminate = false;
};

struct ViewConfig {
    unsigned int width = 800;
    unsigned int height = 600;
    const char *title = "";
    bool fullscreen = false;
};

struct AppConfig {
    CommonState common;
    ViewConfig view;
};

#endif //F2_CONFIG_H