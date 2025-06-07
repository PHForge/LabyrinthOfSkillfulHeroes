#ifndef GAME_H
#define GAME_H

#include "../include/maze.h"

// Déclaration anticipée de la structure GameState avec un tag explicite
struct GameState;

// Définir le typedef pour GameState
typedef struct GameState GameState;

typedef union {
    int damage;      // Pour la compétence d'attaque
    int heal_amount; // Pour la compétence de soin
} SkillData;

typedef struct Skill {
    char *name;
    void (*action)(GameState *); // Utilise le typedef GameState *
    SkillData data;
    struct Skill *next;
} Skill;

typedef struct {
    Skill *head;
} SkillList;

typedef struct GameState {
    Maze *maze;
    SkillList *skills;
    int player_hp;
    char *lang;
    int difficulty;
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