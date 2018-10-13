// Copyright 2018 Stefan Adrian

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "queue.h"


template<class T> class Robot
{
 public:
    Coada<T> C;  // Coada de comenzi a robotului
    int nr_cutii;  // numarul de cutii din inventarul robotului

    int timp;  // o variabila care ma ajuta sa calculez timpul pana cand s-a executat fiecare comanda
               // din coada. Cand adaug un nod in coada , marchez timpul de intrare,
               // iar cand comanda este executata marchez timpul de iesire. Diferenta
               // celor doua momente de timp reprezinta "How much time" pentru fiecare comanda.

    // Constructor

    Robot()
    {
        timp = 0;
        nr_cutii = 0;
    }
};
#endif  // _ROBOT_H_
