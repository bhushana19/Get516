#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_DIMENSION 4
#define MAX_UNDO_STEPS 10

typedef struct {
    int cells[GRID_DIMENSION][GRID_DIMENSION];
    int score;
} GameState;

void initialize_game(GameState *game) {
    for (int i = 0; i < GRID_DIMENSION; i++) {
        for (int j = 0; j < GRID_DIMENSION; j++) {
            game->cells[i][j] = 0;
        }
    }
    game->score = 0;
    // Initialize two random cells with 2
    int x1, y1, x2, y2;
    srand(time(NULL));
    x1 = rand() % GRID_DIMENSION;
    y1 = rand() % GRID_DIMENSION;
    x2 = rand() % GRID_DIMENSION;
    y2 = rand() % GRID_DIMENSION;
    while (x2 == x1 && y2 == y1) {
        x2 = rand() % GRID_DIMENSION;
        y2 = rand() % GRID_DIMENSION;
    }
    game->cells[x1][y1] = 2;
    game->cells[x2][y2] = 2;
}

void print_game(const GameState *game) {
    printf("Score: %d\n", game->score);
    for (int i = 0; i < GRID_DIMENSION; i++) {
        for (int j = 0; j < GRID_DIMENSION; j++) {
            printf("%5d ", game->cells[i][j]);
        }
        printf("\n");
    }
}

void move_up(GameState *game) {
    for (int j = 0; j < GRID_DIMENSION; j++) {
        int temp[GRID_DIMENSION] = {0};
        int k = 0;
        for (int i = 0; i < GRID_DIMENSION; i++) {
            if (game->cells[i][j] != 0) {
                temp[k++] = game->cells[i][j];
            }
        }
        k = 0;
        for (int i = 0; i < GRID_DIMENSION - 1; i++) {
            if (temp[i] == temp[i + 1]) {
                temp[i] *= 2;
                game->score += temp[i];
                temp[i + 1] = 0;
            }
        }
        k = 0;
        for (int i = 0; i < GRID_DIMENSION; i++) {
            if (temp[i] != 0) {
                game->cells[k++][j] = temp[i];
            }
        }
        for (int i = k; i < GRID_DIMENSION; i++) {
            game->cells[i][j] = 0;
        }
    }
}

void move_down(GameState *game) {
    for (int j = 0; j < GRID_DIMENSION; j++) {
        int temp[GRID_DIMENSION] = {0};
        int k = GRID_DIMENSION - 1;
        for (int i = GRID_DIMENSION - 1; i >= 0; i--) {
            if (game->cells[i][j] != 0) {
                temp[k--] = game->cells[i][j];
            }
        }
        k = GRID_DIMENSION - 1;
        for (int i = GRID_DIMENSION - 1; i > 0; i--) {
            if (temp[i] == temp[i - 1]) {
                temp[i] *= 2;
                game->score += temp[i];
                temp[i - 1] = 0;
            }
        }
        k = GRID_DIMENSION - 1;
        for (int i = GRID_DIMENSION - 1; i >= 0; i--) {
            if (temp[i] != 0) {
                game->cells[k--][j] = temp[i];
            }
        }
        for (int i = k; i >= 0; i--) {
            game->cells[i][j] = 0;
        }
    }
}

void move_left(GameState *game) {
    for (int i = 0; i < GRID_DIMENSION; i++) {
        int temp[GRID_DIMENSION] = {0};
        int k = 0;
        for (int j = 0; j < GRID_DIMENSION; j++) {
            if (game->cells[i][j] != 0) {
                temp[k++] = game->cells[i][j];
            }
        }
        k = 0;
        for (int j = 0; j < GRID_DIMENSION - 1; j++) {
            if (temp[j] == temp[j + 1]) {
                temp[j] *= 2;
                game->score += temp[j];
                temp[j + 1] = 0;
            }
        }
        k = 0;
        for (int j = 0; j < GRID_DIMENSION; j++) {
            if (temp[j]!= 0) {
                game->cells[i][k++] = temp[j];
            }
        }
        for (int j = k; j < GRID_DIMENSION; j++) {
            game->cells[i][j] = 0;
        }
    }
}

