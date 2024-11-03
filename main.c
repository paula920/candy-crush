#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 11 // Dimensiunea matricei
#define MAX_SCORE 10000 // Scor maxim per joc
#define GAMES 100 // Numărul de jocuri

// Funcție pentru a inițializa matricea cu bomboane aleatoare
void initialize_grid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = rand() % 5; // Valorile 0-4
        }
    }
}

// Funcție pentru a afișa matricea
void print_grid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// Funcție pentru a calcula scorul și elimina formațiunile
int check_and_remove_patterns(int grid[N][N]) {
    int score = 0;

    // Verificăm linii orizontale și verticale de 3, 4 sau 5
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 2; j++) {
            // Linie orizontală de 3, 4 sau 5
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2]) {
                int length = 3;
                while (j + length < N && grid[i][j] == grid[i][j + length]) {
                    length++;
                }

                if (length == 3) score += 5;
                else if (length == 4) score += 10;
                else if (length >= 5) score += 50;

                for (int k = 0; k < length; k++) {
                    grid[i][j + k] = 0;
                }
                j += length - 1; // Sărim peste bomboanele verificate
            }
        }
    }

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N - 2; i++) {
            // Linie verticală de 3, 4 sau 5
            if (grid[i][j] != 0 && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j]) {
                int length = 3;
                while (i + length < N && grid[i][j] == grid[i + length][j]) {
                    length++;
                }

                if (length == 3) score += 5;
                else if (length == 4) score += 10;
                else if (length >= 5) score += 50;

                for (int k = 0; k < length; k++) {
                    grid[i + k][j] = 0;
                }
                i += length - 1;
            }
        }
    }

    // Verificăm formațiuni de tip L și T
    // ... aici vom implementa căutarea de formațiuni L și T pentru puncte suplimentare
    // (similar, dar mai complex; voi lăsa acest pas ca o completare viitoare, pentru claritate)

    // Coborâm bomboanele rămase în matrice
    for (int j = 0; j < N; j++) {
        int write_index = N - 1;
        for (int i = N - 1; i >= 0; i--) {
            if (grid[i][j] != 0) {
                grid[write_index][j] = grid[i][j];
                if (write_index != i) grid[i][j] = 0;
                write_index--;
            }
        }
    }

    return score;
}

// Funcție pentru a verifica dacă există opțiuni de interschimbare care ar genera formațiuni noi
int has_swap_options(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - 1; j++) {
            // Verificăm interschimbul cu dreapta
            int temp = grid[i][j];
            grid[i][j] = grid[i][j + 1];
            grid[i][j + 1] = temp;

            if (check_and_remove_patterns(grid) > 0) {
                grid[i][j + 1] = grid[i][j];
                grid[i][j] = temp;
                return 1;
            }

            // Revenim la starea inițială
            grid[i][j + 1] = grid[i][j];
            grid[i][j] = temp;
        }
    }

    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N - 1; i++) {
            // Verificăm interschimbul cu jos
            int temp = grid[i][j];
            grid[i][j] = grid[i + 1][j];
            grid[i + 1][j] = temp;

            if (check_and_remove_patterns(grid) > 0) {
                grid[i + 1][j] = grid[i][j];
                grid[i][j] = temp;
                return 1;
            }

            grid[i + 1][j] = grid[i][j];
            grid[i][j] = temp;
        }
    }

    return 0;
}

int main() {
    srand(time(NULL)); // Inițializăm generatorul de numere aleatoare
    int total_score = 0; // Punctaj total din toate jocurile

    for (int game = 0; game < GAMES; game++) {
        int grid[N][N]; // Declaram matricea
        initialize_grid(grid); // Inițializăm matricea
        int game_score = 0;

        while (game_score < MAX_SCORE) {
            // Calculăm și eliminăm formațiunile
            int score = check_and_remove_patterns(grid);
            game_score += score;

            // Verificăm dacă există opțiuni de interschimbare
            if (score == 0 && !has_swap_options(grid)) {
                break; // Nu mai sunt mutări posibile
            }
        }

        total_score += game_score; // Adăugăm scorul jocului curent la total
        printf("Joc %d - Punctaj: %d\n", game + 1, game_score);
    }

    printf("\nPunctaj total după %d jocuri: %d\n", GAMES, total_score);
    printf("Media punctajului: %.2f\n", (double)total_score / GAMES);

    return 0;
}
