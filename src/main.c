#include <stdio.h>
#include "json_parser.h"  // Birim ayrıştırma işlemleri için
#include "unit_counts.h"


int main() {
    // Birimleri JSON dosyasından ayrıştır
    readFileAndParse("../Files/unit_types.json");
     // Canavarları JSON dosyasından ayrıştır
    readFileAndParseCreatures("../Files/creatures.json");
    // Kahramanları JSON dosyasından ayrıştır
    readFileAndParseHeroes("../Files/heroes.json");
    // Yetenekleri JSON dosyasından ayrıştır
    readFileAndParseSkills("../Files/research.json");

    printf("Piyade sayısı: %d\n", piyadeler_count);

    return 0;
}