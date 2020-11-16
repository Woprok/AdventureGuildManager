Nasleduj�ca �pecifik�cia je preroben�m p�vodnej �pecifik�cie do jednoduch�ej varianty.
T�to varianta m� u�el vytvori� baliky pr�ce, kde po ka�dom bal�ku pr�ce sa bude mo�n�,
rozhodn��, �i pokra�ova� dal��m alebo skon�i� a pok�si� sa odovzda� st�vajuce rie�enie.

T�ma: Adventure Guild Manager
Hr�� mana�uje guildu hrdnin�v a dobrodruh�v. Mana�ovanie pokr�va:
- mana�ment dobrodruha
	- pr�jmanie do slu�ieb
	- ukon�enie slu�by dobdrodruha
	- vylep�ovanie dobrodruh�v
		- levelovanie
		- spr�va vybavenia
- mana�ment skup�n dobdrodruhov
	- vytvorenie
	- zru�enie
	- upravenie
- mana�ment questov
	- pr�manie questov
	- ru�enie questov
	- posielanie dobrodruhov na quest
	- posielanie skupin na quest

Overview of entities:
	- Quest:
		- Reward # invoked on quest state success
		- Penalty # invoked on quest state failure
		- Canceled (Cancelation Fee) # invoked on quest state cancel
		- ExpirationTime # time at which quest is canceled automatically
		- CompletitionTime # time required to finish, started quest cant fail due to time
		- State # represents current state of quest
			- New # new quest that was neither accepted or canceled
			- Accepted # quest that is in progress by adventurer
			- Canceled # quest canceled by guild, pays cancelation fee
			- Success # quest that was completed, receive reward
			- Failure # quest that was not completed successfully, pays penalty
		- QuestResolutionRules # how is quest resolved after expiration of completition time

	- Quest History : History
		- Quest Failed
		- Quest Success
		- Quest Canceled
		- Quest Total

	- Guild:
		- Budget # current guild money value
		- Fame # current guild fame value
		- History # collection of all history objects


Guild
 - Members
 - Capital


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
		[Entity] Quest
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
			- Adventurer can lose level is he loses experience
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
		
11-12. Let the Quest have types and heroes skills
	Expected Blocks of Code:
		[Entity] Skill
			* int Id
		[Entity] Adventurer
			* Collection<Skill> Skills
		[Entity] QuestType
		[Entity] Quest
			* QuestType Type
	Functional Requirements:
		- Player can show all defined skills by using command game skills show
			- Each skill is printed on separate line and prints all information including SkillId
		- Heroes start with random selection of skills before they are hired equal to their level
		- Heroes get random skill on level up from these they don't have yet
		- Skill will be defined in code
		- Player can show all defined quest typesby using command game questtypes show
		- For each quest type that is not fullfilled by adventurer, quest level is increased for him, can be over the 10
		- For each quest type that adventurer fullfills, quest level is decreased for him, minimum level 0
			- minimum level 0 result in automatic success without rolls

13. Guild has progression
	Expected Blocks of Code:
		[Entity] Guild
			- int Prestige Level
			- Perks AvailablePerks
	Functional Requirements:
		- Fame defines Guild Prestige Level
		- After dispatching quest prestige is updated
		- Each Prestige Level unlocks perks available to buy
		- If Prestige level should be decreased or guild funds reach negative number guild is disbanded and player loses
		- If player reaches Prestige level 11 he wins the game
			- By default Prestige level rank up can demand also specific amount of task to be completed
			- For example quest completed count or adventurer count
			- Can require adventurer to posses special guild perks like Hero, Saviour of Empire etc.
		- Perks range from adventurer based, special skill unlockment, special quest unlockment. 
			- unlocking special option guild adventurer retrain SKILL_ID -> SKILL_ID
		- Perks are used by dispatchers? automatically if possible and applied where they are legit

14. Finishing touches
	Expected Blocks of Code:
		- Refactoring
	Functional Requirements:
		- Refactoring
		- Bugfixing
		- Test for missing cases and bugs discovered

15. The future is unlimited and time is still limited