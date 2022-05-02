#include "ort.h"

Ort::Ort(const string &name, const long double &latitude, const long double &longitude)
{
    this->name = name;
    this->latitude = latitude;
    this->longitude = longitude;
}

long double Ort::getLatitude() const
{
    return this->latitude;
}

long double Ort::getLongitude() const
{
    return this->longitude;
}

string Ort::getName() const
{
    return this->name;
}

bool Ort::operator < (Ort input)
{
    return (this->getName() < input.getName());
}

bool Ort::putCity(Ort *inputCity, const long double &length)
{
    for(int i = 0; i < this->getAnzahlAusgang(); i++)
    {
        if(citiesWithDistance[i].first == inputCity)
            return false;
    }

    // add exit connections from this city
    std::pair <Ort* , long double> tmp;
    tmp.first = inputCity;
    tmp.second = length;
    this->citiesWithDistance.push_back(tmp);
    this->addConnection(1);
    inputCity->addConnection(0);

    this->sortCities();
    return true;
}

void Ort::sortCities()
{
    long double tmp = 0;
    Ort* tmpOrt = nullptr;
    for(unsigned int i = 0; i < citiesWithDistance.size() - 1; i++)
    {
        if(this->citiesWithDistance[i].second > citiesWithDistance[i+1].second)
        {
            tmp = citiesWithDistance[i].second;
            tmpOrt = citiesWithDistance[i].first;
            citiesWithDistance[i].first = citiesWithDistance[i+1].first;
            citiesWithDistance[i].second = citiesWithDistance[i+1].second;
            citiesWithDistance[i+1].first = tmpOrt;
            citiesWithDistance[i+1].second = tmp;
            i = -1;
        }
    }
}

void Ort::setVisit(const bool &input)
{
    this->visited = input;
}

bool Ort::getVisit() const
{
    return this->visited;
}

long double Ort::getLength(const int &index)
{
    return this->citiesWithDistance[index].second;
}

Ort* Ort::getConnection(const int& index)
{
    return this->citiesWithDistance[index].first;
}

long double Ort::getDistance() const
{
    return this->distanceFromStart;
}

void Ort::setDistance(const long double &input)
{
    this->distanceFromStart = input;
}

void Ort::addConnection(const int &entry)
{
    if(entry == 0)
        this->entries.first++;
    else
        this->entries.second++;
}

void Ort::subConnection(const int &entry)
{
    if(entry == 0)
        this->entries.first--;
    else
        this->entries.second--;
}

bool Ort::deleteArc(const string &name)
{
    for(int i = 0; i < this->getAnzahlAusgang(); i++)
    {
        if(citiesWithDistance[i].first->getName() == name)
        {
            citiesWithDistance[i].first->subConnection(0);
            citiesWithDistance.erase(citiesWithDistance.begin() + i);
            this->subConnection(1);
            return true;
        }
    }
    return false;
}

int Ort::getAnzahlAusgang() const
{
    return this->entries.second;
}

int Ort::getAnzahlEingang() const
{
    return this->entries.first;
}

std::vector <pair <Ort*, long double>> Ort::getCities() const
{
    return this->citiesWithDistance;
}
