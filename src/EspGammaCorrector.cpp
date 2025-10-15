// -- GammaCorrector.cpp --

#include "GammaCorrector.h" // Подключаем наш заголовочный файл
#include <math.h>          // Подключаем математическую библиотеку для функции pow()

// Реализация конструктора
GammaCorrector::GammaCorrector() : gammaTable(nullptr) {
  // Тело конструктора пустое, вся инициализация происходит в списке инициализации (: gammaTable(nullptr))
}

// Реализация деструктора
GammaCorrector::~GammaCorrector() {
  // Проверяем, была ли выделена память, и если да - освобождаем ее
  if (gammaTable != nullptr) {
    delete[] gammaTable;
  }
}

// Реализация метода begin
void GammaCorrector::begin(float gammaValue) {
  // Если таблица уже была создана ранее, удаляем старую, чтобы избежать утечек памяти
  if (gammaTable != nullptr) {
    delete[] gammaTable;
    gammaTable = nullptr; // Хорошая практика - обнулять указатель после удаления
  }
  
  // Выделяем 256 байт в оперативной памяти (на "куче")
  gammaTable = new uint8_t[256];

  // Если память не выделилась (крайне редкий случай на ESP), выходим
  if (gammaTable == nullptr) {
    return;
  }

  // Заполняем таблицу вычисленными значениями
  for (int i = 0; i < 256; i++) {
    gammaTable[i] = (uint8_t)(pow((float)i / 255.0, gammaValue) * 255.0 + 0.5);
  }
}

// Реализация метода correct для одного канала
uint8_t GammaCorrector::correct(uint8_t value) {
  // Если таблица не инициализирована (не был вызван begin()),
  // возвращаем исходное значение, чтобы избежать сбоя
  if (gammaTable == nullptr) {
    return value; 
  }
  return gammaTable[value];
}

// Реализация метода correct для трех каналов
uint32_t GammaCorrector::correct(uint8_t r, uint8_t g, uint8_t b) {
  // Проверяем инициализацию
  if (gammaTable == nullptr) {
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
  }
  
  // Берем скорректированные значения из таблицы
  uint8_t gr = gammaTable[r];
  uint8_t gg = gammaTable[g];
  uint8_t gb = gammaTable[b];
  
  // Собираем 32-битное число
  return ((uint32_t)gr << 16) | ((uint32_t)gg << 8) | gb;
}