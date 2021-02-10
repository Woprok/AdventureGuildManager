#ifndef SKILL_DATA_KEEPERS_HPP
#define SKILL_DATA_KEEPERS_HPP

#include <iterator>
#include <memory>
#include <random>
#include <unordered_map>
#include <unordered_set>

#include "../Helpers/EntityCreators.hpp"
#include "../Interfaces/ISkills.hpp"
#include "../Interfaces/IPerks.hpp"
#include "../Perks/Perks.hpp"
#include "../Skills/QuestTypeCounterSkills.hpp"
#include "../Skills/Skills.hpp"

typedef ParameterEntityCreator<ISkill> SkillCreator;
typedef std::unique_ptr<SkillCreator> VirtualSkillCreator;
typedef std::unordered_set<int> IdSet;
template<typename TSkill>
using FullSkillCreator = IdEntityCreator<ISkill, TSkill>;

class SkillDataKeeper
{
public:
	SkillDataKeeper()
	{
		fill_skill_creator();
		finalize_skill_instances();
	}
	~SkillDataKeeper() = default;
	
	/// <summary>
	/// Uses default restriction system.
	/// </summary>
	skill_set&& generate(int skill_count)
	{
		return std::move(generate_skills(skill_count, get_raw_options(restricted_skills)));
	}
	/// <summary>
	/// Uses custom restriction sytem with default system.
	/// </summary>
	skill_set&& generate(int skill_count, const skill_set& restriction)
	{
		return std::move(generate_skills(skill_count, get_raw_options(restriction)));
	}

	std::unique_ptr<ISkill> create_skill(int skill_id)
	{
		if (skill_creators.contains(skill_id))
		{
			return skill_creators[skill_id]->create_entity();
		}
		throw("SkillDataKeeper does not contain fallback type.");
	}
	
	const skill_set& get_defined_skills() const { return skill_instances; }
protected:
	std::unordered_map<int, VirtualSkillCreator> skill_creators{};
	skill_set skill_instances{};
	skill_set restricted_skills{ std::make_unique<Godslayer>(GODSLAYER_ID) };
	IdSet skill_ids{};

	void fill_skill_creator()
	{
		skill_creators[GODSLAYER_ID] = std::make_unique<FullSkillCreator<Godslayer>>(GODSLAYER_ID);
		skill_creators[1] = std::make_unique<FullSkillCreator<Lucky>>(1);
		skill_creators[2] = std::make_unique<FullSkillCreator<GoldHoarder>>(2);
		skill_creators[3] = std::make_unique<FullSkillCreator<Entertainer>>(3);
		skill_creators[4] = std::make_unique<FullSkillCreator<EscapeArtist>>(4);
		skill_creators[5] = std::make_unique<FullSkillCreator<Noble>>(5);
		skill_creators[6] = std::make_unique<FullSkillCreator<Saviour>>(6);
		skill_creators[100] = std::make_unique<FullSkillCreator<Barbarian>>(100);
		skill_creators[101] = std::make_unique<FullSkillCreator<Assassin>>(101);
		skill_creators[102] = std::make_unique<FullSkillCreator<Mage>>(102);
		skill_creators[103] = std::make_unique<FullSkillCreator<Healer>>(103);
		skill_creators[104] = std::make_unique<FullSkillCreator<Paladin>>(104);
		skill_creators[105] = std::make_unique<FullSkillCreator<Shaman>>(105);
		skill_creators[106] = std::make_unique<FullSkillCreator<Fighter>>(106);
		skill_creators[107] = std::make_unique<FullSkillCreator<Lightbearer>>(107);
		skill_creators[108] = std::make_unique<FullSkillCreator<SurvivalExpert>>(108);
		skill_creators[109] = std::make_unique<FullSkillCreator<Woodcutter>>(109);
		skill_creators[110] = std::make_unique<FullSkillCreator<Digger>>(110);
		skill_creators[111] = std::make_unique<FullSkillCreator<Pyromaniac>>(111);
		skill_creators[112] = std::make_unique<FullSkillCreator<Bard>>(112);
		skill_creators[113] = std::make_unique<FullSkillCreator<Troll>>(113);
		skill_creators[114] = std::make_unique<FullSkillCreator<Warlock>>(114);
		skill_creators[115] = std::make_unique<FullSkillCreator<Clown>>(115);
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
		for (const auto& skill : restriction)
		{
			raw.erase(skill->get_id());
		}
		for (const auto& skill : restricted_skills)
		{
			raw.erase(skill->get_id());
		}
		return raw;
	}

	skill_set&& generate_skills(int skill_count, const IdSet&& raw_set)
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
		return std::move(return_skills);
	}
};

#endif