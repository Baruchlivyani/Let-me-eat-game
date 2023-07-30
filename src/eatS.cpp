#include "eatS.h"
#include "eatM.h"
#include "eatL.h"
//===============================================
bool eatS::handleCollisione(SFish& SFish)
{
	return false;
}
//===============================================
bool eatS::handleCollisione(MFish& MFish)
{
	MFish.updateMood(Mood::Stay, false);
	MFish.setEat();
	return true;
}
//===============================================
bool eatS::handleCollisione(LFish& LFish)
{
	LFish.updateMood(Mood::Eat, false);
	LFish.setEat();
	return true;
}
//===============================================
void eatS::handleCollisione(SmartObject& smartObject , std::function<void(size_t, Score)> func)
{
	smartObject.handleCollisione(*this, func);
}
//===============================================
bool eatS::isGrow(size_t score)
{ 
	return score > S_GROWTH ?  true : false;
};
//===============================================
bool eatS::isSmaller(size_t score)
{
	return false;
};

std::unique_ptr<PlayerBaseBehavior> eatS::increaseBehavior()
{
	return std::make_unique<eatM>();
}

std::unique_ptr<PlayerBaseBehavior> eatS::decreaseBehavior()
{
	return std::make_unique<eatS>();
}