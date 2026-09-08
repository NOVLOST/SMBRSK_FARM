#ifndef CHIKEN_H
#define CHIKEN_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDebug>
//абстрактный класс всех житвотных
class Animal : public QObject
{
    Q_OBJECT
protected:
    explicit Animal(QObject *parent = nullptr);
    QString name ; //имя
    int cost; //цена
    int time; //время за которое производится продукт
    QTimer* productionTimer; // таймер который отсчитывает время до создания продукта

public:
    Animal(QString n,int c,int t, QObject* parent = nullptr)
        : QObject(parent), name(n), cost(c), time(t)
    {
        productionTimer = new QTimer(this);
        productionTimer->setInterval(time * 1000); // задаем время для таймера



        connect(productionTimer, &QTimer::timeout, this,&Animal::produce);
    }

    void startProduction() // функция старта отсчёта
    {
        productionTimer->start();

    }

    virtual void produce() = 0; // нужно переопределить для каждого вида

    //гетеры
    QString getName() const { return name; }
    int getCost() const { return cost; }

signals:
    void resourceProduced(QString product, int value); // сигнал о снесенном яйце


public slots:

};

#endif // CHIKEN_H
