#include <stdio.h>
#include "json_parser.h"
#include "url.h"
#include "battle_mechanics.h"
#include "graph.h"


int main() {
    // JSON dosyalarını ayrıştırır
    readFileAndParse("../Files/unit_types.json");
    readFileAndParseCreatures("../Files/creatures.json");
    readFileAndParseHeroes("../Files/heroes.json");
    readFileAndParseSkills("../Files/research.json");

    // İnternet üzerinden istenilen senaryo verilerini çeker
    char *apiURL = "https://yapbenzet.org.tr/10.json";
    fetchAndParseData(apiURL);

    HealthCheck(piyadeler_count, okcular_count, suvariler_count, kusatma_makineleri_count, ork_dovusculeri_count, mizrakcilar_count, varg_binicileri_count, troller_count);
    struct Human human = {piyadeler_count, okcular_count, suvariler_count, kusatma_makineleri_count, heroName, creatureName};
    struct Ork ork = {ork_dovusculeri_count, mizrakcilar_count, varg_binicileri_count, troller_count, heroName2, creatureName2};
    Game(&human, &ork);

    battle();

    struct Human human2 = {piyadeler_count, okcular_count, suvariler_count, kusatma_makineleri_count, heroName, creatureName};
    struct Ork ork2 = {ork_dovusculeri_count, mizrakcilar_count, varg_binicileri_count, troller_count, heroName2, creatureName2};
    Game(&human2, &ork2);
}