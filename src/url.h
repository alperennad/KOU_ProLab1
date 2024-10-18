#ifndef URL_H
#define URL_H

void parseJSON(const char *jsonData);

// Global değişkenler
extern int piyadeler_count;
extern int okcular_count;
extern int suvariler_count;
extern int kusatma_makineleri_count;
extern int ork_dovusculeri_count;
extern int mizrakcilar_count;
extern int troller_count;
extern int varg_binicileri_count;
extern int research_level;
extern int research_level2;
extern char research_name[50];
extern char research_name2[50];
extern char kahramanlar[5][50]; // Maksimum 5 kahraman, her biri 50 karakter uzunluğunda
extern int kahraman_sayisi;
extern char canavarlar[5][50]; // Maksimum 5 canavar, her biri 50 karakter uzunluğunda
extern int canavar_sayisi;
extern char heroName[50];
extern char heroName2[50];
extern char creatureName[50];
extern char creatureName2[50];

void fetchAndParseData(char *apiURL);


#endif