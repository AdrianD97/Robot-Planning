// Copyright 2018 Stefan Adrian

#ifndef _STACK_H_
#define _STACK_H_

#include "structures.h"

template<class T> class Stiva
{
    int top;  // numarul de elemente din stiva
    int dimensiuneMaxima;  // dimensiunea maxima a stivei
    T *S;  // elementele din stiva

  public:

    // constructor

    Stiva(int dimMax)
    {
        top = -1;
        dimensiuneMaxima = dimMax;
        S = new T[dimMax];
    }

    // destructor

    ~Stiva()
    {
        top = -1;
        delete[] S;
    }

    // verifica daca stiva este goala

    bool vida()
    {
        return top == -1;
    }

    // intoarce numarul de elemente din stiva

    int dimensiune()
    {
        return top + 1;
    }

    // adaug un element in stiva
    // daca stiva este plina, redimensionez stiva

    void adauga(T element)
    {
        if ((top + 1) == dimensiuneMaxima)
        {
            dimensiuneMaxima *= 2;

            T *D = new T[dimensiuneMaxima];  // voi copia elementele stivei in acest vecor
            int x = 1;
            D[0] = element;

            while (!this->vida())
            {
                D[x++] = S[top--];
            }

            delete[] S;
            top = -1;

            S = new T[dimensiuneMaxima];

            for(int i = x - 1; i >= 0; i--)
            {
                S[++top] = D[i];
            }
            delete[] D;
        }
        else
        {
            S[++top] = element;
        }
    }

    // sterge primul element din stiva daca aceasta nu este vida

    void sterge()
    {
        if (top == -1)
        {
            return;
        }

        if (top == dimensiuneMaxima / 2)
        {
            dimensiuneMaxima = dimensiuneMaxima / 2;

            T *D = new T[dimensiuneMaxima];  // voi copia elementele stivei in acest vecor
            int x = 0;

            top--;
            while (!this->vida())
            {
                D[x++] = S[top--];
            }

            delete[] S;
            top = -1;

            S = new T[dimensiuneMaxima];

            for (int i = x - 1; i >= 0; i--)
            {
                S[++top] = D[i];
            }
            delete[] D;
        }
        else
        {
            top--;
        }
    }

    // intoarce continutul primului element

    T primulElement()
    {
        return S[top];
    }
};

#endif  // _STACK_H_
