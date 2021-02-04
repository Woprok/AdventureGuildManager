#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <string_view>
#include <memory>
#include <vector>
#include "Interfaces.hpp"

class ICommand
{
public:
	virtual ~ICommand() = default;
	static bool can_derive_from(std::vector<std::string> command_context) { return false; }
	virtual std::string execute() = 0;
};

class MenuCommand : public ICommand
{
public:
	static bool can_derive_from(std::vector<std::string>& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "menu";
	}
	std::string execute() override
	{
		return interface.to_string();
	}
private:
	static MenuInterface interface;
};

class HelpCommand : public ICommand
{
public:
	static bool can_derive_from(std::vector<std::string>& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "help";
	}
	std::string execute() override
	{
		return interface.to_string();
	}
private:
	static HelpInterface interface;
};

class ExitCommand : public ICommand
{
public:
	static bool can_derive_from(std::vector<std::string>& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "exit";
	}
	std::string execute() override
	{
		return interface.to_string()
	}
private:
	static ExitInterface interface;
};

class ErrorCommand : public ICommand
{
public:
	static bool can_derive_from(std::vector<std::string>& command_context) { return true; }
	std::string execute() override
	{
		return interface.to_string();
	}
private:
	static ErrorInterface interface;

};

template<class TInterface>
class CreatorBase
{
public:
	virtual ~CreatorBase() = default;
	virtual bool can_create_from(std::vector<std::string>& creation_context) = 0;
	virtual std::unique_ptr<TInterface> create_entity() = 0;
};

template<class TInterface, class TCreatable>
class ContextEntityCreator : public CreatorBase<TInterface>
{
	static_assert(std::is_base_of<TInterface, TCreatable>::value, "TCreatable must be derived from TInterface");
public:
	bool can_create_from(std::vector<std::string>& creation_context) override
	{
		return TCreatable::can_derive_from(creation_context);
	}
	std::unique_ptr<TInterface> create_entity() override { return std::make_unique<TCreatable>(); }
};





/*
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
};*/


#endif
