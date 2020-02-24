# Project Lylat
On-rails 3D space shooter for PC in the style of Star Fox. <br>
Written mostly in C#, this project uses **[Godot](https://godotengine.org)** as the game engine.

The short term goal is to create a playable proof of concept with all working logic and a demo. (eg. Star Wolf battle) <br>
The long term goal is subject to discussion as we progress.

## Credits

- **[TheMrIron2](https://github.com/TheMrIron2)** - Project Management, Sound Design
- **[Apfel](https://github.com/Apfel)** - Programming
- **[benjamin238](https://github.com/benjamin238)** - Model Assistance
- **[MikeModder](https://github.com/MikeModder)** - Programming
- **[MotoLegacy](https://github.com/MotoLegacy)** - Planning and Programming

## Gameplay Details

- Pressing the `Fire` (`Left Mouse` by default) button shoots 1 green laser beam.
- If `Fire` is held down, three consecutive beams will be shot, then a "charge" shot will be charged.
- Charge shots will lock to an enemy and releasing the `Fire` button will release the shot.
- "Bombs" may also be fired if you have any; these are collected during gameplay.
- Your laser beam may also be improved by a power up.
- Collecting a laser power-up will increase the amount of shots to two simultaneous shots.
- Collecting a second laser power-up will fire two simultaneous shots, but more powerful blue ones.

---

- The player may "Boost" or "Brake" to change speed for a short time, however the game will still be constantly moving forward.
- The player may also perform a "somersault" or a "barrel roll".
- Somersaults can be performed by pressing the somersault button, or by moving upwards and braking.
- Barrel rolls can be performed by leaning left or right twice in quick succession.
- In "all range" mode, the player may also perform a U-turn by pressing the U-turn button.
- Boosting, braking, somersaults and U-turns all use the "Boost Meter".
- If the meter turns completely red, these techniques cannot be performed until the meter resets.

---

- The player's health is indicated in the "Shield gauge" in the top left corner of the screen.
- When fighting a boss, the boss's "shield gauge" may be displayed vertically on the left side of the screen.
- The player may also take damage to his ship.
- If the player takes a lot of damage at once, there is a chance their ship will lose a wing.
- This affects the control of the ship and reverts any laser power-ups that may have been picked up.
- All wings will be repaired if a Repair or Laser power-up is picked up.

# Disclaimer

This is a non-commercial, free project with no intention of infringement on any Nintendo IPs or otherwise. <br>
Models and the Star Fox name are recognised properties of [Nintendo](https://www.nintendo.com/). 
