#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3
#define WIN_SCORE 21

int main() {
    // Начальные координаты ракеток (центр по вертикали)
    int left_paddle = HEIGHT / 2;
    int right_paddle = HEIGHT / 2;

    // Начальные координаты мяча (центр поля)
    int ball_x = WIDTH / 2;
    int ball_y = HEIGHT / 2;

    // Направление движения мяча (1 — вправо/вниз, -1 — влево/вверх)
    int ball_dir_x = 1;
    int ball_dir_y = 1;

    // Счёт игроков
    int score_left = 0;
    int score_right = 0;

    // Флаг работы игры
    int game_running = 1;

    while (game_running) {
        // 1. ОТРИСОВКА ПОЛЯ
        // Очистка экрана с помощью перевода строки (альтернатива запрещенному system("clear"))
        for (int i = 0; i < 30; i++) {
            printf("\n");
        }

        // Вывод текущего счёта
        printf("                            PLAYER 1: %d  |  PLAYER 2: %d\n", score_left, score_right);

        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                // Верхняя и нижняя границы поля
                if (y == 0 || y == HEIGHT - 1) {
                    printf("-");
                }
                // Левая граница и левая ракетка
                else if (x == 0) {
                    if (y >= left_paddle - 1 && y <= left_paddle + 1) {
                        printf("|");
                    } else {
                        printf(" ");
                    }
                }
                // Правая граница и правая ракетка
                else if (x == WIDTH - 1) {
                    if (y >= right_paddle - 1 && y <= right_paddle + 1) {
                        printf("|");
                    } else {
                        printf(" ");
                    }
                }
                // Мяч
                else if (x == ball_x && y == ball_y) {
                    printf("o");
                }
                // Центральная линия сетки
                else if (x == WIDTH / 2) {
                    printf(":");
                }
                // Пустое пространство
                else {
                    printf(" ");
                }
            }
            printf("\n");
        }

        // Проверка условий победы
        if (score_left >= WIN_SCORE) {
            printf("Congratulations! Player 1 Wins!\n");
            game_running = 0;
            break;
        } else if (score_right >= WIN_SCORE) {
            printf("Congratulations! Player 2 Wins!\n");
            game_running = 0;
            break;
        }

        // 2. ОБРАБОТКА ВВОДА
        printf("Enter move (P1: A/Z, P2: K/M, Space to skip) and press Enter: ");
        
        char command;
        // Считываем символ и пропускаем пробельные символы (включая остаточные \n)
        if (scanf(" %c", &command) != 1) {
            continue;
        }

        // Логика перемещения ракеток с проверкой границ поля
        if ((command == 'A' || command == 'a') && left_paddle > 2) {
            left_paddle--;
        } else if ((command == 'Z' || command == 'z') && left_paddle < HEIGHT - 3) {
            left_paddle++;
        } else if ((command == 'K' || command == 'k') && right_paddle > 2) {
            right_paddle--;
        } else if ((command == 'M' || command == 'm') && right_paddle < HEIGHT - 3) {
            right_paddle++;
        } else if (command == ' ') {
            // Пропуск хода (просто идем дальше к физике мяча)
        } else {
            // Если введён некорректный символ, шаг не засчитывается, запрашиваем ввод заново
            continue;
        }

        // 3. ФИЗИКА МЯЧА
        // Движение мяча на один шаг
        ball_x += ball_dir_x;
        ball_y += ball_dir_y;

        // Отскок от верхней и нижней границ (учитываем, что y=0 и y=HEIGHT-1 это стены)
        if (ball_y <= 1 || ball_y >= HEIGHT - 2) {
            ball_dir_y = -ball_dir_y;
        }

        // Взаимодействие с левой ракеткой (x = 1 — координата перед стенкой)
        if (ball_x == 1) {
            if (ball_y >= left_paddle - 1 && ball_y <= left_paddle + 1) {
                ball_dir_x = -ball_dir_x;
            } else {
                // Игрок 1 пропустил мяч
                score_right++;
                ball_x = WIDTH / 2;
                ball_y = HEIGHT / 2;
                ball_dir_x = 1; // Мяч летит к забившему
            }
        }

        // Взаимодействие с правой ракеткой (x = WIDTH - 2)
        if (ball_x == WIDTH - 2) {
            if (ball_y >= right_paddle - 1 && ball_y <= right_paddle + 1) {
                ball_dir_x = -ball_dir_x;
            } else {
                // Игрок 2 пропустил мяч
                score_left++;
                ball_x = WIDTH / 2;
                ball_y = HEIGHT / 2;
                ball_dir_x = -1; // Мяч летит к забившему
            }
        }
    }

    return 0;
}
