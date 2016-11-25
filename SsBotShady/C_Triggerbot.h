#include "SDK.h"

class C_Triggerbot
{
public:
	void Think();
	void weapon();
	int weaponammo();
	int weap_id;
	int weap_am;
};

extern C_Triggerbot* G_Triggerbot;