#ifndef NICAMAPS_H
#define NICAMAPS_H
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

class NicaMaps
{
public:
    NicaMaps();
    void benutzerMenu() const;
protected:
    const string location = "C:/Users/nican/OneDrive - stud.h-da.de/Documents/WS2021_Praktikum_N1/";
    const string fileName = "ort_liste.csv";
    const string dataName = location + fileName;
private:
    void mode() const;
};

#endif // NICAMAPS_H
