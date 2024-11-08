#include <stdio.h>
#include <string.h>
#include "json_parser.h"
#include "battle_mechanics.h"

Unit humanUnits[10];  // İnsan İmparatorluğu birimleri
Unit orkUnits[10];    // Ork Lejyonu birimleri
int humanCount = 0;   // İnsan İmparatorluğu birim sayısı
int orkCount = 0;     // Ork Lejyonu birim sayısı
Hero humanHeroes[10];      // İnsan İmparatorluğu kahramanları
Hero orkHeroes[10];        // Ork Lejyonu kahramanları
int humanHeroCount = 0;    // İnsan İmparatorluğu kahraman sayısı
int orkHeroCount = 0;      // Ork Lejyonu kahraman sayısı
Creature humanCreatures[10];  // İnsan İmparatorluğu canavarları
Creature orkCreatures[10];    // Ork Lejyonu canavarları
int humanCreatureCount = 0;   // İnsan İmparatorluğu canavar sayısı
int orkCreatureCount = 0;     // Ork Lejyonu canavar sayısı
Skill skills[10];
int skillCount = 0; 

// Birim verisini ayrıştıran fonksiyon
void parseUnit(const char* line, Unit* unit) {
    if (strstr(line, "\"saldiri\"")) {
        sscanf(line, " \"saldiri\" : %d", &unit->attack);
    } else if (strstr(line, "\"savunma\"")) {
        sscanf(line, " \"savunma\" : %d", &unit->defense);
    } else if (strstr(line, "\"saglik\"")) {
        sscanf(line, " \"saglik\" : %d", &unit->health);
    } else if (strstr(line, "\"kritik_sans\"")) {
        sscanf(line, " \"kritik_sans\" : %d", &unit->criticalChance);
    }
}

// JSON dosyasını okuyup ayrıştıran ana fonksiyon
void readFileAndParse(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return;
    }

    char line[256];
    Unit currentUnit;
    int isUnitActive = 0;  // Yeni bir birim başladığında 1 olacak
    char unitName[50];
    int isHuman = 1;  // İnsan İmparatorluğu için başlangıç

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"insan_imparatorlugu\"")) {
            isHuman = 1;  // İnsan İmparatorluğu birimleri
        } else if (strstr(line, "\"ork_legi\"")) {
            isHuman = 0;  // Ork Lejyonu birimleri
        } else if (strstr(line, "\"piyadeler\"") || strstr(line, "\"okcular\"") || strstr(line, "\"suvariler\"") || strstr(line, "\"kusatma_makineleri\"") ||
                   strstr(line, "\"ork_dovusculeri\"") || strstr(line, "\"mizrakcilar\"") || strstr(line, "\"varg_binicileri\"") || strstr(line, "\"troller\"")) {
            // Eğer daha önce bir birim işleniyorsa, o birimi ekle
            if (isUnitActive) {
                if (isHuman) {
                    humanUnits[humanCount++] = currentUnit;
                } else {
                    orkUnits[orkCount++] = currentUnit;
                }
            }

            // Yeni bir birim başlıyor, özelliklerini sıfırla
            sscanf(line, " \"%[^\"]\"", unitName);
            strcpy(currentUnit.name, unitName);
            isUnitActive = 1;  // Yeni bir birim aktif
        } else if (strstr(line, "}")) {
            // Birim tamamlandı, dizilere ekle
            if (isUnitActive) {
                if (isHuman) {
                    humanUnits[humanCount++] = currentUnit;
                } else {
                    orkUnits[orkCount++] = currentUnit;
                }
                isUnitActive = 0;  // Birim tamamlandı, aktiflik bitti
            }
        } else {
            // Birim özelliklerini ayrıştır
            parseUnit(line, &currentUnit);
        }
    }

    // Son birim işleniyorsa onu da ekle
    if (isUnitActive) {
        if (isHuman) {
            humanUnits[humanCount++] = currentUnit;
        } else {
            orkUnits[orkCount++] = currentUnit;
        }
    }

    fclose(file);
}

void parseCreature(const char* line, Creature* creature) {
    if (strstr(line, "\"etki_degeri\"")) {
        sscanf(line, " \"etki_degeri\": \"%[^\"]\"", creature->effectValue);
    } else if (strstr(line, "\"etki_turu\"")) {
        sscanf(line, " \"etki_turu\": \"%[^\"]\"", creature->effectType);
    } else if (strstr(line, "\"aciklama\"")) {
        sscanf(line, " \"aciklama\": \"%[^\"]\"", creature->description);
    }
}

