# Idle Wizard

Idle wizard is a game in the idle/clicker genre. You play as a wizard that can cast various spells.
Spells have costs of a combination of different mana types and/or resources of various kinds.
Build a mana altar dedicated to one particular mana type. The catch is you can only have two mana altars at a time...
But maybe some tinkering with space & time magic could aid you in order to cast more advanced spells!


## build
Prerequisits: cMake
Builds with cMake. Currently only compilation with GCC is allowed. In the future more options will be available.

Can target both web & desktop. 

### Building for desktop
```
cmake -S . -B build -G "MinGW Makefiles"
```

### Building for web
Prerequisits: Emscripten
You only need to start cmake with emcmake in order to build for the web, no extra flags are needed.

```
emcmake cmake -S . -B build -G "MinGW Makefiles"
```

## Dependencies

Idle wizard aims to have as few dependencies as possible, currently [Raylib](https://www.raylib.com/) is the only dependency.

## Contributing

This project is currently maintained by a single developer SkitzFist. If you're intersted in helping out. Please contact me.