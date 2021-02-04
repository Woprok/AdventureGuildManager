#ifndef INTERFACES_HPP
#define INTERFACES_HPP

class IDisplayeableInterface
{
public:
	virtual ~IDisplayeableInterface() = default;
	virtual std::string to_string() = 0;
};

class MenuInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Adventure Guild Manager!\n";
	}
};

class HelpInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Help!\n Following commands are allowed: help, exit, guild.\n";
	}
};

class ExitInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "You decided to left your adventuring life behind!\n";
	}
};

class ErrorInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override
	{
		return "Invalid Command!\n";
	}
};


#endif