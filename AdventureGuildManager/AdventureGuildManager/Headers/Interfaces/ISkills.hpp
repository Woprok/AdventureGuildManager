#ifndef I_SKILLS_HPP
#define I_SKILLS_HPP

#include <string>

#include "../Entities/BasicEntities.hpp"
#include "../Entities/CommonDataEntities.hpp"
#include "../Entities/QuestEntities.hpp"


class ISkill : public IdNameEntity
{
public:
	ISkill(std::string&& new_name, int new_id, std::string&& new_description) : IdNameEntity(std::move(new_name), new_id), description(std::move(new_description)) {}
	virtual ~ISkill() = default;
	ISkill(const ISkill&) = delete;
	ISkill& operator=(ISkill) = delete;
	const std::string& get_description() const { return description; }
	virtual void execute_reward_change([[maybe_unused]] GoldFameData& data, [[maybe_unused]] int& experience) { }
	virtual void execute_penalty_change([[maybe_unused]] GoldFameDeadlyData& data, [[maybe_unused]] int& experience) { }
	virtual void execute_roll_result_change([[maybe_unused]] const quest_type_set& types, [[maybe_unused]] bool& result) { }
	virtual void execute_roll_calculation_change([[maybe_unused]] int& adventurer_level) { }
protected:
	std::string description;
};

typedef std::unordered_set<std::unique_ptr<ISkill>> skill_set;

#endif