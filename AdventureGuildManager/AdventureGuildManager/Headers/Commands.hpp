#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <memory>
#include <vector>
#include "Interfaces.hpp"

typedef std::vector<std::string> string_context;

class ICommand
{
public:
	ICommand(string_context& command_context) : context(std::move(command_context)) { }
	virtual ~ICommand() = default;
	static bool can_derive_from(string_context& command_context) { return false; }
	virtual std::string execute() = 0;
protected:
	string_context context;
};

class MenuCommand : public ICommand
{
public:
	MenuCommand(string_context& command_context) : ICommand(command_context) { }

	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "menu";
	}
	std::string execute() override
	{
		return interface.to_string();
	}
private:
	MenuInterface interface;
};

class HelpCommand : public ICommand
{
public:
	HelpCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "help";
	}
	std::string execute() override
	{
		return interface.to_string();
	}
private:
	HelpInterface interface;
};

class ExitCommand : public ICommand
{
public:
	ExitCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context)
	{
		return command_context.size() == 1 && command_context[0] == "exit";
	}
	std::string execute() override
	{
		return interface.to_string();
	}
private:
	ExitInterface interface;
};

class ErrorCommand : public ICommand
{
public:
	ErrorCommand(string_context& command_context) : ICommand(command_context) { }
	static bool can_derive_from(string_context& command_context) { return true; }
	std::string execute() override
	{
		return interface.to_string(context);
	}
private:
	ErrorInterface interface;
};

template<class TInterface>
class CreatorBase
{
public:
	virtual ~CreatorBase() = default;
	virtual bool can_create_from(string_context& creation_context) = 0;
	virtual std::unique_ptr<TInterface> create_entity(string_context& creation_context) = 0;
};

template<class TInterface, class TCreatable>
class ContextEntityCreator : public CreatorBase<TInterface>
{
	static_assert(std::is_base_of<TInterface, TCreatable>::value, "TCreatable must be derived from TInterface");
public:
	bool can_create_from(string_context& creation_context) override
	{
		return TCreatable::can_derive_from(creation_context);
	}
	std::unique_ptr<TInterface> create_entity(string_context& creation_context) override 
	{ 
		return std::make_unique<TCreatable>(creation_context); 
	}
};





/*
class ICommand
{
public:
	bool is_member();
	static bool is_command(string_context data)
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
	static bool is_command(string_context data)
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
