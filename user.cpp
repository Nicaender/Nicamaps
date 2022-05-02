#include "user.h"

User::User()
{

}


void User::giveOrt(Ort* &startOrt, Ort* &zielOrt)
{
    this->startOrt = startOrt;
    this->zielOrt = zielOrt;
    cout << "Von " << this->startOrt->getName() << " nach " << this->zielOrt->getName() << endl;
}

void User::benutzerMenu() const
{
    cout << "Benutzer-Menu" << endl;
    cout << "  (a) Start- und Zielort eingeben" << endl;
    cout << "  (b) Navigation starten" << endl;
    cout << "  (x) Beenden" << endl;
    cout << "  (y) Ort Suchen" << endl;
    cout << "  (z) Zurueck zum Modus" << endl;
}

void User::navigation()
{
    if(startOrt == nullptr || zielOrt == nullptr)
    {
        std::cout << "Error: city not found\n";
        return;
    }

    Ort* current = startOrt;
    Ort* willBe = nullptr;
    std::vector<pair<Ort*, Ort*>> beforeAfterList;
    pair<Ort*, Ort*> beforeAfter;

    long double currentDistance = 0;
    long double accumulateDistance = 0;
    std::queue<Ort*> q;
    std::queue<long double> distanceQueue;

    if(!current->getVisit())
    {
        current->setVisit(true);
        current->setDistance(currentDistance);
        q.push(current);

        while(!q.empty())
        {
            current = q.front();
            if(!distanceQueue.empty())
                currentDistance = distanceQueue.front();
            if(!distanceQueue.empty())
                distanceQueue.pop();
            q.pop();

            accumulateDistance = currentDistance;
            int size = current->getAnzahlAusgang();
            for(int i = 0; i < size; i++)
            {
                willBe = current->getConnection(i);
                if(!willBe->getVisit())
                {
                    currentDistance += current->getLength(i);
                    willBe->setVisit(true);
                    beforeAfter.first = current;
                    beforeAfter.second = willBe;
                    beforeAfterList.push_back(beforeAfter);
                    distanceQueue.push(currentDistance);
                    willBe->setDistance(currentDistance);
                    q.push(willBe);
                    currentDistance = accumulateDistance;
                }
                else if(willBe->getVisit() && willBe->getDistance() > currentDistance + current->getLength(i)) // kalau willBe memiliki distance yang lebih tinggi
                {
                    currentDistance += current->getLength(i);
                    beforeAfter.first = current;
                    beforeAfter.second = willBe;
                    beforeAfterList.push_back(beforeAfter); // bisa update biar pake yang terbaru, atau schleife untuk ganti dalam tabel
                    willBe->setDistance(currentDistance);
                    currentDistance = accumulateDistance;
                }
            }
        }
    }

    if(zielOrt->getVisit() == false) // return because destination is not visited
    {
        std::cout << "Sorry, route to destination is not yet possible!\n";
        return;
    }

    // reset all stats
    willBe = nullptr;

    std::deque <Ort*> shortestWay;
    Ort* backtrack = zielOrt;
    for(int i = (beforeAfterList.size() - 1); i >= 0; i--)
    {
        if(beforeAfterList[i].second == backtrack)
        {
            shortestWay.push_front(beforeAfterList[i].second);
            backtrack = beforeAfterList[i].first;
            if(beforeAfterList[i].first == startOrt)
                break;
            else
                i = beforeAfterList.size() - 1;
        }
    }
    std::cout << "Distance: " << int(zielOrt->getDistance()) << " km\n";
    std::cout << startOrt->getName();
    for(Ort* o:shortestWay)
        std::cout << " -> " << o->getName() << "(" << int(o->getDistance()) << "Km)";
    std::cout << '\n';
}

bool User::isInDeque(std::deque<Ort *> &list, Ort* input)
{
    for(Ort* o:list)
        if(o == input)
            return true;
    return false;
}
