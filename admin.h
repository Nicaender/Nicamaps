#ifndef ADMIN_H
#define ADMIN_H
#include <iostream>
#include <nicamaps.h>
#include <ort.h>
#include <iomanip>
#include <math.h>

using namespace std;

class Admin : public NicaMaps
{
public:
    Admin();
    ~Admin();
    void benutzerMenu() const;
    void addOrt(Ort* input);
    void delOrt(const string &name);
    void showAllOrt() const;
    bool checkOrtExist(const string &name) const;
    Ort* getOrt(const string &name) const;
    void operator += (Ort* input);
    void setAllVisit(const bool &input);
    void resetAllDistance();
    bool createArc(const string &cityName1, const string &cityName2);
    bool delArc(const string &cityName1, const string &cityName2);
    long double deg2grad(const long double &degree);
    long double distanceCalculate(Ort *ort1, Ort *ort2);
private:
    static const int size = 200;
    vector <Ort*> ortListe[size];
    void exportOrtListe();      // Cannot add const
    int hashing(const string &cityName) const;
    ifstream input;
    ofstream output;
    void automaticArc();
    void fixArcs(Ort* city, const bool &add);
};

#endif // ADMIN_H
