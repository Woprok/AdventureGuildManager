#ifndef	QUEST_TYPE_COUNTER_SKILLS_HPP
#define QUEST_TYPE_COUNTER_SKILLS_HPP

#include "../Entities/QuestEntities.hpp"
#include "../Generators/NeutralGenerators.hpp"
#include "../Interfaces/ISkills.hpp"

constexpr int MIN_GEN_VALUE = 1;
constexpr int MAX_GEN_VALUE = 100;

class QuestTypeCounterSkill : public ISkill
{
public:
	QuestTypeCounterSkill(std::string&& new_name, int new_id, std::string&& new_description, QuestType counter_type)
		: ISkill(std::move(new_name), new_id, std::move(new_description)), quest_type(counter_type) {}
	~QuestTypeCounterSkill() override = default;
	QuestTypeCounterSkill(const QuestTypeCounterSkill&) = delete;
	QuestTypeCounterSkill& operator=(QuestTypeCounterSkill) = delete;
	void execute_roll_result_change(const quest_type_set& types, bool& result) override
	{
		if (types.contains(quest_type))
		{
			result = result || chance.get_next() > 75;
		}
	}
protected:
	QuestType quest_type;
	static inline UniformGenerator chance{ MIN_GEN_VALUE, MAX_GEN_VALUE };
};

class Barbarian : public QuestTypeCounterSkill
{
public:
	Barbarian(int id) : QuestTypeCounterSkill("Barbarian", id, "Destroy all minions.", QuestType::Minions) {}
	~Barbarian() override = default;
	Barbarian(const Barbarian&) = delete;
	Barbarian& operator=(Barbarian) = delete;
};
class Assassin : public QuestTypeCounterSkill
{
public:
	Assassin(int id) : QuestTypeCounterSkill("Assassin", id, "Destroy boss.", QuestType::Boss) {}
	~Assassin() override = default;
	Assassin(const Assassin&) = delete;
	Assassin& operator=(Assassin) = delete;
};
class Mage : public QuestTypeCounterSkill
{
public:
	Mage(int id) : QuestTypeCounterSkill("Mage", id, "Conquer all magical.", QuestType::Magical) {}
	~Mage() override = default;
	Mage(const Mage&) = delete;
	Mage& operator=(Mage) = delete;
};
class Healer : public QuestTypeCounterSkill
{
public:
	Healer(int id) : QuestTypeCounterSkill("Healer", id, "Bane of all bleeding wounds.", QuestType::Bleeding) {}
	~Healer() override = default;
	Healer(const Healer&) = delete;
	Healer& operator=(Healer) = delete;
};
class Paladin : public QuestTypeCounterSkill
{
public:
	Paladin(int id) : QuestTypeCounterSkill("Paladin", id, "Hallow is his presence.", QuestType::Curse) {}
	~Paladin() override = default;
	Paladin(const Paladin&) = delete;
	Paladin& operator=(Paladin) = delete;
};
class Shaman : public QuestTypeCounterSkill
{
public:
	Shaman(int id) : QuestTypeCounterSkill("Shaman", id, "Herbs solve all toxic problems.", QuestType::Poison) {}
	~Shaman() override = default;
	Shaman(const Shaman&) = delete;
	Shaman& operator=(Shaman) = delete;
};
class Fighter : public QuestTypeCounterSkill
{
public:
	Fighter(int id) : QuestTypeCounterSkill("Fighter", id, "Secure kill.", QuestType::Boss) {}
	~Fighter() override = default;
	Fighter(const Fighter&) = delete;
	Fighter& operator=(Fighter) = delete;
};
class Lightbearer : public QuestTypeCounterSkill
{
public:
	Lightbearer(int id) : QuestTypeCounterSkill("Lightbearer", id, "The one who carries a torch.", QuestType::Darkness) {}
	~Lightbearer() override = default;
	Lightbearer(const Lightbearer&) = delete;
	Lightbearer& operator=(Lightbearer) = delete;
};
class SurvivalExpert : public QuestTypeCounterSkill
{
public:
	SurvivalExpert(int id) : QuestTypeCounterSkill("Survival Expert", id, "I am not sure if he knows how to live in a society.", QuestType::Wilderness) {}
	~SurvivalExpert() override = default;
	SurvivalExpert(const SurvivalExpert&) = delete;
	SurvivalExpert& operator=(SurvivalExpert) = delete;
};

class Woodcutter : public QuestTypeCounterSkill
{
public:
	Woodcutter(int id) : QuestTypeCounterSkill("Woodcutter", id, "Natural enemy for humans with pointy ears.", QuestType::Elfs) {}
	~Woodcutter() override = default;
	Woodcutter(const Woodcutter&) = delete;
	Woodcutter& operator=(Woodcutter) = delete;
};
class Digger : public QuestTypeCounterSkill
{
public:
	Digger(int id) : QuestTypeCounterSkill("Digger", id, "Dig a hole with dwarf. Unnamed team that reached moon.", QuestType::Dwarfs) {}
	~Digger() override = default;
	Digger(const Digger&) = delete;
	Digger& operator=(Digger) = delete;
};
class Pyromaniac : public QuestTypeCounterSkill
{
public:
	Pyromaniac(int id) : QuestTypeCounterSkill("Pyromaniac", id, "Burn it. Seriously burn it all. Extra effective against minions, and quite good against everything else too.", QuestType::Minions) {}
	~Pyromaniac() override = default;
	Pyromaniac(const Pyromaniac&) = delete;
	Pyromaniac& operator=(Pyromaniac) = delete;
	void execute_roll_result_change(const quest_type_set& types, bool& result) override
	{
		if (types.contains(quest_type))
		{
			result = result || chance.get_next() > 75;
		}
		else
		{
			result = result || chance.get_next() > 90;
		}
	}
};
class Bard : public QuestTypeCounterSkill
{
public:
	Bard(int id) : QuestTypeCounterSkill("Bard", id, "No one can stop bard performance, not even trolls.", QuestType::Memes) {}
	~Bard() override = default;
	Bard(const Bard&) = delete;
	Bard& operator=(Bard) = delete;
};
class Troll : public QuestTypeCounterSkill
{
public:
	Troll(int id) : QuestTypeCounterSkill("Troll", id, "After reincarnation: Internet was never a safe place from me.", QuestType::Dankness) {}
	~Troll() override = default;
	Troll(const Troll&) = delete;
	Troll& operator=(Troll) = delete;
};
class Warlock : public QuestTypeCounterSkill
{
public:
	Warlock(int id) : QuestTypeCounterSkill("Warlock", id, "The great old one, take this little one as a gift.", QuestType::Fairies) {}
	~Warlock() override = default;
	Warlock(const Warlock&) = delete;
	Warlock& operator=(Warlock) = delete;
};
class Clown : public QuestTypeCounterSkill
{
public:
	Clown(int id) : QuestTypeCounterSkill("Clown", id, "Red nose vs white face. Fight now!", QuestType::Mimes) {}
	~Clown() override = default;
	Clown(const Clown&) = delete;
	Clown& operator=(Clown) = delete;
};

#endif