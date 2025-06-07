#ifndef UTILS_H
#define UTILS_H

#include "../include/game.h"

typedef struct {
    char *key;
    char *value;
} Translation;

void clear_input_buffer(void);
void display_banner(void);
void display_credit(void);
void shuffle(int arr[][2], int size);
char *str_duplicate(const char *str);
void save_game(GameState *game, char *filename);
GameState *load_game(char *filename);
void change_language(GameState *game, char *lang_code);
void set_difficulty(GameState *game, int difficulty);
Translation *load_language(char *lang_code, int *count);
char *get_text(Translation *trans, int count, char *key);
void free_translations(Translation *trans, int count);

#endif