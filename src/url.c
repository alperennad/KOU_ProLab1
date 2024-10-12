#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

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
        return 0;  // Hata durumunda geri döndür
    }

    memcpy(&(response->data[response->size]), ptr, totalSize);
    response->size += totalSize;
    response->data[response->size] = '\0';  // Null-terminating

    return totalSize;
}

// Global değişkenler
int piyadeler_count = 0;
int okcular_count = 0;
int suvariler_count = 0;
int kusatma_makineleri_count = 0;
int ork_dovusculeri_count = 0;
int mizrakcilar_count = 0;
int troller_count = 0;
int varg_binicileri_count = 0;

// Manuel JSON ayrıştırma fonksiyonu
void parseJSON(const char *jsonData) {
    char *ptr;

    // Piyadeler sayısını al
    ptr = strstr(jsonData, "\"piyadeler\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"piyadeler\": %d", &piyadeler_count);
        printf("Piyadeler sayısı: %d\n", piyadeler_count);
    }

    // Okçular sayısını al
    ptr = strstr(jsonData, "\"okcular\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"okcular\": %d", &okcular_count);
        printf("Okçular sayısı: %d\n", okcular_count);
    }

    // Süvariler sayısını al
    ptr = strstr(jsonData, "\"suvariler\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"suvariler\": %d", &suvariler_count);
        printf("Süvariler sayısı: %d\n", suvariler_count);
    }

    // Kuşatma makineleri sayısını al
    ptr = strstr(jsonData, "\"kusatma_makineleri\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"kusatma_makineleri\": %d", &kusatma_makineleri_count);
        printf("Kuşatma Makineleri sayısı: %d\n", kusatma_makineleri_count);
    }

    // Ork Lejyonu Birimleri
    ptr = strstr(jsonData, "\"ork_dovusculeri\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"ork_dovusculeri\": %d", &ork_dovusculeri_count);
        printf("Ork dövüşçüleri sayısı: %d\n", ork_dovusculeri_count);
    }

    ptr = strstr(jsonData, "\"mizrakcilar\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"mizrakcilar\": %d", &mizrakcilar_count);
        printf("Mızrakçılar sayısı: %d\n", mizrakcilar_count);
    }

    ptr = strstr(jsonData, "\"varg_binicileri\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"varg_binicileri\": %d", &varg_binicileri_count);
        printf("Varg binicileri sayısı: %d\n", varg_binicileri_count);
    }

    ptr = strstr(jsonData, "\"troller\"");
    if (ptr != NULL) {
        sscanf(ptr, "\"troller\": %d", &troller_count);
        printf("Troller sayısı: %d\n", troller_count);
    }
}

int main(void) {
    CURL *curl;
    CURLcode res;

    struct Response response;
    response.data = malloc(1);  // İlk başta boş bir veri tahsis et
    response.size = 0;          // Başlangıç boyutu

    // CURL başlat
    curl = curl_easy_init();
    if (curl) {
        // URL'yi ayarla
        curl_easy_setopt(curl, CURLOPT_URL, "https://yapbenzet.org.tr/2.json");

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
            // JSON verisini manuel olarak ayrıştır
            parseJSON(response.data);
        }

        // CURL temizle
        curl_easy_cleanup(curl);
    }

    // Kullanılmayan belleği serbest bırak
    free(response.data);

    return 0;
}
