#include "Config.h"

std::string spritePath(int frameNum, int action)
{
	ALLEGRO_BITMAP* sprite; 
	std::string path = "";
	if (action == WALK)
	{
		path += "res\\wwalking\\wwalk-F";
		path += std::to_string(frameNum);
		path += ".png";
	}

	if (action == JUMP)
	{
		path += "res\\wjump\\wjump-F";
		path += std::to_string(frameNum);
		path += ".png";
	}

	return path;
}