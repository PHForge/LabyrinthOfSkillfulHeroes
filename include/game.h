#ifndef GAME_H
#define GAME_H

#include "../include/maze.h"

// Forward declaration of the GameState structure with an explicit tag
struct GameState;

// Declare the GameState type to avoid circular dependency issues
typedef struct GameState GameState;

typedef union {
    int damage;                     // For the attack skill
    int heal_amount;                // For the heal skill
} SkillData;

typedef struct Skill {
    char *name;                     // Skill name
    void (*action)(GameState *);    // Function pointer for skill action
    SkillData data;                 // Data associated with the skill (e.g., damage or heal amount)
    struct Skill *next;             // Pointer to the next skill in the list
} Skill;

typedef struct {
    Skill *head;                    // Pointer to the first skill in the list
} SkillList;

typedef struct GameState {
    Maze *maze;                     // Pointer to the maze structure 
    SkillList *skills;              // Pointer to the list of skills
    int player_hp;                  // Player's health points
    char *lang;                     // Language code for translations
    int difficulty;                 // Game difficulty level
} GameState;

void game_loop(GameState *game);
void attack(GameState *game);
void heal(GameState *game);
Skill *create_skill(char *name, void (*action)(GameState *), SkillData data);
void add_skill(SkillList *list, Skill *skill);
void remove_skill(SkillList *list, char *name);
void execute_skill(Skill *skill, GameState *game);
void free_skills(SkillList *list);

#endif