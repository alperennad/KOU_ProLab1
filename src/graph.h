#ifndef GRAPH_H
#define GRAPH_H

struct Human {
    int infantry_count;
    int archer_count;
    int cavalry_count;
    int siege_count;
    char *hero;
    char *creature;
};

struct Ork {
    int ork_warrior_count;
    int spearman_count;
    int warg_rider_count;
    int troll_count;
    char *hero;
    char *creature;
};

void Game(struct Human *human, struct Ork *ork);
void StartScreen();

#endif