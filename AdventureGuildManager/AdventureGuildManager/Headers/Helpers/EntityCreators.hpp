#ifndef ENTITY_CREATORS_HPP
#define ENTITY_CREATORS_HPP

#include <memory>
#include "StringContexts.hpp"

template<class TInterface>
class CreatorBase
{
public:
	CreatorBase() = default;
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

template<class TInterface>
class ParameterEntityCreator
{
public:
	virtual ~ParameterEntityCreator() = default;
	virtual std::unique_ptr<TInterface> create_entity() = 0;
	virtual int get_constructor_parameter() = 0;
};

template<class TInterface, class TCreatable>
class IdEntityCreator : public ParameterEntityCreator<TInterface>
{
	static_assert(std::is_base_of<TInterface, TCreatable>::value, "TCreatable must be derived from TInterface");
public:
	IdEntityCreator(int use_parameter) : parameter(use_parameter) {}
	~IdEntityCreator() override = default;
	
	std::unique_ptr<TInterface> create_entity() override
	{
		return std::make_unique<TCreatable>(parameter);
	}
	int get_constructor_parameter() override { return parameter; }
protected:
	int parameter;
};

#endif