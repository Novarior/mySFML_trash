#include "Core.h"
int main ()
{
    Core mc;
    //mc.run();
    std::string s = "aba";
    std::string ms = "Simple variable of a string";
    std::cout << "\nsize string: "<<ms.size()<<'\t'
              << "leght string: "<<ms.length()<<'\n';
    for(int i=0; i<ms.length();i++)
        if(ms[i]=='a')
             ms.replace(i,1,"аbф");

    std::cout << '\t'<<ms;
    std::cout << "\nsize string: "<<ms.size()<<'\t'
              << "leght string: "<<ms.length()<<'\n';


    return 0;
} 