#include "Animal.h"
#include <QDebug>

class Chiken : public Animal
{
public:
    Chiken(QObject* parent = nullptr)
        : Animal("Курица",50,3,parent){
        startProduction();
    }


    void produce() override {
        emit resourceProduced("egg",1);
        qDebug() << name << "снела яйцо!";


    }

};
