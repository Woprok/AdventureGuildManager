#ifndef I_PERKS_HPP
#define I_PERKS_HPP

#include <string>

#include "../Entities/BasicEntities.hpp"

class IPerk : public IdNameEntity
{
public:
	IPerk(std::string new_name, int new_id, std::string&& new_description, int new_level_requirement)
		: IdNameEntity(new_name, new_id), description(new_description), level_requirement(new_level_requirement) {}
	~IPerk() = default;
	GetSetEntity<int> level_requirement;
	const std::string& get_description() const { return description; }
protected:
	std::string description;
};

/*/
class GuildPerk
{
public:
	GuildPerk(int level_restriction, int perk_id) : guild_level_required(level_restriction), guild_perk_id(perk_id) {}
	virtual ~GuildPerk() = default;
	virtual bool fulfill_requirements(GameData& game_data)
	{
		return game_data.current_guild.get_level() >= guild_level_required;
	}
	virtual void execute_guild_perk(Guild& guild) {}
	virtual void execute_quest_perk(Reward& reward, Penalty& penalty) {}
	int get_perk_id() { return guild_perk_id; }
private:
	const int guild_level_required;
	const int guild_perk_id;
};
/**/


#endif