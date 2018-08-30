//
// PCSX-ReloadedX - Pre-Beta v1.2
//

This is a port of PCSX-Reloaded to XBox using hardware rendered graphics.

Note: This is still a work in progress and in pre-beta/alpha stages. Parts of the port are still not complete,
especially the GUI that is still in early stages atm (i.e. ugly and slightly broken).

Knowen bugs:
- Scissor screwed after re-entering game from GUI until the game sets it again (usually makes menus look broken).
- Analog sticks stop working after re-entering from GUI (I think I know the issue, should be an easy fix).
- Audio crackle when switching from GUI to in-game.
- Fix rumble, it currently works but has a bug that causes it to say on sometimes.

Main remaining tasks:
- Heavily improve the GUI and add configs, buttons, etc.
- Get support for sub-directories.
- Save configs against each indervidual games.
- Explore speed optimizations. 
- Get built in cheats working.
- Get save states working.