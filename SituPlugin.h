#pragma once
#include <EuroScopePlugIn.h>
#include <vector>
#include <string>

class SituPlugin :
    public EuroScopePlugIn::CPlugIn
{
public:

    SituPlugin();
    virtual ~SituPlugin();
    EuroScopePlugIn::CRadarScreen* OnRadarScreenCreated(const char* sDisplayName, bool NeedRadarContent, bool GeoReferenced, bool CanBeSaved, bool CanBeCreated);

    virtual void OnGetTagItem(EuroScopePlugIn::CFlightPlan FlightPlan,
        EuroScopePlugIn::CRadarTarget RadarTarget,
        int ItemCode,
        int TagData,
        char sItemString[16],
        int* pColorCode,
        COLORREF* pRGB,
        double* pFontSize);

    inline virtual void OnFunctionCall(int FunctionId,
        const char* sItemString,
        POINT Pt,
        RECT Area);

    virtual void OnAirportRunwayActivityChanged();

    inline virtual void OnCompilePrivateChat(const char* sSenderCallsign, const char* sReceiverCallsign, const char* sChatMessage);

    static void SendKeyboardPresses(std::vector<WORD> message);
    static void SendKeyboardString(std::string str);
    static POINT prevMousePt;
    static int prevMouseDelta;
    static bool mouseAtRest;

};