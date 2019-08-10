/**
 * This file is part of tuna
 * which is licensed under the GPL v2.0
 * See LICENSE or http://www.gnu.org/licenses
 * github.com/univrsal/tuna
 */

#include <obs-module.h>
#include <obs-frontend-api.h>
#include <QAction>
#include <QMainWindow>
#include "util/constants.hpp"
#include "gui/tuna_gui.hpp"
#include "util/config.hpp"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(S_PLUGIN_ID, "en-US")

void register_gui()
{
    /* UI registration from
     * https://github.com/Palakis/obs-websocket/
     */
    const auto menu_action = static_cast<QAction*>
            (obs_frontend_add_tools_menu_qaction(T_MENU_TUNA));
    obs_frontend_push_ui_translation(obs_module_get_string);
    const auto main_window = static_cast<QMainWindow*>
            (obs_frontend_get_main_window());
    tuna_dialog = new tuna_gui(main_window);
    obs_frontend_pop_ui_translation();
    const auto menu_cb = []
    {
        tuna_dialog->toggleShowHide();
    };
    QAction::connect(menu_action, &QAction::triggered, menu_cb);
}

bool obs_module_load()
{
    config::load();
    register_gui();
    return true;
}

void obs_module_unload()
{
    config::close();
    delete tuna_dialog;
    tuna_dialog = nullptr;
}