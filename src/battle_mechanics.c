// 1 - ) SALDIRI GÜCÜNÜN HESAPLANMASI 
//     Saldırı Gucu = Birim başına Saldırı Gucu * Birim Sayısı

// 2 - ) SAVUNMA GÜCÜNÜN HESAPLANMASI
//     Savunma Gucu = Birim başına Savunma Gucu * Birim Sayısı

// 3 - ) Kritik Vuruş Şansının Hesaplanması
//      Kritik Vuruş Sayısı = 1 / kritik_sans
//      Kritik vurus her x saldirida bir yapilir. x = Saldırı Sayısı

// 1. Okçular (%10 kritik şansı):
//  Kritik Vuruş Oranı: %10 (her 10 saldırıda 1 kere kritik vuruş yapar).
//  Saldırı Gücü: 500 okçu, her biri 40 saldırı gücüne sahipse:
//  Toplam Saldırı Gücü: 500 * 40 = 20,000
//  Kritik Vuruş: Her 10. saldırıda kritik vuruş gerçekleşir.
//  Net Hasar (Kritik Vuruş Olmadan): 20,000
//  Net Hasar (Kritik Vuruşla): 20,000 * 1.5 = 30,000
//  Örnek: 10. saldırıda kritik vuruş yapılır, net hasar 30,000 olur.

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
// butun birimlerin saldırı ve savunmaları fonksiyonlara atandı

int humanAttackPower(){
    // Piyade, Okçu, Süvari ve Kuşatma Makineleri saldırı güçlerinin toplamı
    return calculatePiyadeAttack() + calculateOkcuAttack() + calculateSuvariAttack() + calculateKusatmaMakineleriAttack();
}

int humanDeffensePower(){
    // Piyade, Okçu, Süvari ve Kuşatma Makineleri savunma güçlerinin toplamı
    return calculatePiyadeDefense() + calculateOkcuDefense() + calculateSuvariDefense() + calculateKusatmaMakineleriDefense();
}
 
int orkAttackPower(){
    // Ork Dövüşçüleri, Mızrakçılar, Varg Binicileri ve Troller saldırı güçlerinin toplamı
    return calculateOrkDovusculeriAttack() + calculateMizrakcilarAttack() + calculateVargBinicileriAttack() + calculateTrollerAttack();
}

int orkDeffensePower(){
    // Ork Dövüşçüleri, Mızrakçılar, Varg Binicileri ve Troller savunma güçlerinin toplamı
    return calculateOrkDovusculeriDefense() + calculateMizrakcilarDefense() + calculateVargBinicileriDefense() + calculateTrollerDefense();
}

// Kritik vurus hesaplanmalı
// Savasın her adımı % kritik sans == 0 oldugunda kritik vurus yapmaları gerekir
int CriticalHitPiyade(){
    //5 vurusta bir kritik vurus yapar
    return calculatePiyadeAttack() * 1.5;
}

int CriticalHitOkcu(){
    //10 vurusta bir kritik vurus yapar
    return calculateOkcuAttack() * 1.5;
}

int CriticalHitSuvari(){
    //7 vurusta bir kritik vurus yapar
    return calculateSuvariAttack() * 1.5;
}

int CriticalHitOrkDovusculeri(){
    //8 vurusta bir kritik vurus yapar
    return calculateOrkDovusculeriAttack() * 1.5;
}

int CriticalHitMizrakcilar(){
    //5 vurusta bir kritik vurus yapar
    return calculateMizrakcilarAttack() * 1.5;
}

int CriticalHitVargBinicileri(){
    //6 vurusta bir kritik vurus yapar
    return calculateVargBinicileriAttack() * 1.5;
}

int CriticalHitTroller(){
    //5 vuusta bir kritik vurus yapar
    return calculateTrollerAttack() * 1.5;
}

//Yorgunluk hesaplanmalı
//Savasun her adımı % 5 == 0 oldugunda saldırı gucu %10 azalmalı

