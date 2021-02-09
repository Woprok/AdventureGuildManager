#ifndef SKILLS_HPP
#define SKILLS_HPP

#include "../Interfaces/ISkills.hpp"

class Lucky final : public ISkill
{
public:
	Lucky(int new_id) : ISkill("Lucky", new_id, "Sometimes you are protected by luck.") {}
	~Lucky() override = default;
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

#endif