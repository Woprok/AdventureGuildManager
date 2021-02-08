#ifndef ENCYCLOPEDIA_INTERFACES_HPP
#define ENCYCLOPEDIA_INTERFACES_HPP

class EncyclopediaInterface : public IDisplayeableInterface
{
public:
	std::string to_string() override { return "Encyclopedia"; }
	std::string wiki_quest_types(EncyclopediaKeeper& keeper)
	{
		std::ostringstream result;
		result << "Encyclopedia Quest Types: " << "\n";
		for (auto&& quest_type : keeper.get_quest_types())
		{
			result << "[" << static_cast<size_t>(quest_type.get_self()) << "]"
				<< " " << quest_type.get_name() << " "
				<< " --> " << quest_type.get_description()
				<< "\n";
		}

		return result.str();
	}
	std::string wiki_skill_types(EncyclopediaKeeper& keeper)
	{
		std::ostringstream result;
		result << "Encyclopedia Skill Types: " << "\n";
		for (auto&& skill : keeper.get_skills())
		{
			result << "[" << skill->get_skill_id() << "]"
				<< " " << skill->get_name()
				<< "\n";
		}
		return result.str();
	}
};

#endif