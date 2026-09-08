#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H


#include <QDialog>
#include <QTableWidget>
#include <QLabel>
#include <QVBoxLayout>


class InventoryMenu : public QDialog
{
    Q_OBJECT

public:
    explicit InventoryMenu(const QHash<QString, int>& inventoryDict,
                           const QHash<QString,QString>& TranslateProductName,
                            QWidget* parent = nullptr);
protected:



public slots:

    void UpdateTable(const QHash<QString, int>& inventoryDict,
                     const QHash<QString,QString>& TranslateProductName); // обновление таблицы инвентаря на экране
private:
    QTableWidget* tableWidget; // виджет таблицы


    void populateTable(const QHash<QString, int>& InventoryDict,
                       const QHash<QString,QString>& TranslateProductName
                       );
};

#endif // INVENTORYMENU_H
