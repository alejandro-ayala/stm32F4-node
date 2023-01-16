
#pragma once
#include "../../include/Definitions.h"
namespace Hardware
{
class IController {
public:
	cstring name;
	bool initialized;

	IController(cstring name) : name(name), initialized(false){};
	virtual ~IController(){};

	virtual void initialize() = 0;
	virtual bool selfTest()   = 0;
};
}
