#pragma once

#include <Arduino.h>

namespace CDEM {

  class SuccessPage {

    public:
      static String render(void) {
        return "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><title>CDEM</title></head><body><body style=\"background-color:#39b54a\"><svg style=\"background-color:#fff\" viewBox=\"0 0 128 128\" xmlns=\"http://www.w3.org/2000/svg\"><path d=\"m0 0v128h128v-128h-128zm60.137 112.85-45.173-45.322 11.146-12.483 30.383 30.243 43.545-68.88 14.022 10.282-53.923 86.16z\" fill=\"#39B54A\"/></svg></body></body></html>";
      }

  };

};