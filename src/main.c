/*
 * Labyrinth of Skillful Heroes
 * Copyright (c) 2025 PHForge
 *
 * A text-based RPG where a hero explores a dynamically generated maze, solves puzzles, and fights enemies using skills.
 *
 * Licensed under the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> // For setlocale
#ifdef _WIN32
#include <windows.h> // For SetConsoleOutputCP
#endif

#include "../include/utils.h"
#include "../include/game.h"

void display_menu(GameState *game, Translation *trans, int trans_count) {
    printf("\n%s\n", get_text(trans, trans_count, "MSG_WELCOME"));
    printf("1. %s\n", get_text(trans, trans_count, "MENU_NEW_GAME"));
    printf("2. %s\n", get_text(trans, trans_count, "MENU_LOAD"));
    printf("3. %s\n", get_text(trans, trans_count, "MENU_SETTINGS"));
    printf("4. %s\n", get_text(trans, trans_count, "MENU_CREDITS"));
    printf("5. %s\n", get_text(trans, trans_count, "MENU_QUIT"));
    printf("%s: ", get_text(trans, trans_count, "MENU_CHOICE"));
}

int main() {
    // Configure console locale and encoding
    setlocale(LC_ALL, "C.UTF-8"); // Use system regional settings
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // Configure the console for UTF-8
        SetConsoleCP(CP_UTF8);      // Configure input for UTF-8
    #endif

    display_banner();
    GameState *game = malloc(sizeof(GameState));
    game->maze = NULL;
    game->skills = malloc(sizeof(SkillList));
    game->skills->head = NULL;
    game->player_hp = 100;
    game->lang = str_duplicate("en");
    game->difficulty = 1;

    int trans_count;
    Translation *trans = load_language(game->lang, &trans_count);

    int choice;
    while (1) {
        display_menu(game, trans, trans_count);
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1: // New Game
                game->maze = create_maze(9 + game->difficulty * 2, 9 + game->difficulty * 2);
                generate_maze(game->maze, 1, 1);
                add_skill(game->skills, create_skill("attack", attack, (SkillData){.damage = 10}));
                add_skill(game->skills, create_skill("heal", heal, (SkillData){.heal_amount = 20}));
                game_loop(game);
                break;
            case 2: // Load
                free_maze(game->maze);
                free_skills(game->skills);
                free(game);
                game = load_game("data/saves/game_slot1.save");
                if (game) {
                    free_translations(trans, trans_count);
                    trans = load_language(game->lang, &trans_count);
                    game_loop(game);
                }
                break;
            case 3: // Settings
                printf("%s (en/fr): ", get_text(trans, trans_count, "SETTINGS_LANG"));
                char lang[3];
                scanf("%2s", lang);
                clear_input_buffer();
                change_language(game, lang);
                free_translations(trans, trans_count);
                trans = load_language(game->lang, &trans_count);
                printf("%s (1-3): ", get_text(trans, trans_count, "SETTINGS_DIFFICULTY"));
                int diff;
                scanf("%d", &diff);
                clear_input_buffer();
                set_difficulty(game, diff);
                break;
            case 4: // Credits
                display_credit();
                break;
            case 5: // Quit
                save_game(game, "data/saves/game_slot1.save");
                free_maze(game->maze);
                free_skills(game->skills);
                free_translations(trans, trans_count);
                free(game->lang);
                free(game);
                return 0;
        }
    }
}