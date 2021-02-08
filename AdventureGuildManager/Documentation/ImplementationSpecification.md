A. [Architecture]
	This paragraph explains architecture of this project.

B. Command Specification:
- Each command is one line of input.
- First is command_name, followed by command_parameters/command_arguments separated by spaces.
- White/Space characters are used as separator and are all purged from input line.

E. [Entities]
	This paragraph contains overview of all entities used in the project in simplified manner.
	[GameWorld]
		* Collection<Player.Id, Player> Players
		* Collection<Player.Id, Guild.Id> PlayerGuildPairs
		* GuildKeeper Guilds
		[Player]
			* Id
			* Name
		[GuildKeeper]
			* Collection<Guild.Id, Guild> Guilds
			[Guild]
				* Id
				* Name
				[GuildResources]
					* int Gold
					* int Fame
				[GuildStats]
					* int Difficulty
					* int Prestige Level

	[Guild]
		* Perks AvailablePerks
		* AdventurerKeeper AdventurersKeeper
		* QuestKeeper QuestKeeper
	[AdventurerKeeper]
		* collection Adventurers
	[QuestKeeper]
		* collection Quests
		* Collection<Quest> QuestFailed
		* int questFailed	
	[Quest] 
		* string Name	
		* int Id	
		* int Difficulty	
		* QuestType Type
		* Reward Reward
		* Penalty Penalty
		[QuestType] 
		[Reward] 
			* int Gold
			* int Fame
		[Penalty] 
			* bool Deadly
			* int Gold
			* int Fame
	[Adventurer] 
		* string Name	
		* int RecruitmentCost
		* int RetirementCost
		* int LivingExpenses
		* int Experience
		* int Level
		* Collection<Skill> Skills
		[Skill] 
			* int Id
	[GuildDispatcher] 
	[CommandLineInputParser] 
	[CommandLineOutputPrinter] 
	[CommandLineCommandController]
	
S. [Steps]
	This paragraph describes individual steps of the implementation.

Game Developement Steps:

1. It does nothing but it's glorious
	Expected Blocks of Code:
		- [CL-IP] CommandLine Input Parser
			* Responsible for handling all user input.
		- [CL-CC] CommandLine Command Controller
			* Function Method Dictionary
			* Based on Function Invokes corresponding command
			* Uses CL-IP & CL-OP
		- [CL-OP] CommandLine Output Printer
			* Responsible for handling User Interface switching and presentation.
		- Error User Interface
		- Command User Interface
		- Help User Interface
	Functional Requirements:
		- Can clean CommandLine
		- Can reprint basic User Interface
		- Can consume User CommandLine Command
			* successful command displays expected User Interface
			* Non existing Command fallback's to default state.
			* Any error return's program to initialization state. 

2. Let the Guild Exist
	Expected Blocks of Code:
		[Entity] Guild
			* string Name
			* int Difficulty
	Functional Requirements:
		- Player can Create Guild by using command "guild new"
		- Player can Set Difficulty by using command "guild difficulty"
		- Player can Print his Guild by using command "guild info"
		- command "guild info"
			- Displays guild name
			- Displays guild difficulty
		
3. Let the Guild Information Exist
	Expected Blocks of Code:
		[Entity] Guild
			* int Gold
			* int Fame
	Functional Requirements:
		- command "guild new"
			- gold is set to 1000
			- fame is set to 0
		- command "guild info"
			- Displays amount of gold
			- Displays amount of fame

4. Let the Guild have Heroes
	Expected Blocks of Code:
		[Entity] Guild
			* AdventurerKeeper AdventurersKeeper
		[Entity] AdventurerKeeper
			* collection Adventurers
		[Entity] Adventurer
			* string Name		
	Functional Requirements
		- Player can Print Guild Adventurers by using command "guild adventurer show"
		- Player can Print Available Adventurers to Hire by using command "guild adventurer recruits"
		- command "guild adventurer show"
			- Displays list of adventurers
				- Displays one adventurer per line
					- Displays adventurer name
		- command "guild adventurer recruits"
			- Displays list of adventurers
				- Displays one adventurer per line
					- Displays adventurer name
	
