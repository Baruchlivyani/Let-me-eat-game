#include "AnimationData.h"
#include <iostream>
//===============================================
AnimationData::AnimationData(std::vector<details> detailsVec)
{
	for (size_t i = 0; i < detailsVec.size(); i++)
		for (size_t j = 0; j < detailsVec[i].sumImages; j++)
			m_data[detailsVec[i].mood].emplace_back(nextStart(detailsVec[i], j), detailsVec[i].size);

}
//===============================================
sf::Vector2i AnimationData::nextStart(struct details& details, size_t index) const
{
	return details.location + sf::Vector2i((details.size.x + details.middleSpace.x) * index, 0);
}
//===============================================
AnimationData::DataType& AnimationData::AnimationDataData()
{
	return m_data;
}