#ifndef GENERIC_ENTITIES_HPP
#define GENERIC_ENTITIES_HPP

#include <string>

class NamedEntity
{
public:
	NamedEntity(std::string entity_name) : name(entity_name) {}
	virtual ~NamedEntity() = default;
	std::string get_name() const { return name; }
	std::string set_name(std::string value) { name = value; return name; }
protected:
	std::string name = "Entity";
};

class NamedUniqueEntity : public NamedEntity
{
public:
	NamedUniqueEntity(std::string entity_name) : NamedEntity(entity_name), id(last_id++) {}
	int get_id() const { return id; }
protected:
	int id;
	inline static int last_id = 0;
};

#endif