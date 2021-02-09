#ifndef	QUEST_TYPE_COUNTER_SKILLS_HPP
#define QUEST_TYPE_COUNTER_SKILLS_HPP

#include "../Entities/QuestEntities.hpp"
#include "../Interfaces/ISkills.hpp"

class QuestTypeCounterSkill : public ISkill
{
public:
	QuestTypeCounterSkill(std::string&& new_name, int new_id, std::string&& new_description, QuestType counter_type)
		: ISkill(std::move(new_name), new_id, std::move(new_description)), quest_type(counter_type) {}
	~QuestTypeCounterSkill() override = default;
	void execute_skill() override
	{
		//ChanceGenerator chance;
		//if (quest.has_quest_type(get_counter()))
		//{
		//	result = result || chance.get_chance() > 75;
		//}
	}
private:
	QuestType quest_type;
};

class Barbarian : public QuestTypeCounterSkill
{
public:
	Barbarian(int id) : QuestTypeCounterSkill("Barbarian", id, "Destroy all minions.", QuestType::Minions) {}
	~Barbarian() override = default;
};
class Assassin : public QuestTypeCounterSkill
{
public:
	Assassin(int id) : QuestTypeCounterSkill("Assassin", id, "Destroy boss.", QuestType::Boss) {}
	~Assassin() override = default;
};
class Mage : public QuestTypeCounterSkill
{
public:
	Mage(int id) : QuestTypeCounterSkill("Mage", id, "Conquer all magical.", QuestType::Magical) {}
	~Mage() override = default;
};
class Healer : public QuestTypeCounterSkill
{
public:
	Healer(int id) : QuestTypeCounterSkill("Healer", id, "Bane of all bleeding wounds.", QuestType::Bleeding) {}
	~Healer() override = default;
};
class Paladin : public QuestTypeCounterSkill
{
public:
	Paladin(int id) : QuestTypeCounterSkill("Paladin", id, "Hallow is his presence.", QuestType::Curse) {}
	~Paladin() override = default;
};
class Shaman : public QuestTypeCounterSkill
{
public:
	Shaman(int id) : QuestTypeCounterSkill("Shaman", id, "Herbs solve all toxic problems.", QuestType::Poison) {}
	~Shaman() override = default;
};
class Fighter : public QuestTypeCounterSkill
{
public:
	Fighter(int id) : QuestTypeCounterSkill("Fighter", id, "Secure kill.", QuestType::Boss) {}
	~Fighter() override = default;
};
class Lightbearer : public QuestTypeCounterSkill
{
public:
	Lightbearer(int id) : QuestTypeCounterSkill("Lightbearer", id, "The one who carries a torch.", QuestType::Darkness) {}
	~Lightbearer() override = default;
};
class SurvivalExpert : public QuestTypeCounterSkill
{
public:
	SurvivalExpert(int id) : QuestTypeCounterSkill("Survival Expert", id, "I am not sure if he knows how to live in a society.", QuestType::Wilderness) {}
	~SurvivalExpert() override = default;
};

class Woodcutter : public QuestTypeCounterSkill
{
public:
	Woodcutter(int id) : QuestTypeCounterSkill("Woodcutter", id, "Natural enemy for humans with pointy ears.", QuestType::Elfs) {}
	~Woodcutter() override = default;
};
class Digger : public QuestTypeCounterSkill
{
public:
	Digger(int id) : QuestTypeCounterSkill("Digger", id, "Dig a hole with dwarf. Unnamed team that reached moon.", QuestType::Dwarfs) {}
	~Digger() override = default;
};
class Pyromaniac : public QuestTypeCounterSkill
{
public:
	Pyromaniac(int id) : QuestTypeCounterSkill("Pyromaniac", id, "Burn it. Seriously burn it.", QuestType::Minions) {}
	~Pyromaniac() override = default;
};
class Bard : public QuestTypeCounterSkill
{
public:
	Bard(int id) : QuestTypeCounterSkill("Bard", id, "No one can stop bard performance, not even trolls.", QuestType::Memes) {}
	~Bard() override = default;
};
class Troll : public QuestTypeCounterSkill
{
public:
	Troll(int id) : QuestTypeCounterSkill("Troll", id, "After reincarnation: Internet was never a safe place from me.", QuestType::Dankness) {}
	~Troll() override = default;
};
class Warlock : public QuestTypeCounterSkill
{
public:
	Warlock(int id) : QuestTypeCounterSkill("Warlock", id, "The great old one, take this little one as a gift.", QuestType::Fairies) {}
	~Warlock() override = default;
};
class Clown : public QuestTypeCounterSkill
{
public:
	Clown(int id) : QuestTypeCounterSkill("Clown", id, "Red nose vs white face. Fight now!", QuestType::Mimes) {}
	~Clown() override = default;
};

#endif