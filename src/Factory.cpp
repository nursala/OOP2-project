#include "Factory.h"

Factory& Factory::instance() {
    static Factory inst;
    return inst;
}
