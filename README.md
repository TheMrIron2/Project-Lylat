# Project: Lylat
**Project: Lylat** is an On-Rails and 360° 3D space shooter in the style of Star Fox.  

Project: Lylat is made with **[Unreal](https://www.unrealengine.com/)** and written purely in C++.

The short term goal is to create a playable proof of concept with all working logic and a demo (eg. Star Wolf battle).  
The long term goal is subject to discussion as we progress.

If you want to get in touch, get more information or if you'd just like to hang out with the developers, join us on **[Discord](https://discord.gg/XaewHrj)**.

## Getting involved
Getting involved is fairly easy, all you need is experience with Unreal.  
Project: Lylat uses the latest stable version of Unreal 4 (currently 4.25.1).

First and foremost, make a fork and clone it:
```
git clone https://github.com/ < name of the user / organization to which you forked Project: Lylat to > /Project-Lylat Lylat
```

Secondly, you need Discord's Game SDK.
1. Download the [Game SDK](https://discord.com/developers/docs/game-sdk/sdk-starter-guide#step-1-get-the-thing).
1. Copy all sources and headers from the `cpp` directory of the downloaded Game SDK ZIP into `Source/Lylat/Discord`.
1. Copy the following files from `lib/< your architecture >` from the Game SDK archive into `Source/Lylat/Discord`, according to this table:

| Operating System | Files to copy                                              |
|------------------|------------------------------------------------------------|
| Windows          | `discord_game_sdk.dll` and `discord_game_sdk.dll.lib`      |
| macOS            | `discord_game_sdk.dylib` and `discord_game_sdk.bundle`     |
| Linux            | `discord_game_sdk.so`                                      |

Now, open the `Lylat.uproject` in Unreal.  
Make your changes, push them into your fork and make a pull request.  
We'll try to respond as soon as possible.

## Gameplay Details

- Pressing the `Fire` (`Left Mouse` by default) button shoots one green laser beam.
- If `Fire` is held down, three consecutive beams will be shot, then a "charge" shot will be charged.
- Charge shots will lock to an enemy and releasing the `Fire` button will release the shot.
- "Bombs" may also be fired if the player has any; these are collected during gameplay.
- The laser beam may also be improved by a power up.
- Collecting a laser power-up will increase the amount of shots to two simultaneous shots.
- Collecting a second laser power-up will fire two simultaneous shots, but more powerful blue ones.

---

- The player may accelerate (referred to as "boost") or brake to change speed for a short time, however, the player cannot stop moving forward.
- The player may also perform a somersault or a barrel roll.
- Somersaults can be performed by pressing the somersault button, or by moving upwards and braking.
- Barrel rolls can be performed by leaning left or right twice in quick succession.
- In `all range` mode (referred to as `360°`), the player may also perform a U-turn by pressing the U-turn button (`F` by default.).
- Boosting, braking, somersaults and U-turns all deplete the `Energy Meter`.
- If the meter turns completely red, these techniques cannot be performed until the meter resets.
- The energy meter replenishes automatically after a short time.

---

- The player's health is indicated in the "Shield Gauge" in the top left corner of the screen.
- When fighting a boss, the boss's "Shield Gauge" may be displayed vertically on the left side of the screen.
- The player may also take damage to their ship.
- If the player takes a lot of damage at once, there is a chance their ship will lose a wing.
- This affects the control of the ship and reverts any laser power-ups that may have been picked up.
- All wings will be repaired if a Repair or Laser power-up is picked up.

## Credits
- **[TheMrIron2](https://github.com/TheMrIron2)** - Project Management, Sound Design
- **[Apfel](https://github.com/Apfel)** - Programming
- **[benjamin238](https://github.com/benjamin238)** - Model Assistance
- **[MotoLegacy](https://github.com/MotoLegacy)** - Planning and Programming

## Disclaimer
This is a non-commercial, free project with no intention of infringement on any Nintendo IPs or otherwise.  
Models and the Star Fox name are recognized properties of [Nintendo](https://www.nintendo.com/).  
You can find this notice in the license, too.