void move_right(GameState *game) {
    for (int i = 0; i < GRID_DIMENSION; i++) {
        int temp[GRID_DIMENSION] = {0};
        int k = GRID_DIMENSION - 1;
        for (int j = GRID_DIMENSION - 1; j >= 0; j--) {
            if (game->cells[i][j]!= 0) {
                temp[k--] = game->cells[i][j];
            }
        }
        k = GRID_DIMENSION - 1;
        for (int j = GRID_DIMENSION - 1; j > 0; j--) {
            if (temp[j] == temp[j - 1]) {
                temp[j] *= 2;
                game->score += temp[j];
                temp[j - 1] = 0;
            }
        }
        k = GRID_DIMENSION - 1;
        for (int j = GRID_DIMENSION - 1; j >= 0; j--) {
            if (temp[j]!= 0) {
                game->cells[i][k--] = temp[j];
            }
        }
        for (int j = k; j >= 0; j--) {
            game->cells[i][j] = 0;
        }
    }
}

int is_full(const GameState *game) {
    for (int i = 0; i < GRID_DIMENSION; i++) {
        for (int j = 0; j < GRID_DIMENSION; j++) {
            if (game->cells[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int can_move(const GameState *game) {
    for (int i = 0; i < GRID_DIMENSION; i++) {
        for (int j = 0; j < GRID_DIMENSION - 1; j++) {
            if (game->cells[i][j] == game->cells[i][j + 1]) {
                return 1;
            }
        }
    }
    for (int i = 0; i < GRID_DIMENSION - 1; i++) {
        for (int j = 0; j < GRID_DIMENSION; j++) {
            if (game->cells[i][j] == game->cells[i + 1][j]) {
                return 1;
            }
        }
    }
    return 0;
}

void add_random_cell(GameState *game) {
    int x, y;
    do {
        x = rand() % GRID_DIMENSION;
        y = rand() % GRID_DIMENSION;
    } while (game->cells[x][y]!= 0);
    game->cells[x][y] = 2;
}

int check_game_over(const GameState *game) {
    if (is_full(game) &&!can_move(game)) {
        return 1;
    }
    return 0;
}

void undo(GameState *game, GameState undo_moves[MAX_UNDO_STEPS], int *undo_index){
    if (*undo_index > 0) {
        *undo_index -= 1;
        *game = undo_moves[*undo_index];
        printf("Undo successful. %d undo moves left.\n", *undo_index);
    } else {
        printf("No more undo moves left.\n");
    }
}

int main() {
    GameState game;
    GameState undo_moves[MAX_UNDO_STEPS];
    int undo_index = 0;
    initialize_game(&game);
    print_game(&game);
    while (1) {
        char direction;
        printf("Enter direction (w: up, s: down, a: left, d: right, u: undo, q: quit): ");
        scanf(" %c", &direction);
        if (direction == 'q') {
            break;
        }
        GameState temp_game = game;
        int temp_score = game.score;
        if (direction == 'w') {
            move_up(&game);
        } else if (direction == 's') {
            move_down(&game);
        } else if (direction == 'a') {
            move_left(&game);
        } else if (direction == 'd') {
            move_right(&game);
        } else if (direction == 'u') {
            undo(&game, undo_moves, &undo_index);
            continue;
        }
        if (game.score!= temp_score) {
            undo_moves[undo_index] = temp_game;
            undo_index++;
        }
        add_random_cell(&game);
        print_game(&game);
        if (check_game_over(&game)) {
            printf("Game Over! 😔\n");
            break;
        }
        if (game.score >= 516) {
            printf("Congratulations! You won! 🏆\n");
            break;
        }
    }
    return 0;
}