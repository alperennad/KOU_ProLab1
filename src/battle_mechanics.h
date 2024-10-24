#ifndef BATTLE_MECHANICS_H
#define BATTLE_MECHANICS_H

int calculatePiyadeAttack();
int calculatePiyadeDefense();
int calculateOkcuAttack();
int calculateOkcuDefense();
int calculateSuvariAttack();
int calculateSuvariDefense();
int calculateKusatmaMakineleriAttack();
int calculateKusatmaMakineleriDefense();
int calculateOrkDovusculeriAttack();
int calculateOrkDovusculeriDefense();
int calculateMizrakcilarAttack();
int calculateMizrakcilarDefense();
int calculateVargBinicileriAttack();
int calculateVargBinicileriDefense();
int calculateTrollerAttack();
int calculateTrollerDefense();
int humanAttackPower();
int calculateOrkUnits();
int calculateHumanUnits();
int NetHasar(int savunma, int saldiri);
int olenBirimSayisi(int birim_hasar, int health);
int battle();

extern int piyade_health;
extern int okcu_health;
extern int suvari_health;
extern int kusatmaMakineleri_health;
extern int orkDovusculeri_health;
extern int mizrakcilar_health;
extern int vargBinicileri_health;
extern int troller_health;
#endif
