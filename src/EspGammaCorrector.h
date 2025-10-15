// -- GammaCorrector.h --

#pragma once // Стандартная защита от двойного включения заголовочного файла

#include <Arduino.h> // Для типов uint8_t, uint32_t

class GammaCorrector {
public:
  // Конструктор: вызывается при создании объекта
  GammaCorrector();

  // Деструктор: вызывается при уничтожении объекта для освобождения памяти
  ~GammaCorrector();

  /**
   * @brief Инициализирует таблицу гамма-коррекции.
   * @param gammaValue Значение гаммы (например, 2.8 для LED, 2.2 для дисплеев).
   */
  void begin(float gammaValue = 2.8);

  /**
   * @brief Применяет гамма-коррекцию к одному 8-битному значению.
   * @param value Входное значение яркости (0-255).
   * @return Скорректированное значение яркости (0-255).
   */
  uint8_t correct(uint8_t value);

  /**
   * @brief Применяет гамма-коррекцию к трем каналам цвета.
   * @param r Красный канал (0-255).
   * @param g Зеленый канал (0-255).
   * @param b Синий канал (0-255).
   * @return 32-битное значение цвета в формате для NeoPixel.
   */
  uint32_t correct(uint8_t r, uint8_t g, uint8_t b);

private:
  // Указатель на наш динамический массив в RAM.
  // Изначально он никуда не указывает (nullptr).
  uint8_t* gammaTable;
};