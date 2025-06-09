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

// Function to display the menu
// This function displays the main menu of the game, allowing the player to choose between starting a new game, loading a saved game, changing settings, viewing credits, or quitting.
void display_menu(GameState *game, Translation *trans, int trans_count) {
    printf("\n === %s === \n\n", get_text(trans, trans_count, "MSG_WELCOME")); // Display welcome message
    printf("1. %s\n", get_text(trans, trans_count, "MENU_NEW_GAME")); // Display option for new game
    printf("2. %s\n", get_text(trans, trans_count, "MENU_LOAD")); // Display option for loading a game
    printf("3. %s\n", get_text(trans, trans_count, "MENU_SETTINGS")); // Display option for settings
    printf("4. %s\n", get_text(trans, trans_count, "MENU_CREDITS")); // Display option for credits
    printf("5. %s\n", get_text(trans, trans_count, "MENU_QUIT")); // Display option for quitting the game
    printf("\n%s: ", get_text(trans, trans_count, "MENU_CHOICE")); // Prompt for user input
}

int main() {
    // Configure console locale and encoding
    setlocale(LC_ALL, "C.UTF-8"); // Use system regional settings
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8); // Configure the console for UTF-8
        SetConsoleCP(CP_UTF8);      // Configure input for UTF-8
    #endif

    // Display the game banner
    display_banner();
    // Allocate memory for the game state and initialize its fields
    GameState *game = malloc(sizeof(GameState));
    game->maze = NULL;
    game->skills = malloc(sizeof(SkillList));
    game->skills->head = NULL;
    game->player_hp = 100;
    game->lang = str_duplicate("en");
    game->difficulty = 1;

    // Load the translations for the default language and store the count of translations
    int trans_count;
    Translation *trans = load_language(game->lang, &trans_count);

    // Display the main menu and handle user input
    int choice;
    while (1) {
        display_menu(game, trans, trans_count);
        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice) {
            case 1: // New Game
                game->maze = create_maze(9 + game->difficulty * 2, 9 + game->difficulty * 2);
                printf("\n");
                generate_maze(game->maze, 1, 1);
                printf("\n");
                add_skill(game->skills, create_skill("attack", attack, (SkillData){.damage = 50}));
                add_skill(game->skills, create_skill("heal", heal, (SkillData){.heal_amount = 20}));
                game_loop(game);
                break;
            case 2: // Load - Not working correctly in this version
                free_maze(game->maze);
                free_skills(game->skills);
                free(game);
                game = load_game("../data/saves/game_slot1.save");
                if (game) {
                    free_translations(trans, trans_count);
                    trans = load_language(game->lang, &trans_count);
                    game_loop(game);
                }
                break;
            case 3: // Settings
                // Change language and difficulty settings
                printf("\n%s (en / fr): ", get_text(trans, trans_count, "SETTINGS_LANG"));
                char lang[3];
                scanf("%2s", lang);
                clear_input_buffer();
                change_language(game, lang);
                free_translations(trans, trans_count);
                trans = load_language(game->lang, &trans_count);
                printf("\n%s (1-3): ", get_text(trans, trans_count, "SETTINGS_DIFFICULTY"));
                int diff;
                scanf("%d", &diff);
                clear_input_buffer();
                set_difficulty(game, diff);
                break;
            case 4: // Credits
                display_credit();
                break;
            case 5: // Quit
                //save_game(game, "../data/saves/game_slot1.save"); // Not working in this version
                free_maze(game->maze);
                free_skills(game->skills);
                free_translations(trans, trans_count);
                free(game->lang);
                free(game);
                return 0;
        }
    }
}