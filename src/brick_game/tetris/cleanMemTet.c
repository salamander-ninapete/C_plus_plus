#include "tetris.h"

void cleanupGame(GameInfo_t *game) {
  if (game->next)
    for (int i = 0; i < BLOCK_SIZE; i++) {
      free(game->next[i]);
    }
  if (game->field)
    for (int i = 0; i < HEIGHT + 3; i++) {
      free(game->field[i]);
    }
  free(game->next);
  free(game->field);
  game->next = NULL;
  game->field = NULL;
}
