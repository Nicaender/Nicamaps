#include "admin.h"

Admin::Admin()
{
    input.open(dataName.c_str(), ios::in);
    if(input)
    {
        string lesen, name, tempLatitude, tempLongitude;
        long double latitude, longitude;
        int state = 0;        // 0 = name, 1 = latitude, 2 = longitude
        while(getline(input, lesen))
        {
            if(lesen == "Ort, Latitude, Longitude")
            {
                continue;
            }
            else
            {
                for(int i = 0; i < int(lesen.size()); i++)
                {
                    if(lesen[i] == ',')
                    {
                        state++;
                        continue;
                    }
                    if(state == 0) name.push_back(lesen[i]);
                    else if(state == 1) tempLatitude.push_back(lesen[i]);
                    else if(state == 2) tempLongitude.push_back(lesen[i]);
                }
                latitude = stod(tempLatitude);
                longitude = stod(tempLongitude);
                state = 0;
                Ort* importOrt = new Ort(name, latitude, longitude);
                int key = hashing(importOrt->getName());
                ortListe[key].push_back(importOrt);
                // Reset strings
                name.clear();
                tempLatitude.clear();
                tempLongitude.clear();
            }
        }
        input.close();
    }

    // initalize bridges
    this->automaticArc();
    //    this->createArc("Zittau", "Wismar");
    //    this->createArc("Wismar", "Aerzen");
    //    this->createArc("Wismar", "Berlin");
    //    this->createArc("Aerzen", "Berlin");
}

void Admin::exportOrtListe()
{
    output.open(dataName.c_str(), ios::out);
    output << "Ort, Latitude, Longitude";
    output << '\n';
    for(int i = 0; i < size; i++)
    {
        if(ortListe[i].size())
        {
            for(Ort* o:ortListe[i])
            {
                output << o->getName();
                output << ",";
                output << fixed << setprecision(7) << o->getLatitude();
                output << ",";
                output << fixed << setprecision(7) << o->getLongitude();
                output << '\n';
            }
        }
    }
    output.close();
}

void Admin::benutzerMenu() const
{
    cout << "Administrator-Menu" << endl;
    cout << "  (a) Neuen Ort (mit Namen) hinzufuegen" << endl;
    cout << "  (b) Ort Loeschen" << endl;
    cout << "  (c) Ausgabe aller Orte (sortiert)" << endl;
    cout << "  (d) Create Arc" << endl;
    cout << "  (e) Delete Arc" << endl;
    cout << "  (x) Beenden" << endl;
    cout << "  (y) Ort Suchen" << endl;
    cout << "  (z) Zurueck zum Modus" << endl;
}

void Admin::addOrt(Ort *input)
{
    int key = hashing(input->getName());
    ortListe[key].push_back(input);
    cout << "Der Ort " << input->getName() << " wurde hinzugefuegt" << endl;
    // initalize bridges
    this->fixArcs(input, true);
}

void Admin::delOrt(const string &name)
{
    int key = hashing(name);
    if(ortListe[key].size() == 0)
    {
        cout << "Dieser Ort wurde nicht gefunden! dattebayo" << endl;
        return;
    }

    // delete the city
    for(int i = 0; i < int(ortListe[key].size()); i++)
    {
        if(ortListe[key][i]->getName() == name)
        {
            // remove all bridges
            this->fixArcs(ortListe[key][i], false);
            delete ortListe[key][i];
            ortListe[key].erase(ortListe[key].begin() + i);
            cout << "Dieser Ort wurde geloescht! dattebayo" << endl;
            return;
        }
    }
}

void Admin::showAllOrt() const
{
    vector <Ort*> copyVector;

    // adding the cities to copy vector
    for(int i = 0; i < size; i++)
        if(ortListe[i].size())
            copyVector.insert(copyVector.end(),ortListe[i].begin(), ortListe[i].end());

    // Selection sort
    for(unsigned int i = 0; i < copyVector.size() - 1; i++)
    {
        int index = i;
        Ort* max = copyVector[i];
        for(unsigned int j = i+1; j < copyVector.size(); j++)
        {
            if(*copyVector[j] < *max)
            {
                index = j;
                max = copyVector[j];
            }
        }
        copyVector[index] = copyVector[i];
        copyVector[i] = max;
    }

    for(int i = 0; i < int(copyVector.size()); i++)
    {
        cout << "Name: ";
        cout.width(20);
        cout.setf(ios::left);
        cout << fixed << setprecision(7);
        cout << copyVector[i]->getName() << " Latitude: " << copyVector[i]->getLatitude() << " Longitude: " << copyVector[i]->getLongitude() << endl;
    }
}

bool Admin::checkOrtExist(const string &name) const
{
    int key = hashing(name);

    // check index from array
    if(ortListe[key].size() != 0)
    {
        // actual search inside the index in that array
        for(int i = 0; i < int(ortListe[key].size()); i++)
            if(ortListe[key][i]->getName() == name)
                return true;
    }

    return false;
}

Ort* Admin::getOrt(const string &name) const
{
    int key = hashing(name);

    // check index from array
    if(ortListe[key].size() != 0)
        // actual search inside the index in that array
        for(int i = 0; i < int(ortListe[key].size()); i++)
            if(ortListe[key][i]->getName() == name)
                return ortListe[key][i];

    return nullptr;
}

