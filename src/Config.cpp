#include "Config.h"

/**********************************************
SPRITEPATH
Funcion que crea la ruta de acceso para que los sprte puedan cargarse correctamente

Recibe : int, numero correspondiente de frame; int movimiento correspondiente 

Retorna: string, devuelve la ruta en un string

**********************************************/
std::string spritePath(int frameNum, int action)
{
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

	//std::cout << path << std::endl;
	return path;
}

