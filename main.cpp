// Copyright 2018 Stefan Adrian

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstring>

#include "robot.h"
#include "stack.h"
#include "structures.h"
#include "functions.h"

//  functia simuleaza comportamentul robotilor


void comenzi(int **A, int LIN, int COL, std::ifstream &f, std::ofstream &g, Robot<data> *roboti, int N, Stiva<undo> &execute, Stiva<undo> &add)
{
    f.get();
    int t = 1;  // da ordinea comenzilor de tip execute si add

    char *p;
    std::string linie;

    while (getline(f, linie))
    {
        if (linie == "")
        {
            return;
        }

        char delimitator[]= " ";

        p = strtok(&linie[0], delimitator);

        if (strcmp(p, "ADD_GET_BOX") == 0 || strcmp(p, "ADD_DROP_BOX") == 0)
        {
            data D;
            undo U;

            D.C.tip_comanda = (strcmp(p, "ADD_GET_BOX") == 0) ? "GET" : "DROP";
            U.C.tip_comanda = D.C.tip_comanda;

            p = strtok(NULL, delimitator);
            U.id_robot = atoi(p);

            p = strtok(NULL, delimitator);
            U.C.x = D.C.x = atoi(p);
            p = strtok(NULL, delimitator);
            U.C.y = D.C.y = atoi(p);

            p = strtok(NULL, delimitator);
            U.C.nr_cuti = D.C.nr_cuti = atoi(p);

            p = strtok(NULL, delimitator);
            U.H.prioritate = atoi(p);

            D.timp = roboti[U.id_robot].timp;

            U.ordine = t++;

            if (U.H.prioritate == 0)
            {
                roboti[U.id_robot].C.adaugaInceput(D);
            }
            else
            if (U.H.prioritate == 1)
            {
                roboti[U.id_robot].C.adaugaSfarsit(D);
            }

            add.adauga(U);
        }
        else
        if (strcmp(p, "EXECUTE") == 0)
        {
            p = strtok(NULL, delimitator);
            int cuti;
            int id = atoi(p);
            undo U;

            if (roboti[id].C.vida())
            {
                g << "EXECUTE: No command to execute\n";
            }
            else
            {
                data D = roboti[id].C.primul();
                roboti[id].C.stergePrimul();

                if (D.C.tip_comanda == "GET")
                {
                    cuti = A[D.C.x][D.C.y] < D.C.nr_cuti ? A[D.C.x][D.C.y] : D.C.nr_cuti;
                    roboti[id].nr_cutii += cuti;
                    A[D.C.x][D.C.y] -= cuti;
                }
                else
                {
                    cuti = roboti[id].nr_cutii < D.C.nr_cuti ? roboti[id].nr_cutii : D.C.nr_cuti;
                    roboti[id].nr_cutii -= cuti;
                    A[D.C.x][D.C.y] += cuti;
                }

                U.id_robot = id;
                U.C.tip_comanda = D.C.tip_comanda;
                U.C.x = D.C.x;
                U.C.y = D.C.y;
                U.C.nr_cuti = cuti;
                U.H.timp = roboti[id].timp - D.timp;
                U.ordine = t++;

                execute.adauga(U);
            }
        }
        else
        if (strcmp(p, "PRINT_COMMANDS") == 0)
        {
            p = strtok(NULL, delimitator);
            int id = atoi(p);

            afisare_comenzi(roboti[id], id, g);
        }
        else
        if (strcmp(p, "LAST_EXECUTED_COMMAND") == 0)
        {
            g << "LAST_EXECUTED_COMMAND: ";
            if (execute.vida())
            {
                g << "No command was executed\n";
            }
            else
            {
                undo var = execute.primulElement();
                g << var.id_robot << ": " << var.C.tip_comanda << ' ' << var.C.x << ' ' << var.C.y << ' ' <<var.C.nr_cuti << '\n';
            }
        }
        else
        if (strcmp(p, "UNDO") == 0)
        {
            undo var, aux;
            data D;

            if (execute.vida() && add.vida())
            {
                g << "UNDO: No history\n";
            }
            else
            if (execute.vida() && !add.vida())
            {
                var = add.primulElement();
                add.sterge();
                if (var.H.prioritate == 0)
                {
                    roboti[var.id_robot].C.stergePrimul();
                }
                else
                {
                    roboti[var.id_robot].C.stergeUltimul();
                }
            }
            else
            if (add.vida() && !execute.vida())
            {
                var = execute.primulElement();
                execute.sterge();

                D.timp = roboti[var.id_robot].timp;
                D.C.tip_comanda = var.C.tip_comanda;
                D.C.x = var.C.x;
                D.C.y = var.C.y;
                D.C.nr_cuti = var.C.nr_cuti;
                roboti[var.id_robot].C.adaugaInceput(D);

                if (var.C.tip_comanda == "GET")
                {
                    A[D.C.x][D.C.y] += D.C.nr_cuti;
                    roboti[var.id_robot].nr_cutii -= D.C.nr_cuti;
                }
                else
                {
                    A[D.C.x][D.C.y] -= D.C.nr_cuti;
                    roboti[var.id_robot].nr_cutii += D.C.nr_cuti;
                }
            }
            else
            if (!execute.vida() && !add.vida())
            {
                var = execute.primulElement();
                aux = add.primulElement();

                if (var.ordine > aux.ordine)
                {
                    execute.sterge();
                    D.timp = roboti[var.id_robot].timp;
                    D.C.tip_comanda = var.C.tip_comanda;
                    D.C.x = var.C.x;
                    D.C.y = var.C.y;
                    D.C.nr_cuti = var.C.nr_cuti;
                    roboti[var.id_robot].C.adaugaInceput(D);

                    if (var.C.tip_comanda == "GET")
                    {
                        A[D.C.x][D.C.y] += D.C.nr_cuti;
                        roboti[var.id_robot].nr_cutii -= D.C.nr_cuti;
                    }
                    else
                    {
                        A[D.C.x][D.C.y] -= D.C.nr_cuti;
                        roboti[var.id_robot].nr_cutii += D.C.nr_cuti;
                    }
                }
                else
                {
                        add.sterge();

                        if (aux.H.prioritate == 0)
                        {
                            roboti[aux.id_robot].C.stergePrimul();
                        }
                        else
                        {
                            roboti[aux.id_robot].C.stergeUltimul();
                        }
                }
            }
        }
        else
        if (strcmp(p, "HOW_MUCH_TIME") == 0)
        {
            g << "HOW_MUCH_TIME: ";

            if (execute.vida())
            {
                g << "No command was executed\n";
            }
            else
            {
                undo var = execute.primulElement();
                g << var.H.timp << '\n';
            }
        }
        else
        if (strcmp(p, "HOW_MANY_BOXES") == 0)
        {
            p = strtok(NULL, delimitator);
            int id = atoi(p);
            g << "HOW_MANY_BOXES: " << roboti[id].nr_cutii << '\n';
        }
        else
        {
            std::cout << "Invalid command\n";
        }

        cresteTimp(roboti, N);
    }
}

int main()
{
    int N, LIN, COL;  // numarul de roboti, dimensiunile matricei
    int **A;  // matricea

    Stiva<undo> execute(250);  // memoreaza istoricul comenzilor de tip execute
    Stiva<undo> add(250);  // memoreaza istoricul comenzilor de tip add
    Robot<data> *roboti;  // cei N roboti

    std::ifstream f("robots.in");
    std::ofstream g("robots.out");

    f >> N >> LIN >> COL;

    A = new int*[LIN];
    roboti = new Robot<data>[N];

    for (int i = 0; i < LIN; i++)
    {
        A[i] = new int[COL];
    }

    citire_matrice(A, f, LIN, COL);

    comenzi(A, LIN, COL, f, g, roboti, N, execute, add);

    for (int i = 0; i < LIN; i++)
    {
        delete[] A[i];
    }

    delete[] A;
    delete[] roboti;

    f.close();
    g.close();

    return 0;
}
