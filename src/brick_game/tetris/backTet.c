#include "tetris.h"

void initializeGame(GameInfo_t *game) {
  game->field = createField();
  game->next = createNextFigure();
  game->score = START_SCORE;
  game->level = LVL_START;
  game->speed = START_SPEED;
  game->pause = false;
  srand(time(NULL));
  game->next_fig = generateFig();
}

int **createField() {
  int **field = (int **)malloc((HEIGHT + 3) * sizeof(int *));
  for (int i = 0; i < (HEIGHT + 3); i++) {
    field[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  return field;
}

int **createNextFigure() {
  int **figure = (int **)malloc(BLOCK_SIZE * sizeof(int *));
  for (int i = 0; i < BLOCK_SIZE; i++) {
    figure[i] = (int *)calloc(BLOCK_SIZE, sizeof(int));
  }
  return figure;
}

int generateFig() {
  int index = (rand() / 17) % NUM_FIGURES;
  return index;
}

TetFigure placeFigure(GameInfo_t *game) {
  int index = game->next_fig;
  TetFigure figure = allFigures[index];
  game->next_fig = generateFig();
  figure.currentState = 0;
  for (int i = 0; i < figure.size; i++) {
    for (int j = 0; j < figure.size; j++) {
      if (figure.blocks[figure.currentState][i][j] != 0) {
        int fx = figure.x + j + ((WIDTH / 2) - 2);
        int fy = figure.y + i + SDWIG;
        if (fx >= 0 && fx < WIDTH && fy >= 0 && fy < HEIGHT + SDWIG &&
            game->field[fx][fy] == 0) {
          game->field[fy][fx] = figure.blocks[figure.currentState][i][j];
        }
      }
    }
  }
  return figure;
}

bool moveFigure(UserAction_t action, TetFigure *figure, GameInfo_t *game) {
  bool run = true;
  switch (action) {
    case T_Action:
      if (!game->pause) figure = handleRotation(game, figure);
      break;
    case T_Pause:
      game->pause = !game->pause;
      break;
    case T_Terminate:
      run = false;
      break;
    case T_Left:
      if (!game->pause) figure = moveLeft(game, figure);
      break;
    case T_Right:
      if (!game->pause) figure = moveRight(game, figure);
      break;
    case T_Down:
      if (!game->pause) run = moveFigureDown(game, figure);
      break;
    case T_Up:
      if (!game->pause) run = moveFigureDown(game, figure);
      break;
    case T_Start:
      game->pause = false;
      break;
    default:
      break;
  }
  return run;
}

void placeFigureOnField(GameInfo_t *game, TetFigure *figure) {
  for (int i = 0; i < figure->size; i++) {
    for (int j = 0; j < figure->size; j++) {
      if (figure->blocks[figure->currentState][i][j] != 0) {
        int fx = figure->x + j + (WIDTH / 2) - 2;
        int fy = figure->y + i + SDWIG;
        if (fy >= 0 && fx >= 0 && fx < WIDTH && fy < HEIGHT + SDWIG) {
          game->field[fy][fx] = figure->blocks[figure->currentState][i][j];
        }
      }
    }
  }
  clearFullRows(game);
}

void clearFullRows(GameInfo_t *game) {
  int count = 0;
  for (int y = HEIGHT; y >= 0; y--) {
    bool isRowFull = true;
    for (int x = 0; x < WIDTH; x++) {
      if (game->field[y][x] == 0) {
        isRowFull = false;
        break;
      }
    }
    if (isRowFull) {
      for (int ty = y; ty > 0; ty--) {
        for (int tx = 0; tx < WIDTH; tx++) {
          game->field[ty][tx] = game->field[ty - 1][tx];
        }
      }
      count++;
      y++;
    }
  }
  if (count == one_row)
    game->score += COUNT_POINTS_FOR_1;
  else if (count == two_row)
    game->score += COUNT_POINTS_FOR_2;
  else if (count == three_row)
    game->score += COUNT_POINTS_FOR_3;
  else if (count == four_row)
    game->score += COUNT_POINTS_FOR_4;
}

GameInfo_t *leveling(GameInfo_t *game) {
  int lvl = (game->score / LVL_CURRENT) + LVL_START;
  if (lvl < LVL_MAX) {
    game->speed = START_SPEED + (LVL_STEP * lvl);
    game->level = lvl;
  } else {
    game->level = LVL_MAX;
    game->speed = FINISH_SPEED;
  }
  return game;
}

int readHighScore(const char *filename) {
  FILE *file = fopen(filename, "r");
  int high_score = 0;
  if (file) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  } else {
    file = fopen(filename, "w");
    fprintf(file, "%d", 0);
    fclose(file);
  }
  return high_score;
}

void writeHighScore(const char *filename, int score) {
  FILE *file = fopen(filename, "w");
  if (file) {
    fprintf(file, "%d", score);
    fclose(file);
  }
}

void drawFigure(GameInfo_t *game, TetFigure *figure) {
  for (int i = 0; i < figure->size; i++) {
    for (int j = 0; j < figure->size; j++) {
      if (figure->blocks[figure->currentState][i][j] != 0) {
        int fx = figure->x + j + (WIDTH / 2) - 2;
        int fy = figure->y + i + SDWIG;
        if (fx >= 0 && fx < WIDTH && fy >= 0 && fy < HEIGHT + SDWIG) {
          game->field[fy][fx] = figure->blocks[figure->currentState][i][j];
        }
      }
    }
  }
}

void washTraceFigure(GameInfo_t *game, TetFigure *figure) {
  for (int i = 0; i < figure->size; i++) {
    for (int j = 0; j < figure->size; j++) {
      if (figure->blocks[figure->currentState][i][j] != 0) {
        int fx = figure->x + j + (WIDTH / 2) - 2;
        int fy = figure->y + i + SDWIG;
        if (fx >= 0 && fx < WIDTH && fy >= 0 && fy < HEIGHT + SDWIG) {
          game->field[fy][fx] = 0;
        }
      }
    }
  }
}

TetFigure allFigures[NUM_FIGURES] = {
    // 0 - I
    {.blocks = {{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}},
                {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}},
     .currentState = 0,
     .x = 0,
     .y = 0,
     .size = 4},
    // 1 - []
    {.blocks = {{{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
     .currentState = 0,
     .x = 0,
     .y = 0,
     .size = 3},
    // 2 - T
    {.blocks = {{{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
                {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}}},
     .currentState = 0,
     .x = 0,
     .y = 0,
     .size = 3},
    // 3 - s
    {.blocks = {{{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
                {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
                {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
     .currentState = 0,
     .x = 0,
     .y = 0,
     .size = 3},
    // 4 - z
    {.blocks = {{{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
                {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 0, 0}, {1, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}},
                {{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
     .currentState = 0,
     .x = 0,
     .y = 0,
     .size = 3},
    // 5 - J
    {.blocks = {{{0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
                {{0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}},
                {{0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}},
                {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
     .currentState = 0,
     .x = 0,
     .y = 0,
     .size = 3},
    // 6 - L
    {.blocks = {{{1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}},
                {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
                {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
                {{0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}}},
     .currentState = 0,
     .x = 0,
     .y = 0,
     .size = 3}};
