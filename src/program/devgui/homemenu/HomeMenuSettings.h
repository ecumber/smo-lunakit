#pragma once

#include "imgui.h"
#include "imgui_internal.h"

#include "devgui/settings/DevGuiSettings.h"
#include "devgui/homemenu/HomeMenuBase.h"

class HomeMenuSettings : public HomeMenuBase {
public:
    HomeMenuSettings(DevGuiManager* parent, const char* menuName);

    virtual void updateMenuDisplay();
private:

    void parameterEdit(const char* name, bool* value, bool isSave);
};