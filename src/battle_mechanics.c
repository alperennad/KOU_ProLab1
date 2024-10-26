#include "url.h"
#include "json_parser.h"
#include "battle_mechanics.h"
#include <stdio.h>
#include <string.h>

int calculatePiyadeAttack() {
    return piyadeler_count * humanUnits[0].attack;
}

int calculatePiyadeDefense() {
    return piyadeler_count * humanUnits[0].defense;
}

int calculateOkcuAttack() {
    return okcular_count * humanUnits[1].attack;
}

int calculateOkcuDefense() {
    return okcular_count * humanUnits[1].defense;
}

int calculateSuvariAttack() {
    return suvariler_count * humanUnits[2].attack;
}

int calculateSuvariDefense() {
    return suvariler_count * humanUnits[2].defense;
}

int calculateKusatmaMakineleriAttack() {
    return kusatma_makineleri_count * humanUnits[3].attack;
}

int calculateKusatmaMakineleriDefense() {
    return kusatma_makineleri_count * humanUnits[3].defense;
}

int calculateOrkDovusculeriAttack() {
    return ork_dovusculeri_count * orkUnits[0].attack;
}

int calculateOrkDovusculeriDefense() {
    return ork_dovusculeri_count * orkUnits[0].defense;
}

int calculateMizrakcilarAttack() {
    return mizrakcilar_count * orkUnits[1].attack;
}
int calculateMizrakcilarDefense() {
    return mizrakcilar_count * orkUnits[1].defense;
}

int calculateVargBinicileriAttack() {
    return varg_binicileri_count * orkUnits[2].attack;
}

int calculateVargBinicileriDefense() {
    return varg_binicileri_count * orkUnits[2].defense;
}

int calculateTrollerAttack() {
    return troller_count * orkUnits[3].attack;
}

int calculateTrollerDefense() {
    return troller_count * orkUnits[3].defense;
}

int calculateHumanUnits(){
    return piyadeler_count + okcular_count + suvariler_count + kusatma_makineleri_count;
}

int calculateOrkUnits(){
    return ork_dovusculeri_count + mizrakcilar_count + varg_binicileri_count + troller_count;
}

// type-cast ederek çözdüm.
int NetHasar(int savunma, int saldiri){
    return saldiri * (1 - ((float)savunma/(float)saldiri));
}
// ork'a saldırırken netHasar(orkDefans, humanAtak);
// insan'a saldırırken netHasar(humanDefans, orkAtak);

int reduceHealth(int birim_hasar, int birim_sayisi){
    return (float)birim_hasar / (float)birim_sayisi;
}

int damageLeftEach(int DamageLeft, int birim_savunma, int butun_savunma){
    return DamageLeft * ((float)birim_savunma / (float)butun_savunma);
}

int damageLeft(int healthLeft, int birim_count){
    return (healthLeft * -1) * birim_count;
}

int piyadeAtak = 0;
int piyadeDefans = 0;
int okcuAtak = 0;
int okcuDefans = 0;
int suvariAtak = 0;
int suvariDefans = 0;
int kusatmaMakineleriAtak = 0;
int kusatmaMakineleriDefans = 0;
int orkDovusculeriAtak = 0;
int orkDovusculeriDefans = 0;
int mizrakcilarAtak = 0;
int mizrakcilarDefans = 0;
int vargBinicileriAtak = 0;
int vargBinicileriDefans = 0;
int trollerAtak = 0;
int trollerDefans = 0;
int humanAtak = 0;
int humanDefans = 0;
int orkAtak = 0;
int orkDefans = 0;

int piyade_health = 100;
int okcu_health = 80;
int suvari_health = 120;
int kusatmaMakineleri_health = 150;
int orkDovusculeri_health = 100;
int mizrakcilar_health = 90;
int vargBinicileri_health = 130;
int troller_health = 200;

int calculateCriticalChance(int criticalChance){
    return (float)1 / (float)criticalChance * 100; 
}

