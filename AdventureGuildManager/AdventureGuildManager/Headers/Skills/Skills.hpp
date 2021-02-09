﻿#ifndef SKILLS_HPP
#define SKILLS_HPP

#include "../Interfaces/ISkills.hpp"

class Lucky final : public ISkill
{
public:
	Lucky(int new_id) : ISkill("Lucky", new_id, "Sometimes you are protected by luck.") {}
	~Lucky() override = default;
	void execute_roll_calculation_change(int& adventurer_level) override
	{
		adventurer_level += level_bonus;
	}
private:
	const int level_bonus = 3;
};
class Saviour final : public ISkill
{
public:
	Saviour(int new_id) : ISkill("Saviour", new_id, "Destiny chose you to be born in really bright day.") {}
	~Saviour() override = default;
	void execute_reward_change(GoldFameData& data, int& experience) override
	{
		experience = experience * experience_multi_reward;
	}
	void execute_penalty_change(GoldFameDeadlyData& data, int& experience) override
	{
		experience = experience * experience_multi_penalty;
	}
private:
	const int experience_multi_reward = 2;
	const int experience_multi_penalty = 0.5;
};
class GoldHoarder final : public ISkill
{
public:
	GoldHoarder(int new_id) : ISkill("Gold Hoarder", new_id, "There is always a hidden treasure.") {}
	~GoldHoarder() override = default;
	void execute_reward_change(GoldFameData & data, int& experience) override
	{
		data.gold.set_value(data.gold.get_value() * bonus_gold_factor);
	}
private:
	const double bonus_gold_factor = 1.25;
};
class Entertainer final : public ISkill
{
public:
	Entertainer(int new_id) : ISkill("Entertainer", new_id, "All stories are worth telling.") {}
	~Entertainer() override = default;
	void execute_reward_change(GoldFameData& data, int& experience) override
	{
		data.fame.set_value(data.fame.get_value() * bonus_fame_factor);
	}
private:
	const double bonus_fame_factor = 1.25;
};
class EscapeArtist final : public ISkill
{
public:
	EscapeArtist(int new_id) : ISkill("Escape Artist", new_id, "Did somebody say I can't escape death?") {}
	~EscapeArtist() override = default;
	void execute_penalty_change(GoldFameDeadlyData& data, int& experience) override
	{
		data.deadly.set_value(data.deadly.get_value() && chance.get_next() <= survive_chance);
	}
private:
	const double survive_chance = 75;
	static inline UniformGenerator chance{ MIN_GEN_VALUE, MAX_GEN_VALUE };
};
class Noble final : public ISkill
{
public:
	Noble(int new_id) : ISkill("Noble", new_id, "It was not my fault!") {}
	~Noble() override = default;
	void execute_penalty_change(GoldFameDeadlyData& data, int& experience) override
	{
		data.gold.set_value(data.gold.get_value() * reduction_gold_factor);
		data.fame.set_value(data.fame.get_value() * reduction_fame_factor);
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
	void execute_reward_change(GoldFameData& data, int& experience) override
	{
		data.gold.set_value(data.gold.get_value() * bonus_gold_factor);
		data.fame.set_value(data.fame.get_value() * bonus_fame_factor);
	}
	void execute_penalty_change(GoldFameDeadlyData& data, int& experience) override
	{
		data.gold.set_value(data.gold.get_value() * reduction_gold_factor);
		data.fame.set_value(data.fame.get_value() * reduction_fame_factor);
		data.deadly.set_value(data.deadly.get_value() && chance.get_next() <= survive_chance);
	}
private:
	const double bonus_fame_factor = 1.50;
	const double bonus_gold_factor = 2.50;
	const double reduction_gold_factor = 0.25;
	const double reduction_fame_factor = 0.25;
	const double survive_chance = 60;
	static inline UniformGenerator chance{ MIN_GEN_VALUE, MAX_GEN_VALUE };
};

#endif