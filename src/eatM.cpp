#include "eatM.h"
#include "eatL.h"
#include "eatS.h"
//===============================================
bool eatM::handleCollisione(SFish& SFish)
{
	return false;
}
//===============================================
bool eatM::handleCollisione(MFish& MFish)
{
	return false;
}
//===============================================
bool eatM::handleCollisione(LFish& LFish)
{
	LFish.setEat();
	return true;
}
//===============================================
void eatM::handleCollisione(SmartObject& smartObject ,std::function<void(size_t, Score)> func)
{
	smartObject.handleCollisione(*this, func);
}
//===============================================
bool eatM::isGrow(size_t score)
{
	return score > M_GROWTH ? true : false;
};
//===============================================
bool eatM::isSmaller(size_t score)
{
	return score < M_GROWTH ? true : false;
};
//===============================================
std::unique_ptr<PlayerBaseBehavior> eatM::increaseBehavior()
{
	return std::make_unique<eatL>();
}

std::unique_ptr<PlayerBaseBehavior> eatM::decreaseBehavior()
{
	return std::make_unique<eatS>();
}