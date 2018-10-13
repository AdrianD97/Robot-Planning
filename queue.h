// Copyright 2018 Stefan Adrian

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "structures.h"

template<class T> class Coada
{
    nod<T> *head, *tail;  // pointeri catre primul, respectiv ultimul nod din coada
    int nr_elemente;  // numarul de noduri din coada

 public:
    // constructor : creeaza o coada vida

    Coada()
    {
        head = tail = NULL;
        nr_elemente = 0;
    }

    // destructor : elibereaza zona de memorie alocata pt fiecare nod

    ~Coada()
    {
        nod<T> *p = head;

        while (head != NULL)
        {
            head = head->next;
            delete p;
            p = head;
        }

        head = tail = NULL;
    }

    // verifica daca coada este vida

    bool vida()
    {
        return nr_elemente == 0;
    }

    // returneaza dimensiunea cozii

    int dimensiune()
    {
        return nr_elemente;
    }

    // adauga un nod la inceputul cozii

    void adaugaInceput(T info)
    {
        nod<T> *p = new nod<T>;
        p->info = info;
        p->next = NULL;
        p->prev = NULL;
        nr_elemente++;

        if (head == NULL)
        {
            head = tail = p;
            return;
        }

        p->next = head;
        head->prev = p;
        head = p;
    }

    // adauga un nod la sfarsitul cozii

    void adaugaSfarsit(T info)
    {
        nod<T> *p = new nod<T>;
        p->info = info;
        p->next = NULL;
        p->prev = NULL;
        nr_elemente++;

        if (tail == NULL)
        {
            head = tail = p;
            return;
        }

        tail->next = p;
        p->prev = tail;
        tail = p;
    }

    // intoarce data continuta in primul nod

    T primul()
    {
        return head->info;
    }

    // sterge primul nod din coada si intoarce data continuta in el

    void stergePrimul()
    {
        nr_elemente--;

        if (head == tail)
        {
            delete head;
            head = tail = NULL;
            return;
        }

        nod<T> *p = head;
        head = head->next;
        head->prev = NULL;
        delete p;
    }

    // sterge ultimul nod

    void stergeUltimul()
    {
        nr_elemente--;

        if (tail == head)
        {
            delete tail;
            head = tail = NULL;
            return;
        }

        nod<T> *p = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete p;
    }
};

#endif  // _QUEUE_H_
