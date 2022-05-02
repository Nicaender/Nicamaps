#ifndef ORT_H
#define ORT_H
#include <iostream>
#include <vector>

using namespace std;

class Ort
{
public:
    Ort(const string &name, const long double &latitude, const long double &longitude);
    string getName() const;
    long double getLatitude() const;
    long double getLongitude() const;
    bool operator <(Ort input);
    bool putCity(Ort *inputCity, const long double &length);
    bool getVisit() const;
    void setVisit(const bool &input);
    long double getLength(const int &index);
    Ort* getConnection(const int& index);
    long double getDistance() const;
    void setDistance(const long double &input);
    void addConnection(const int &entry);
    void subConnection(const int &entry);
    bool deleteArc(const string &name);
    int getAnzahlAusgang() const;
    int getAnzahlEingang() const;
    std::vector <pair <Ort*, long double>> getCities() const;
private:
    string name;
    long double latitude;
    long double longitude;
    bool visited = false;
    std::vector <pair <Ort*, long double>> citiesWithDistance; // connected cities with its distance
    std::pair<int, int> entries;
    void sortCities();
    long double distanceFromStart = -1;
};

#endif // ORT_H
