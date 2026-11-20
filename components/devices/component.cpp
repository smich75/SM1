#include "component.h"

Component::Component() {
    parent=NULL;
    unit=0;
}

Component::Component(Device *p, int32_t u) {
    parent=p;
    unit=u;
}

Component::~Component() {
}