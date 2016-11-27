#include "source.h"
#include "AllegroWrap.h"

int main()
{
    init_singltons();
    CAllegroWrap &inst = CAllegroWrap::instance();
    inst.run();
    return 0;
}