//Senaryoda olmayan birimlerin can barını düzenlemek için
void HealthCheck(int piyadeler_count, int okcular_count, int suvariler_count, int kusatma_makineleri_count, int ork_dovusculeri_count, int mizrakcilar_count, int varg_binicileri_count, int troller_count){
    if(piyadeler_count == 0) piyade_health = 0;
    if(okcular_count == 0) okcu_health = 0;
    if(suvariler_count == 0) suvari_health = 0;
    if(kusatma_makineleri_count == 0) kusatmaMakineleri_health = 0;
    if(ork_dovusculeri_count == 0) orkDovusculeri_health = 0;
    if(mizrakcilar_count == 0) mizrakcilar_health = 0;
    if(varg_binicileri_count == 0) vargBinicileri_health = 0;
    if(troller_count == 0) troller_health = 0;

}

int tempPiyade; int tempOkcu; int tempSuvari; int tempKusatmaMakineleri;
int tempOrkDovusculeri; int tempMizrakcilar; int tempVargBinicileri; int tempTroller;

int battle() {
int step = 1;
int orkStep = 1;
int humanStep = 1;

//Hasar Tanımlamaları
int piyadeHasar = 0;
int okcuHasar = 0;
int suvariHasar = 0;
int kusatmaMakineleriHasar = 0;
int ork_dovusculeriHasar = 0;
int mizrakcilarHasar = 0;
int varg_binicileriHasar = 0;
int trollerHasar = 0;
int kalanHasar = 0;


FILE *file = fopen("battle_sim.txt", "w+");
    if (!file) {
        printf("battle_sim.txt açılamadı!");
    }

    while (calculateHumanUnits() > 0 && calculateOrkUnits() > 0){

        if(step == 1){
            fprintf(file,"Insan Irkı Birimleri:\n");
            fprintf(file,"Piyadeler: %d\n", piyadeler_count);
            fprintf(file,"Okcular: %d\n", okcular_count);
            fprintf(file,"Suvariler: %d\n", suvariler_count);
            fprintf(file,"Kuşatma Makineleri: %d\n", kusatma_makineleri_count);
            fprintf(file,"Aktif Kahraman: %s\n",heroName);
            fprintf(file,"Aktif Canavar: %s\n",creatureName);
            fprintf(file,"Aktif Araştırma ve Seviyesi : %s %d\n\n",research_name,research_level);
            fprintf(file,"Ork Lejyonu Birimleri:\n");
            fprintf(file,"Ork Dovusculeri: %d\n",ork_dovusculeri_count);
            fprintf(file,"Mizrakcilar: %d\n",mizrakcilar_count);
            fprintf(file,"Varg Binicileri: %d\n",varg_binicileri_count);
            fprintf(file,"Troller: %d\n",troller_count);
            fprintf(file,"Aktif Kahraman: %s\n",heroName2);
            fprintf(file,"Aktif Canavar: %s\n",creatureName2);
            fprintf(file,"Aktif Araştırma ve Seviyesi : %s %d\n",research_name2,research_level2);
        }
        if (step % 2 == 0)
        {
            
            fprintf(file,"\n%d . Adım - ", step);
            fprintf(file,"(Ork Lejyonu Saldırıyor)\n");
            fprintf(file,"__________________________________\n");

            if (ork_dovusculeri_count > 0){
                if(orkStep % calculateCriticalChance(orkUnits[0].criticalChance) == 0){
                    orkDovusculeriAtak = calculateOrkDovusculeriAttack() * 1.5;
                }
                else{
                    orkDovusculeriAtak = calculateOrkDovusculeriAttack();
                }
                if(strcmp(heroName2,"Goruk_Vahsi") == 0){
                    orkDovusculeriAtak *= 1.2;
                }
            }
            fprintf(file,"Ork Dovusculeri Atak: %d\n", orkDovusculeriAtak);
            if (mizrakcilar_count > 0){
                if(orkStep% calculateCriticalChance(orkUnits[1].criticalChance) == 0){
                    mizrakcilarAtak = calculateMizrakcilarAttack() * 1.5;
                }
                else{
                    mizrakcilarAtak = calculateMizrakcilarAttack();
                }
            }
            fprintf(file,"Mizrakcilar Atak: %d\n", mizrakcilarAtak);
            if (varg_binicileri_count > 0){
                if(orkStep% calculateCriticalChance(orkUnits[2].criticalChance) == 0){
                    vargBinicileriAtak = varg_binicileri_count * orkUnits[2].attack * 1.5;
                }
                else{
            fprintf(file,"Varg Binicileri Sayısı: %d\n", varg_binicileri_count);

                    vargBinicileriAtak = varg_binicileri_count * orkUnits[2].attack;
                }
                if (strcmp(creatureName2, "Ates_Iblisi") == 0) {
                    vargBinicileriAtak *= 1.3;
                }
            }
            fprintf(file,"Varg Binicileri Sayısı: %d\n", varg_binicileri_count);
            fprintf(file,"Varg Binicileri Atak: %d\n", vargBinicileriAtak);
            if (troller_count > 0){
                if (orkStep% calculateCriticalChance(orkUnits[3].criticalChance) == 0) {
                    trollerAtak = calculateTrollerAttack() * 1.5;
                }
                else{
                    trollerAtak = calculateTrollerAttack();
                }
                if (strcmp(creatureName2, "Kara_Troll") == 0) {
                    trollerAtak *= 1.2;
                }
            }
            fprintf(file,"Troller Atak: %d\n", trollerAtak);
            if (piyadeler_count > 0){
                piyadeDefans = calculatePiyadeDefense();
                if (strcmp(creatureName, "Samur") == 0) {
                    piyadeDefans *= 1.1;
                }
                if(strcmp(heroName, "Alparslan") == 0){
                    piyadeDefans *= 1.2;
                }
            }
            fprintf(file,"Piyade Defans: %d\n", piyadeDefans);
            if (okcular_count > 0){
                okcuDefans = calculateOkcuDefense();
                if (strcmp(heroName, "Metehan") == 0) {
                    okcuDefans *= 1.2;
                }
            }
            fprintf(file,"Okcu Defans: %d\n", okcuDefans);
            if (suvariler_count > 0){
                suvariDefans = calculateSuvariDefense();
                if(strcmp(creatureName, "Agri_Dagi_Devleri") == 0){
                    suvariDefans *= 1.20;
                }
            }
            fprintf(file,"Suvari Defans: %d\n", suvariDefans);
            if (kusatma_makineleri_count > 0){
                kusatmaMakineleriDefans = calculateKusatmaMakineleriDefense(); 
            }
            fprintf(file,"Kusatma Makineleri Defans: %d\n", kusatmaMakineleriDefans);
            //Kahraman,Canavar veya Araştırma Etkilerinde toplu değer artışı olabilir.
            orkAtak = orkDovusculeriAtak + mizrakcilarAtak + vargBinicileriAtak + trollerAtak;
            humanDefans = piyadeDefans + okcuDefans + suvariDefans + kusatmaMakineleriDefans;
            int humanDefansSabit = humanDefans;

            if (strcmp(research_name,"savunma_ustaligi") == 0){
                if(research_level == 1){
                    humanDefans *= 1.1;
                }
                else if(research_level == 2){
                    humanDefans *= 1.2;
                }
                else if(research_level == 3){
                    humanDefans *= 1.3;
                }
            }
            if (strcmp(research_name2,"saldiri_gelistirmesi") == 0){
                if(research_level2 == 1){
                    orkAtak *= 1.1;
                }
                else if(research_level2 == 2){
                    orkAtak *= 1.2;
                }
                else if(research_level2 == 3){
                    orkAtak *= 1.3;
                }
            }
            
            //YORGUNLUK KONTROLU
            int isTired = 1;
            if(step >= 5 && isTired == 1){
                int yorgunlukSeviyesi = step / 5;
                float yorgunlukEtkeni = 1;
                for(int i=0; i < yorgunlukSeviyesi; i++){
                    yorgunlukEtkeni *= 0.9;
                }
                humanDefans *= yorgunlukEtkeni;
                orkAtak *= yorgunlukEtkeni;
                isTired = 0;
            }

            fprintf(file,"Ork Atak: %d\n", orkAtak);
            fprintf(file,"İnsan Defans: %d\n", humanDefans);
            int nethasar = NetHasar(humanDefans, orkAtak);
            if (nethasar < 0) {
                nethasar = 0;
            }
            fprintf(file,"Net Hasar: %d\n", nethasar);

            piyadeHasar += nethasar * ((float)piyadeDefans / (float)humanDefansSabit);
            fprintf(file,"Piyade Hasar: %d\n", piyadeHasar);
            piyade_health -= reduceHealth(piyadeHasar, piyadeler_count);
            piyadeHasar = 0;
            if (piyade_health < 0) {
                humanDefans -= piyadeDefans;
                piyadeDefans = 0;
                kalanHasar = damageLeft(piyade_health, piyadeler_count);
                fprintf(file,"  Piyadeler Yok Oldu Kalan Hasar: %d\n", kalanHasar);
                okcuHasar += damageLeftEach(kalanHasar, okcuDefans, humanDefans);
                suvariHasar += damageLeftEach(kalanHasar, suvariDefans, humanDefans);
                kusatmaMakineleriHasar += damageLeftEach(kalanHasar, kusatmaMakineleriDefans, humanDefans);
        
                piyadeAtak = 0;
                piyadeDefans = 0;
                piyadeHasar = 0;
                kalanHasar = 0;
                tempPiyade = piyadeler_count;
                piyadeler_count = 0;
                piyade_health = 0;
            }
            fprintf(file,"Piyade Kalan Can: %d\n", piyade_health);

            okcuHasar += nethasar * ((float)okcuDefans / (float)humanDefansSabit);
            fprintf(file,"Okcu Hasar: %d\n", okcuHasar);
            okcu_health -= reduceHealth(okcuHasar, okcular_count);
            okcuHasar = 0;
            if (okcu_health < 0) {
                humanDefans -= okcuDefans;
                okcuDefans = 0;
                kalanHasar = damageLeft(okcu_health, okcular_count);
                fprintf(file,"  Okcular Yok Oldu Kalan Hasar: %d\n", kalanHasar);
                suvariHasar += damageLeftEach(kalanHasar, suvariDefans, humanDefans);
                kusatmaMakineleriHasar += damageLeftEach(kalanHasar, kusatmaMakineleriDefans, humanDefans);
                ork_dovusculeriHasar += damageLeftEach(kalanHasar, orkDovusculeriDefans, humanDefans);

                okcuAtak = 0;
                okcuDefans = 0;
                okcuHasar = 0;
                kalanHasar = 0;           
                tempOkcu = okcular_count;     
                okcular_count = 0;
                okcu_health = 0;
            }
            fprintf(file,"Okcu Kalan Can: %d\n", okcu_health);

            suvariHasar += nethasar * ((float)suvariDefans / (float)humanDefansSabit);
            fprintf(file,"Suvari Hasar: %d\n", suvariHasar);
            suvari_health -= reduceHealth(suvariHasar, suvariler_count);
            suvariHasar = 0;
            if (suvari_health < 0) {
                humanDefans -= suvariDefans;
                suvariDefans = 0;
                kalanHasar = damageLeft(suvari_health, suvariler_count);
                fprintf(file,"  Suvariler Yok Oldu Kalan Hasar: %d\n", kalanHasar);
                kusatmaMakineleriHasar += damageLeftEach(kalanHasar, kusatmaMakineleriDefans, humanDefans);
                okcuHasar += damageLeftEach(kalanHasar, okcuDefans, humanDefans);
                piyadeHasar += damageLeftEach(kalanHasar, piyadeDefans, humanDefans);

                suvariAtak = 0;
                suvariDefans = 0;
                suvariHasar = 0;
                kalanHasar = 0;
                tempSuvari = suvariler_count;
                suvariler_count = 0;
                suvari_health = 0;
            }
            fprintf(file,"Suvari Kalan Can: %d\n", suvari_health);

            kusatmaMakineleriHasar += nethasar * ((float)kusatmaMakineleriDefans / (float)humanDefansSabit);
            fprintf(file,"Kusatma Makineleri Hasar: %d\n", kusatmaMakineleriHasar);
            kusatmaMakineleri_health -= reduceHealth(kusatmaMakineleriHasar, kusatma_makineleri_count);
            kusatmaMakineleriHasar = 0;
            if (kusatmaMakineleri_health < 0) {
                humanDefans -= kusatmaMakineleriDefans;
                kusatmaMakineleriDefans = 0;
                kalanHasar = damageLeft(kusatmaMakineleri_health, kusatma_makineleri_count);
                fprintf(file,"  Kusatma Makineleri Yok Oldu Kalan Hasar: %d\n", kalanHasar);
                suvariHasar += damageLeftEach(kalanHasar, suvariDefans, humanDefans);
                okcuHasar += damageLeftEach(kalanHasar, okcuDefans, humanDefans);
                piyadeHasar += damageLeftEach(kalanHasar, piyadeDefans, humanDefans);

                kusatmaMakineleriAtak = 0;
                kusatmaMakineleriDefans = 0;
                kusatmaMakineleriHasar = 0;
                kalanHasar = 0;
                tempKusatmaMakineleri = kusatma_makineleri_count;
                kusatma_makineleri_count = 0;
                kusatmaMakineleri_health = 0;
            }
            fprintf(file,"Kusatma Makineleri Kalan Can: %d\n", kusatmaMakineleri_health);
            orkStep++;
        }
        else    //İNSAN İMPARATORLUGU İSLEMLERİ//////////////////////
        {
            fprintf(file,"\n%d . Adım - ", step);
            fprintf(file,"(Insan Imparatorlugu Saldırıyor)\n");
            fprintf(file,"__________________________________\n");
            if (piyadeler_count > 0){                
                if (humanStep % calculateCriticalChance(humanUnits[0].criticalChance) == 0){
                    piyadeAtak = calculatePiyadeAttack() * 1.5;
                }
                else{
                    piyadeAtak = calculatePiyadeAttack();
                }
                if(strcmp(creatureName, "Ejderha") == 0){
                    piyadeAtak *= 1.15;
                }                
            }
            fprintf(file,"Piyade Atak: %d\n", piyadeAtak);
            if (okcular_count > 0){
                if (humanStep % calculateCriticalChance(humanUnits[1].criticalChance) == 0){
                    okcuAtak = calculateOkcuAttack() * 1.5;
                }
                else{
                    okcuAtak = calculateOkcuAttack();
                }
                if(strcmp(heroName, "Tugrul_Bey") == 0){
                    okcuAtak *= 1.2;
                }
                if(strcmp(creatureName, "Tepegoz") == 0){
                    okcuAtak *= 1.25;
                }
            }
            fprintf(file,"Okçu Atak: %d\n", okcuAtak);
            if (suvariler_count > 0){
                if (humanStep % calculateCriticalChance(humanUnits[2].criticalChance) == 0){
                    suvariAtak = calculateSuvariAttack() * 1.5;
                }
                else{
                    suvariAtak = calculateSuvariAttack();
                }
                if(strcmp(heroName, "Yavuz_Sultan_Selim") == 0){
                    humanUnits[2].criticalChance = 6;
                }
            }
            fprintf(file,"Suvari Atak: %d\n", suvariAtak);
            if (kusatma_makineleri_count > 0){
                if (humanStep % calculateCriticalChance(humanUnits[3].criticalChance) == 0){
                    kusatmaMakineleriAtak = calculateKusatmaMakineleriAttack() * 1.5;
                }
                else{
                    kusatmaMakineleriAtak = calculateKusatmaMakineleriAttack();
                }
                if(strcmp(heroName, "Fatih_Sultan_Mehmet") == 0){
                    kusatmaMakineleriAtak *= 1.25;
                }
                if(strcmp(research_name, "kusatma_ustaligi") == 0){
                    if(research_level == 1){
                        kusatmaMakineleriAtak *= 1.1;
                    }
                    else if(research_level == 2){
                        kusatmaMakineleriAtak *= 1.2;
                    }
                    else if(research_level == 3){
                        kusatmaMakineleriAtak *= 1.3;
                    }
                }
            }
            fprintf(file,"Kuşatma Makineleri Atak: %d\n", kusatmaMakineleriAtak);
            if (ork_dovusculeri_count > 0){
                orkDovusculeriDefans = calculateOrkDovusculeriDefense();
                if (strcmp(creatureName2, "Camur_Devleri") == 0) {
                    orkDovusculeriDefans *= 1.25;
                }
            }
            fprintf(file,"Ork Dovusculeri Defans: %d\n", orkDovusculeriDefans);
            if (mizrakcilar_count > 0){
                mizrakcilarDefans = calculateMizrakcilarDefense();
                if(strcmp(creatureName2, "Buz_Devleri") == 0){
                    mizrakcilarDefans *= 1.15;
                }
            }
            fprintf(file,"Mizrakcilar Defans: %d\n", mizrakcilarDefans);
            if (varg_binicileri_count > 0){
                vargBinicileriDefans = calculateVargBinicileriDefense();
                if (strcmp(creatureName2, "Golge_Kurtlari") == 0) {
                    vargBinicileriDefans *= 1.15;
                }
            }
            if (troller_count > 0){
                trollerDefans = calculateTrollerDefense();
                if (strcmp(heroName2, "Thruk_Kemikkiran") == 0) {
                    trollerDefans *= 1.25;
                }
                if (strcmp(creatureName2, "Makrog_Savas_Beyi") == 0) {
                    trollerDefans *= 1.25;
                }
            }
            fprintf(file,"Troller Defans: %d\n", trollerDefans);
            //Kahraman,Canavar veya Araştırma Etkilerinde toplu değer artışı olabilir.
            humanAtak = piyadeAtak + okcuAtak + suvariAtak + kusatmaMakineleriAtak;
            orkDefans = orkDovusculeriDefans + mizrakcilarDefans + vargBinicileriDefans + trollerDefans;
            int orkDefansSabit = orkDefans;

            if(strcmp(heroName2, "Ugar_Zalim") == 0){
                orkDefans *= 1.1;
            }
            if (strcmp(research_name,"saldırı_gelistirmesi") == 0){
                if(research_level == 1){
                    humanAtak *= 1.1;
                }
                else if(research_level == 2){
                    humanAtak *= 1.2;
                }
                else if(research_level == 3){
                    humanAtak *= 1.3;
                }
            }
            if (strcmp(research_name2, "savunma_ustaligi") == 0) {
                if (research_level2 == 1) {
                    orkDefans *= 1.1;
                }
                else if (research_level2 == 2) {
                    orkDefans *= 1.2;
                }
                else if (research_level2 == 3) {
                    orkDefans *= 1.3;
                }
            }
           //YORGUNLUK KONTROLU
           int isTired = 1;
           if(step >= 5 && isTired == 1){
                int yorgunlukSeviyesi = step / 5;
                float yorgunlukEtkeni = 1;
                for(int i=0; i < yorgunlukSeviyesi; i++){
                    yorgunlukEtkeni *= 0.9;
                }
                humanAtak *= yorgunlukEtkeni;
                orkDefans *= yorgunlukEtkeni;
                isTired = 0;
           }
            fprintf(file,"İnsan İmparatorlugu Atak: %d\n", humanAtak);
            fprintf(file,"Ork Lejyonu Defans: %d\n", orkDefans);
            int nethasar = NetHasar(orkDefans, humanAtak);
            if (nethasar < 0) {
                nethasar = 0;
            }            
            fprintf(file,"Net Hasar: %d\n", nethasar);
        
            ork_dovusculeriHasar += nethasar * ((float)orkDovusculeriDefans / (float)orkDefansSabit);
            fprintf(file,"Ork Dovusculeri Hasar: %d\n", ork_dovusculeriHasar);
            orkDovusculeri_health -= reduceHealth(ork_dovusculeriHasar, ork_dovusculeri_count);
            ork_dovusculeriHasar = 0;
            if (orkDovusculeri_health < 0) {
                orkDefans -= orkDovusculeriDefans; 
                orkDovusculeriDefans = 0;
                kalanHasar = damageLeft(orkDovusculeri_health, ork_dovusculeri_count);
                fprintf(file,"  Ork Dovusculeri Yok Oldu Kalan Hasar: %d\n", kalanHasar);
                mizrakcilarHasar += damageLeftEach(kalanHasar, mizrakcilarDefans, orkDefans);
                varg_binicileriHasar += damageLeftEach(kalanHasar, vargBinicileriDefans, orkDefans);
                trollerHasar += damageLeftEach(kalanHasar, trollerDefans, orkDefans);

                orkDovusculeriAtak = 0;
                orkDovusculeriDefans = 0;
                ork_dovusculeriHasar = 0;
                kalanHasar = 0;
                tempOrkDovusculeri = ork_dovusculeri_count;
                ork_dovusculeri_count = 0;
                orkDovusculeri_health = 0;
            }
            fprintf(file,"Ork Dovusculeri Kalan Can: %d\n", orkDovusculeri_health);

            mizrakcilarHasar += nethasar * ((float)mizrakcilarDefans / (float)orkDefansSabit);
            fprintf(file,"Mizrakcilar Hasar: %d\n", mizrakcilarHasar);
            mizrakcilar_health -= reduceHealth(mizrakcilarHasar, mizrakcilar_count);
            mizrakcilarHasar = 0;
            if (mizrakcilar_health < 0) {
                orkDefans -= mizrakcilarDefans;
                mizrakcilarDefans = 0;
                kalanHasar = damageLeft(mizrakcilar_health, mizrakcilar_count);
                fprintf(file,"  Mizrakcilar Yok Oldu Kalan Hasar: %d\n", kalanHasar);
                varg_binicileriHasar += damageLeftEach(kalanHasar, vargBinicileriDefans, orkDefans);
                trollerHasar += damageLeftEach(kalanHasar, trollerDefans, orkDefans);
                ork_dovusculeriHasar += damageLeftEach(kalanHasar, orkDovusculeriDefans, orkDefans);
                
                mizrakcilarAtak = 0;
                mizrakcilarDefans = 0;
                mizrakcilarHasar = 0;
                kalanHasar = 0;
                tempMizrakcilar = mizrakcilar_count;
                mizrakcilar_count = 0;
                mizrakcilar_health = 0;
            }
            fprintf(file,"Mizrakcilar Kalan Can: %d\n", mizrakcilar_health);

            varg_binicileriHasar += nethasar * ((float)vargBinicileriDefans / (float)orkDefansSabit);
            fprintf(file,"Varg Binicileri Hasar: %d\n", varg_binicileriHasar);
            vargBinicileri_health -= reduceHealth(varg_binicileriHasar, varg_binicileri_count);
            varg_binicileriHasar = 0;
            if (vargBinicileri_health < 0) {
                orkDefans -= vargBinicileriDefans;
                vargBinicileriDefans = 0;                
                kalanHasar = damageLeft(vargBinicileri_health, varg_binicileri_count);
                    fprintf(file,"  Varg Binicileri Yok Oldu Kalan Hasar: %d\n", kalanHasar);
                trollerHasar += damageLeftEach(kalanHasar, trollerDefans, orkDefans);
                ork_dovusculeriHasar += damageLeftEach(kalanHasar, orkDovusculeriDefans, orkDefans);
                mizrakcilarHasar += damageLeftEach(kalanHasar, mizrakcilarDefans, orkDefans);

                vargBinicileriAtak = 0;
                vargBinicileriDefans = 0;
                varg_binicileriHasar = 0;
                kalanHasar = 0;
                tempVargBinicileri = varg_binicileri_count;
                varg_binicileri_count = 0;
                vargBinicileri_health = 0;
            }
            fprintf(file,"Varg Binicileri Kalan Can: %d\n", vargBinicileri_health);

            trollerHasar += nethasar * ((float)trollerDefans / (float)orkDefansSabit);
            fprintf(file,"Troller Hasar: %d\n", trollerHasar);
            troller_health -= reduceHealth(trollerHasar, troller_count);
            trollerHasar = 0;
            if (troller_health < 0) {
                orkDefans -= trollerDefans;
                trollerAtak = 0;
                trollerDefans = 0;
                kalanHasar = damageLeft(troller_health, troller_count);
                fprintf(file,"  Troller Yok Oldu Kalan Hasar: %d\n", kalanHasar);
                ork_dovusculeriHasar += damageLeftEach(kalanHasar, orkDovusculeriDefans, orkDefans);
                mizrakcilarHasar += damageLeftEach(kalanHasar, mizrakcilarDefans, orkDefans);
                varg_binicileriHasar += damageLeftEach(kalanHasar, vargBinicileriDefans, orkDefans);               
    
                trollerAtak = 0;
                trollerDefans = 0;
                trollerHasar = 0;
                kalanHasar = 0;
                tempTroller = troller_count;
                troller_count = 0;
                troller_health = 0;
            }
            fprintf(file,"Troller Kalan Can: %d\n", troller_health);
            humanStep++;
        }
        step++;
        
    }
    
    if (calculateOrkUnits() > 0)
    {
        fprintf(file,"\nORK LEJYONU KAZANDI\n");
        return calculateOrkUnits();
    }
    else
    {
        fprintf(file,"\nINSAN IMPARATORLUGU KAZANDI \n");
        return calculateOrkUnits();
    }
return 0;
}
