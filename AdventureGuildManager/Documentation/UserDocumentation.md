## User Documentation

### Introduction  
Adventure guild is simple game in console/terminal environment.  
Player goal is to successfully manage his guild and reach final prestige level.  
Game is controlled by commands (written to console, each command is one line of input, spaces should be used to separate parts of command)  

### How to play  
Gameplay is straightforward:  
    Either you use "guild wait" and let the game generate new quests and adventure (there is cap how many can be available).  
    Or you dispatch adventurer on quest "quest dispatch adventurer_id quest_id".  
    Available quests are shown by "quest available" and can be taken by "quest take quest_id".  
    Available adventurers are shown by "adventurer available" and can be recruited by "adventurer recruit adventurer_id".  
    For other commands see "help"...   
    Help describes all basic informations that are required for understanding game and commands...  

### Known issues  
After current phase of playtesting several UI headaches were discovered, due to simplicity of the game they were left in this release version.   
    - Commands display what happened in really bad way as you are left to wonder how much resources you have left.  
    - Design is awful (well it's console, but it could be better).  
    - Balance is all overplace. It might be really not possible to level up adventurer in consistent manner.  
    - All failure states show not really helpful message, mostly due to simplicity of result being just a true / false.  

### Endgame
Game is won once player achieves prestige level 10.
Game is lost once player money and fame both reach negative number at same time.

### Commands
Debug Commands: (DEBUG VERSION ONLY)   
        - debug: shows all debug commands. They are all same commands and can be used as "debug more" or "debug less". (Yes, they are cheats.)  
Help Commands:  
        - help (h): shows all help.  
Menu Commands:  
        - menu (m): current game state.  
        - menu start (m -s): start game.   
        - menu end (m -e): end game.  
        - menu difficulty "new difficulty" (m -d x): change game difficulty.  
Exit Commands:  
        - exit: closes game.  
Error Commands:  
        - error: displays error message.  
Encyclopedia Commands:  
        - encyclopedia (e): help for encyclopedia commands.  
        - encyclopedia quest_types (e -qt): show quest types and their description.  
        - encyclopedia quest_rarities (e -qr): show quest rarities and their description.  
        - encyclopedia adventurer_rarities (e -ar): show adventurer rarities and their description.  
        - encyclopedia skills (e -s): show skills and their description.  
        - encyclopedia perks (e -p): show perks and their description.  
Guild Commands:  
        - guild (g): help for commands.  
        - guild info (g -i): show guild informations.  
        - guild rename "My Guild Name" (g -r x): rename guild to your desired name.  
        - guild wait (g -w): advances to next turn. Quest rent and hired adventurer living expenses are paid.  
Perk Commands:  
        - perk (p): help for perk commands.  
        - perk trade_fame "fame amount" (p -r x): trade fame for gold. Ratio is 1:10.  
        - perk requalification_course "hired adventurer id" (p -r x): randomize adventurer skills. For each of his skill you pay: 250.  
        - perk armory "hired adventurer id" (p -a x): upgrade adventurer rarity. Can be upgraded from commoner up to innkeeper. Cost is rarity difference * 250.  
        - perk church_of_heroes "dead adventurer id" (p -c x): revive dead adventurer. Amount of gold required is: level recruit cost + 1000.  
        - perk madness_of_master "hired adventurer id" (p -m x): upgrade adventurer. Cost is: 500 fame.  
        - perk buy "perk id" (p -b x): buy perk.You need to have prestige level equal to perk level. Cost is equal to perk level * 500.  
Adventurer Commands:  
        - adventurer (a): help for adventurer commands.  
        - adventurer available (a -a): show available adventurers.  
        - adventurer hired (a -h): show hired adventurers.  
        - adventurer dead (a -d): show dead adventurers.  
        - adventurer inactive (a -i): show retired adventurers.  
        - adventurer recruit "adventurer id" (a -r x): transfers available adventurer to hired. Full level based recruitment cost is paid.  
        - adventurer pension "adventurer id" (a -p x): retires adventure. Full level based retirement cost is paid. Fame is gained.  
Quest Commands:  
        - quest (q): help for quest commands.  
        - quest available (q -a): show available quests.  
        - quest reserved (q -r): show reserved quests.  
        - quest completed (q -c): show completed quests.  
        - quest failed (q -f): show failed quests.  
        - quest take "quest id" (q -t x): transfers available quest to reserved quests. Foreach quest in reserve you pay around 50gold.  
        - quest dispatch "adventurer id" "quest id" (q -d x y): dispatches adventure on quest. Adventurer living expenses are paid.  