#ifndef SKILLS_HPP
#define SKILLS_HPP

#include "GameEntities.hpp"
#include "Generators.hpp"
#include "GenericEntities.hpp"
#include "Quests.hpp"

template<class TInterface>
class EntityCreatorBase
{
public:
	virtual ~EntityCreatorBase() = default;
	virtual std::unique_ptr<TInterface> create_entity() = 0;
	virtual int get_skill_id() = 0;
};

template<class TInterface, class TCreatable>
class SimpleEntityCreator : public EntityCreatorBase<TInterface>
{
	static_assert(std::is_base_of<TInterface, TCreatable>::value, "TCreatable must be derived from TInterface");
public:
	SimpleEntityCreator(int defined_skill_id) : skill_id(defined_skill_id) {}
	std::unique_ptr<TInterface> create_entity() override
	{
		return std::make_unique<TCreatable>(skill_id);
	}
	int get_skill_id() override { return skill_id; }
protected:
	int skill_id;
};


class ISkill : public NamedEntity
{
public:
	ISkill(int defined_skill_id, std::string skill_name) : NamedEntity(skill_name), skill_id(defined_skill_id) {}
	virtual ~ISkill() = default;
	virtual void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) = 0;
	int get_skill_id() const { return skill_id; }
	//bool operator==(const ISkill& qtw) const { return qtw.skill_id == skill_id; }
	//size_t operator()(const ISkill& qtw) const { return static_cast<size_t>(qtw.skill_id); }
protected:
	int skill_id;
};

/*namespace std
{
	template<> struct hash<ISkill>
	{
		std::size_t operator()(QuestTypeWrapper const& s) const noexcept
		{
			return static_cast<size_t>(s.get_self());
		}
	};
}*/

typedef std::unordered_set<std::unique_ptr<ISkill>> skill_collection;

class Hoarder : public ISkill
{
public:
	Hoarder(int id) : ISkill(id,"Hoarder") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		reward.set_gold(reward.get_gold() * 1.2);
	}
};
class EscapeArtist : public ISkill
{
public:
	EscapeArtist(int id) : ISkill(id, "EscapeArtist") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		ChanceGenerator chance;
		penalty.set_deadly(penalty.get_deadly() && chance.get_chance() <= 75);
	}
};
class MisterHandsome : public ISkill
{
public:
	MisterHandsome(int id) : ISkill(id, "MisterHandsome") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		reward.set_fame(reward.get_fame() * 2.0);
	}
};
class PerfectHero : public ISkill
{
public:
	PerfectHero(int id) : ISkill(id,"PerfectHero") {}
	void execute_skill(bool& result, Quest& quest, Reward& reward, Penalty& penalty) override
	{
		penalty.set_gold(0);
		penalty.set_fame(0);
		penalty.set_deadly(false);
	}
};
class CounterSkill : public ISkill
{
public:
	CounterSkill(int id, std::string value) : ISkill(id, value) {}
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
	Cleave(int id) : CounterSkill(id, "Cleave") {}
	QuestType get_counter() override { return QuestType::Minions; }
};
class Assassin : public CounterSkill
{
public:
	Assassin(int id) : CounterSkill(id, "Assassin") {}
	QuestType get_counter() override { return QuestType::Boss; }
};
class Mage : public CounterSkill
{
public:
	Mage(int id) : CounterSkill(id, "Mage") {}
	QuestType get_counter() override { return QuestType::Magical; }
};
class Healer : public CounterSkill
{
public:
	Healer(int id) : CounterSkill(id, "Healer") {}
	QuestType get_counter() override { return QuestType::Bleeding; }
};
class Paladin : public CounterSkill
{
public:
	Paladin(int id) : CounterSkill(id, "Paladin") {}
	QuestType get_counter() override { return QuestType::Curse; }
};
class Shaman : public CounterSkill
{
public:
	Shaman(int id) : CounterSkill(id, "Shaman") {}
	QuestType get_counter() override { return QuestType::Poison; }
};
class Fighter : public CounterSkill
{
public:
	Fighter(int id) : CounterSkill(id, "Fighter") {}
	QuestType get_counter() override { return QuestType::Boss; }
};
class Lightbearer : public CounterSkill
{
public:
	Lightbearer(int id) : CounterSkill(id, "Lightbearer") {}
	QuestType get_counter() override { return QuestType::Darkness; }
};
class SurvivalExpert : public CounterSkill
{
public:
	SurvivalExpert(int id) : CounterSkill(id, "SurvivalExpert") {}
	QuestType get_counter() override { return QuestType::Wilderness; }
};
class Woodcutter : public CounterSkill
{
public:
	Woodcutter(int id) : CounterSkill(id, "Woodcutter") {}
	QuestType get_counter() override { return QuestType::Elfs; }
};
class Digger : public CounterSkill
{
public:
	Digger(int id) : CounterSkill(id, "Digger") {}
	QuestType get_counter() override { return QuestType::Dwarfs; }
};
class Pyromaniac : public CounterSkill
{
public:
	Pyromaniac(int id) : CounterSkill(id, "Pyromaniac") {}
	QuestType get_counter() override { return QuestType::Elfs; }
};
class Bard : public CounterSkill
{
public:
	Bard(int id) : CounterSkill(id, "Bard") {}
	QuestType get_counter() override { return QuestType::Memes; }
};
class Troll : public CounterSkill
{
public:
	Troll(int id) : CounterSkill(id, "Troll") {}
	QuestType get_counter() override { return QuestType::Dankness; }
};
class Warlock : public CounterSkill
{
public:
	Warlock(int id) : CounterSkill(id, "Warlock") {}
	QuestType get_counter() override { return QuestType::Fairies; }
};
class Clown : public CounterSkill
{
public:
	Clown(int id) : CounterSkill(id, "Clown") {}
	QuestType get_counter() override { return QuestType::Mimes; }
};
#pragma endregion 


#endif