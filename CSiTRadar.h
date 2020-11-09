#pragma once
#include "EuroScopePlugIn.h"
#include "SituPlugin.h"
#include <chrono>
#include <string>
#include <map>
#include <iostream>
#include <math.h>
#include "pch.h"

using namespace EuroScopePlugIn;
using namespace std;

struct ACData {
    bool hasCTP;
};

class CSiTRadar :
    public EuroScopePlugIn::CRadarScreen

{
public:

    CSiTRadar(void);
    virtual ~CSiTRadar(void);

    static map<string, ACData> mAcData; 

    inline virtual void OnFlightPlanDisconnect(CFlightPlan FlightPlan);
    static void RegisterButton(RECT rect) {};

    void OnRefresh(HDC hdc, int phase);

    void CSiTRadar::OnClickScreenObject(int ObjectType,
        const char* sObjectId,
        POINT Pt,
        RECT Area,
        int Button);

    inline virtual void OnAsrContentToBeClosed(void) {

        delete this;
    };

protected:
    void ButtonToScreen(CSiTRadar* radscr, RECT rect, string btext, int itemtype);

    const int BUTTON_MENU_RELOCATE = 1200;
};
