# CA1-AI-
Space Station Rescue assignment for games AI

# Description
Player collects the green and blue workers which wander to gain score. Worker bots spawn on the red tiles

The sweeper bots(ship with yellow ring), also collect these workers to gain score, if the player kills the sweeper bot 
the sweeper bots score will be added to the player score.

The sweeper bot wanders when no workers are in range, when workers are in range it seeks towards them and collects them,
if the player is in range the sweeper bot will prioritise fleeing instead of seeking.

Nests spawn randomly in game (blue squares), when the player is in range of this nest it will fire a heat seaking missle at the player which seeks the player.
From the nests spawn predators. Which pathfind to the player using a flowfield. When in range of the player they fire missles at the player

The player can shoot these nests and kill them, if so they wont fire  at the player and presators wont respawn from here.

If the player loses all health they lose and the game ends

Collsiion detection implmeneted with all ships in the game 

Power ups are placed around the map that can be picked up:


# Controls
Up Arrow: Accelerate
Down Arrow: Slow Down
Right Arrow: Rotate right
Left Arrow: Rotate left
Space: Player shoots bullet ahead of them.(limited to 3 bullets at a time).

# Extras
Map Culling: Only renders tiles that are in the gameview
HUD: Displays game info to the player
Win / Lose state: Player wins when all workers are saved, lose when you run out of life
HealthSystem: Healthbars displayed under nests and player hearts in the HUD
Workers and predators randomly spawn from spwanpoints on the map 

Split: Aaron 50%, Jack 50%

# Doxygen 
Doxygen files are located in project DOX folder
