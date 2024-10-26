#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "url.h"
#include "battle_mechanics.h"


// Yanıt verisini tutmak için bir yapı
struct Response {
    char *data;
    size_t size;
};

// Yanıt verisini yazacak geri çağırma fonksiyonu
size_t WriteCallback(void *ptr, size_t size, size_t nmemb, struct Response *response) {
    size_t totalSize = size * nmemb;

    response->data = realloc(response->data, response->size + totalSize + 1);
    if (response->data == NULL) {
        fprintf(stderr, "Hafıza tahsisi hatası!\n");
        return 0;
    }

    memcpy(&(response->data[response->size]), ptr, totalSize);
    response->size += totalSize;
    response->data[response->size] = '\0';

    return totalSize;
}

int piyadeler_count = 0;
int okcular_count = 0;
int suvariler_count = 0;
int kusatma_makineleri_count = 0;
int ork_dovusculeri_count = 0;
int mizrakcilar_count = 0;
int troller_count = 0;
int varg_binicileri_count = 0;
int research_level = 0;
int research_level2 = 0;
char research_name2[50];
char research_name[50];
char heroName[50];
char heroName2[50];
char creatureName[50];
char creatureName2[50];

// Manuel JSON ayrıştırma fonksiyonu
void parseJSON(const char *jsonData) {
    char *ptr;

    ptr = strstr(jsonData, "\"piyadeler\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"piyadeler\": %d", &piyadeler_count);
    }
    ptr = strstr(jsonData, "\"okcular\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"okcular\": %d", &okcular_count);
    }
    ptr = strstr(jsonData, "\"suvariler\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"suvariler\": %d", &suvariler_count);
    }
    ptr = strstr(jsonData, "\"kusatma_makineleri\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"kusatma_makineleri\": %d", &kusatma_makineleri_count);
    }
    ptr = strstr(jsonData, "\"ork_dovusculeri\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"ork_dovusculeri\": %d", &ork_dovusculeri_count);
    }
    ptr = strstr(jsonData, "\"mizrakcilar\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"mizrakcilar\": %d", &mizrakcilar_count);
    }
    ptr = strstr(jsonData, "\"varg_binicileri\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"varg_binicileri\": %d", &varg_binicileri_count);
    }
    ptr = strstr(jsonData, "\"troller\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"troller\": %d", &troller_count);
    }

    ptr = strstr(jsonData, "\"insan_imparatorlugu\"");
    if (ptr != NULL) {
        ptr = strstr(ptr, "\"arastirma_seviyesi\"");
        if (ptr != NULL) {
            sscanf(ptr, "\"arastirma_seviyesi\": { \"%[^\"]\": %d", research_name, &research_level);
        }
    }
    goto ork_research;
    ork_research:
    ptr = strstr(jsonData, "\"ork_legi\"");
    if (ptr != NULL) {
        ptr = strstr(ptr, "\"arastirma_seviyesi\"");
        if (ptr != NULL) {
            sscanf(ptr, "\"arastirma_seviyesi\": { \"%[^\"]\": %d", research_name2, &research_level2);
        }
    }

    ptr = strstr(jsonData, "\"insan_imparatorlugu\"");
    if (ptr != NULL) {
        ptr = strstr(ptr, "\"kahramanlar\"");
        if (ptr != NULL) {
            sscanf(ptr, "\"kahramanlar\": [ \"%[^\"]", heroName);            
        }
    }
    goto ork_hero;
    ork_hero:
    ptr = strstr(jsonData, "\"ork_legi\"");
    if (ptr != NULL) {
        ptr = strstr(ptr, "\"kahramanlar\"");
        if (ptr != NULL) {
            sscanf(ptr, "\"kahramanlar\": [ \"%[^\"]", heroName2);            
        }
    }

    ptr = strstr(jsonData, "\"insan_imparatorlugu\"");
    if (ptr != NULL) {
        ptr = strstr(ptr, "\"canavarlar\"");
        if (ptr != NULL) {
            sscanf(ptr, "\"canavarlar\": [ \"%[^\"]", creatureName);            
        }
    }
    goto ork_creature;
    ork_creature:
    ptr = strstr(jsonData, "\"ork_legi\"");
    if (ptr != NULL) {
        ptr = strstr(ptr, "\"canavarlar\"");
        if (ptr != NULL) {
            sscanf(ptr, "\"canavarlar\": [ \"%[^\"]", creatureName2);            
        }
    }
}

// Veriyi almak ve ayrıştırmak için işlev
void fetchAndParseData(char *apiURL) {
    CURL *curl;
    CURLcode res;

    struct Response response;
    response.data = malloc(1);  //Boş bir veri tahsis et
    response.size = 0;

    curl = curl_easy_init();
    if (curl) {
        // URL'yi ayarla
        curl_easy_setopt(curl, CURLOPT_URL, apiURL);

        // Tarayıcıyı simüle etmek için kullanıcı aracısını belirleyin
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        // Yanıt verisini almak için geri çağırma fonksiyonunu ayarla
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);

        // HTTP isteğini yap
        res = curl_easy_perform(curl);

        // Hata kontrolü
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            parseJSON(response.data);
        }
        curl_easy_cleanup(curl);
    }
    free(response.data);
}

