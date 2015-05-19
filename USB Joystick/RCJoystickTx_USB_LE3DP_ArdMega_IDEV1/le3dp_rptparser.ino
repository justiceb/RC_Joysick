#include "le3dp_rptparser.h"

int Joyvar0;
int Joyvar1;
int Joyvar2;
int Joyvar3;
int Joyvar4;
int Joyvar5;
int Joyvar6;

JoystickReportParser::JoystickReportParser(JoystickEvents *evt) : 
	joyEvents(evt)
{}

void JoystickReportParser::Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
	bool match = true;

	// Checking if there are changes in report since the method was last called
	for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) {
		if( buf[i] != oldPad[i] ) {
			match = false;
			break;
		}
  }
  	// Calling Game Pad event handler
	if (!match && joyEvents) {
		joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

		for (uint8_t i=0; i<RPT_GAMEPAD_LEN; i++) oldPad[i] = buf[i];
	}
}


void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{

	// IanJ - Vars created for passing to main routines.
    Joyvar0 = (evt->x);
	Joyvar1 = (evt->y);
	Joyvar2 = (evt->hat);
	Joyvar3 = (evt->twist);
	Joyvar4 = (evt->slider);
	Joyvar5 = (evt->buttons_a);
	Joyvar6 = (evt->buttons_b);

}

