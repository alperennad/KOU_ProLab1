// 1 - ) SALDIRI GÜCÜNÜN HESAPLANMASI 
//     Saldırı Gucu = Birim başına Saldırı Gucu * Birim Sayısı

// 2 - ) SAVUNMA GÜCÜNÜN HESAPLANMASI
//     Savunma Gucu = Birim başına Savunma Gucu * Birim Sayısı

// 3 - ) Kritik Vuruş Şansının Hesaplanması
//      Kritik Vuruş Sayısı = 1 / kritik_sans
//      Kritik vurus her x saldirida bir yapilir. x = Saldırı Sayısı

// 1. Okçular (%10 kritik şansı):
//  Kritik Vuruş Oranı: %10 (her 10 saldırıda 1 kere kritik vuruş yapar).
//  Saldırı Gücü: 500 okçu, her biri 40 saldırı gücüne sahipse:
//  Toplam Saldırı Gücü: 500 * 40 = 20,000
//  Kritik Vuruş: Her 10. saldırıda kritik vuruş gerçekleşir.
//  Net Hasar (Kritik Vuruş Olmadan): 20,000
//  Net Hasar (Kritik Vuruşla): 20,000 * 1.5 = 30,000
//  Örnek: 10. saldırıda kritik vuruş yapılır, net hasar 30,000 olur.

