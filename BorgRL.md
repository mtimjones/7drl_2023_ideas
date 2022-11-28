# BorgRL Game Design Document

BorgRL is a Borg Roguelike (to be developed for the 2023 7DRL).  The player is the Borg and travels across N sectors, fighting enemies, scavanging resources, mining planets and converting these resources into upgrades for its evolving fleet of assimilated drones.  The player explores each sector, jumping to the next at the sector's end.  In the last sector is a boss fight and the end-game.  The player must optimize resources to heal drones, assimilate or kill enemies, and kill the final boss to win.  Drones have status effects, so a mix will be necessary to win.

## Features
- Procedurally generated sectors
- Turn-based and real-time gameplay (user can pause)
- Permadeath
- Random enemies, wrecks, planets, gas clouds, etc.
- Randomly scavenged implants (power-ups).
- Resource management

## UI Concept
```
           1         2         3         4         5         6         7         8         9         1
  1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 1+----------------------------------------------------------------+---------------------------------+
 2|                                                                | Entity    State     Lvl HP |
 3|                                                       P        | Borg      @           1  2 |
 4|                                                                | Drone     Docked      1  2 |
 5|                                                                | Scout     Docked      1  3 |
 6|                                                                | Digger    Docked      1  1 |
 7|                       %                         #####          | Vagrant   Undocked    1  1 |
 8|                                                ########        |                                 |
 9|                                                  ########      |                                 |
10|                                                   ######       |                                 |
11|                           V                        ####        |                                 |
12|                                                                |                                 |
13|                                                                |                                 |
14|                               @                                |                                 |
15|      ####                                                      |                                 |
16|   ########                                                     |                                 |
17|  ########                                                      |                                 |
18|   ######                                                       |                                 |
19|    ####                                                        |                                 |
20|     ##                                                         |                                 |
21|                                                                |                                 |
22|            R                                                   +---------------------------------+
23|                                                                |  Attack: ***   Mining    : ***  |
24|                                           P                  ##|  Armor : ***   Scavanging: ***  |
25|                                                            ####|         <<< Paused >>>          |
26|                                                         #######|  Time: ****    Resources: ****  |
27+----------------------------------------------------------------+---------------------------------+
28|          |    (h)elp    |   (p)ause    |   ( )step    | (a)ssimilate |    (d)ock    |            |
29| Actions: +---------------------------------------------------------------------------------------+
30|          |    (k)ill    |  (r)ecycle   |   (m)ine     |  (s)cavange  |    (h)eal    |            |
31+--------------------------------------------------------------------------------------------------+
32| Context: <mouse-over context info>                                                               |
33+--------------------------------------------------------------------------------------------------+
34| Press 'h' for help.                                                                              |
35|                                                                                                  |
36|                                                                                                  |
37|                                                                                                  |
38|                                                                                                  |
39|                                                                                                  |
40+--------------------------------------------------------------------------------------------------+
```
### Map Window
The Map (upper left) shows the map of the portion of the sector the Borg (@) is in.  It can consist of gas clouds (#), planets (P), wrecks (%), enemies (D) and player drones.  Gas clouds hide enemies, and cannot be passed by the player.  Player drones are in bold to differentiate between enemy drones.

### Drone Window
The Drone window (upper right) shows the Borg and its contents (drones and their stats).  Below the drone window is the Stats window which shows the current implants and resources.

### Context/Log Window
The context window shows context for the item under the passive mouse cursor.  Below this is the log, which contains a scrolling log of information.

### Actions Window
The actions window shows the key-bindings used to play the game.  The user may use the key, or left-click the action.

## Controls
The player uses the mouse and/or keyboard.  Below are some examples of mouse and/or keyboard play.
- Left-click an drone in the Drone window and then a target in space to undock and begin operation (attack, mine, scavange).
- Left-click an enemy drone and (a)ssimilate to attempt to assimilate this enemy drone.
- Left-click a drone in space and then Left-click the (d)ock button (or press 'd') to return a drone to the Borg.
- Left-click a docked drone and press (h)eal or (r)ecycle to heal or destroy the drone.
- Left-click an enemy wreck and press (s)cavange to send all scavenger drones to scavenge the wreck.
- Left-click a planet and press (m)ine to send all mining drones to mine the planet.
- (p)ause the game to perform actions, resume to re-enter real-time, spacebar to step.
- Arrow keys are used to move the Borg.

## Drones

### Player Drones

Note that player drones are always in Bold.

| Name | Type | Icon | Armor | Damage | HP | Notes |
| :-- | :-: | :-: | :-: | :-: | :-: | :-- |
| Vagrant | Scavenger | V | Mid | None | Low | Scavenges wrecks for resources, retrieves implants from containers |
| Digger | Miner | D | Mid | None | Low | Mines planets for resources |


### Enemy (or Assimilated Player) Drones
| Name | Type | Icon | Armor | Damage | HP | Notes |
| :-- | :-: | :-: | :-: | :-: | :-: | :-- |
| Scout | Combat | S | High | Low | Low  | |
| Raven | Combat | R | Mid | Mid | Mid | |
| Kestral | Combat | K | Mid | High | High | |
| Tank | Combat | T | High | High | High | |
| Gnat | Combat | G | Mid | Low | Low | |
| Eagle | Combat | E | Low | Mid | Mid | |
| Hunter | Combat | H | Mid | Mid | Mid | |
| Minotaur | Combat | M | Mid | High| High | |

### Other Objects

| Name | Icon | Notes |
| :-- | :-: | :-- |
| Borg | @ | Borg mothership |
| Wrecks | % | Resources available for scavenging by Vagrants |
| Containers | ? | Resources or implants available for scavenging by Vagrants |
| Planets | P | Planets available for mining by Diggers |
| Gas Clouds | # | Inaccessible regions (which can hide enemies) |
| Gate | > | Warp to next sector |

## Combat
An enemy engages in combat when the Borg or one of its drones comes within a specific distance (note that gas clouds can hide enemies).

Combat occurs in phases.  Each entity attacks in turn with entities that are killed becoming wrecks.  Combat drones can have status effects (Energy, Plasma, Kinetic) which also are resistence.  In a rock-paper-scissors style, weapons have the following effects on combat.

| &nbsp; | Energy | Plasma | Kinetic |
| :-- | :-: | :-: | :-: |
| Energy | 0 | +1 | -1 |
| Plasma | -1 | 0 | +1 |
| Kinetic | +1 | -1 | 0 |

In other words, Energy weapons are +1 against Plasma weapons.  Kinetic weapons are -1 effective against Plasma weapons.  Like weapons have no advantage or disadvantage.

A hit is calculated by:

```
potential = ( 1.0 / ( attacker.attack + attackee.armor ) ) * attacker.attack
if ( random() < potential) Hit!
```

If a hit succeeds, damage uses the following calculation:

```
damage = attacker.attack * random() + resistance
```

## Progression System

The leveling system is based upon Disgea[^1], with a gentle progression of xp per level.

```
xp2lvlup = 0.04 * (level^3) + 0.8 * (level^2) + 2*level
```

| Level | xp2NextLvl |
| :-: | --: |
| 1 | 3 |
| 2 | 8 |
| 3 | 14 |
| 4 | 23 |
| 5 | 35 |
| 6 | 49 |
| 7 | 67 |
| 8 | 88 |
| 9 | 112 |
| 10 | 140 |

## Economy
The currency of the game are 'resources' which are mined from planets, scavenged from enemy wrecks. or salvaged from recycled drones.  These resources are used to heal drones (in the Borg), assimilate (hack) enemy drones, or upgrade capabilities at academies.

<img src="https://github.com/mtimjones/7drl_2023_ideas/blob/main/IMG_0001.jpg" width="600">

## Implants
Implants can be randomly found in enemy wrecks or containers.  These increase the player stats (attack, armor, mining, scavenging).  These should be rare (one every two or three levels), but should encourage exploration and combat.

## Map Layout
The map is laid out in FTL style where the player starts off on the left side and must reach the exit on the right side.  The map viewport is 64x25.  The entire sector map is 3 viewports deep (75) by 9 viewports wide (9x64).  The entire sector is loaded with gas clouds and then each viewport is loaded with entities (planets, wrecks, enemies).  No entities will exist in the first player viewport (middle row, first column).  THe last middle viewport will also have nothing but the exit gate.

## Game Start
The player begins with the Borg, a scavenger drone, a combat drone, and a small amount of resources.

## Prototype Plan
- [X] Experiment with drone attribute balancing (monte carlo simulation). mc_combat.*
- [ ] Intro screen.
- [ ] Reuse prior 7drl map UI.
- [ ] Implement procedural map generation.
- [ ] Implement CES for entity scheduling.
- [ ] Implement basic UI.
- [ ] Create object for entities in space (with individual/random behavior).
- [ ] Implement the FOV algorithm.
- [ ] Create random wrecks (no behavior).
- [ ] Create scavenger drone type (scavange behavior).
- [ ] Mouse-over context development.
- [ ] Mouse select/deselect of drone.
- [ ] Implement scavenging drone behavior
- [ ] Implement redocking behavior.
- [ ] End-game screen (stats, etc.).

Stretch Goals
- [ ] Create orbit behavior for drones (around enemies, planets, wrecks).
- [ ] Mini-game for hacking (assimilating) a drone in space.
- [ ] Create OnVerb methods (OnDock, OnAttack, OnDeath, OnRecycle, etc.) to implement component behaviors.

[^1]: https://pavcreations.com/level-systems-and-character-growth-in-rpg-games/
