#include "Kontener.h"
#include <iostream>

Kontener::Kontener() : table(NULL),size(0),table_size(0) {};
Kontener::Kontener(const int& many) : size(0),table_size(many) { table = new Material*[many]; }
Kontener::Kontener(const Kontener& kontener) : size(kontener.size),table_size(kontener.table_size) {
    table = new Material*[kontener.table_size];
    for(int i=0;i < size; i++)
        table[i] = kontener.table[i];
}

Kontener::~Kontener(){
    delete[] table;
}

Kontener& Kontener::Dodaj( const Material& m){
    resize();
    table[ size++ ] = const_cast<Material*>(&m);//new Material( m );
    return *this;
}

void Kontener::resize(){
    if( table_size <= size ){//wielkosc tablicy a wielkosc to calkowicie inne sprawy.
        //Wielkosc tablicy to taki 'buffor' wprowadzany przez konstruktor Kontener(int many).
        Material ** temp_table = new Material*[size];
        for(int i=0;i < size; i++)
            temp_table[i] = table[i];
        delete table;
        table = temp_table;
        table_size++;
    }
}

void Kontener::print(){
    for(int i=0;i != size; i++){
        std::cout <<  i << ") ";
        table[i]->print();
    }
}