5. Let the Guild have Quests
	Expected Blocks of Code:
		[Entity] Guild
			* QuestKeeper QuestKeeper
		[Entity] QuestKeeper
			* collection Quests
		[Entity] Quest
			* string Name	
	Functional Requirements:
		- Player can Print Guild Quests by using command "guild quest show"
		- Player can Print Available Quests to Accept by using command "guild quest requests"
		- command "guild quest show"
			- Displays list of quests
				- Displays one quest per line
					- Displays quest name		
		- command "guild quest requests"
			- Displays list of quests
				- Displays one quest per line
					- Displays quest name

4.1. Let the Adventurers have Info
	Expected Blocks of Code:
		[Entity] Adventurer
			* int Id
	Functional Requirements:
		- Player can Print Guild Adventurers by using command "guild adventurer show ADVENTURER_ID"
		- Player can Print Available Adventurers to Hire by using command "guild adventurer recruits RECRUIT_ADVENTURER_ID"
		- Player can Hire Available Adventurers by using command "guild adventurer hire RECRUIT_ADVENTURER_ID"
		- command "guild adventurer show"
			- Displays adventurer id
		- command "guild adventurer recruits"
			- Displays adventurer id
		- command "guild adventurer hire RECRUIT_ADVENTURER_ID"
			- Hire adventurer and insert it into guild collection
	
5.1. Let the Quests have Info
	Expected Blocks of Code:
		[Entity] Quest
			* int Id
	Functional Requirements:
		- Player can Print Guild Quests by using command "guild quest show QUEST_ID"
		- Player can Print Available Quests to Accept by using command "guild quest requests REQUEST_QUEST_ID"
		- Player can Accept Available Quests by using command "guild quest accept REQUEST_QUEST_ID"
		- command "guild quest show"
			- Displays quest id
		- command "guild quest requests"
			- Displays quest id
		- command "guild quest accept REQUEST_QUEST_ID"
			- Accept quest and insert it into guild collection

6. Let the Quests have reward
	Expected Blocks of Code:
		[Entity] GuildDispatcher
		[Entity] Reward
			* int Gold
			* int Fame
		[Entity] Quest
			* Reward Reward
	Functional Requirements:
		- Player can print more information about quests, e.g. reward
		- Player can dispatch adventurer on quest by using command "guild dispatch ADVENTURER_ID QUEST_ID"
			- Player receives reward for doing so.
			- Quest moves to completed.
		- Player can print quest completed by using command "guild quest completed"
			- follows same as for normal quests, includes hero who completed it
		- command "guild quest show"
			- Displays quest reward
		- command "guild quest requests"
			- Displays quest reward
		- command "guild dispatch ADVENTURER_ID QUEST_ID"
			- Guild receives reward
			- Transfers quest to completed collection

7. Let the Quests have penalty
	Expected Blocks of Code:
		[Entity] GuildDispatcher
		[Entity] Penalty
			* bool Deadly
			* int Gold
			* int Fame
		[Entity] Quest
			* Penalty Penalty
		[Entity] Collection<Quest> QuestDone
			* int questDone	
		[Entity] Collection<Quest> QuestFailed
			* int questFailed	
	Functional Requirements:
		- Player can print quest completed by using command "guild quest failed"
			- follows same as for normal quests, includes hero who attempted it
		- command "guild quest show"
			- Displays quest penalty
		- command "guild quest requests"
			- Displays quest penalty
		- command "guild dispatch ADVENTURER_ID QUEST_ID"
			- Guild receives reward or penalty, chance is 50 : 50
				- Chance can be calculated as: RND[1-100] compated to [Max(50 - QC, 10), Min(50 + QF, 90)]
			- Penalty can kill adventurer
			- Transfers quest to completed/failed collection
			- Can transfers adventurer to dead collection
			- Adventurer tracks amount of quest completed and failed

