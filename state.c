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
  {
    state->board[i] = (char *)malloc((state->x_size + 1) * sizeof(char));
  }
  char *wall_1 = "##############\n";
  char *wall_2 = "#            #\n";
  strcpy(state->board[0], wall_1);
  strcpy(state->board[state->y_size - 1], wall_1);
  for (int i = 1; i < state->y_size - 1; i += 1)
  {
    strcpy(state->board[i], wall_2);
  }

  state->board[2][9] = '*';
  state->board[4][4] = 'd';
  state->board[4][5] = '>';

  return state;
}

/* Task 2 */
void free_state(game_state_t *state)
{
  for (int i = 0; i < state->y_size; i += 1)
  {
    free(state->board[i]);
  }
  free(state->board);
  free(state->snakes);
  free(state);
  return;
}

/* Task 3 */
void print_board(game_state_t *state, FILE *fp)
{
  for (int i = 0; i < state->y_size; i += 1)
  {
    fprintf(fp, "%s", state->board[i]);
  }
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
  return c == 'w' || c == 'a' || c == 's' || c == 'd';
}

static bool is_snake(char c)
{
  return c == '^' || c == '<' || c == '>' || c == 'v' || c == 'x';
}

static char body_to_tail(char c)
{
  if (c == '^')
  {
    return 'w';
  }
  else if (c == '<')
  {
    return 'a';
  }
  else if (c == '>')
  {
    return 'd';
  }
  else if (c == 'v')
  {
    return 's';
  }
  return '?';
}

static int incr_x(char c)
{
  if (c == '>' || c == 'd')
  {
    return 1;
  }
  else if (c == '<' || c == 'a')
  {
    return -1;
  }
  return 0;
}

static int incr_y(char c)
{
  if (c == 'v' || c == 's')
  {
    return 1;
  }
  else if (c == '^' || c == 'w')
  {
    return -1;
  }
  return 0;
}

/* Task 4.2 */
static char next_square(game_state_t *state, int snum)
{
  char head = get_board_at(state, state->snakes->head_x, state->snakes->head_y);
  int pos_x_next = state->snakes->head_x + incr_x(head);
  int pos_y_next = state->snakes->head_y + incr_y(head);
  return get_board_at(state, pos_x_next, pos_y_next);
}

/* Task 4.3 */
static void update_head(game_state_t *state, int snum)
{
  char head = get_board_at(state, state->snakes->head_x, state->snakes->head_y);
  int pos_x_next = state->snakes->head_x + incr_x(head);
  int pos_y_next = state->snakes->head_y + incr_y(head);
  set_board_at(state, pos_x_next, pos_y_next, head);
  state->snakes->head_x = pos_x_next;
  state->snakes->head_y = pos_y_next;
  return;
}

/* Task 4.4 */
static void update_tail(game_state_t *state, int snum)
{
  char tail = get_board_at(state, state->snakes->tail_x, state->snakes->tail_y);
  int pos_x_next = state->snakes->tail_x + incr_x(tail);
  int pos_y_next = state->snakes->tail_y + incr_y(tail);
  char tail_before = get_board_at(state, pos_x_next, pos_y_next);
  set_board_at(state, state->snakes->tail_x, state->snakes->tail_y, ' ');
  set_board_at(state, pos_x_next, pos_y_next, body_to_tail(tail_before));
  state->snakes->tail_x = pos_x_next;
  state->snakes->tail_y = pos_y_next;
  return;
}

/* Task 4.5 */
void update_state(game_state_t *state, int (*add_food)(game_state_t *state))
{
  char next = next_square(state, 0);
  if (next == '#' || is_snake(next) || is_tail(next))
  {
    state->snakes->live = false;
    set_board_at(state, state->snakes->head_x, state->snakes->head_y, 'x');
  }
  else if (next == '*')
  {
    update_head(state, 0);
    add_food(state);
  }
  else
  {
    update_head(state, 0);
    update_tail(state, 0);
  }
  return;
}

/* Task 5 */
game_state_t *load_board(char *filename)
{
  game_state_t *state = (game_state_t *)malloc(sizeof(game_state_t));
  int length_x = 0;
  int length_y = 0;
  FILE *f = fopen(filename, "r");
  char c = getc(f);
  while (c != EOF)
  {
    if (c == '\n')
    {
      length_y += 1;
      length_x += 1;
    }
    else
    {
      length_x += 1;
    }
    c = getc(f);
  }
  length_x = length_x / length_y - 1;
  char **board = (char **)malloc(length_y * sizeof(char *));
  for (int i = 0; i < length_y; i += 1)
  {
    board[i] = (char *)malloc((length_x + 1) * sizeof(char));
  }
  rewind(f);
  fread(board, length_y, length_x + 1, f);
  state->board = board;
  state->x_size = length_x;
  state->y_size = length_y;
  printf("y: %i, x: %i\n", length_y, length_x);
  fclose(f);
  for (int i = 0; i < state->y_size; i += 1)
  {
    printf("%s", state->board[i]);
  }
  return state;
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
