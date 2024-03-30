# Rise of the Pantheon: Goddess Rising (Parts I - III)

## Game Brainstorming Document

## January 8, 2015

**General ideas**

* Skill books that give people small stat boosts (like the potions that increase +1 DEF, etc)
* Sword Chucks & Armoire of Invincibility (-50 defense, bad or joke item, some chance for something awesome)
* Secret dungeon after beating game
* Bestiary to look at every enemy (like pokedex?)
* Bonus enemies that are super powerful
* Difficulty settings, one that has enemies that level with you
* Arena for getting hidden item
* Stores that have exclusive items based on the main character

## January 15, 2015

**Battle system examples**

* Frontal view battle system (Lufia, Dragon Warrior, Wizardry)
* Linear motion battle system (Tales series)
* Sideline turn battle system (FF1-3)
* Active time battle system (FF4-6, Grandia)
* Full action battle system (Star Ocean)
* Strategy battle system (Final Fantasy Tactics, Vandal Hearts)
* Military battle system (Fire Emblem, Super Robot Wars)
* Duel battle system (Pokemon, Yu-gi-oh)

**Battle system ideas**

* Simple enough that it can be completed within 6-12 months or less
* Turn based system, not active
* Based on speed of character, maybe can go more than once before the enemy can go
* Timeline bar like Grandia (or FFX) where you see the time meter and who is going to go next
* Have it stop on your turn to open a window on what you will do?
* 2-3 characters fighting at a time, if a character drops, they can be replaced
* Priority queue for your party that you set up ahead of time
* Experience can be only gotten for characters that participated
* Pull back a character and lose the turn you are on (counts as an action)
* If the whole party is downed, then maybe they get captured?
* Move over to a scene where they have to escape?
* Enemies can capture downed characters and they cannot be revived or healed until the battle is won.
* Want to make sure this doesn’t happen often for people who are constantly losing battles -- could be jarring to see the same thing if you aren’t doing well
* Storyline wise it could help because it adds extra time for scenes
* Non captured characters are the ones who have to travel somewhere to break them out?
* Battle skills could be supplanted with breakout skills, like D&D
* Some enemy groups have higher or lower capture chance
* Some enemies have absolutely no capture, and have it be a ratio so that people cannot always know
* Decrease the capture likelihood with higher difficulty settings
* Have unique battle elements that tie into and support the story (fight back for the portal in CH 1 and 2)
* Switch between different battles
* Nested battles that affect the outcomes of other battles (we heard you liked battles, so we put battles in your battles, so you could battle while you battle).
* Relationship system relates to ability effects, powers, if they die or are close to death, they could get boosts (scream out, etc). This could start with a crit boost to be simple
* Allow players to construct plans, perhaps at the risk of them going wrong
* Customizable main attack
* A few characters can do this
* Two part component, earn new components with leveling
* Characters can combine skills into shortcuts, like in Star Ocean.
* They have slots, and basic attacks.
* This was for a live action battle system
* Characters could have a special ability that prevents them from dying or being downed
* Passive effects, like the ones in FF6, if the health is 1-2% of total
* Concept of what it will look like
* You can move freely before committing to the attack you are using.
* Some attacks can only be used at range or close up.
* After attack, you are committed to the spot where you are standing.
* Timeline like Grandia: [https://www.youtube.com/watch?v=3KLgbzvm4O4](https://www.youtube.com/watch?v=3KLgbzvm4O4)
* Battles are like Final Fantasy where the people are taking turns on a battle bar timeline, but visually they are moving towards the sprites if they are attacking them.
* Timeline battle bar
* Wait bars, maybe 2 or 3, or just the whole section
* End of command bar means that they are able to enter commands
* From command to execution, they still have a time to get to the execution
* Sword attacks could go from command to execution very fast
* Spells could take a bit longer
* Preview of how long your command is going to take to get to execution
* More badass abilities take longer to use
* The look and feel of the battle system
* Players and enemies intermix their location based on who or what they’ve attacked.
* Sprites have different states of animation and statuses.
* The sprites move into a background depth but it is literally just the sprites moving up and down, and scaling them down/up so they look like they are moving into the background.
* Battle bar with timeline (it destroys all)
* Character portraits with basic information (health, magic, level)
* Action selection window (Attack, Magic/Power, Item, Defend, Retreat)
* Magic/Power selection window
* Item selection window
* Targeting rectangle to select enemies
* Animations for magic or powers
* Dialogue box for names of enemies, characters as they are selected
* Dialogue box for speech bubbles in battle
* Dialogue box for victory screen and what they earned
* Sprites of characters don’t change unless story makes it necessary
* Character progression could be based on a random list constructed at the beginning.
* Or it could be a very simplified skill tree, maybe get skill points where you can “purchase” a spell or skill that is something they could learn but they cannot learn everything, and have prerequisites. Like feats in D&D.
* We need to write a bunch of use cases that detail each step in various uses of the battle system.
* Design one to two custom characters
* Add in unlocked characters from future games
* Side quests that will offer various challenges to give you an easter egg character
* Character progression data will be saved and can be imported into newer games and when they show up they have the same stats later on, but don’t get them unlocked from the start of the new game.

## March 3, 2015

**Basic Ability Components**

* Summon a character into the battlefield
* Apply damage to a character
* Apply a status effect
* Apply a stat boost
* Create a shield
* Create a weapon

**Core Spells**

* Defensive spells
* Defensive AoE spells

**Categories**

* Buff
  * Individual
  * Area of Effect
* Utility
  * Summon
  * Travel
* Healing
  * Individual
  * AoE
  * Heal over time Individual
  * Heal over time AoE
* Damage
  * Regular
  * Damage over time
  * Drain
  * Hold while dealing damage (status effect?)
  * Prevents them from moving or taking turn

**Templates**

* Missile
  * Individual damage
  * High damage
* Bolt (eg. Energy Bolt)
  * Individual damage over time
  * Lower damage
* Ball
  * Individual drain
  * Lower damage
* Beam
  * Individual hold
  * Lower damage
  * No damage ver, but knocks them out more effectively
* Wave (Aoe Missile), Bomb (thrown)
  * Cone/spray (Aoe Bolt)
  * Rain/meteor (Aoe drain)
  * Column/lightning (Aoe hold)

**Summons**

* Only one summon per character at a time
  * Ex party of 4 chars can summon up to 4 summons
  * If already out, the same entry in the menu would be greyed out
* Control
  * Summon characters can be setup to be manual or auto controlled
  * Auto controlled characters have behavior scripts
* Animations
  * Can have multiple animations but still be considered a single unit
* Health
  * Each unit has its own health and stats that gets reset at the beginning of battle
  * If replaced with another unit before the first one is defeated, the original

**Spell Examples**

* Portal - travel to a given location, open up world map for fast travel
  * Have to leave someone behind, item version
  * Don’t have to leave someone, if using spell version
* Leaf shuriken, turns leaves into flying missile

## March 29, 2015

**Kickstarter ideas**

* Finish one game and bring over save data to the second game
  * Arc the lad, dot hack, walking dead games
* Expansions?
* People need to know we have a reputation for finishing the games we start
* RPGs with expansions? Need examples for this
* Borderlands with level caps that increase, new quests
* Characters you build over the games…
* New game plus modes? Different modes or quests on new game plus
* New sidequests

**Episodes**

* Part of a book, half or a third of the content there, definitely a third of a book.
* 9 episodes for the first chunk and engine
* Chunks of the engine without changing the basic engine
* 6-9 episodes for the first part without changing
* New build with new features, like a new battle system
* Bring characters back to their first appearance in a new game plus
* Characters have to follow their storylines no matter what
* Items or whatever that don’t have limits can be brought back
* Keep stats for each character through all episodes new game pluses

**Experience system for leveling**

* We need to define character stats, levels, experience, etc
* Since we are not doing the standard stats of STR, DEF, etc
* Stats for defense, attack, adjusted based on armor/weapons, health points, magic points, power points. Base stats for character.

**Stats**

* Health points / HP
* Magic points / MP
* Power points / PP
* Speed - fill battle bar
* Dodge - invisible stat? bonus perks based on a spell or skill. Perk tree?
  * Blunt dodge
  * Slash dodge
  * Pierce dodge
  * Magic dodge
* Blunt attack
* Slash attack
* Pierce attack
* Magic attack
* Blunt defense
* Slash defense
* Pierce defense
* Magic defense

## April 14, 2015

**First Playable**

* Town
  * Player is able to move character around
  * Buildings that have collision
  * NPCs that are walking around randomly
  * NPCs also have collision
  * Have some atmospheric weather effects (clouds, rain)
  * Events
* Cutscene from a trigger tile
* Cutscene from an action button
* Open a chest
* Enter/exit buildings
* Exit town transition to Dungeon
* Dialogue for NPCs
* Shop transitions
* Inventory transitions
* Save/load transitions
  * Shop
  * Inventory
  * Save/Load
  * Dungeon
* Player is able to move character around
* Have random battle transitions
* Player can exit dungeon to go back to town
* Battle
  * Losing a battle and transitioning to Game Over
  * Losing a battle and transitioning to Capture
  * Winning a battle and transitioning to Dungeon
  * Have 3 test characters on player side
  * Have 3 test enemies on enemy side
  * Show the battle bar for time
  * Add all combatants to battle bar with random start times
  * When player char is at DECIDE phase, a menu box appears
  * When enemy char is at DECIDE phase, they choose ATTACK, and random opposite person to target
  * Menu box has ATTACK, MAGIC, ITEM, RUN
  * ATTACK shows target icon over first enemy
  * Target icon can be moved to any enemy and loops
  * If action button pressed over enemy, adds to action queue who is going to attack who.
  * If cancel button pressed over any, goes back to Menu Box
* Capture
  * Cutscene at the start
  * Simon says minigame where they have to succeed 3 times to break free of bonds
  * Player is given control
  * Either have NPCs that start battle when “talked to” or random battles
  * They can move to the mini dungeon exit to transition to Dungeon
* Game Over
* Introduction
* Opening Menu
