#include "pch.h"
#include "vatsimAPI.h"
#include "SituPlugin.h"
#include "CSiTRadar.h"
#include "json.hpp"
#include "curl/curl.h"

// Include dependency
using json = nlohmann::json;
string CDataHandler::url1;
int CDataHandler::refreshInterval;

static size_t write_data(void* buffer, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)buffer, size * nmemb);
	return size * nmemb;
}

void CDataHandler::loadSettings() {
	try {
		std::ifstream settings_file(".\\settings.json");
		json j = json::parse(settings_file);

		CDataHandler::url1 = j["slotURL"];
		CDataHandler::refreshInterval = j["refreshInterval"];
	}
	catch (std::ifstream::failure e) {
		
	};
}

void CDataHandler::GetVatsimAPIData(void* args) {

	CAsync* data = (CAsync*)args;

	string cidString;
	json cidJson;

	CURL* curl = curl_easy_init();
	CURL* curl1 = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, CDataHandler::url1.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cidString);
		CURLcode res;
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}

	try {

		// Now we parse the json
		cidJson = json::parse(cidString);

		// Everything succeeded, show to user

		data->Plugin->DisplayUserMessage("VATCAN Situ", "Update Successful", string("CTP slot times parsed").c_str(), true, false, false, false, false);

	}
	catch (exception& e) {
		data->Plugin->DisplayUserMessage("VATCAN Situ", "Error", string("Failed to parse CID data" + string(e.what())).c_str(), true, true, true, true, true);

	}

	// Parse CID data from the VATSIM API

	string responseString;

	if (curl1)
	{
		curl_easy_setopt(curl1, CURLOPT_URL, "http://cluster.data.vatsim.net/vatsim-data.json");
		curl_easy_setopt(curl1, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl1, CURLOPT_WRITEDATA, &responseString);
		CURLcode res;
		res = curl_easy_perform(curl1);
		curl_easy_cleanup(curl1);
	}

	try {

		// Now we parse the json
		auto jsonArray = json::parse(responseString);
		if (!cidJson["pilots"].empty()) {
			for (auto& pilots : cidJson["pilots"]) {
				string cid = to_string(pilots["cid"]);
				string slot = pilots["slot"];

				CSiTRadar::slotTime[cid] = slot;
			}
		}

		if (!jsonArray["clients"].empty()) {
			for (auto& array : jsonArray["clients"]) {
				string apiCallsign = array["callsign"];
				string apiCID = array["cid"];

				CSiTRadar::mAcData[apiCallsign].CID = apiCID;

				if (CSiTRadar::slotTime.find(apiCID) != CSiTRadar::slotTime.end()) {
					CSiTRadar::mAcData[apiCallsign].slotTime = CSiTRadar::slotTime[apiCID];
					CSiTRadar::mAcData[apiCallsign].hasCTP = TRUE;
				}
				else {
					CSiTRadar::mAcData[apiCallsign].slotTime = "";
					CSiTRadar::mAcData[apiCallsign].hasCTP = FALSE;
				}
			}
		}

		string timeStamp = jsonArray["general"]["update_timestamp"];

		// Everything succeeded, show to user
		data->Plugin->DisplayUserMessage("Slot Helper", "Update Successful", string("Slot times validated at " + timeStamp).c_str(), true, false, false, false, false);

	}
	catch (exception& e) {
		data->Plugin->DisplayUserMessage("Slot Helper", "Error", string("Failed to parse CID data" + string(e.what())).c_str(), true, true, true, true, true);
	}

	CSiTRadar::canAmend = TRUE;

	delete args;
}

void CDataHandler::AmendFlightPlans(void* args) {

	CAsync* data = (CAsync*)args;
	string oldRemarks;
	string newRemarks;
	int countFP = 0;

	struct tm gmt;
	time_t t = time(0);
	gmtime_s(&gmt, &t);

	char timeStr[50];
	strftime(timeStr, 50, "%H%MZ", &gmt);

	for (CFlightPlan flightPlan = data->Plugin->FlightPlanSelectFirst(); flightPlan.IsValid();
		flightPlan = data->Plugin->FlightPlanSelectNext(flightPlan)) {
		oldRemarks = flightPlan.GetFlightPlanData().GetRemarks();

		// if the callsign has not been correlated with a CID, don't try to amend the Flightplan yet, needs update from vatsim status
		if (CSiTRadar::mAcData[flightPlan.GetCallsign()].CID == "") { continue; }

		if (flightPlan.GetFlightPlanData().IsReceived()) {

			if (CSiTRadar::mAcData[flightPlan.GetCallsign()].hasCTP == TRUE) {
				oldRemarks = flightPlan.GetFlightPlanData().GetRemarks();

				if (oldRemarks.find("CTP SLOT") == string::npos) {

					newRemarks = (string)"CTP SLOT / " + timeStr + " " + oldRemarks;
					flightPlan.GetFlightPlanData().SetRemarks(newRemarks.c_str());
				}
			}
			// If someone adds CTP SLOT to their remarks, but isn't on the list, then flag this in the remarks
			else {
				if (oldRemarks.find("CTP SLOT") != string::npos && oldRemarks.find("CTP MISMATCH") == string::npos) {
					newRemarks = (string)"CTP MISMATCH / NON EVENT / " + timeStr + " " + oldRemarks;

					flightPlan.GetFlightPlanData().SetRemarks(newRemarks.c_str());
				}

				else if (oldRemarks.find("NON EVENT") == string::npos) {
					newRemarks = (string)"NON EVENT / " + timeStr + " " + oldRemarks;

					flightPlan.GetFlightPlanData().SetRemarks(newRemarks.c_str());
				}
			}
			flightPlan.GetFlightPlanData().AmendFlightPlan();
		}
		countFP++;
	}
	data->Plugin->DisplayUserMessage("Slot Helper", "Success", (to_string(countFP) + (string)" Flight Plans Updated").c_str(), true, false, false, false, false);

	delete args;
}