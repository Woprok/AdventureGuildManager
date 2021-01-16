Nasledujúca špecifikácia je prerobením pôvodnej špecifikácie do jednoduchšej varianty.
Táto varianta má uèel vytvori baliky práce, kde po kadom balíku práce sa bude moné,
rozhodnú, èi pokraèova dalším alebo skonèi a pokúsi sa odovzda stávajuce riešenie.

Téma: Adventure Guild Manager
Hráè manauje guildu hrdninóv a dobrodruhóv. Manaovanie pokrıva:
- manament dobrodruha
	- príjmanie do sluieb
	- ukonèenie sluby dobdrodruha
	- vylepšovanie dobrodruhóv
		- levelovanie
		- správa vybavenia
- manament skupín dobdrodruhov
	- vytvorenie
	- zrušenie
	- upravenie
- manament questov
	- prímanie questov
	- rušenie questov
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
