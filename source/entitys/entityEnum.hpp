#pragma once

namespace entityEnum {

// Enumerations for entity state, to short saying what is the entity doing right now
// VOID nonused (default init)
enum class entityMovementState {
    VOID,
    STAYON,
    IDLE,
    WALKING,
    RUNNING,
    MAXENUM
};

// enum for direction, to short saying where the entity is looking at
// VOID is for the case that the entity is not moving
// UP, DOWN, LEFT, RIGHT are for the main case that the entity is moving
// four more directions are for the case that the entity is moving diagonal
// MAXENUM is for the case that the entity is not moving
enum class entityDirection {
    VOID,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    MAXENUM
};

// enum for entity state, saying if the entity is alive or dead, or if the entity is not used (disabled)
// VOID is for the case that the entity is not used (default)
// ALIVE the entity is alive and now can be used in the game
// DEAD the entity is dead and now can be used in the game, but the entity is not alive
// DISABLE the entity is disabled and now can't be used in the game
enum class entityState {
    VOID,
    ALIVE,
    DEAD,
    DISABLED,
    MAXENUM
};

// enum for Behavior it, can be
// VOID non used (default initialisation)
// PLAYER not friendly and not Enemy, some like a neutral but can kill your ass)
// ENEMY that all non friendly entity, like a slime, rat, bosses, etc
// NEUTRAL that is neutral entity, but if player (you) did some bad or gut, can be changed Behavior to some side
// NPC for that case need coments?
enum class entityBehaviorClass {
    VOID,
    PLAYER,
    ENEMY,
    NEUTRAL,
    NPC,
    MAXENUM
};

// CLASSes
// idk for what use this shiet, stiil coments down
enum class entityClass {
    VOID,
    WARRIOR,
    MAGE,
    ROGUE,
    MAXENUM
};
};