int Admin::hashing(const string &cityName) const
{
    int resultat = -1;
    for(int i = 0; i < int(cityName.length()); i++)
    {
        int ascii = int(cityName[i]);
        resultat += ascii;
    }

    return resultat % size;
}

void Admin::operator += (Ort* input)
{
    this->addOrt(input);
}

bool Admin::createArc(const string &cityName1, const string &cityName2)
{
    if(cityName1 == cityName2)
        return false;
    int key1 = this->hashing(cityName1);
    int key2 = this->hashing(cityName2);
    Ort* city1 = nullptr;
    Ort* city2 = nullptr;

    // search city from
    for(int i = 0; i < int(ortListe[key1].size()); i++)
    {
        if(ortListe[key1][i]->getName() == cityName1)
        {
            city1 = this->ortListe[key1][i];
        }
    }

    // search city to
    for(int i = 0; i < int(ortListe[key2].size()); i++)
    {
        if(ortListe[key2][i]->getName() == cityName2)
        {
            city2 = this->ortListe[key2][i];
        }
    }

    if(city1 != nullptr && city2 != nullptr)
    {
        long double length = this->distanceCalculate(city1, city2);
        if(city1->putCity(city2, length))
            return true;
    }

    return false;
}

bool Admin::delArc(const string &cityName1, const string &cityName2)
{
    if(cityName1 == cityName2)
        return false;
    int key1 = this->hashing(cityName1);
    Ort* city1 = nullptr;

    // search city from
    for(int i = 0; i < int(ortListe[key1].size()); i++)
    {
        if(ortListe[key1][i]->getName() == cityName1)
        {
            city1 = this->ortListe[key1][i];
        }
    }

    if(city1)
    {
        if(city1->deleteArc(cityName2))
            return true;
    }

    return false;
}

void Admin::automaticArc()
{
    for(int i = 0; i < size; i++)
        if(ortListe[i].size())
            for(unsigned int o = 0; o < ortListe[i].size(); o++)
            {
                for(int j = 0; j < size; j++)
                    if(ortListe[j].size())
                        for(unsigned int l = 0; l < ortListe[j].size(); l++)
                        {
                            if(ortListe[i][o]->getName() == ortListe[j][l]->getName())
                                break;
                            if(int(distanceCalculate(ortListe[i][o], ortListe[j][l])) < 100)
                                this->createArc(ortListe[i][o]->getName(), ortListe[j][l]->getName());
                        }
            }
}

void Admin::setAllVisit(const bool &input)
{
    for(int i = 0; i < size; i++)
        if(ortListe[i].size())
            for(Ort* o:ortListe[i])
                o->setVisit(input);
}

void Admin::resetAllDistance()
{
    for(int i = 0; i < size; i++)
        if(ortListe[i].size())
            for(Ort* o:ortListe[i])
                o->setDistance(-1);
}

long double Admin::deg2grad(const long double &degree){
    const double pi = 3.14;
    return (degree * (pi/180));
}

long double Admin :: distanceCalculate(Ort *ort1, Ort *ort2){
    if(ort1 == nullptr || ort2 == nullptr){
        return -1;
    }
    long double Distanz;
    long double lat1 = deg2grad(ort1->getLatitude());
    long double lat2 = deg2grad(ort2->getLatitude());
    long double long1 = deg2grad(ort1->getLongitude());
    long double long2 = deg2grad(ort2->getLongitude());

    long double deltalat = (lat2-lat1)/2;
    long double deltalong = (long2-long1)/2;

    Distanz = 2 * 6371 * asin(sqrt(sin(deltalat)*sin(deltalat)+cos(lat1)*cos(lat2)*(sin(deltalong)*sin(deltalong))));
    return Distanz;
}

void Admin::fixArcs(Ort* city, const bool &add)
{
    if(!city) return;
    if(add == true) // kalau mau tambah kota
    {
        if(city)
        {
            for(int i = 0; i < size; i++)
            {
                if(ortListe[i].size())
                {
                    for(Ort* o:ortListe[i])
                    {
                        std::cout << i << '\n';
                        if(int(distanceCalculate(o, city) < 100))
                        {
                            this->createArc(o->getName(), city->getName());
                            this->createArc(city->getName(), o->getName());
                        }
                    }
                }
            }
        }
    }
    else // kalau mau delete kota
    {
        if(city)
        {
            // search all connections from city
            while(city->getAnzahlAusgang() > 0)
            {
                city->getCities()[city->getAnzahlAusgang()-1].first->deleteArc(city->getName()); // to city delete arcs with from city
                city->deleteArc(city->getCities()[city->getAnzahlAusgang()-1].first->getName()); // from city delete city with to city
            }
        }

        // only if necessary
        if(city->getAnzahlAusgang() != 0 || city->getAnzahlEingang() != 0)
        {
            // check everything
            for(int i = 0; i < size; i++)
                if(ortListe[i].size())
                    for(Ort* o:ortListe[i])
                        o->deleteArc(city->getName());
        }
    }
}

Admin::~Admin()
{
    exportOrtListe();
    // delete everything
    for(int i = 0; i < size; i++)
        if(ortListe[i].size())
            for(Ort* o:ortListe[i])
                delete o;
}