8. Let the Adventurer have financial dillemma
	Expected Blocks of Code:
		[Entity] Adventurer
			* int RecruitmentCost
			* int RetirementCost
			* int LivingExpenses
	Functional Requirements:
		- Player can hire adventurer only and only if they have enough money to pay his RecruitmentCost
			- Gold is substracted from guild financials
		- Player can retire adventurer only and only if they have enough money to pay his RetirementCost
			- Gold is substracted from guild financials
		- Dispatching for a quest requires guild to pay adventurer living expenses
		- Player can see all information added in this block

9-10. Let the Adventurer have experience
	Expected Blocks of Code:
		[Entity] Adventurer
			* int Experience
			* int Level
		[Entity] Quest
			* int Difficulty
	Functional Requirements:
		- Player can see Adventurer Experience and Quest Difficulty
		- Quest difficulty is value between 1 - 10
		- GuildDispatcher updates correctly experience value, after quest
			- Add static_value after completing
			- Remove % after losing
		- Heroes Level is based on current experience signature function
			- Function is part of class ? that describes amount of experience per level
			- Min level is 1 max level is 10
			- Adventurer can lose level if he loses experience
			- Adventurer level increases his hire and retirement cost
			- retiring adventurer of higher level grants more fame
		- Quest success calculation considers advantage and disadvantage
			- Quest Roll happen now multiple times
				- For each level of quest is roll increased by one. e.g. for Quest level 1 = 1 roll, Quest level 10 = 10 rolls
			- Quest Roll are rerolled in following way
				- success from level advantage or failure from level disadvantage
					- 0 for quest difficulty == adventurer level
				- if roll fails and success from level advantage value is larger than 0
					- decrement by one
					- reroll
					- applies one decrement per roll
				- if roll succcess and failure from level disadvantage value is larger than 0
					- decrement by one
					- reroll
					- applies one decrement per roll
		
11. Let the Quest have types and heroes skills
	Expected Blocks of Code:
		[Entity] Skill
			* int Name
		[Entity] Adventurer
			* Collection<Skill> Skills
		[Entity_Enum] QuestType
		[Entity] Quest
			* Collection<QuestType> Type
	Functional Requirements:
		- Player can show all defined quest types by using command game questtypes show
		- Player can show all defined skills by using command game skills show
		- QuestType is defined in code as simple enum
		- Skill will be defined in code
			- Each skill has different effect on quest dispatch
			- More might be added later...

12. Let skills be there for heroes.
		[Entity] Adventurer, Quest
			* Enum Rarity
		- Adventurers start with selection of skills
			- Number of skills 1 - 3 (1:Adventurer, 2:Hero, 3:Innkeeper)
			- Each skill must be unique
		- Adventurers get additional skill at level 5 and at level 10
			- Skill can be lost if their level decreases

13. Guild has progression
	Expected Blocks of Code:
		[Entity] Guild
			- int Prestige Level
			- Perks AvailablePerks
	Functional Requirements:
		- Fame defines Guild Prestige Level
		- After dispatching quest prestige is updated
		- Each Prestige Level unlocks perks available to buy
		- If player reaches Prestige level 11 he wins the game
			//- By default Prestige level rank up can demand also specific amount of task to be completed
			//- For example quest completed count or adventurer count
			//- Can require adventurer to posses special guild perks like Hero, Saviour of Empire etc.
		- Perks range from adventurer based, special skill unlockment, special quest unlockment. 
			- unlocking special option guild adventurer retrain SKILL_ID -> SKILL_ID
		- Perks are used by dispatchers? automatically if possible and applied where they are legit

14. Finishing touches
	Expected Blocks of Code:
		- Refactoring
		- If guild fame or guild funds reach negative number guild is disbanded and player loses
		- Game Glued Gameplay Loop
		- Guild Difficulty effect on generation and etc.
	Functional Requirements:
		- Refactoring
		- Bugfixing
		- Test for missing cases and bugs discovered

15. The future is unlimited and time is still limited