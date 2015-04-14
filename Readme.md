[![Build Status](https://travis-ci.org/Sumolari/TacticsDS.svg?branch=master)](https://travis-ci.org/Sumolari/TacticsDS)

`Tactics DS` is an example game developed using `FMAW Framework` which is included in this repository. This project is the result of our work for different subjects on video game design and architecture.

## FMAW Framework

`FMAW Framework` is a custom framework built on top of `libnds` and designed to be ported to any platform easily. Currently there is only available an implementation for Nintendo DS.

Files prefixed `fmaw_` are part of the framework.

Documentation can be generated using Doxygen with `make doc`.

## Tactics DS

`Tactics DS` is just a demo of the capabilities of `FMAW Framework`. It's inspired on Fire Emblem saga and features single and multiplayer modes. It's not meant to be a commercial product in any way but an academic example of `FMAW Framework usage`.

### Building

Just a `make` call should be enough to build the project, assuming you have set up [devKitPro](http://devkitpro.org).

### Running Tactics DS

`Tactics DS` requires access to filesystem. If you are running the game on a Nintendo DS with a flashcard you should ensure that at the root of the flashcard filesystem exists a folder named `maps` containing the maps of the game, otherwise you wont be able to play it.

When running on a simulator, we recommend [DesMuME](http://www.desmume.com/). You'll need to run DesMuME with a special parameter to tell which folder should be mounted as root of the filesystem. We usually run `Tactics DS` with the following command, called on root of the project.

````
desmume framework.nds --cflash-path=FAT
````

## Development blog

We wrote a blog during development, which is available on [Github](http://sumolari.github.io/TacticsDS) (only in Spanish).