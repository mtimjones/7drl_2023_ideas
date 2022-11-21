# BorgRL Game Design Document

This documents the design for the 2023 7DRL.

BorgRL is a Borg Roguelike.  The player is the Borg and travels across N sectors, fighting enemies, scavanging resources, mining planets and converting these resources into upgrades for its evolving fleet of assimilated drones.  The player explores each sector, jumping to the next at the sector's end.  In the last sector is a boss fight and the end-game.

## Features
- Procedurally generated sectors
- Turn-based and real-time gameplay (user can pause)
- Permadeath
- Random enemies, wrecks, planets, gas clouds, etc.
- Sector Exit Bosses.
- Randomly scavenged implants (power-ups).

## UI Concept
```
           1         2         3         4         5         6         7         8         9         1
  1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
 1+----------------------------------------------------------------+---------------------------------+
 2|                                                                | Entity    State    Type  HP Lvl |
 3|                                                       P        | Borg      @         H/A   2   1 |
 4|                                                                | Drone     Docked      K   2   1 |
 5|                                                                | Scout     Docked      K   3   1 |
 6|                                                                | Miner     Docked      M   1   1 |
 7|                       %                         ###            | Scav      Undocked    S   1   1 |
 8|                                                ########        |                                 |
 9|                                                  ########      |                                 |
10|                                                   ######       |                                 |
11|                           S                        ####        |                                 |
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
22|            D                                                   +---------------------------------+
23|                                                                |  Attack: + 1   Mining    : + 1  |
24|                                           P                  ##|  Armor : + 1   Scavanging: + 1  |
25|                                                            ####|                                 |
26|                                                         #######|  Time: ****    Resources: ****  |
27+----------------------------------------------------------------+---------------------------------+
28| Context: <mouse-over context info>                             | Actions:                        |
29+----------------------------------------------------------------+   (h)elp        (p)ause         |
30| Press 'h' for help.                                            |   (a)ssimilate  ( )step         |
31|                                                                |   (k)ill                        |
32|                                                                |   (s)cavange                    |
33|                                                                |   (m)ine                        |
34|                                                                |   (d)ock        (r)ecycle       |
35+----------------------------------------------------------------+---------------------------------+
```

### Map Window
The Map (upper left) shows the map of the portion of the sector the Borg (@) is in.  It can consist of gas clouds (#), planets (P), wrecks (%), enemies (D) and your drones (S).  Gas clouds hide objects, so the Borg must explore to optionally discover what's hidden.

### Drone Window
The Drone window (upper right) shows the Borg and its contents (drones and their stats).  Below the drone window is the Stats window which shows the current implants and resources.

### Context/Log Window
The context window shows context for the item under the passive mouse cursor.  Below this is the log, which contains a scrolling log of information.

### Actions Window
The actions window shows the key-bindings used to play the game.

## Controls
The player uses the mouse and/or keyboard.  Below are some examples of mouse and/or keyboard play.
- Left-click an entity in the Drone window and a target in space to undock and begin operation (attack, mine, scavange).
- Left-click a drone in space and then Left-Select the Dock button to return a drone to the Borg.
- Left-click a drone in space and then press (d)ock to return a drone to the Borg.
- Left-click an enemy drone and press (a)ssimilate to try to hack that drone.
- Left-click a drone and press (r)ecycle to destroy and turn into resources.
- Left-click an enemy drone and press (k)ill to send all combat drones to attack that enemy drone.
- Left-click an enemy wreck and press (s)cavange to send all scavenger drones to scavenge the wreck.
- Left-click a planet and press (m)ine to send all mining drones to mine the planet.
- (p)ause the game to perform actions, resume to re-enter real-time, spacebar to step.
- Arrow keys are used to move the Borg.

## Drones

## Combat
Combat occurs in phases.  Each entity attacks in turn with entities that are killed becoming wrecks.  Combat drones can have status effects (Energy, Plasma, Kinetic) which also are resistence.  In a rock-paper-scissors style, weapons have the following effects on combat.

| &nbsp; | Energy | Plasma | Kinetic |
| :-- | :-: | :-: | :-: |
| Energy | 0 | +1 | -1 |
| Plasma | -1 | 0 | +1 |
| Kinetic | +1 | -1 | 0 |

In other words, Energy weapons are +1 against Plasma weapons.  Kinetic weapons are -1 effective against Plasma weapons.  Like weapons have no advantage or disadvantage.

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

## Combat System
Each entity takes turns attacking.

A hit is calculated by:

```
potential = ( 1.0 / ( attacker.attack + attackee.armor ) ) * attacker.attack
if ( random() < potential) Hit!
```

If a hit succeeds, damage uses the following calculation:

```
damage = attacker.attack * random()
```

## Development Plan
- [X] Experiment with drone attribute balancing (monte carlo simulation). mc_combat.*
- [ ] Reuse prior 7drl map UI.
- [ ] Implement CES for entity scheduling.
- [ ] Implement basic UI.
- [ ] Create object for entities in space (with individual/random behavior).
- [ ] Create random wrecks (no behavior).
- [ ] Create scavenger drone type (scavange behavior).
- [ ] Mouse-over context development.
- [ ] Mouse select/deselect of drone.
- [ ] Implement scavenging drone behavior
- [ ] Implement redocking behavior.

Stretch Goals
- [ ] Create orbit behavior for drones (around enemies, planets, wrecks).
- [ ] Mini-game for hacking (assimilating) a drone in space.


[^1]: https://pavcreations.com/level-systems-and-character-growth-in-rpg-games/
