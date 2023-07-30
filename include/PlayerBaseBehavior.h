#pragma once
#include "SmartObject.h"
#include "SFish.h"
#include "MFish.h"
#include "LFish.h"
//===============================================
class eatL;
class eatM;
class eatS;
//===============================================

//the base class of the various
//player behaviors.

class PlayerBaseBehavior
{
public:
	PlayerBaseBehavior() {};
	virtual bool handleCollisione(SFish& SFish) = 0;
	virtual bool handleCollisione(MFish& MFish) = 0;
	virtual bool handleCollisione(LFish& LFish) = 0;
	virtual void handleCollisione(SmartObject& smartObject, std::function<void(size_t, Score)> func) = 0;
	virtual std::unique_ptr<PlayerBaseBehavior> increaseBehavior() { return std::unique_ptr<PlayerBaseBehavior>(); };
	virtual std::unique_ptr<PlayerBaseBehavior> decreaseBehavior() = 0;
	virtual bool isGrow(size_t score) { return false; };
	virtual bool isSmaller(size_t score) { return false; };


private:

};
