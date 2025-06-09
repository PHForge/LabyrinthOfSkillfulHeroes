#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/utils.h"

// Clears input buffer
// This function is used to clear the input buffer after reading user input
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Displays retro ASCII banner
// ASCII Maze door inspired by https://www.asciiart.eu/art-and-design/mazes
void display_banner(void) {
    printf("\n");
    printf("\n");
    printf(" 88888888888888888888888888888888888888888888888888888888888888888888888\n");
    printf(" 88.._|      | `-.  | `.  -_-_ _-_  _-  _- -_ -  .'|   |.'|     |  _..88\n");
    printf(" 88   `-.._  |    |`!  |`.  -_ -__ -_ _- _-_-  .'  |.;'   |   _.!-'|  88\n");
    printf(" 88      | `-!._  |  `;!  ;. _______________ ,'| .-' |   _!.i'     |  88\n");
    printf(" 88..__  |     |`-|._ | `.| |_______________||.''|  _|.:'   |     _|..88\n");
    printf(" 88   |'''..__ |    |'':.|  |_|MMMMMMMMMMM|_|'| _!-|   |   _|..-|'    88\n");
    printf(" 88   |      |``--..|_ | `;!|@|MMMMMMMMMMM|@|.'|   |_..!-'|     |     88\n");
    printf(" 88   |      |    |   |`-,!_|_|MMMMP'YMMMM|_||.!-;'  |    |     |     88\n");
    printf(" 88___|______|____!.,.!,.!,!|@|MMMM * MMMM|@|,!,.!.,.!..__|_____|_____88\n");
    printf(" 88      |     |    |  |  | |_|MMMMb,dMMMM|_|| |   |   |    |      |  88\n");
    printf(" 88      |     |    |..!-;' |@|MMMMMMMMMMM|@| |`-..|   |    |      |  88\n");
    printf(" 88      |    _!.-j'  | _!,'|_|MMMMMMMMMMM|_||!._|  `--!.._ |      |  88\n");
    printf(" 88     _!.-'|    | _.'|  !;|@|MMMMMMMMMMM|@|`.| `-._|    |``-.._  |  88\n");
    printf(" 88..-i'     |  _.''|  !-| !|_|MMMMMMMMMMM|_|.|`-. | ``._ |     |``'..88\n");
    printf(" 88   |      |.|    |.|  !| |@|MMMMMMMMMMM|@||`. |`!   | `'.    |     88\n");
    printf(" 88   |  _.-'  |  .'  |.' |/|_|MMMMMMMMMMM|_|! |`!  `,.|    |-._|     88\n");
    printf(" 88  _!''|     !.'|  .'| .'|[@]MMMMMMMMMMM[@] \\|  `. | `._  |   `-._  88\n");
    printf(" 88-'    |   .'   |.|  |/| /                 \\|`.  |`!    |.|      |`-88\n");
    printf(" 88      |_.'|   .' | .' |/                   \\  \\ |  `.  | `._-   |  88\n");
    printf(" 88     .'   | .'   |/|  /                     \\ |`!   |`.|    `.  |  88\n");
    printf(" 88  _.'     !'|   .' | /                       \\|  `  |  `.    |`.|  88\n");
    printf(" 88888888888888888888888888888888888888888888888888888888888888888888888\n");
    printf(" 888888888888888888888 Labyrinth of Skillful Heroes 88888888888888888888\n");
    printf(" 88888888888888888888888888888888888888888888888888888888888888888888888\n");
    printf("\n                                                             by PHForge\n");
}

// Displays credits
// This function displays a heartfelt message to my family, thanking them for their support and love.
void display_credit(void) {
    printf("\nTo my beloved wife and son,\n");
    printf("Thank you for your endless love, patience, and support.\n");
    printf("This game is a small tribute to the joy you bring into my life every day.\n");
    printf("Press Enter to continue...\n");
    clear_input_buffer();
}

// Shuffles a 2D array of integers
// This function randomly shuffles the elements of a 2D array, which can be useful for randomizing game elements like skill order or item placement.
void shuffle(int arr[][2], int size) {
    srand(time(NULL));
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp[2] = {arr[i][0], arr[i][1]};
        arr[i][0] = arr[j][0];
        arr[i][1] = arr[j][1];
        arr[j][0] = temp[0];
        arr[j][1] = temp[1];
    }
}

// Duplicates a string
// This function allocates memory for a new string and copies the contents of the original string into it. It is used to create independent copies of strings, such as language codes or skill names.
char *str_duplicate(const char *str) {
    char *dup = malloc(strlen(str) + 1);
    strcpy(dup, str);
    return dup;
}

