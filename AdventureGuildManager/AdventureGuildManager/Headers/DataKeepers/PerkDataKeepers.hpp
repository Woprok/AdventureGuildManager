#ifndef SKILL_DATA_KEEPERS_HPP
#define SKILL_DATA_KEEPERS_HPP

#include <iterator>
#include <memory>
#include <random>
#include <unordered_map>
#include <unordered_set>

#include "../Helpers/EntityCreators.hpp"
#include "../Interfaces/IPerks.hpp"
#include "../Perks/Perks.hpp"
#include "../Skills/QuestTypeCounterSkills.hpp"

typedef ParameterEntityCreator<IPerk> PerkCreator;
typedef std::unique_ptr<PerkCreator> VirtualPerkCreator;
typedef std::unordered_set<int> IdSet;
template<typename TPerk>
using FullPerkCreator = IdEntityCreator<IPerk, TPerk>;


class PerkDataKeeper
{
public:
	PerkDataKeeper()
	{
		fill_perk_creator();
		finalize_perk_instances();
	}
	~PerkDataKeeper() = default;

	std::unique_ptr<IPerk> create_perk(int perk_id)
	{
		if (perk_creators.contains(perk_id))
		{
			return perk_creators[perk_id]->create_entity();
		}
		throw("PerkDataKeeper does not contain fallback type.");
	}

	const perk_set& get_defined_skills() const { return perk_instances; }
protected:
	std::unordered_map<int, VirtualPerkCreator> perk_creators{};
	perk_set perk_instances{};

	void fill_perk_creator()
	{
		perk_creators[TRADE_FAME_PERK] = std::make_unique<FullPerkCreator<TradeFame>>(TRADE_FAME_PERK);
		perk_creators[REQUALIFICATION_COURSE_PERK] = std::make_unique<FullPerkCreator<RequalificationCourse>>(REQUALIFICATION_COURSE_PERK);
		perk_creators[ARMORY_PERK] = std::make_unique<FullPerkCreator<Armory>>(ARMORY_PERK);
		perk_creators[CHURCH_OF_HEROES_PERK] = std::make_unique<FullPerkCreator<ChurchOfHeroes>>(CHURCH_OF_HEROES_PERK);
		perk_creators[MADNESS_OF_MASTER_PERK] = std::make_unique<FullPerkCreator<MadnessOfMaster>>(MADNESS_OF_MASTER_PERK);
		perk_creators[SHARED_EXPERIENCE_PERK] = std::make_unique<FullPerkCreator<SharedExperience>>(SHARED_EXPERIENCE_PERK);
		perk_creators[RETIREMENT_SAVINGS_PERK] = std::make_unique<FullPerkCreator<RetirementSavings>>(RETIREMENT_SAVINGS_PERK);
		perk_creators[DANGEROUS_EXPEDITION_PERK] = std::make_unique<FullPerkCreator<DangerousExpeditions>>(DANGEROUS_EXPEDITION_PERK);
		perk_creators[LEGENDARY_HEROES_PERK] = std::make_unique<FullPerkCreator<LegendaryHeroes>>(LEGENDARY_HEROES_PERK);
	}

	void finalize_perk_instances()
	{
		for (auto&& perk_creator : perk_creators)
		{
			perk_instances.insert(std::move(perk_creator->create_entity()));
		}
	}
};

#endif