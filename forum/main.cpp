#include "Kontener.h"
#include "Spec_Sort.h"
#include "Fotopomiler.h"
#include "Wosk.h"
#include "Odczynnik_Chemiczny.h"
#include <iostream>
#include <vector>

using namespace std;

Kolor funkWart(Kolor a){
    Kolor b;
    Kolor c = a;
    b = a;
    return b;
}

Kolor funkIter (Kolor *a){
    Kolor b;
    Kolor c = *a;
    b = *a;
    return *a;
}

Kolor & funkRef (Kolor &a){
    Kolor b;
    Kolor c = a;
    b = a;
    return a;
}

void test_TString(){
    TString Q("Test");
    TString QQ('A',10);
    ++QQ;
    QQ++;
    cout << Q << '#' << QQ << ' ' << (Q > QQ) << endl;
    Q = "sdfsdf";
    Q.print();
    Q = QQ;
    Q.print();
    cout << "Napisz coś" << std::endl;
    cin >> Q;
    cout << Q << endl;
}

void test_Kolor_Material(){
    Kolor kolor("Czarny");
    kolor.print();
    Kolor kolor2(0,0,0, "Czarny");
    Kolor kolor3(0,0,0);
    Material m1( TString("Test") );
    Material m2( TString("Test"), Kolor(25,25,100) );
    m1.print();
    m2.print();
}

void test_Ref(){
    Kolor aa("Testtest");
    cout << "funkWart" << endl;
    funkWart(aa);
    cout << "funkIter" << endl;
    funkIter(&aa);
    cout << "funkRef" << endl;
    funkRef(aa);
}

void test_Inheritance_Material(){
    Fotopomiler testA;
    Wosk testB;
    Odczynnik_Chemiczny testC;

    testA.print();
    testB.print();
    testC.print();
}

void test_Specyfikacja(){
    Specyfikacja test;

    test.put( Komunikat( 25, "TEST" ) )
        .put( Komunikat( 5, "TEST2" ) )
        .put( Komunikat( 5, "TEST5" ) );
    cout << " ---" << endl;
    Specyfikacja  testB( test );

    testB.print();
    cout << " ---" << endl;
    test.print();
    cout << " ---" << endl;
    --test;
    testB = test;
    testB.print();
    cout << " ---" << endl;
    test.print();
}

void test_Spec_Sort(){
    Spec_Sort test;
    Specyfikacja spec;

    test.put( Komunikat(200,"TESTA") )
        .put( Komunikat(100,"TESTB") )
        .put( Komunikat(100,"TESTA") )
        .put( Komunikat(200,"TESTD") );
    cout << test << "Ilosc: " << (int)test  << endl;

    spec.put( Komunikat(200,"TESTA") )
        .put( Komunikat(100,"TESTA") )
        .put( Komunikat(300,"TESTC") )
        .print();

    --test;
    test -= spec;
    test.print();
    cout << "Ilosc: " << (int)test << endl;

    test = spec;
    test.print();

}

void test_Spec_Sort2(){
    Spec_Sort test;
    Spec_Sort kopia;
    test.wstaw( Komunikat(200,"TESTK") , 50 )
        .put( Komunikat(200,"TESTA") )
        .put( Komunikat(100,"TESTB") )
        .put( Komunikat(100,"TESTA") )
        .put( Komunikat(150,"TESTD") )
        .wstaw( Komunikat(100,"TESTF") , 200 )
        .wstaw( Komunikat(200,"TESTZ") , 100 )
        .put( Komunikat(50,"TESTE") );

    test.print();
    cout << "##----------" << endl;
    kopia = test.cut( 100 , 4 );
    kopia.print();
    cout << "----------" << endl;
    kopia = test.cut(99,4);
    kopia.print();
    cout << "----------" << endl;
    kopia = test.past(100);
    kopia.print();
    cout << "----------" << endl;
    kopia = test.past(99);
    kopia.print();
}

void test_Kontener(){
    Kontener kontener;
    Material m;
    Wosk w;
    {
        Fotopomiler f;
        kontener.Dodaj(m)
                .Dodaj(w)
                .Dodaj(f);
    }


    kontener.print();
}

int main(){
    bool quit(false);
    while( !quit ){

        cout <<
        "Wpisz liczbe" << endl <<
        "0) Wyjdz" << endl <<
        "1) Test TString" << endl <<
        "2) Test Kolor&Material" << endl <<
        "3) Test Referencji" << endl <<
        "4) Test Dziedziczenia materialow" << endl <<
        "5) Test Specyfikacji" << endl <<
        "6) Test Spec_Sort" << endl <<
        "7) Test Spec_Sort ( cw 5 )" << endl <<
        "8) Test Kontener" << endl;

        int liczba;
        cin >> liczba;
        cout << endl;
        switch(liczba){
            case 0: quit = true; break;
            case 1: test_TString(); break;
            case 2: test_Kolor_Material(); break;
            case 3: test_Ref(); break;
            case 4: test_Inheritance_Material(); break;
            case 5: test_Specyfikacja(); break;
            case 6: test_Spec_Sort(); break;
            case 7: test_Spec_Sort2(); break;
            case 8: test_Kontener(); break;
        }
    }
}
