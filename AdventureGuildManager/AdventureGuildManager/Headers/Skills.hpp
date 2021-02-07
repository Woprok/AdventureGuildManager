#ifndef SKILLS_HPP
#define SKILLS_HPP

#include "GameEntities.hpp"
#include "Generators.hpp"
#include "GenericEntities.hpp"
#include "Quests.hpp"

class Skill : public NamedEntity
{
public:
	Skill(std::string skill_name) : NamedEntity(skill_name) {}
	virtual void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) = 0;
};

typedef std::unordered_set<std::unique_ptr<Skill>> skill_collection;

class Hoarder : public Skill
{
public:
	Hoarder() : Skill("Hoarder") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		reward.set_gold(reward.get_gold() * 1.2);
	}
};
class EscapeArtist : public Skill
{
public:
	EscapeArtist() : Skill("EscapeArtist") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		ChanceGenerator chance;
		penalty.set_deadly(penalty.get_deadly() && chance.get_chance() <= 75);
	}
};
class MisterHandsome : public Skill
{
public:
	MisterHandsome() : Skill("MisterHandsome") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		reward.set_fame(reward.get_fame() * 2.0);
	}
};
class PerfectHero : public Skill
{
public:
	PerfectHero() : Skill("PerfectHero") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		penalty.set_gold(0);
		penalty.set_fame(0);
		penalty.set_deadly(false);
	}
};
class CounterSkill : public Skill
{
public:
	CounterSkill(std::string value) : Skill(value) {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		ChanceGenerator chance;
		if (quest.has_quest_type(get_counter()))
		{
			result = result || chance.get_chance() > 75;
		}
	}
	virtual QuestType get_counter() = 0;
};
#pragma region Skills
class Cleave : public CounterSkill
{
public:
	Cleave() : CounterSkill("Cleave") {}
	QuestType get_counter() override { return QuestType::Minions; }
};
class Assassin : public CounterSkill
{
public:
	Assassin() : CounterSkill("Assassin") {}
	QuestType get_counter() override { return QuestType::Boss; }
};
class Mage : public CounterSkill
{
public:
	Mage() : CounterSkill("Mage") {}
	QuestType get_counter() override { return QuestType::Magical; }
};
class Healer : public CounterSkill
{
public:
	Healer() : CounterSkill("Healer") {}
	QuestType get_counter() override { return QuestType::Bleeding; }
};
class Paladin : public CounterSkill
{
public:
	Paladin() : CounterSkill("Paladin") {}
	QuestType get_counter() override { return QuestType::Curse; }
};
class Shaman : public CounterSkill
{
public:
	Shaman() : CounterSkill("Shaman") {}
	QuestType get_counter() override { return QuestType::Poison; }
};
class Fighter : public CounterSkill
{
public:
	Fighter() : CounterSkill("Fighter") {}
	QuestType get_counter() override { return QuestType::Boss; }
};
class Lightbearer : public CounterSkill
{
public:
	Lightbearer() : CounterSkill("Lightbearer") {}
	QuestType get_counter() override { return QuestType::Darkness; }
};
class SurvivalExpert : public CounterSkill
{
public:
	SurvivalExpert() : CounterSkill("SurvivalExpert") {}
	QuestType get_counter() override { return QuestType::Wilderness; }
};
class Woodcutter : public CounterSkill
{
public:
	Woodcutter() : CounterSkill("Woodcutter") {}
	QuestType get_counter() override { return QuestType::Elfs; }
};
class Digger : public CounterSkill
{
public:
	Digger() : CounterSkill("Digger") {}
	QuestType get_counter() override { return QuestType::Dwarfs; }
};
class Pyromaniac : public CounterSkill
{
public:
	Pyromaniac() : CounterSkill("Pyromaniac") {}
	QuestType get_counter() override { return QuestType::Elfs; }
};
class Bard : public CounterSkill
{
public:
	Bard() : CounterSkill("Bard") {}
	QuestType get_counter() override { return QuestType::Memes; }
};
class Troll : public CounterSkill
{
public:
	Troll() : CounterSkill("Troll") {}
	QuestType get_counter() override { return QuestType::Dankness; }
};
class Warlock : public CounterSkill
{
public:
	Warlock() : CounterSkill("Warlock") {}
	QuestType get_counter() override { return QuestType::Fairies; }
};
class Clown : public CounterSkill
{
public:
	Clown() : CounterSkill("Clown") {}
	QuestType get_counter() override { return QuestType::Mimes; }
};
#pragma endregion 


#endif