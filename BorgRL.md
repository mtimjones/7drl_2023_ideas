# BorgRL Game Design Document

This documents the design for the 2023 7DRL.

BorgRL is a Borg Roguelike.  The player is the Borg and travels across N sectors, fighting enemies, scavanging resources, mining planets and converting these resources into upgrades for its evolving fleet of assimilated drones.

## Features
- Procedurally generated sectors
- Turn-based and real-time gameplay (user can pause)
- Permadeath
- Random enemies, wrecks, planets, gas clouds, etc.
- Sector Exit Bosses.
- Randomly scavenged implants (power-ups).

## Development Plan
- [X] Experiment with drone attribute balancing (monte carlo simulation).
- [ ] Reuse prior 7drl map UI.
- [ ] Use CES for scheduling.
- [ ] Implement basic UI.
- [ ] Create random wrecks.
- [ ] Create scavenger drone type.
- [ ] Mouse-over context development.
- [ ] Mouse select/deselect of drone.
- [ ] Implement scavenging drone behavior
- [ ] Implemnet redocking behavior.

## UI Concept
`
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
`
