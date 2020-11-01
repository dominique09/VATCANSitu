#pragma once

#include <string>
#include "EuroScopePlugIn.h"

using namespace std;
using namespace EuroScopePlugIn;


// Colours for the plugin

const COLORREF C_PPS_ORANGE = RGB(242, 120, 57);
const COLORREF C_PPS_YELLOW = RGB(202, 205, 169);
const COLORREF C_PPS_RED = RGB(209, 39, 27);

// Math
const double PI = 3.14159;

// Tag Settings
const int TAG_MAX_X_OFFSET = 45;
const int TAG_MAX_Y_OFFSET = 30;
const int TAG_WIDTH = 50;
const int TAG_HEIGHT = 25;

// Tag Items
const int TAG_ITEM_PLANE_HALO = 1;
const int AIRCRAFT_SYMBOL = 200;
const int AIRCRAFT_CJS = 400;

const int TAG_ITEM_CS = 401;
const int TAG_ALT = 402;

const int BUTTON_MENU = 201;
const int BUTTON_MENU_HALO_OPTIONS = 202;
const int BUTTON_MENU_ALT_FILT_OPT = 203;
const int BUTTON_MENU_ALT_FILT_ON = 204;
const int BUTTON_MENU_ALT_FILT_SAVE = 205;

// Menu Modules
const int MODULE_1_X = 0;
const int MODULE_1_Y = 2;
const int MODULE_2_X = 300;
const int MODULE_2_Y = 2;

// Menu functions
const int FUNCTION_ALT_FILT_LOW = 301;
const int FUNCTION_ALT_FILT_HIGH = 302;
const int FUNCTION_ALT_FILT_SAVE = 303;

// Radar Background
const int SCREEN_BACKGROUND = 501;

const int ADD_FREE_TEXT = 1101;
const int DELETE_FREE_TEXT = 1102;
const int DELETE_ALL_FREE_TEXT = 1103;


// Module 2 : distances relative to module origin
const int HALO_TOOL_X = 0;
const int HALO_TOOL_Y = 0;