#include <stdio.h>
#include "json_parser.h"  // Birim ayrıştırma işlemleri için
#include "url.h"
#include "battle_mechanics.h"


int main() {
    // Birimleri JSON dosyasından ayrıştır
    readFileAndParse("../Files/unit_types.json");
     // Canavarları JSON dosyasından ayrıştır
    readFileAndParseCreatures("../Files/creatures.json");
    // Kahramanları JSON dosyasından ayrıştır
    readFileAndParseHeroes("../Files/heroes.json");
    // Yetenekleri JSON dosyasından ayrıştır
    readFileAndParseSkills("../Files/research.json");

    char *apiURL = "https://yapbenzet.org.tr/1.json";
    fetchAndParseData(apiURL);  // Veriyi al ve ayrıştır

    
    battle();

}