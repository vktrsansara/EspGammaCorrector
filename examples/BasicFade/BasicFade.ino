// -- YourSketchName.ino --

#include <Adafruit_NeoPixel.h>
#include "GammaCorrector.h" // Просто подключаем наш заголовочный файл

#define PIN D4
#define NUMPIXELS 60

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Создаем глобальный объект нашего класса.
// Конструктор вызовется автоматически.
GammaCorrector gamma; 

void setup() {
  Serial.begin(115200);
  strip.begin();
  
  // Инициализируем таблицу. Теперь это выглядит очень аккуратно.
  gamma.begin(2.8); 
  
  strip.show();
  Serial.println("Setup complete. Gamma table created.");
}

void loop() {
  Serial.println("Fading red up...");
  for (int i = 0; i <= 255; i++) {
    strip.setPixelColor(0, gamma.correct(i, 0, 0));
    strip.show();
    delay(5);
  }

  Serial.println("Fading red down...");
  for (int i = 255; i >= 0; i--) {
    strip.setPixelColor(0, gamma.correct(i, 0, 0));
    strip.show();
    delay(5);
  }
}