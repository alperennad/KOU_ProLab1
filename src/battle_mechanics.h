#ifndef BATTLE_MECHANICS_H
#define BATTLE_MECHANICS_H

int calculateOrkUnits();
int calculateHumanUnits();
int battle();

extern int piyade_health;
extern int okcu_health;
extern int suvari_health;
extern int kusatmaMakineleri_health;
extern int orkDovusculeri_health;
extern int mizrakcilar_health;
extern int vargBinicileri_health;
extern int troller_health;

extern int tempPiyade; extern int tempOkcu; extern int tempSuvari; extern int tempKusatmaMakineleri;
extern int tempOrkDovusculeri; extern int tempMizrakcilar; extern int tempVargBinicileri; extern int tempTroller;
#endif
