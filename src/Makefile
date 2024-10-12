# Değişkenler
CC = gcc
CURL_FLAGS = -lcurl

# Hedefler
all: url

# url hedefi
url: url.c
	$(CC) -o url url.c $(CURL_FLAGS)

# Temizleme komutu
clean:
	rm -rf url