int calculatehumanTiredness(){
    //yorgun olunan her 5 adımda tum guc %10 azalsın
    return humanAttackPower() * 0.9;
}

int calculateOrkTiredness(){
    //yorgun olunan adımda tum gucun %90 ı alınsın
    return orkAttackPower() * 0.9;
}

//NetHasar = SaldırıGucu * (1 - BirimSavunmaGucu / MaxSavunmaGucu)
//Her adım sonunda yeni saglık hesaplanmalı
//YeniSaglık = EskiSaglık - (NetHasar / BirimSayısı)

//Kahraman ve Canavar etkileri hesaplanmalı

int calculateAlparslanEffect(){
    //Eger Alparslan varsa piyade defansı = calculateAlparslanEffect() olarak işlenecek

    return calculatePiyadeDefense() * 1.2;
}

int calculateFSMEffect(){
    //Eger FSM varsa kusatma makinesi saldırısı = calculateFSMEffect() olarak işlenecek    

    return calculateKusatmaMakineleriAttack() * 1.25;
}

int calculateMetehanEffect(){
    //Eger Metehan varsa okcu saldırısı = calculateMetehanEffect() olarak işlenecek

    return calculateOkcuDefense() * 1.2;
}

int calculateTugrulBeyEffect(){
    //Eger Tugrul Bey varsa suvari saldırısı = calculateTugrulBeyEffect() olarak işlenecek

    return calculateOkcuAttack() * 1.2;
}

///////////////////////////////////////////////////////////////////////////////////////////
/////////////////ORK LEGİ//////////////////////////////////////////////////////////////////

int calculateGorukVahsiEffect(){
    //Eger Goruk Vahsi varsa ork dovusculeri saldırısı = calculateGorukVahsıEffect() olarak işlenecek

    return calculateOrkDovusculeriAttack() * 1.2;
}

int calculateThrukEffect(){
    //Eger Thruk varsa mizrakcılar saldırısı = calculateThrukEffect() olarak işlenecek

    return calculateTrollerDefense() * 1.25;
}

int calculateVrogEffect(){
    //Eger Vrog varsa varg binicileri saldırısı = calculateVrogEffect() olarak işlenecek

    return CriticalHitVargBinicileri() * 1.15;
}
int calculateUgarEffect(){
    return orkDeffensePower() * 1.1;
}

int calculateHumanUnits(){
    return piyadeler_count + okcular_count + suvariler_count + kusatma_makineleri_count;
}

int calculateOrkUnits(){
    return ork_dovusculeri_count + mizrakcilar_count + varg_binicileri_count + troller_count;
}
char *currentHumanHero(){
    return heroName;
}

char *currentOrkHero(){
    return heroName2;
}

int NetHasar(int savunma, int saldiri){
    return saldiri * (1 - (savunma / saldiri));
}
// ork'a saldırırken netHasar(orkDefans, humanAtak);
// insan'a saldırırken netHasar(humanDefans, orkAtak);

