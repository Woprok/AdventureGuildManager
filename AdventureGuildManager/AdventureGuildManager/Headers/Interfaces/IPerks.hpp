#ifndef I_PERKS_HPP
#define I_PERKS_HPP

#include <string>

#include "../Entities/BasicEntities.hpp"

class IPerk : public IdNameEntity
{
protected:
	std::string description;
public:
	GetSetEntity<int> level_requirement;
	IPerk(std::string&& new_name, int new_id, std::string&& new_description, int new_level_requirement)
		: IdNameEntity(std::move(new_name), new_id), description(std::move(new_description)), level_requirement(new_level_requirement) {}
	virtual ~IPerk() = default;
	IPerk(const IPerk&) = delete;
	IPerk& operator=(IPerk) = delete;
	const std::string& get_description() const { return description; }
	virtual void execute_reward_change([[maybe_unused]] GoldFameData& data, [[maybe_unused]] int& experience) { }
	virtual void execute_penalty_change([[maybe_unused]] GoldFameDeadlyData& data, [[maybe_unused]] int& experience) { }
	virtual void execute_wait_change([[maybe_unused]] int& expenses_total) { }
	virtual void execute_retirement_change([[maybe_unused]] int& retirement_total, [[maybe_unused]] int& retirement_fame) { }
	virtual void execute_gain_change([[maybe_unused]] GoldFameData& data, [[maybe_unused]] int& max_quest_rarity) { }
};

typedef std::unordered_set<std::unique_ptr<IPerk>> perk_set;

#endif