#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QList>
#include <Animal.h>
#include <inventorymenu.h>
#include <QPixmap>
#include <chikenbutton.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void newharvest(const QHash<QString, int> inventoryDict,
                    const QHash<QString,QString> TranslateProductName);

protected:
    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private slots:
    void UpdateScore(); // обновить счетчик денег на экране
    void AddMoney(); // добавить деняк
    void AddAnimal(); // добавить купленное животное в список
    void OpenInventory(); // открыть окно инвентаря
    void AddHarvest(QString product, int value); // добавить продукт в инвентарь


private:
    Ui::MainWindow *ui;
    QLabel *moneyLabel; // счетчик деняг
    QPushButton *collectBtn; // кнопка сбора урожая
    ChikenButton *buyAnimal; // кнопка покупки животного
    QPushButton *inventoryBtn; // кнопка открытия инвентаря
    int money; // переменная деняг
    QList<Animal*> animalsList; // список для животных
    QHash<QString, int> inventoryDict; // словарь инвентаря
    QHash<QString,QString> TranslateProductName; // перевод названий с англ на русский
    InventoryMenu* InventoryMenuPointer = nullptr;

    QPixmap backgroundPixmap;


};

#endif // MAINWINDOW_H
