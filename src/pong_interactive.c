#include <ncurses.h>
 
#define WIDTH 80
#define HEIGHT 25
#define WIN_SCORE 21
#define DELAY_MS 60
 
int main(void) {
initscr();
noecho();
cbreak();
timeout(DELAY_MS);
curs_set(0);
 
int left_paddle = HEIGHT / 2;
int right_paddle = HEIGHT / 2;
int ball_x = WIDTH / 2;
int ball_y = HEIGHT / 2;
int ball_dir_x = 1;
int ball_dir_y = 1;
int score_left = 0;
int score_right = 0;
int game_running = 1;
 
while (game_running) {
clear();
 
printw(" PLAYER 1: %d | PLAYER 2: %d\n",
score_left, score_right);
 
for (int y = 0; y < HEIGHT; y++) {
for (int x = 0; x < WIDTH; x++) {
if (y == 0 || y == HEIGHT - 1) {
printw("-");
} else if (x == 0) {
if (y >= left_paddle - 1 && y <= left_paddle + 1) {
printw("|");
} else {
printw(" ");
}
} else if (x == WIDTH - 1) {
if (y >= right_paddle - 1 && y <= right_paddle + 1) {
printw("|");
} else {
printw(" ");
}
} else if (x == ball_x && y == ball_y) {
printw("o");
} else if (x == WIDTH / 2) {
printw(":");
} else {
printw(" ");
}
}
printw("\n");
}
 
refresh();
 
if (score_left >= WIN_SCORE) {
timeout(-1);
clear();
printw("Congratulations! Player 1 Wins!\nPress any key to exit...");
refresh();
getch();
game_running = 0;
} else if (score_right >= WIN_SCORE) {
timeout(-1);
clear();
printw("Congratulations! Player 2 Wins!\nPress any key to exit...");
refresh();
getch();
game_running = 0;
}
 
if (game_running) {
int command = getch();
 
if ((command == 'A' || command == 'a') && left_paddle > 2) {
left_paddle--;
} else if ((command == 'Z' || command == 'z') &&
left_paddle < HEIGHT - 3) {
left_paddle++;
} else if ((command == 'K' || command == 'k') && right_paddle > 2) {
right_paddle--;
} else if ((command == 'M' || command == 'm') &&
right_paddle < HEIGHT - 3) {
right_paddle++;
} else if (command == 'q' || command == 'Q') {
game_running = 0;
}
 
ball_x += ball_dir_x;
ball_y += ball_dir_y;
 
if (ball_y <= 1 || ball_y >= HEIGHT - 2) {
ball_dir_y = -ball_dir_y;
}
 
if (ball_x == 1) {
if (ball_y >= left_paddle - 1 && ball_y <= left_paddle + 1) {
ball_dir_x = -ball_dir_x;
} else {
score_right++;
ball_x = WIDTH / 2;
ball_y = HEIGHT / 2;
ball_dir_x = 1;
}
}
 
if (ball_x == WIDTH - 2) {
if (ball_y >= right_paddle - 1 && ball_y <= right_paddle + 1) {
ball_dir_x = -ball_dir_x;
} else {
score_left++;
ball_x = WIDTH / 2;
ball_y = HEIGHT / 2;
ball_dir_x = -1;
}
}
}
}
 
endwin();
return 0;
}