﻿#ifndef SKILL_KEEPERS_HPP
#define SKILL_KEEPERS_HPP

#include <iterator>
#include <memory>
#include <random>
#include <unordered_map>
#include <unordered_set>

#include "../Helpers/EntityCreators.hpp"
#include "../Interfaces/ISkills.hpp"
#include "../Skills/Skills.hpp"

typedef ParameterEntityCreator<ISkill> SkillCreator;
typedef std::unique_ptr<SkillCreator> VirtualSkillCreator;
typedef std::unordered_set<int> IdSet;
template<typename TSkill>
using FullSkillCreator = IdEntityCreator<ISkill, TSkill>;

class SkillKeeper
{
public:
	SkillKeeper()
	{
		fill_skill_creator();
		finalize_skill_instances();
	}
	~SkillKeeper() = default;
	
	/// <summary>
	/// Uses default restriction system.
	/// </summary>
	skill_set generate(int skill_count)
	{
		return generate_skills(skill_count, get_raw_options(restricted_skills));
	}
	/// <summary>
	/// Uses custom restriction sytem.
	/// </summary>
	skill_set generate(int skill_count, const skill_set& restriction)
	{
		return generate_skills(skill_count, get_raw_options(restriction));
	}

	const skill_set& get_defined_skills() const { return skill_instances; }
protected:
	std::unordered_map<int, VirtualSkillCreator> skill_creators{};
	skill_set skill_instances{};
	skill_set restricted_skills{ std::unique_ptr<Lucky>() };
	IdSet skill_ids{};

	void fill_skill_creator()
	{
		skill_creators[1] = std::make_unique<FullSkillCreator<Lucky>>(1);
		skill_creators[2] = std::make_unique<FullSkillCreator<Lucky>>(2);
		skill_creators[3] = std::make_unique<FullSkillCreator<Lucky>>(3);
		skill_creators[4] = std::make_unique<FullSkillCreator<Lucky>>(4);
		skill_creators[5] = std::make_unique<FullSkillCreator<Lucky>>(5);
		skill_creators[100] = std::make_unique<FullSkillCreator<Lucky>>(100);
		skill_creators[101] = std::make_unique<FullSkillCreator<Lucky>>(101);
		skill_creators[102] = std::make_unique<FullSkillCreator<Lucky>>(102);
		skill_creators[103] = std::make_unique<FullSkillCreator<Lucky>>(103);
		skill_creators[104] = std::make_unique<FullSkillCreator<Lucky>>(104);
		skill_creators[105] = std::make_unique<FullSkillCreator<Lucky>>(105);
		skill_creators[106] = std::make_unique<FullSkillCreator<Lucky>>(106);
		skill_creators[107] = std::make_unique<FullSkillCreator<Lucky>>(107);
		skill_creators[108] = std::make_unique<FullSkillCreator<Lucky>>(108);
		skill_creators[109] = std::make_unique<FullSkillCreator<Lucky>>(109);
	}

	void finalize_skill_instances()
	{
		for (auto&& skill_creator : skill_creators)
		{
			auto&& new_skill = skill_creator.second->create_entity();
			skill_ids.insert(new_skill->get_id());
			skill_instances.insert(std::move(new_skill));
		}
	}
private:
	IdSet get_raw_options(const skill_set& restriction)
	{
		IdSet raw = skill_ids;
		for (auto&& skill : restriction)
		{
			raw.erase(skill->get_id());
		}
		return raw;
	}

	skill_set generate_skills(int skill_count, const IdSet&& raw_set)
	{
		std::unordered_set<int> result;
		std::sample(raw_set.begin(),
			raw_set.end(),
			std::inserter(result, result.begin()),
			std::clamp(skill_count, 0, static_cast<int>(raw_set.size())),
			std::mt19937{ std::random_device{}() });

		skill_set return_skills;
		for (auto&& value : result)
		{
			return_skills.insert(create_skill(value));
		}
		return return_skills;
	}

	std::unique_ptr<ISkill> create_skill(int skill_id)
	{
		if (skill_creators.contains(skill_id))
		{
			return skill_creators[skill_id]->create_entity();
		}
		throw("SkillKeeper does not contain fallback type.");
	}
};

#endif