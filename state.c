#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snake_utils.h"
#include "state.h"

/* Helper function definitions */
static char get_board_at(game_state_t *state, int x, int y);
static void set_board_at(game_state_t *state, int x, int y, char ch);
static bool is_tail(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static int incr_x(char c);
static int incr_y(char c);
static void find_head(game_state_t *state, int snum);
static char next_square(game_state_t *state, int snum);
static void update_tail(game_state_t *state, int snum);
static void update_head(game_state_t *state, int snum);

/* Helper function to get a character from the board (already implemented for you). */
static char get_board_at(game_state_t *state, int x, int y)
{
  return state->board[y][x];
}

/* Helper function to set a character on the board (already implemented for you). */
static void set_board_at(game_state_t *state, int x, int y, char ch)
{
  state->board[y][x] = ch;
}

/* Task 1 */
game_state_t *create_default_state()
{
  game_state_t *state = (game_state_t *)malloc(sizeof(game_state_t));
  state->x_size = 14;
  state->y_size = 10;
  state->num_snakes = 1;
  state->snakes = (snake_t *)malloc(sizeof(snake_t));
  state->snakes->head_x = 5;
  state->snakes->head_y = 4;
  state->snakes->tail_x = 4;
  state->snakes->tail_y = 4;
  state->snakes->live = true;
  state->board = (char **)malloc(state->y_size * sizeof(char *));
  for (int i = 0; i < state->y_size; i += 1)
    state->board[i] = (char *)malloc((state->x_size + 1) * sizeof(char));

  char *wall_1 = "##############\n";
  char *wall_2 = "#            #\n";
  strcpy(state->board[0], wall_1);
  strcpy(state->board[state->y_size - 1], wall_1);
  for (int i = 1; i < state->y_size - 1; i += 1)
    strcpy(state->board[i], wall_2);

  state->board[2][9] = '*';
  state->board[4][4] = 'd';
  state->board[4][5] = '>';

  return state;
}

/* Task 2 */
void free_state(game_state_t *state)
{
  for (int i = 0; i < state->y_size; i += 1)
    free(state->board[i]);
  free(state->board);
  free(state->snakes);
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp)
{
  for (int i = 0; i < state->y_size; i += 1)
    fprintf(fp, "%s", state->board[i]);
  return;
}

/* Saves the current state into filename (already implemented for you). */
void save_board(game_state_t *state, char *filename)
{
  FILE *f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */
static bool is_tail(char c)
{
  // TODO: Implement this function.
  return true;
}

static bool is_snake(char c)
{
  // TODO: Implement this function.
  return true;
}

static char body_to_tail(char c)
{
  // TODO: Implement this function.
  return '?';
}

static int incr_x(char c)
{
  // TODO: Implement this function.
  return 0;
}

static int incr_y(char c)
{
  // TODO: Implement this function.
  return 0;
}

/* Task 4.2 */
static char next_square(game_state_t *state, int snum)
{
  // TODO: Implement this function.
  return '?';
}

/* Task 4.3 */
static void update_head(game_state_t *state, int snum)
{
  // TODO: Implement this function.
  return;
}

/* Task 4.4 */
static void update_tail(game_state_t *state, int snum)
{
  // TODO: Implement this function.
  return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state))
{
  // TODO: Implement this function.
  return;
}

/* Task 5 */
game_state_t *load_board(char *filename)
{
  // TODO: Implement this function.
  return NULL;
}

/* Task 6.1 */
static void find_head(game_state_t *state, int snum)
{
  // TODO: Implement this function.
  return;
}

/* Task 6.2 */
game_state_t *initialize_snakes(game_state_t *state)
{
  // TODO: Implement this function.
  return NULL;
}
