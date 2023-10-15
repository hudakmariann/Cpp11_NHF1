/*
Felhasznalt segedanyagok:
    https://prog2.cppftw.org/ea03/#3
    https://cpp11.eet.bme.hu/ea07/#4
    https://cpp11.eet.bme.hu/nhf/
*/

#include <iostream>
#include "mystring.h"

MyString& kiir(MyString& x){
std::cout << "kiir_ref x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;
return x;
}

MyString kiir2(MyString x){
std::cout << "kiir_copy x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;
return x;
}
MyString kiir3(MyString&& x){
std::cout << "kiir_move x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;
return x;
}

int main() {

    MyString s1, s2;
    std::cin >> s1 >> s2;

    std::cout << "s1 + s2 = " << s1 + s2 << std::endl;

    s2 += s1;
    std::cout << "s2 + s1 = " << s2 << std::endl;

    const MyString s3 = "Teszt"; //Konstans string tesztelese [] operatorhoz
    std::cout << s3[2] << std::endl;;

    MyString a("A"), b("B"), c("C");
    std::cout << a << " " << b << " " << c << std::endl;
    a = b = c;
    std::cout << a << " " << b << " " << c << std::endl;
    MyString x;
    std::cout << "x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;
    x = "hello";
    std::cout << "x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;
    MyString y = x;
    std::cout << "x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;

    y[0] = 'c';
    MyString z(x);
    std::cout << "x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;     /* hello */
    std::cout << "y= " <<  y << ", y refcount= "  << y.getRefCount() <<std::endl;     /* cello */
    z[0] = 'a';
    std::cout << "z= " <<  z <<  ", x refcount= "  << z.getRefCount() <<std::endl;
    std::cout << "x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;

    MyString q = kiir(x);
    MyString r(kiir(x));

    MyString j;  //igy mukodik sima masolassal, nem referencia
    j = kiir2(x);

    //MyString k = kiir2(x); //Igy viszont "Segmentation fault." futas kozben. Miert???
    //MyString l(kiir2(x)); //szinten! Miert?


    MyString s(kiir3(" world "));
    std::cout << "x = " << x <<  ", x refcount= "  << x.getRefCount() << std::endl;
    //std::cout << "r = " << r <<  ", r refcount= "  << r.getRefCount() << std::endl;
    return 0;
}
