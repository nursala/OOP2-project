#include "Factory.h"

//-------------------------------------
// Factory Singleton Instance
Factory& Factory::instance() {
    static Factory inst;
    return inst;
}
