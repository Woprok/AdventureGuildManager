#ifndef COMMON_DATA_ENTITIES
#define COMMON_DATA_ENTITIES

#include <string>

#include "BasicEntities.hpp"

class GoldFameData
{
public:
	GoldFameData(int new_gold, int new_fame): gold(new_gold), fame(new_fame) {}
	GoldFameData(GoldFameData& new_data)
		: GoldFameData(new_data.gold.get_value(), new_data.fame.get_value()) {}
	virtual ~GoldFameData() = default;
	ChangeEntity<int> gold;
	ChangeEntity<int> fame;
};

class GoldFameDeadlyData : GoldFameData
{
public:
	GoldFameDeadlyData(int new_gold, int new_fame, bool is_deadly)
		: GoldFameData(new_gold, new_fame), deadly(is_deadly) {}
	GoldFameDeadlyData(GoldFameDeadlyData& new_data)
		: GoldFameData(new_data), deadly(new_data.deadly.get_value()) {}
	virtual ~GoldFameDeadlyData() = default;
	GetSetEntity<bool> deadly;
};


#endif