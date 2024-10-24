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


// Global diziler ve sayaçlar
extern Creature humanCreatures[10];   // İnsan İmparatorluğu canavarları
extern Creature orkCreatures[10];     // Ork Lejyonu canavarları
extern int humanCreatureCount;        // İnsan İmparatorluğu canavar sayısı
extern int orkCreatureCount;          // Ork Lejyonu canavar sayısı

// Diziler ve sayaçlar
extern Unit humanUnits[10];
extern Unit orkUnits[10];
extern int humanCount;
extern int orkCount;

// Kahraman yapısı
extern Hero humanHeroes[10];          // İnsan İmparatorluğu kahramanları
extern Hero orkHeroes[10];            // Ork Lejyonu kahramanları
extern int humanHeroCount;            // İnsan İmparatorluğu kahraman sayısı
extern int orkHeroCount;              // Ork Lejyonu kahraman sayısı

//Yetenek Dizi ve Sayac
extern Skill skills[10];   // Yetenek verileri
extern int skillCount;     // Yetenek sayısı

// Fonksiyonlar
void parseUnit(const char* line, Unit* unit);
void readFileAndParseCreatures(const char* filename);  // Canavarları JSON dosyasından ayrıştırır
void readFileAndParseHeroes(const char* filename); 
void readFileAndParseSkills(const char* filename);  // Yetenekleri JSON dosyasından ayrıştırır
void readFileAndParse(const char* filename);

#endif