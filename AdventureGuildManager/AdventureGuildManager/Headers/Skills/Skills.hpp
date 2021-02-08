#ifndef SKILLS_HPP
#define SKILLS_HPP

#include "../Interfaces/ISkills.hpp"

class Lucky final : public ISkill
{
public:
	Lucky(int new_id) : ISkill("Lucky", new_id, "Sometimes you are protected by luck.") {}
	~Lucky() override = default;
	const std::string& get_description() override { return description; }
	void execute_skill() override 
	{
		
	}
};
class GoldHoarder final : public ISkill
{
public:
	GoldHoarder(int new_id) : ISkill("Gold Hoarder", new_id, "There is always a hidden treasure.") {}
	~GoldHoarder() override = default;
	void execute_skill() override
	{
		//reward.set_gold(reward.get_gold() * bonus_gold_factor);
	}
private:
	const double bonus_gold_factor = 1.25;
};
class Entertainer final : public ISkill
{
public:
	Entertainer(int new_id) : ISkill("Entertainer", new_id, "All stories are worth telling.") {}
	~Entertainer() override = default;
	void execute_skill() override
	{
		//reward.set_fame(reward.get_fame() * bonus_fame_factor);
	}
private:
	const double bonus_fame_factor = 1.25;
};
class EscapeArtist final : public ISkill
{
public:
	EscapeArtist(int new_id) : ISkill("Escape Artist", new_id, "Did somebody say I can't escape death?") {}
	~EscapeArtist() override = default;
	void execute_skill() override
	{
		//penalty.set_deadly(penalty.get_deadly() && chance.get_chance() <= 75);
	}
private:
	const double survive_chance = 75;
	//ChanceGenerator chance;
};
class Noble final : public ISkill
{
public:
	Noble(int new_id) : ISkill("Noble", new_id, "It was not my fault!") {}
	~Noble() override = default;
	void execute_skill() override
	{
		//penalty.set_gold(penalty.get_gold() * reduction_gold_factor);
		//penalty.set_fame(penalty.get_fame() * reduction_fame_factor);
	}
private:
	const double reduction_gold_factor = 0.25;
	const double reduction_fame_factor = 0.25;
};
class Godslayer : public ISkill
{
public:
	Godslayer(int new_id) : ISkill("Godslayer", new_id, "I once surpassed my limits a little.") {}
	~Godslayer() override = default;
	void execute_skill() override
	{
	}
private:
	const double bonus_fame_factor = 1.25;
	const double bonus_gold_factor = 1.25;
	const double reduction_gold_factor = 0.25;
	const double reduction_fame_factor = 0.25;
	const double survive_chance = 75;
};



/*/
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

*/
#endif