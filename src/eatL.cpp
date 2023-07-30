#include "eatL.h"
#include "eatS.h"
#include "eatM.h"
//===============================================
bool eatL::handleCollisione(SFish& SFish)
{
	return false;
}
//===============================================
bool eatL::handleCollisione(MFish& MFish)
{
	return false;
}
//===============================================
bool eatL::handleCollisione(LFish& LFish)
{
	return false;
}
//===============================================
void eatL::handleCollisione(SmartObject& smartObject, std::function<void(size_t, Score)> func)
{
	smartObject.handleCollisione(*this, func);
}
std::unique_ptr<PlayerBaseBehavior> eatL::decreaseBehavior()
{
	return std::make_unique<eatM>();
}

bool eatL::isSmaller(size_t score)
{
	return score < M_GROWTH ? true : false;
};
