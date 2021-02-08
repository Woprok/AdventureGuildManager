#ifndef I_SKILLS_HPP
#define I_SKILLS_HPP

#include <string>

#include "../Entities/BasicEntities.hpp"


class ISkill : public IdNameEntity
{
public:
	ISkill(std::string&& new_name, int new_id, std::string&& new_description) : IdNameEntity(new_name, new_id), description(new_description) {}
	virtual ~ISkill() = default;
	virtual const std::string& get_description() { return description; }
	virtual void execute_skill(/*bool& result, Quest& quest, Reward& reward, Penalty& penalty*/) = 0;
protected:
	std::string description;
};

typedef std::unordered_set<std::unique_ptr<ISkill>> skill_set;

#endif