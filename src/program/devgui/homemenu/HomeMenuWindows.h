#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuWindows : public HomeMenuBase {
public:
    HomeMenuWindows(DevGuiManager* parent, const char* menuName);

    virtual void updateMenuDisplay();

private:
    void setAnc(int type);
};