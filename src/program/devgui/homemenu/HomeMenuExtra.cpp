#include "devgui/DevGuiManager.h"
#include "devgui/homemenu/HomeMenuExtra.h"
#include "devgui/popups/PopupKeyboard.h"

HomeMenuExtra::HomeMenuExtra(DevGuiManager* parent, const char* menuName)
    : HomeMenuBase(parent, menuName)
{}

void HomeMenuExtra::updateMenu()
{
    if(mIsFirstStep) {
        mIsLoggerDisabled = Logger::instance().getDisabledState();
        mIsFirstStep = false;
        return;
    }

    if(!mKeyboardString)
        return;

    if(mIsIPKeyboardOpen) {
        mIPString.clear();
        mIPString.append(mKeyboardString);
    }

    if(mIsPortKeyboardOpen) {
        mPortString.clear();
        mPortString.append(mKeyboardString);
    }
}

void HomeMenuExtra::updateMenuDisplay()
{
    ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);

    if(!mIsLoggerDisabled && ImGui::MenuItem("Disable Logger")) {
        Logger::instance().writeLoggerSave(mHeap, true, "0", 0);
        mIsLoggerDisabled = true;
    }

    if(mIsLoggerDisabled && addMenu("Server Logging")) {
        if(ImGui::MenuItem("IP", mIPString.cstr())) {
            mParent->tryOpenKeyboard(15, KEYTYPE_IP, &mKeyboardString, &mIsIPKeyboardOpen);
        }
        
        if(ImGui::MenuItem("Port", mPortString.cstr())) {
            mParent->tryOpenKeyboard(5, KEYTYPE_NUMBER, &mKeyboardString, &mIsPortKeyboardOpen);
        }
        
        if(!mIPString.isEmpty() && !mPortString.isEmpty()) {
            ImGui::MenuItem(" ", nullptr, false, false);
            ImGui::MenuItem("Requires restart", nullptr, false, false);
            ImGui::MenuItem("Server must run on startup", nullptr, false, false);
            ImGui::MenuItem(" ", nullptr, false, false);
            ImGui::MenuItem("Disable via menu or deleting:", nullptr, false, false);
            ImGui::MenuItem("LunaKit/LKData/logger.byml", nullptr, false, false);
            if(ImGui::MenuItem("Activate Logger")) {
                mNewPort = std::__cxx11::stoi(mPortString.cstr());
                Logger::instance().writeLoggerSave(mHeap, false, mIPString.cstr(), mNewPort);

                mIsLoggerDisabled = false;
                mIPString.clear();
                mPortString.clear();
                mKeyboardString = nullptr;
            }
        }

        ImGui::EndMenu();
    }

    bool* demoWinState = mParent->getImGuiDemoWindowState();
    if (ImGui::MenuItem("ImGui Demo Window", NULL, *demoWinState)) {
        *demoWinState = !(*demoWinState);
    }

    if(addMenu("Credits")) {
        ImGui::MenuItem("Amethyst-szs", NULL, false, false);
        ImGui::MenuItem("CraftyBoss", NULL, false, false);
        ImGui::MenuItem("Mars", NULL, false, false);
        ImGui::MenuItem("ExLaunch Devs", NULL, false, false);

        ImGui::EndMenu();
    }

    ImGui::PopItemFlag();
}