#ifndef I_SKILLS_HPP
#define I_SKILLS_HPP

#include <string>

#include "../Entities/BasicEntities.hpp"
#include "../Entities/QuestEntities.hpp"


class ISkill : public IdNameEntity
{
public:
	ISkill(std::string&& new_name, int new_id, std::string&& new_description) : IdNameEntity(new_name, new_id), description(new_description) {}
	virtual ~ISkill() = default;
	virtual const std::string& get_description() { return description; }
	virtual void execute_reward_change(GoldFameData& data, int& experience) {}
	virtual void execute_penalty_change(GoldFameDeadlyData& data, int& experience) {}
	virtual void execute_roll_result_change(const quest_type_set& types, bool& result) {}
	virtual void execute_roll_calculation_change(int& adventurer_level) {}
protected:
	std::string description;
};

typedef std::unordered_set<std::unique_ptr<ISkill>> skill_set;

#endif