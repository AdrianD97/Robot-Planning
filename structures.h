// Copyright 2018 Stefan Adrian

#ifndef _STRUCTURES_H

#define _STRUCTURES_H
#include<string>

// primele trei structuri descriu tipurile particulare cu care vom popula structurile de tip
 // coada si stiva

 // descrie structura unei comenzi

struct comanda
{
    std::string tip_comanda;  // GET sau DROP
    int x, y;  // coordonatele celulei
    int nr_cuti;  // numarul de cutii pe care trebuie sa-l ia/puna robotul in celula
};

// descrie continutul unui nod din coada

struct data
{
    comanda C;
    int timp;  // va reprezenta momentul adaugarii comenzii in coada
};

union help
{
    int timp;  // timpul cat timp a stat comanda respectiva in coada robotului
               // acest camp va fi folosit pentru stiva care contine comenzile executate
    int prioritate;  // prioritate comenzii. acest camp va fi utilizat de stiva care contine comenzile de tip ADD
};

// descrie un element din stiva

struct undo
{
    int id_robot;  // id-ul robotului
    comanda C;
    help H;
    int ordine;  // numarul de ordine al comenzii din istoric
};

// structura urmatoare descrie un nod al unei cozi generice

template<class T> struct nod
{
    T info;
    nod* next;
    nod* prev;
};

#endif  // _STRUCTURES_H
