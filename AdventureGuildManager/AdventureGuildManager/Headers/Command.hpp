#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <string_view>
#include <memory>
#include <vector>

class ICommand;

class creator
{
public:
	virtual ~creator() = default;
	virtual std::unique_ptr<ICommand> create_as_unique() = 0;
};

template<class TInterface, class TCreateable>
class generic_creator : public creator
{
public:
	bool is_createable_from(std::string pop)
	{
		return TCreateable::can_derive_from(pop);
	}
	std::unique_ptr<TInterface> create_as_unique() override { return std::make_unique<TCreateable>(); }
};


class ICommand
{
public:
	bool is_member();
	static bool is_command(std::vector<std::string> data)
	{
		return false;
	}
};

class guild_info : ICommand
{
public:
};
class guild_create : ICommand
{
public:
};
class guild_change_difficulty : ICommand
{
public:
};
class guild_change_name : ICommand
{
public:
};
class guild_adventurer_show : ICommand
{
public:
	static bool is_command(std::vector<std::string> data)
	{


		return false;
		
	}
};

class i_command_group
{
public:
	virtual ~i_command_group() = default;
	virtual bool is_group_member(std::string_view key) { return false; }
	std::unique_ptr<ICommand> GetCommand();
};


class world_command_group : i_command_group
{
public:
	bool is_group_member(std::string_view key) override { return primary_key == key; }
protected:
	std::string primary_key = "world";
};

class guild_command_group : i_command_group
{
public:
	bool is_group_member(std::string_view key) override { return primary_key == key; }
protected:
	std::string primary_key = "guild";
};


#endif
