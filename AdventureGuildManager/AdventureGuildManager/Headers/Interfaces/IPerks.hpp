#ifndef I_PERKS_HPP
#define I_PERKS_HPP

#include <string>

#include "../Entities/BasicEntities.hpp"

class IPerk : public IdNameEntity
{
public:
	IPerk(std::string new_name, int new_id, std::string&& new_description, int new_level_requirement)
		: IdNameEntity(new_name, new_id), description(new_description), level_requirement(new_level_requirement) {}
	~IPerk() = default;
	GetSetEntity<int> level_requirement;
	const std::string& get_description() const { return description; }
	virtual void execute_reward_change(GoldFameData& data, int& experience) {}
	virtual void execute_penalty_change(GoldFameDeadlyData& data, int& experience) {}
	virtual void execute_wait_change(int& expenses_total) {}
	virtual void execute_retirement_change(int& retirement_total, int& retirement_fame) {}
	virtual void execute_gain_change(GoldFameData& data, int& max_quest_rarity) {}
protected:
	std::string description;
};

typedef std::unordered_set<std::unique_ptr<IPerk>> perk_set;

#endif