#pragma once
#include "wled.h"
#include <my92xx.h>

#define MY9231_DI_PIN    5   // D1 на плате NodeMCU
#define MY9231_DCKI_PIN  4   // D2 на плате NodeMCU
#define MY9231_PIXEL_COUNT 100 

class UsermodMY9231 : public Usermod {
  private:
    my92xx* _my92xx = nullptr;
    bool initDone = false;
  public:
    void setup() {
      _my92xx = new my92xx(MY92XX_MODEL_MY9231, MY9231_PIXEL_COUNT, MY9231_DI_PIN, MY9231_DCKI_PIN);
      for (uint16_t i = 0; i < (MY9231_PIXEL_COUNT * 3); i++) {
        _my92xx->setChannel(i, 0);
      }
      _my92xx->update();
      initDone = true;
    }
    void loop() {
      if (!initDone || !_my92xx) return;
      for (uint16_t i = 0; i < MY9231_PIXEL_COUNT; i++) {
        uint32_t color = strip.getPixelColor(i); 
        uint8_t r = (color >> 16) & 0xFF;
        uint8_t g = (color >> 8)  & 0xFF;
        uint8_t b =  color        & 0xFF;
        uint16_t baseChannel = i * 3;
        _my92xx->setChannel(baseChannel + 0, r); 
        _my92xx->setChannel(baseChannel + 1, g); 
        _my92xx->setChannel(baseChannel + 2, b); 
      }
      _my92xx->update();
    }
};

// Автоматическая регистрация мода без редактирования других файлов
REGISTER_USERMOD(UsermodMY9231)
