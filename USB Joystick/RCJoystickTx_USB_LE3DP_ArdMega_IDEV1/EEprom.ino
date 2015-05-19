/*

EEprom Read/Write

Value in EEprom must always be positive (0-255) and since the value to be written may
be negative, by adding the maximum allowable trim value in the range ensures it
is always positive. However, this sets a limit of 127 on trimMax (254 max to eprom).

*/

// Eprom write with offset
void EEpromwrite() {
    Epromvar = Epromvar + trimMax;  // Value in Eprom always positive
	EEPROM.write(EpromPointer + RatesHIMIDLOEEprom + Offset + ModelAddressOffset, Epromvar);
}
// Eprom read with offset
void EEpromread() { 
	Epromvar = EEPROM.read(EpromPointer + RatesHIMIDLOEEprom + Offset + ModelAddressOffset);
	Epromvar = Epromvar - trimMax;  // Value back to +/-
}


// Direct Eprom write with offset
void EEpromwriteDirect() { 
	EEPROM.write(Address + ModelAddressOffset, Epromvar);
}
// Direct Eprom read with offset
void EEpromreadDirect() { 
	Epromvar = EEPROM.read(Address + ModelAddressOffset);
}


// Direct Eprom write no offset
void EEpromwriteDirectNoOffset() { 
	EEPROM.write(Address, Epromvar);
}
// Direct Eprom read no offset
void EEpromreadDirectNoOffset() { 
	Epromvar = EEPROM.read(Address);
}