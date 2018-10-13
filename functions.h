// Copyright 2018 Stefan Adrian

#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "robot.h"

//citeste configuratia depozitului

void citire_matrice(int **A, std::ifstream& f, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            f >> A[i][j];
        }
    }
}

// maresc timpul de fiecare data cand omul da o comanda

void cresteTimp(Robot<data> *roboti, int n)
{
    for (int i = 0; i < n; i++)
    {
        roboti[i].timp++;
    }
}

// afiseaza comenzile din coada robotului

void afisare_comenzi(Robot<data> &robot, int id, std::ofstream &g)
{
    g << "PRINT_COMMANDS: ";
    if(robot.C.vida())
    {
        g << "No command found\n";
        return;
    }

    data var;

    g << id << ": ";

    for(int i = 0; i < robot.C.dimensiune() - 1; i++)
    {
        var = robot.C.primul();
        robot.C.stergePrimul();
        robot.C.adaugaSfarsit(var);
        g << var.C.tip_comanda << ' ' << var.C.x << ' ' << var.C.y << ' ' << var.C.nr_cuti << "; ";
    }

    var = robot.C.primul();
    robot.C.stergePrimul();
    robot.C.adaugaSfarsit(var);
    g << var.C.tip_comanda << ' ' << var.C.x << ' ' <<var.C.y << ' ' << var.C.nr_cuti << '\n';
}

#endif // _FUNCTIONS_H_
