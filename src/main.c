#include <stdio.h>
#include "json_parser.h"  // Birim ayrıştırma işlemleri için
#include "url.h"
#include "battle_mechanics.h"
#include "graph.h"


int main() {
    // Birimleri JSON dosyasından ayrıştır
    readFileAndParse("../Files/unit_types.json");
     // Canavarları JSON dosyasından ayrıştır
    readFileAndParseCreatures("../Files/creatures.json");
    // Kahramanları JSON dosyasından ayrıştır
    readFileAndParseHeroes("../Files/heroes.json");
    // Yetenekleri JSON dosyasından ayrıştır
    readFileAndParseSkills("../Files/research.json");

    char *apiURL = "https://yapbenzet.org.tr/3.json";
    fetchAndParseData(apiURL);  // Veriyi al ve ayrıştır

    struct Human human = {piyadeler_count, okcular_count, suvariler_count, kusatma_makineleri_count, heroName, creatureName};
    struct Ork ork = {ork_dovusculeri_count, mizrakcilar_count, varg_binicileri_count, troller_count, heroName2, creatureName2};
    //StartScreen();
    Game(&human, &ork);
    battle();
    struct Human human2 = {piyadeler_count, okcular_count, suvariler_count, kusatma_makineleri_count, heroName, creatureName};
    struct Ork ork2 = {ork_dovusculeri_count, mizrakcilar_count, varg_binicileri_count, troller_count, heroName2, creatureName2};
    Game(&human2, &ork2);
}