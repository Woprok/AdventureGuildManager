#ifndef BASIC_ENTITIES_HPP
#define BASIC_ENTITIES_HPP

#include <string>

class NameEntity
{
public:
	NameEntity(std::string& new_name) : name(new_name) {}
	virtual ~NameEntity() = default;
	virtual const std::string& get_name() const { return name; }
	virtual const std::string& set_name(std::string new_name) { name = new_name; return name; }
protected:
	std::string name = "Entity";
};

class IdEntity
{
public:
	IdEntity(int new_id) : id(new_id) {}
	virtual ~IdEntity() = default;
	virtual int get_id() const { return id; }
	virtual int set_id(int new_id) { id = new_id; return id; }
protected:
	int id = 0;
};

class IdNameEntity : public NameEntity, public IdEntity
{
public:
	IdNameEntity(std::string& new_name, int new_id)	: NameEntity(new_name), IdEntity(new_id) { }
	virtual ~IdNameEntity() = default;
};

template<class T>
class ChangeEntity
{
public:
	ChangeEntity(int new_value) : value(new_value) {}
	virtual ~ChangeEntity() = default;
	virtual T get_value() const { return value; }
	virtual T set_value(T new_value) { value = new_value; return value; }
	virtual T add_value(T add_value) { value += add_value; return value; }
	virtual T rmv_value(T rmv_value) { value -= rmv_value; return value; }
protected:
	T value = 0;
};

template<class T>
class GetSetEntity
{
public:
	GetSetEntity(T new_value) : value(new_value) {}
	virtual ~GetSetEntity() = default;
	virtual T get_value() const { return value; }
	virtual T set_value(T new_value) { value = new_value; return value; }
protected:
	T value = 0;
};

#endif