#ifndef USER_H
#define USER_H
#include <iostream>
#include <nicamaps.h>
#include <ort.h>
#include <admin.h>

using namespace std;

class User : public NicaMaps
{
public:
    User();
    void benutzerMenu() const;
    void giveOrt(Ort *&startOrt, Ort *&zielOrt);
    void navigation();
    bool isInDeque(std::deque <Ort*> &list, Ort* input);
private:
    Ort* startOrt = nullptr;
    Ort* zielOrt = nullptr;
};

#endif // USER_H