void readFileAndParseCreatures(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return;
    }

    char line[256];
    Creature currentCreature;
    int isUnitActive = 0;
    char creatureName[50];
    int isHuman = 1;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"insan_imparatorlugu\"")) {
            isHuman = 1;
        } else if (strstr(line, "\"ork_legi\"")) {
            isHuman = 0;
        } else if (strstr(line, "\"Ejderha\"") || strstr(line, "\"Agri_Dagi_Devleri\"") || 
                   strstr(line, "\"Tepegoz\"") || strstr(line, "\"Karakurt\"") ||
                   strstr(line, "\"Samur\"") || strstr(line, "\"Kara_Troll\"") ||
                   strstr(line, "\"Golge_Kurtlari\"") || strstr(line, "\"Camur_Devleri\"") ||
                   strstr(line, "\"Ates_Iblisi\"") || strstr(line, "\"Makrog_Savas_Beyi\"") ||
                   strstr(line, "\"Buz_Devleri\"")) {
            if (isUnitActive) {
                if (isHuman) {
                    humanCreatures[humanCreatureCount++] = currentCreature;
                } else {
                    orkCreatures[orkCreatureCount++] = currentCreature;
                }
            }
            sscanf(line, " \"%[^\"]\"", creatureName);
            strcpy(currentCreature.name, creatureName);
            isUnitActive = 1;
        } else if (strstr(line, "}")) {
            if (isUnitActive) {
                if (isHuman) {
                    humanCreatures[humanCreatureCount++] = currentCreature;
                } else {
                    orkCreatures[orkCreatureCount++] = currentCreature;
                }
                isUnitActive = 0;
            }
        } else {
            parseCreature(line, &currentCreature);
        }
    }
    if (isUnitActive) {
        if (isHuman) {
            humanCreatures[humanCreatureCount++] = currentCreature;
        } else {
            orkCreatures[orkCreatureCount++] = currentCreature;
        }
    }
    fclose(file);
}

void parseHero(const char* line, Hero* hero) {
    if (strstr(line, "\"bonus_turu\"")) {
        sscanf(line, " \"bonus_turu\": \"%[^\"]\"", hero->bonusType);
    } else if (strstr(line, "\"bonus_degeri\"")) {
        sscanf(line, " \"bonus_degeri\": \"%[^\"]\"", hero->bonusValue);
    } else if (strstr(line, "\"aciklama\"")) {
        sscanf(line, " \"aciklama\": \"%[^\"]\"", hero->description);
    }
}

void readFileAndParseHeroes(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return;
    }

    char line[256];
    Hero currentHero;
    char heroName[50];
    int isHeroActive = 0;
    int isHuman = 1;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"insan_imparatorlugu\"")) {
            isHuman = 1;
        } else if (strstr(line, "\"ork_legi\"")) {
            isHuman = 0;
        } else if (strstr(line, "\"Alparslan\"") || strstr(line, "\"Fatih_Sultan_Mehmet\"") || 
                   strstr(line, "\"Mete_Han\"") || strstr(line, "\"Yavuz_Sultan_Selim\"") || 
                   strstr(line, "\"Tugrul_Bey\"") || strstr(line, "\"Goruk_Vahsi\"") || 
                   strstr(line, "\"Thruk_Kemikkiran\"") || strstr(line, "\"Vrog_Kafakiran\"") || 
                   strstr(line, "\"Ugar_Zalim\"")) {
            if (isHeroActive) {
                if (isHuman) {
                    humanHeroes[humanHeroCount++] = currentHero;
                } else {
                    orkHeroes[orkHeroCount++] = currentHero;
                }
            }
            sscanf(line, " \"%[^\"]\"", heroName);
            strcpy(currentHero.name, heroName);
            isHeroActive = 1;
        } else if (strstr(line, "}")) {
            if (isHeroActive) {
                if (isHuman) {
                    humanHeroes[humanHeroCount++] = currentHero;
                } else {
                    orkHeroes[orkHeroCount++] = currentHero;
                }
                isHeroActive = 0;
            }
        } else {
            parseHero(line, &currentHero);
        }
    }
    if (isHeroActive) {
        if (isHuman) {
            humanHeroes[humanHeroCount++] = currentHero;
        } else {
            orkHeroes[orkHeroCount++] = currentHero;
        }
    }
    fclose(file);
}

 void parseSkillLevel(const char* line, SkillLevel* level) {
    if (strstr(line, "\"deger\"")) {
        sscanf(line, " \"deger\": \"%[^\"]\"", level->value);
    } else if (strstr(line, "\"aciklama\"")) {
        sscanf(line, " \"aciklama\": \"%[^\"]\"", level->description);
    }
}

void readFileAndParseSkills(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Dosya açılamadı: %s\n", filename);
        return;
    }

    char line[256];
    Skill currentSkill;
    int levelIndex = 0;
    memset(&currentSkill, 0, sizeof(currentSkill));
    int isSkillActive = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"savunma_ustaligi\"") || strstr(line, "\"saldiri_gelistirmesi\"") || 
            strstr(line, "\"elit_egitim\"") || strstr(line, "\"kusatma_ustaligi\"")) {
            if (isSkillActive) {
                skills[skillCount++] = currentSkill;
                memset(&currentSkill, 0, sizeof(currentSkill));
            }
            sscanf(line, " \"%[^\"]\"", currentSkill.name);
            levelIndex = 0;
            isSkillActive = 1;
        } else if (strstr(line, "seviye_1") || strstr(line, "seviye_2") || strstr(line, "seviye_3")) {
            sscanf(line, " \"%[^\"]\": {", currentSkill.levels[levelIndex].level);
        } else if (strstr(line, "}")) {
            if (isSkillActive && levelIndex < 3) {
                levelIndex++;
            }
        } else {
            parseSkillLevel(line, &currentSkill.levels[levelIndex]);
        }
    }
    if (isSkillActive) {
        skills[skillCount++] = currentSkill;
    }
    fclose(file);
}