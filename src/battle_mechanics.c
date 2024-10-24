//derleme : cc main.c url.c json_parser.c battle_mechanics.c -lcurl

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

int battle() {
int step = 1;

//Hasar Tanımlamaları
int piyadeHasar = 0;
int okcuHasar = 0;
int suvariHasar = 0;
int kusatmaMakineleriHasar = 0;
int ork_dovusculeriHasar = 0;
int mizrakcilarHasar = 0;
int mizrakcilarTemelHasar = 0;
int varg_binicileriHasar = 0;
int trollerHasar = 0;
int kalanHasar = 0;

FILE *file = fopen("battle_sim.txt", "w+"); // Open the file for writing
    if (!file) {
        perror("Could not open battle_sim.txt");
        return -1; // Return an error if the file cannot be opened
    }
//calculateHumanUnits() > 0 && calculateOrkUnits() > 0
    while (calculateHumanUnits() > 0 && calculateOrkUnits() > 0){

        if(step == 1){
            fprintf(file,"Insan Irkı Birimleri:\n");
            fprintf(file,"Piyadeler: %d\n", piyadeler_count);
            fprintf(file,"Okcular: %d\n", okcular_count);
            fprintf(file,"Suvariler: %d\n", suvariler_count);
            fprintf(file,"Kuşatma Makineleri: %d\n", kusatma_makineleri_count);
            fprintf(file,"Aktif Kahraman: %s\n",heroName);
            fprintf(file,"Aktif Canavar: %s\n",creatureName);
        }
        if(step == 2){
            fprintf(file,"Ork Lejyonu Birimleri:\n");
            fprintf(file,"Ork Dovusculeri: %d\n",ork_dovusculeri_count);
            fprintf(file,"Mizrakcilar: %d\n",mizrakcilar_count);
            
        }
        if (step % 2 == 0)
        {
            fprintf(file,"%d . Adım - ", step);
            fprintf(file,"(Ork Lejyonu Saldırıyor)\n");
            fprintf(file,"__________________________________");

            //Ork saldırır
            if (ork_dovusculeri_count > 0){
                if(step % orkUnits[0].criticalChance == 0){
                    orkDovusculeriAtak *= 1.5;
                }
                else{
                    orkDovusculeriAtak = calculateOrkDovusculeriAttack();
                }
                if(strcmp(heroName2,"Goruk_Vahsi") == 0){
                    orkDovusculeriAtak *= 1.2;
                }
            }
            if (mizrakcilar_count > 0){
                if(step % orkUnits[1].criticalChance == 0){
                    mizrakcilarAtak *= 1.5;
                }
                else{
                    mizrakcilarAtak = calculateMizrakcilarAttack();
                }
            }
            if (varg_binicileri_count > 0){
                if(step % orkUnits[2].criticalChance == 0){
                    vargBinicileriAtak *= 1.5;
                }
                else{
                    vargBinicileriAtak = calculateVargBinicileriAttack();
                }
                if (strcmp(creatureName2, "Ates_Iblisi") == 0) {
                    vargBinicileriAtak *= 1.3;
                }
                if (strcmp(heroName2, "Vrog_Kafakiran") == 0 && step % orkUnits[2].criticalChance == 0){
                    
                }
            }
            if (troller_count > 0){
                if (step % orkUnits[3].criticalChance == 0) {
                    trollerAtak *= 1.5;
                }
                else{
                    trollerAtak = calculateTrollerAttack();
                }
                if (strcmp(creatureName2, "Kara_Troll") == 0) {
                    trollerAtak *= 1.2;
                }
            }
            if (piyadeler_count > 0){
                piyadeDefans = calculatePiyadeDefense();
                if (strcmp(creatureName, "Samur") == 0) {
                    piyadeDefans *= 1.1;
                }
                if(strcmp(heroName, "Alparslan") == 0){
                    piyadeDefans *= 1.2;
                }
            }
            if (okcular_count > 0){
                okcuDefans = calculateOkcuDefense();
                if (strcmp(heroName, "Metehan") == 0) {
                    okcuDefans *= 1.2;
                }
            }
            if (suvariler_count > 0){
                suvariDefans = calculateSuvariDefense();
                if(strcmp(creatureName, "Agri_Dagi_Devleri") == 0){
                    suvariDefans *= 1.20;
                }
            }
            if (kusatma_makineleri_count > 0){
                kusatmaMakineleriDefans = calculateKusatmaMakineleriDefense(); 
            }
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
            if(step % 5 == 0){
                int yorgunlukSeviyesi = step / 5;
                float yorgunlukEtkeni = 1;
                for(int i=0; i < yorgunlukSeviyesi; i++){
                    yorgunlukEtkeni *= 0.9;
                }
                humanDefans *= yorgunlukEtkeni;
                orkAtak *= yorgunlukEtkeni;
            }
            int nethasar = NetHasar(humanDefans, orkAtak);
            if (nethasar < 0) {
                nethasar = 0;
            }
            //Orklar Savaşıyor
            piyadeHasar += nethasar * ((float)piyadeDefans / (float)humanDefansSabit);
            piyade_health -= reduceHealth(piyadeHasar, piyadeler_count);
            piyadeHasar = 0;
            if (piyade_health < 0) {
                humanDefans -= piyadeDefans;
                piyadeDefans = 0;
                kalanHasar = damageLeft(piyade_health, piyadeler_count);
                okcuHasar += damageLeftEach(kalanHasar, okcuDefans, humanDefans);
                suvariHasar += damageLeftEach(kalanHasar, suvariDefans, humanDefans);
                kusatmaMakineleriHasar += damageLeftEach(kalanHasar, kusatmaMakineleriDefans, humanDefans);
        
                kalanHasar = 0;
                piyadeler_count = 0;
                piyade_health = 0;
            }

            okcuHasar += nethasar * ((float)okcuDefans / (float)humanDefansSabit);
            okcu_health -= reduceHealth(okcuHasar, okcular_count);
            okcuHasar = 0;
            if (okcu_health < 0) {
                humanDefans -= okcuDefans;
                okcuDefans = 0;
                kalanHasar = damageLeft(okcu_health, okcular_count);
                suvariHasar += damageLeftEach(kalanHasar, suvariDefans, humanDefans);
                kusatmaMakineleriHasar += damageLeftEach(kalanHasar, kusatmaMakineleriDefans, humanDefans);
                ork_dovusculeriHasar += damageLeftEach(kalanHasar, orkDovusculeriDefans, humanDefans);

                kalanHasar = 0;                
                okcular_count = 0;
                okcu_health = 0;
            }

            suvariHasar += nethasar * ((float)suvariDefans / (float)humanDefansSabit);
            suvari_health -= reduceHealth(suvariHasar, suvariler_count);
            suvariHasar = 0;
            if (suvari_health < 0) {
                humanDefans -= suvariDefans;
                suvariDefans = 0;
                kalanHasar = damageLeft(suvari_health, suvariler_count);
                kusatmaMakineleriHasar += damageLeftEach(kalanHasar, kusatmaMakineleriDefans, humanDefans);
                okcuHasar += damageLeftEach(kalanHasar, okcuDefans, humanDefans);
                piyadeHasar += damageLeftEach(kalanHasar, piyadeDefans, humanDefans);

                kalanHasar = 0;
                suvariler_count = 0;
                suvari_health = 0;
            }

            kusatmaMakineleriHasar += nethasar * ((float)kusatmaMakineleriDefans / (float)humanDefansSabit);
            kusatmaMakineleri_health -= reduceHealth(kusatmaMakineleriHasar, kusatma_makineleri_count);
            kusatmaMakineleriHasar = 0;
            if (kusatmaMakineleri_health < 0) {
                humanDefans -= kusatmaMakineleriDefans;
                kusatmaMakineleriDefans = 0;
                kalanHasar = damageLeft(kusatmaMakineleri_health, kusatma_makineleri_count);
                suvariHasar += damageLeftEach(kalanHasar, suvariDefans, humanDefans);
                okcuHasar += damageLeftEach(kalanHasar, okcuDefans, humanDefans);
                piyadeHasar += damageLeftEach(kalanHasar, piyadeDefans, humanDefans);

                kalanHasar = 0;
                kusatma_makineleri_count = 0;
                kusatmaMakineleri_health = 0;
            }

        }
        else    //İNSAN İMPARATORLUGU İSLEMLERİ//////////////////////
        {
            fprintf(file,"%d . Adım\n", step);
            if (piyadeler_count > 0){                
                if (step % humanUnits[0].criticalChance == 0){
                    piyadeAtak *= 1.5;
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
                if (step % humanUnits[1].criticalChance == 0){
                    okcuAtak *= 1.5;
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
                if (step % humanUnits[2].criticalChance == 0){
                    suvariAtak *= 1.5;
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
                if (step % humanUnits[3].criticalChance == 0){
                    kusatmaMakineleriAtak *= 1.5;
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
           if(step % 5 == 0){
                int yorgunlukSeviyesi = step / 5;
                float yorgunlukEtkeni = 1;
                for(int i=0; i < yorgunlukSeviyesi; i++){
                    yorgunlukEtkeni *= 0.9;
                }
            humanAtak *= yorgunlukEtkeni;
            orkDefans *= yorgunlukEtkeni;
           }

            fprintf(file,"Human Atak: %d\n", humanAtak);
            fprintf(file,"Ork Defans: %d\n", orkDefans);
            int nethasar = NetHasar(orkDefans, humanAtak);
            if (nethasar < 0) {
                nethasar = 0;
            }            
            fprintf(file,"Net Hasar: %d\n", nethasar);
        
            //Ork_Dovusculerı Savaşıyor
            ork_dovusculeriHasar += nethasar * ((float)orkDovusculeriDefans / (float)orkDefansSabit);
            fprintf(file,"Ork Dovusculeri Hasar: %d\n", ork_dovusculeriHasar);
            orkDovusculeri_health -= reduceHealth(ork_dovusculeriHasar, ork_dovusculeri_count);
            fprintf(file,"Ork Dovusculeri Health: %d\n", orkDovusculeri_health);
            //orkDovusculeri_health = -9;
            ork_dovusculeriHasar = 0;
            if (orkDovusculeri_health < 0) {
                orkDefans -= orkDovusculeriDefans; 
                orkDovusculeriDefans = 0;
                kalanHasar = damageLeft(orkDovusculeri_health, ork_dovusculeri_count);
                mizrakcilarHasar += damageLeftEach(kalanHasar, mizrakcilarDefans, orkDefans);
                fprintf(file,"Mizrakcilar Hasar: %d\n", mizrakcilarHasar);
                varg_binicileriHasar += damageLeftEach(kalanHasar, vargBinicileriDefans, orkDefans);
                trollerHasar += damageLeftEach(kalanHasar, trollerDefans, orkDefans);

                kalanHasar = 0;
                ork_dovusculeri_count = 0;
                orkDovusculeri_health = 0;
            }

            //Birim Hasar hesaplamasında sıkıntı var
            //Herhangi bir birim oldugunde defansını cıkardıgımız için digerine 
            //olması gerekenden fazla hasar gidiyor
            //Mizrakci Savasıyor
            fprintf(file,"Mizrakcilar Defans: %d\n", mizrakcilarDefans);
            mizrakcilarTemelHasar += nethasar * ((float)mizrakcilarDefans / (float)orkDefansSabit);
            mizrakcilarHasar += mizrakcilarTemelHasar;
            fprintf(file,"Mizrakcilar Hasar: %d\n", mizrakcilarHasar);
            mizrakcilar_health -= reduceHealth(mizrakcilarHasar, mizrakcilar_count);
            fprintf(file,"Mizrakcilar Vurulduktan Sonraki Health: %d\n", mizrakcilar_health);
            mizrakcilarHasar = 0;
            if (mizrakcilar_health < 0) {
                orkDefans -= mizrakcilarDefans;
                mizrakcilarDefans = 0;
                kalanHasar = damageLeft(mizrakcilar_health, mizrakcilar_count);
                fprintf(file,"Kalan Hasar: %d\n", kalanHasar);
                fprintf(file,"Varg Binicileri Hasar1: %d\n", varg_binicileriHasar);
                varg_binicileriHasar = damageLeftEach(kalanHasar, vargBinicileriDefans, orkDefans);
                trollerHasar = damageLeftEach(kalanHasar, trollerDefans, orkDefans);
                ork_dovusculeriHasar = damageLeftEach(kalanHasar, orkDovusculeriDefans, orkDefans);
                
                kalanHasar = 0;
                mizrakcilar_count = 0;
                mizrakcilar_health = 0;
            }
            fprintf(file,"Varg Binicileri Hasar2: %d\n", varg_binicileriHasar);
            //Varg Binicileri Savaşıyor
            varg_binicileriHasar += nethasar * ((float)vargBinicileriDefans / (float)orkDefansSabit);
            fprintf(file,"Varg Binicileri Hasar3: %d\n", varg_binicileriHasar);
            vargBinicileri_health -= reduceHealth(varg_binicileriHasar, varg_binicileri_count);
            fprintf(file,"Varg Binicileri Vurulduktan sonraki Health: %d\n", vargBinicileri_health);
            varg_binicileriHasar = 0;
            if (vargBinicileri_health < 0) {
                orkDefans -= vargBinicileriDefans;
                vargBinicileriDefans = 0;                
                kalanHasar = damageLeft(vargBinicileri_health, varg_binicileri_count);
                trollerHasar += damageLeftEach(kalanHasar, trollerDefans, orkDefans);
                ork_dovusculeriHasar += damageLeftEach(kalanHasar, orkDovusculeriDefans, orkDefans);
                mizrakcilarHasar += damageLeftEach(kalanHasar, mizrakcilarDefans, orkDefans);


                kalanHasar = 0;
                varg_binicileri_count = 0;
                vargBinicileri_health = 0;
            }
            //Troller Savaşıyor
            trollerHasar += nethasar * ((float)trollerDefans / (float)orkDefansSabit);
            fprintf(file,"Troller Hasar: %d\n", trollerHasar);
            troller_health -= reduceHealth(trollerHasar, troller_count);
            fprintf(file,"Troller Health: %d\n", troller_health);
            trollerHasar = 0;

            if (troller_health < 0) {
                orkDefans -= trollerDefans;
                trollerAtak = 0;
                trollerDefans = 0;
                kalanHasar = damageLeft(troller_health, troller_count);
                ork_dovusculeriHasar += damageLeftEach(kalanHasar, orkDovusculeriDefans, orkDefans);
                mizrakcilarHasar += damageLeftEach(kalanHasar, mizrakcilarDefans, orkDefans);
                varg_binicileriHasar += damageLeftEach(kalanHasar, vargBinicileriDefans, orkDefans);               
    
                troller_count = 0;
                troller_health = 0;
                kalanHasar = 0;
            }
                fprintf(file,"\n------------------------------------------------\n");

        }
        step++;
        
    }
    
    if (calculateOrkUnits() > 0)
    {
        fprintf(file,"ork kazandı\n");
        return calculateOrkUnits();
    }
    else
    {
        fprintf(file,"insan kazandı\n");
        return calculateOrkUnits();
    }
return 0;
}