// Saves the game state to a file
// This function writes the current game state, including the player's position, maze dimensions, maze data, skills, language, and difficulty level, to a specified file. It is used for saving progress so that players can continue later.
void save_game(GameState *game, char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;
    fprintf(file, "player_pos: %d,%d\n", game->maze->player_row, game->maze->player_col);
    fprintf(file, "maze_rows: %d\n", game->maze->rows);
    fprintf(file, "maze_cols: %d\n", game->maze->cols);
    fprintf(file, "maze_data: ");
    for (int i = 0; i < game->maze->rows; i++) {
        for (int j = 0; j < game->maze->cols; j++) {
            fprintf(file, "%c", game->maze->grid[i][j]);
        }
    }
    fprintf(file, "\nskills: ");
    Skill *current = game->skills->head;
    while (current) {
        fprintf(file, "%s,%d", current->name, current->data.damage);
        if (current->next) fprintf(file, ";");
        current = current->next;
    }
    fprintf(file, "\nlang: %s\n", game->lang);
    fprintf(file, "difficulty: %d\n", game->difficulty);
    fclose(file);
}

// Loads the game state from a file
// This function reads the game state from a specified file, reconstructing the maze, player position, skills, language, and difficulty level. It returns a pointer to the loaded GameState structure or NULL if loading fails.
GameState *load_game(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;
    GameState *game = malloc(sizeof(GameState));
    game->skills = malloc(sizeof(SkillList));
    game->skills->head = NULL;
    
    int row, col, rows, cols;
    char maze_data[1024], lang[3];
    fscanf(file, "player_pos: %d,%d\n", &row, &col);
    fscanf(file, "maze_rows: %d\n", &rows);
    fscanf(file, "maze_cols: %d\n", &cols);
    fscanf(file, "maze_data: %s\n", maze_data);
    char skills[1024];
    fscanf(file, "skills: %[^\n]\n", skills);
    fscanf(file, "lang: %s\n", lang);
    fscanf(file, "difficulty: %d\n", &game->difficulty);
    fclose(file);

    game->maze = create_maze(rows, cols);
    game->maze->player_row = row;
    game->maze->player_col = col;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            game->maze->grid[i][j] = maze_data[i * cols + j];
        }
    }
    game->lang = str_duplicate(lang);
    game->player_hp = 100;

    char *skill_token = strtok(skills, ";");
    while (skill_token) {
        char *name = strtok(skill_token, ",");
        int value = atoi(strtok(NULL, ","));
        SkillData data = {.damage = value};
        void (*action)(GameState *) = (strcmp(name, "attack") == 0) ? attack : heal;
        add_skill(game->skills, create_skill(name, action, data));
        skill_token = strtok(NULL, ";");
    }
    return game;
}

// Changes the game's language
// This function updates the game's language code, freeing the previous language string and allocating a new one. It is used to switch between different languages for translations.
void change_language(GameState *game, char *lang_code) {
    free(game->lang);
    game->lang = str_duplicate(lang_code);
}

// Sets the game's difficulty level
// This function updates the game's difficulty level, ensuring it is within a valid range (1 to 3). It is used to adjust the game's challenge based on player preference.
void set_difficulty(GameState *game, int difficulty) {
    if (difficulty >= 1 && difficulty <= 3) {
        game->difficulty = difficulty;
    }
}

// Loads translations from a language file
// This function reads a language file and loads translations into a Translation structure. It counts the number of translations and returns a pointer to the loaded translations, along with the count. If the file cannot be opened or memory allocation fails, it returns NULL and sets the count to 0.
Translation *load_language(char *lang_code, int *count) {
    char filename[50];
    sprintf(filename, "../data/translations/%s.lang", lang_code);
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", filename);
        *count = 0;
        return NULL;
    }
    Translation *trans = NULL;
    *count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file)) (*count)++;
    rewind(file);
    trans = malloc(*count * sizeof(Translation));
    if (!trans) {
        fprintf(stderr, "Erreur : échec de l'allocation mémoire pour les traductions\n");
        fclose(file);
        *count = 0;
        return NULL;
    }
    for (int i = 0; i < *count; i++) {
        if (fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0;
            trans[i].key = str_duplicate(strtok(line, "="));
            char *value = strtok(NULL, "=");
            trans[i].value = value ? str_duplicate(value) : str_duplicate("");
        } else {
            trans[i].key = str_duplicate("");
            trans[i].value = str_duplicate("");
        }
    }
    fclose(file);
    return trans;
}

// Retrieves the translated text for a given key
// This function searches through the loaded translations for a specific key and returns the corresponding translated text. If the key is not found, it prints an error message and returns a default "Text not found" message.
char *get_text(Translation *trans, int count, char *key) {
    for (int i = 0; i < count; i++) {
        if (strcmp(trans[i].key, key) == 0) return trans[i].value;
    }
    fprintf(stderr, "Erreur : clé de traduction '%s' non trouvée\n", key);
    return "Text not found";
}

// Frees the memory allocated for translations
// This function iterates through the array of Translation structures, freeing the memory allocated for each key and value, and then frees the array itself. It is used to clean up resources when translations are no longer needed.
void free_translations(Translation *trans, int count) {
    for (int i = 0; i < count; i++) {
        free(trans[i].key);
        free(trans[i].value);
    }
    free(trans);
}