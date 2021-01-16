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
