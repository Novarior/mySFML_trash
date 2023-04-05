#include "Core.h"

int main()
{
    std::fstream ff;
    ff.open("file.txt");
    ff<<"i'm here";
    ff.close();
    std::cout << ff.getloc().global();

    Core mc;
    mc.run();
    return 0;
}
