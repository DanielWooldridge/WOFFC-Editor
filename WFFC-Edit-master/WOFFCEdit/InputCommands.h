#pragma once

struct InputCommands
{
	bool forward;
	bool back;
	bool right;
	bool left;
	bool rotRight;
	bool rotLeft;

	// Mouse Selection
	int mouse_X;
	int mouse_Y;
	bool mouse_LB_Down;

	// Mouse camera
	bool mouse_RB_Down;
	int mcamX;
	int mcamY;
	bool arc_Cam_Enabled;

};
