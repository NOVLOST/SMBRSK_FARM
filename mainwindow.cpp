#include "GameController.h"
#include "ui_mainwindow.h"
#include "inventorymenu.h"
#include "Chiken.h"
#include "chikenbutton.h"

#include <QGridLayout>
#include <QDebug>
#include <QPainter>

//TODO:поработать с графикой. Сделать красивый инвентарь
//сделать свой фон как zenGraden и сделать возможность размещать на нем куриц
//курица должна покупиться как в PvsZ  тоесть нужно меню покупки животных как в игре
// идея игры днем развиваешь ферму ,ночь отбиваешь зомбаков ставишь турели и тд и тп

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)


{
    // иницилизация
    money = 0;

    inventoryDict["egg"] = 0;
    inventoryDict["milk"] = 0;
    inventoryDict["wool"] = 0;

    // словарь для перевода имен из inventoryDict в таблицу инвентаря
    TranslateProductName["egg"] = "яйца";
    TranslateProductName["milk"] = "молоко";
    TranslateProductName["wool"] = "шерсть";

    // кнопки
    ui->setupUi(this);
    moneyLabel = new QLabel("Деньги: 0", this);
    collectBtn = new QPushButton("собрать урожай",this);
    buyAnimal = new ChikenButton("/home/user/SmbrskFarm/image/chikenTruePng.png",50,this);
    inventoryBtn = new QPushButton("инвентарь",this);

    //фон
    backgroundPixmap = QPixmap("/home/user/SmbrskFarm/image/ферма.jpg");

    // стиль кнопок
    moneyLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: yellow ;"
                              "background-color: rgba(0,0,0,150); padding: 15px; border-radius: 10px;"
                              );
    collectBtn->setStyleSheet("font-size: 16px; padding: 15px 30px;"
                              "background-color: rga(76,175,80,150); color: white;"
                              "border-radius: 10px; font-weight: bold;"
                              );
    buyAnimal->setStyleSheet("font-size: 16px; padding: 12px 20px;"
                             "background-color: rgba(255,152,0,200);color: white;"
                             "border-radius: 8px;");
    inventoryBtn->setStyleSheet("font-size: 16px; padding: 10px;"
                                "background-color: rgba(33,150,243,200); color: white;"
                                "border-radius: 8px;"
                                );


    QGridLayout *layout = new QGridLayout();

    layout->setSpacing(20);
    layout->setContentsMargins(30,30,30,30);

    layout->addWidget(moneyLabel,2,2, Qt::AlignRight | Qt::AlignBottom);
    layout->addWidget(collectBtn, 2,1, Qt::AlignHCenter | Qt::AlignBottom);
    layout->addWidget(buyAnimal,0,0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(inventoryBtn,0,2, Qt::AlignRight | Qt::AlignTop);
    layout->setRowStretch(1,1);
    layout->setColumnStretch(1,1);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);


    setCentralWidget(centralWidget);

    setWindowTitle("Симбирская-Ферма");
    resize(800,600);

    // кнонекты кнопок
    connect(collectBtn, &QPushButton::clicked, this, &MainWindow::AddMoney);
    connect(buyAnimal, &QPushButton::clicked, this, &MainWindow::AddAnimal);
    connect(inventoryBtn, &QPushButton::clicked, this, &MainWindow::OpenInventory);



    qDebug() << "SGT june 2026 Welcome ;) ";


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap scaledPixmap = backgroundPixmap.scaled(
                this->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation // отвечает за сглаживание при растяжении

                );
    painter.drawPixmap(0,0,scaledPixmap);

    QMainWindow::paintEvent(event);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);


}

void MainWindow::AddMoney()
{
    money++;
    MainWindow::UpdateScore();
    qDebug() << "Ура деньги!" << money;



}

void MainWindow::AddHarvest(QString product, int value)
{
    qDebug() << "урожай дабавлен" << product << value ;
    inventoryDict[product] += value ;
    emit newharvest(inventoryDict,TranslateProductName);
}

void MainWindow::UpdateScore()
{
    moneyLabel->setText("Деньги: " + QString::number(money));

}

void MainWindow::AddAnimal()
{


        if (money >= 50)
        {
            Chiken* chick = new Chiken(this);
            animalsList.append(chick);
            money = money - chick->getCost();
            MainWindow::UpdateScore();
            connect(chick, &Animal::resourceProduced, this, &MainWindow::AddHarvest);
            qDebug() << "New Chiken!!!" << animalsList ;

        }
        else qDebug() << "No money!!!"  ;


}

void MainWindow::OpenInventory()
{

    qDebug() << "инвентарь" << inventoryDict;

    if ( !InventoryMenuPointer)
    {
        InventoryMenuPointer = new InventoryMenu(inventoryDict,TranslateProductName,  this);
        connect(this,&MainWindow::newharvest,InventoryMenuPointer,&InventoryMenu::UpdateTable);
    }
    InventoryMenuPointer->show();



}


