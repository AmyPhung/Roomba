#ifndef msgs_h
#define msgs_h

#include <Arduino.h>

struct TwistMsg : public Printable {
  int linear;
  int angular;

  size_t printTo(Print& p) const {
    
    size_t r = 0;

    r += p.print("Linear: ");
    r += p.print(linear);
    r += p.print(" | ");
    r += p.print("Angular: ");
    r += p.print(angular);
    return r;
 }
};

#endif
