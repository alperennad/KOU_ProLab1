#ifndef JSON_PARSER_H
#define JSON_PARSER_H

// Unit yapısı
typedef struct {
    char name[20];
    int attack;
    int defense;
    int health;
    int criticalChance;
} Unit;

// Creatures
typedef struct {
    char name[20];
    char effectValue[10];
    char effectType[10];
    char description[100];
} Creature;

// Hero yapısı
typedef struct {
    char name[20];           // Kahraman adı
    char bonusType[20];     // Bonus türü (savunma, saldırı, vb.)
    char bonusValue[10];    // Bonus değeri
    char description[100];   // Açıklama
} Hero; // Hero[0].name --> ALPARSLAN

// Araştırma yapısı
typedef struct {
    char level[20];          // Araştırma seviyesi
    char value[10];          // Araştırma değeri
    char description[100];   // Açıklama
} SkillLevel;

typedef struct {
    char name[20];           // Yetenek adı
    SkillLevel levels[5];    // Yetenek seviyeleri
} Skill;


extern Creature humanCreatures[10];   // İnsan İmparatorluğu canavarları
extern Creature orkCreatures[10];     // Ork Lejyonu canavarları
extern int humanCreatureCount;        // İnsan İmparatorluğu canavar sayısı
extern int orkCreatureCount;          // Ork Lejyonu canavar sayısı

extern Unit humanUnits[10];
extern Unit orkUnits[10];
extern int humanCount;
extern int orkCount;

// Kahraman yapısı
extern Hero humanHeroes[10];          // İnsan İmparatorluğu kahramanları
extern Hero orkHeroes[10];            // Ork Lejyonu kahramanları
extern int humanHeroCount;            // İnsan İmparatorluğu kahraman sayısı
extern int orkHeroCount;              // Ork Lejyonu kahraman sayısı

extern Skill skills[10];   // Yetenek verileri
extern int skillCount;     // Yetenek sayısı

// Fonksiyonlar
void readFileAndParseCreatures(const char* filename);
void readFileAndParseHeroes(const char* filename); 
void readFileAndParseSkills(const char* filename);
void readFileAndParse(const char* filename);

#endif