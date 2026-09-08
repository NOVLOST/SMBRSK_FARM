#include "inventorymenu.h"
#include <QHeaderView>
#include <QDebug>

// код окна инвентаря
InventoryMenu::InventoryMenu(const QHash<QString, int>& inventoryDict,
                             const QHash<QString,QString>& TranslateProductName,
                             QWidget* parent)

    : QDialog(parent)

{


    setWindowTitle("Инвентарь фермы");
    resize(640,480);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4); // количество столбцов
    tableWidget->setHorizontalHeaderLabels({"предмет","Кол-во","Цена за шт","Общая стоимость"});
    tableWidget->horizontalHeader()->setStretchLastSection(true); // подгоняет размер стобца под длинну текста
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // хз на что влияет


    QVBoxLayout* layout = new QVBoxLayout(); // вергикальное расположение виджетов

    layout-> addWidget(new QLabel("ваши ресурсы:",this));
    layout-> addWidget(tableWidget);
    setLayout(layout);




    populateTable(inventoryDict,TranslateProductName); // функция заполнения таблицы


}


void InventoryMenu::UpdateTable(const QHash<QString, int>& inventoryDict,
                 const QHash<QString,QString>& TranslateProductName)
{

    tableWidget->setRowCount(0);
    populateTable(inventoryDict,TranslateProductName);
}

void InventoryMenu::populateTable(const QHash<QString, int>& inventoryDict,
                                  const QHash<QString,QString>& TranslateProductName)
{
    int row = 0;
    //поумолчанию кол-во строк 0. Больше указнного числа строк не добавит
    tableWidget->setRowCount(inventoryDict.size());

    for (auto item = inventoryDict.begin(); item != inventoryDict.end(); item++)
    {
        QString name = item.key(); // название продукта
        int value = item.value(); // кол-во продукта

        name = TranslateProductName.value(name,name); // безопасная установка значения если не нашли оставляем то что есть

        tableWidget->setItem(row,0,new QTableWidgetItem(name));
        tableWidget->setItem(row,1,new QTableWidgetItem(QString::number(value)));

        row++;
        qDebug() << name << value;


    }

}
