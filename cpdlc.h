#pragma once

#include "curl/curl.h"
#include <EuroScopePlugIn.h>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <vector>

class CPDLCMessage {

private:


public:
	const static std::string hoppieCode;  // Hoppie Logon Code
	const static std::string hoppieICAO;
	static u_int CPDLCMessage::ids;
	int id;

	bool isdlMessage; // if not DL message, then it is UL message
	bool isCompleted{ false }; // checkmark if completed
	bool sent{ false };

	std::time_t timeParsed; // time that message was created
	std::string hoppieMessageID{""}; // from the api, empty string if doesn't exist
	std::string messageType; // telex or CPDLC

	std::string sender;
	std::string receipient;
	int messageID{ -1 };
	int responseToMessageID{ -1 };
	std::string responseRequired;
	std::string rawMessageContent;

	u_int ARINCmessageType; // standardized ARINC message type for CPDLC

	CPDLCMessage();
	~CPDLCMessage();

	static std::string CPDLCMessage::PollCPDLCMessages();
	CPDLCMessage MakePDCMessage(EuroScopePlugIn::CFlightPlan& flightplan, EuroScopePlugIn::CController& controller, std::string atisLetter);
	void SendCPDLCMessage();
	static CPDLCMessage parseDLMessage(std::string& rawMessage);
	void processMessage();


	// Formating Helpers

	static std::string ZuluTimeStringGen();
	static std::string FreqTruncate(double freq);
	static std::string YYMMDDString();
	static std::string ZuluTimeFormated(std::time_t time);
};