int olenBirimSayisi(int birim_hasar, int health){
    return birim_hasar / health;
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


int battle() {
    int step = 1;
//calculateHumanUnits() > 0 && calculateOrkUnits() > 0
    while (step != 2){

        if (step % 2 == 0)
        {
            //Ork saldırır
            if (ork_dovusculeri_count > 0){
                orkDovusculeriAtak = calculateOrkDovusculeriAttack();
            }
            else if (mizrakcilar_count > 0){
                mizrakcilarAtak = calculateMizrakcilarAttack();
            }
            else if (varg_binicileri_count > 0){
                vargBinicileriAtak = calculateVargBinicileriAttack();
            }
            else if (troller_count > 0){
                trollerAtak = calculateTrollerAttack();            
            }
            if (piyadeler_count > 0){
                piyadeDefans = calculatePiyadeDefense();
            }
            else if (okcular_count > 0){
                okcuDefans = calculateOkcuDefense();
            }
            else if (suvariler_count > 0){
                suvariDefans = calculateSuvariDefense();
            }
            else if (kusatma_makineleri_count > 0){
                kusatmaMakineleriDefans = calculateKusatmaMakineleriDefense();
            }            
            //hangi kahraman olduğunun kontrolü yapılmalı
            //strcmp kullanılabilir
            if (strcmp(currentOrkHero(),"Goruk_Vahsi") == 0){
                //Goruk Vahsi varsa ork dovusculeri saldırısı = calculateGorukVahsıEffect() olarak işlenecek
                orkDovusculeriAtak = calculateGorukVahsiEffect();
            }
            else if (strcmp(currentOrkHero(),"Thruk_Kemikkiran") == 0){
                //Thruk varsa mizrakcılar saldırısı = calculateThrukEffect() olarak işlenecek
                trollerDefans = calculateThrukEffect();
            }
            else if (strcmp(currentOrkHero(),"Vrog_Kafakiran") == 0){
                //Vrog varsa varg binicileri saldırısı = calculateVrogEffect() olarak işlenecek
                vargBinicileriAtak = calculateVrogEffect();
            }
            else if (strcmp(currentOrkHero(),"Ugar_Zalim") == 0){
                //Ugar varsa ork defansı = calculateUgarEffect() olarak işlenecek
                orkDefans = calculateUgarEffect();
            }
            //hangi canavar oldugu kontrol edilmeli
            if (strcmp(creatureName2, "Kara_Troll") == 0){
                trollerAtak = calculateTrollerAttack() * 1.2;
            }
            else if (strcmp(creatureName2, "Golge_Kurtlari") == 0 ){
                vargBinicileriDefans = calculateVargBinicileriDefense() * 1.15;
            }
            else if (strcmp(creatureName2, "Camur_Devleri") == 0){
                orkDovusculeriDefans = calculateOrkDovusculeriDefense() * 1.25;
            }
            else if (strcmp(creatureName2, "Ates_Iblisi") == 0) {
                vargBinicileriAtak = calculateVargBinicileriAttack() * 1.3;
                }
            else if (strcmp(creatureName2, "Makrog_Savas_Beyi") == 0) {
                trollerDefans = calculateTrollerDefense() * 1.25;
            }
            else if (strcmp(creatureName2, "Buz_Devleri") == 0) {
                mizrakcilarDefans = calculateMizrakcilarDefense() * 1.15;
            }
            if (strcmp(research_name2,"savunma_ustaligi") == 0){
                if(research_level2 == 1){
                    orkDefans = orkDeffensePower() * 1.1;
                }
                else if(research_level2 == 2){
                    orkDefans = orkDeffensePower() * 1.2;
                }
                else if(research_level2 == 3){
                    orkDefans = orkDeffensePower() * 1.3;
                }
            }
            else if (strcmp(research_name2,"saldırı_gelistirmesi") == 0){
                if(research_level2 == 1){
                    orkAtak = orkAttackPower() * 1.1;
                }
                else if(research_level2 == 2){
                    orkAtak = orkAttackPower() * 1.2;
                }
                else if(research_level2 == 3){
                    orkAtak = orkAttackPower() * 1.3;
                }
            }
            //else if (strcmp(research_name2,"elit_egitim") == 0) {
            // ///////////////////////KRİTİK SANS//////////////
            // }
            step++;


        }
        else    //İNSANNNNNNNNNN İMPARATORLUGU İSLEMLERİ//////////////////////
        {
            if (piyadeler_count > 0){
                piyadeAtak = calculatePiyadeAttack();
            }
            if (okcular_count > 0){
                okcuAtak = calculateOkcuAttack();
            }
            if (suvariler_count > 0){
                suvariAtak = calculateSuvariAttack();
            }
            if (kusatma_makineleri_count > 0){
                kusatmaMakineleriAtak = calculateKusatmaMakineleriAttack();
            }
            if (ork_dovusculeri_count > 0){
                orkDovusculeriDefans = calculateOrkDovusculeriDefense();
            }
            if (mizrakcilar_count > 0){
                mizrakcilarDefans = calculateMizrakcilarDefense();
                printf("%d mzrk\n",mizrakcilarDefans);
            }
            if (varg_binicileri_count > 0){
                vargBinicileriDefans = calculateVargBinicileriDefense();
            }
            if (troller_count > 0){
                trollerDefans = calculateTrollerDefense();
            }
            if (strcmp(currentHumanHero(),"Alparslan") == 0){
                //
                piyadeDefans = calculateAlparslanEffect();
            }
            else if (strcmp(currentHumanHero(),"Fatih_Sultan_Mehmet") == 0){
                kusatmaMakineleriAtak = calculateFSMEffect();
            }
            else if (strcmp(currentHumanHero(),"Mete_Han") == 0){
                okcuDefans = calculateVrogEffect();
            }
            else if (strcmp(currentHumanHero(),"Yavuz_Sultan_Selim") == 0){
                //kritigi arttırır
            }
            else if (strcmp(currentHumanHero(),"Tugrul_Bey") == 0){
                okcuAtak = calculateOkcuAttack();
            }
            if (strcmp(creatureName, "Ejderha") == 0) {
                piyadeAtak = calculatePiyadeAttack() * 1.15;
            }
            else if (strcmp(creatureName,"Agri_Dagi_Devleri") == 0) {
                suvariDefans = calculateSuvariDefense() * 1.2;
            }
            else if (strcmp(creatureName, "Tepegoz") == 0) {
                okcuAtak = calculateOkcuAttack() * 1.25;
            }
            else if (strcmp(creatureName, "Karakurt") == 0) {
                //kritik sans
            }
            else if (strcmp(creatureName, "Samur") == 0) {
                piyadeDefans = calculatePiyadeDefense() * 1.1;
            }
            if (strcmp(research_name,"savunma_ustaligi") == 0){
                if(research_level == 1){
                    humanDefans = humanDeffensePower() * 1.1;
                }
                else if(research_level == 2){
                    humanDefans = humanDeffensePower() * 1.2;
                }
                else if(research_level == 3){
                    humanDefans = humanDeffensePower() * 1.3;
                }
            }
            else if (strcmp(research_name,"saldırı_gelistirmesi") == 0){
                if(research_level == 1){
                    humanDefans = humanDeffensePower() * 1.1;
                }
                else if(research_level == 2){
                    humanDefans = humanDeffensePower() * 1.2;
                }
                else if(research_level == 3){
                    humanDefans = humanDeffensePower() * 1.3;
                }
            }
            //else if (strcmp(research_name2,"elit_egitim") == 0) {
            // ///////////////////////KRİTİK SANS//////////////
            // }
            else if (strcmp(research_name, "kusatma_ustaligi") == 0) {
                if (research_level == 1) {
                    kusatmaMakineleriAtak = calculateKusatmaMakineleriAttack() * 1.1;
                }
                else if (research_level == 2) {
                    kusatmaMakineleriAtak = calculateKusatmaMakineleriAttack() * 1.2;
                }
                else if (research_level == 3) {
                    kusatmaMakineleriAtak = calculateKusatmaMakineleriAttack() * 1.3;
                }
            }

            humanAtak = piyadeAtak + okcuAtak + suvariAtak + kusatmaMakineleriAtak;
            orkDefans = orkDovusculeriDefans + mizrakcilarDefans + vargBinicileriDefans + trollerDefans;
            //Yorgunluk kontrolu
            if (step % 5 == 0){
                humanAtak = humanAtak * 0.9;
                orkDefans = orkDefans * 0.9;
            }

            int nethasar = NetHasar(orkDefans, humanAtak);
            if (nethasar < 0) {
                nethasar = 0;
            }            
            int ork_dovusculeriHasar = 0;
            int mizrakcilarHasar = 0;
            int varg_binicileriHasar = 0;
            int trollerHasar = 0;
            int kalanHasar = 0;

            //Ork_Dovusculerı Savaşıyor
            ork_dovusculeriHasar = nethasar * (orkDovusculeriDefans / orkDefans);
            ork_dovusculeri_count -= olenBirimSayisi(ork_dovusculeriHasar, orkUnits[0].health);
            if (ork_dovusculeri_count < 0) {
                orkDefans -= orkDovusculeriDefans;
                orkDovusculeriDefans = 0;
                orkDovusculeriAtak = 0;
                kalanHasar = (ork_dovusculeriHasar - (ork_dovusculeri_count*orkUnits[0].health)) * -1;
                mizrakcilarHasar += kalanHasar * (mizrakcilarDefans / orkDefans);
                varg_binicileriHasar += kalanHasar * (vargBinicileriDefans / orkDefans);
                trollerHasar += kalanHasar * (trollerDefans / orkDefans);

                ork_dovusculeri_count = 0;
            }
            //Mizrakci Savasıyor
            mizrakcilarHasar += nethasar * (mizrakcilarDefans / orkDefans);
            mizrakcilar_count -= olenBirimSayisi(mizrakcilarHasar, orkUnits[1].health);
            if (mizrakcilar_count < 0) {
                orkDefans -= mizrakcilarDefans;
                mizrakcilarDefans = 0;
                kalanHasar = (mizrakcilarHasar - (mizrakcilar_count*orkUnits[1].health)) * -1;
                varg_binicileriHasar += kalanHasar * (vargBinicileriDefans / orkDefans);
                trollerHasar += kalanHasar * (trollerDefans / orkDefans);
                ork_dovusculeriHasar = kalanHasar * (orkDovusculeriDefans / orkDefans);
                
                mizrakcilar_count = 0;
            }
            //Varg Binicileri Savaşıyor
             varg_binicileriHasar += nethasar * (vargBinicileriDefans / orkDefans);
            
            varg_binicileri_count -= olenBirimSayisi(varg_binicileriHasar, orkUnits[2].health);
            if (varg_binicileri_count < 0) {
                orkDefans -= vargBinicileriDefans;
                vargBinicileriAtak = 0;
                vargBinicileriDefans = 0;
                kalanHasar = (varg_binicileriHasar - (varg_binicileri_count*orkUnits[2].health)) * -1;
                trollerHasar += kalanHasar * (trollerDefans / orkDefans);
                ork_dovusculeriHasar = kalanHasar * (orkDovusculeriDefans / orkDefans);
                mizrakcilarHasar = kalanHasar * (mizrakcilarDefans / orkDefans);

                varg_binicileri_count = 0;
            }
            //Troller Savaşıyor
            trollerHasar += nethasar * (trollerDefans / orkDefans);
            troller_count -= olenBirimSayisi(trollerHasar, orkUnits[3].health);
            if (troller_count < 0) {
                orkDefans -= trollerDefans;
                trollerAtak = 0;
                trollerDefans = 0;
                kalanHasar = (trollerHasar - (troller_count*orkUnits[3].health)) * -1;
                ork_dovusculeriHasar = kalanHasar * (orkDovusculeriDefans / orkDefans);
                mizrakcilarHasar = kalanHasar * (mizrakcilarDefans / orkDefans);
                varg_binicileriHasar = kalanHasar * (vargBinicileriDefans / orkDefans);                
    
                troller_count = 0;
            }



        }
        step++;
    }
    
    if (calculateHumanUnits() > 0)
    {
        printf("insan kazandı\n");
        return calculateHumanUnits();
    }
    else
    {
        printf("ork kazandı\n");
        return calculateOrkUnits();
    }
return 0;
}
