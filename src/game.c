#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/game.h"
#include "../include/utils.h"

// Game loop function
// This function handles the main game loop, allowing the player to interact with the maze and use skills.
void game_loop(GameState *game) {
    int trans_count;
    Translation *trans = load_language(game->lang, &trans_count);
    char input;
    while (1) {
        display_maze(game->maze);
        printf("\n%s (1: %s, 2: %s, e: %s): ", get_text(trans, trans_count, "GAME_ACTIONS"), 
               get_text(trans, trans_count, "MSG_ATTACK"), get_text(trans, trans_count, "MSG_HEAL"), 
               get_text(trans, trans_count, "GAME_QUIT"));
        scanf("%c", &input);
        clear_input_buffer();
        if (input == 'e') break;
        else if (input == '1') {
            Skill *skill = game->skills->head;
            while (skill && strcmp(skill->name, "attack") != 0) skill = skill->next;
            if (skill) execute_skill(skill, game);
        } else if (input == '2') {
            Skill *skill = game->skills->head;
            while (skill && strcmp(skill->name, "heal") != 0) skill = skill->next;
            if (skill) execute_skill(skill, game);
        } else {
            move_player(game->maze, input, game->lang);
            if (game->maze->grid[game->maze->player_row][game->maze->player_col] == 'E') {
                printf("%s\n", get_text(trans, trans_count, "GAME_WIN"));
                break;
            }
        }
    }
    free_translations(trans, trans_count);
}

// Attack function
// This function simulates an attack action, displaying a message and reducing the player's health.
void attack(GameState *game) {
    int trans_count;
    Translation *trans = load_language(game->lang, &trans_count);
    printf("%s\n", get_text(trans, trans_count, "MSG_ATTACK"));
    free_translations(trans, trans_count);
}

// Heal function
// This function simulates a healing action, restoring a portion of the player's health and displaying a message.
void heal(GameState *game) {
    int trans_count;
    Translation *trans = load_language(game->lang, &trans_count);
    game->player_hp = (game->player_hp + 20 > 100) ? 100 : game->player_hp + 20;
    printf("%s HP: %d\n", get_text(trans, trans_count, "MSG_HEAL"), game->player_hp);
    free_translations(trans, trans_count);
}

// Skill creation and management functions
// These functions handle the creation, addition, removal, and execution of skills in the game.
Skill *create_skill(char *name, void (*action)(GameState *), SkillData data) {
    Skill *skill = malloc(sizeof(Skill));
    skill->name = str_duplicate(name);
    skill->action = action; // Compatible avec GameState *
    skill->data = data;
    skill->next = NULL;
    return skill;
}

// Add a skill to the skill list
// This function adds a new skill to the beginning of the skill list.
void add_skill(SkillList *list, Skill *skill) {
    skill->next = list->head;
    list->head = skill;
}

// Remove a skill from the skill list by name
// This function searches for a skill by name and removes it from the list if found.
void remove_skill(SkillList *list, char *name) {
    Skill *current = list->head, *prev = NULL;
    while (current && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    if (!current) return;
    if (prev) prev->next = current->next;
    else list->head = current->next;
    free(current->name);
    free(current);
}

// Execute a skill action
// This function calls the action associated with a skill, passing the current game state.
void execute_skill(Skill *skill, GameState *game) {
    skill->action(game); // Compatible avec GameState *
}

// Free the skill list
// This function iterates through the skill list, freeing each skill and its associated resources.
void free_skills(SkillList *list) {
    Skill *current = list->head;
    while (current) {
        Skill *temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }
    free(list);
}
