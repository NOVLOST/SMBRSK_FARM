#ifndef CHIKENBUTTON_H
#define CHIKENBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

class ChikenButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ChikenButton(const QString& imagePath,
                         int price,
                         QWidget* parent = nullptr)
        : QPushButton(parent), price(price)
    {
        chikenPixmap = QPixmap(imagePath); // устанавливаем картинку

        setStyleSheet("background-color: transparent; border: none;");

        setFixedSize(150, 150); //размер картинки

        setToolTip(QString("Купить курицу за %1").arg(price));

    }

protected:
    void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        QPixmap scaled = chikenPixmap.scaled(
                    size(),
                    Qt::KeepAspectRatio,
                    Qt::SmoothTransformation
                    );

        int x = (width() - scaled.width()) / 2;
        int y = (height() - scaled.height()) / 2;
        painter.drawPixmap(x,y, scaled); // рисуем картинку

        //работа с шрифтом
        QString priceText = QString("%1 ").arg(price);
        QFont font;
        font.setPixelSize(18);
        font.setBold(true);
        painter.setFont(font);

        QFontMetrics fm(font);
        QRect textRect = fm.boundingRect(priceText);

        QRect bgRect(
               width() - textRect.width() - 15,
               height()  - textRect.height() - 10,
               textRect.width() + 10,
               textRect.height() + 5
         );
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(0,0,0,180));
        painter.drawRoundedRect(bgRect,5,5);

        painter.setPen(Qt::yellow);
        painter.drawText(
                    bgRect.x() + 5,
                    bgRect.y() + textRect.height(),
                    priceText
                  );
        // эффект при наведении
        if (underMouse()) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(255,255,255,40));
            painter.drawRoundedRect(rect(),10,10);

        }
    }

private:
    QPixmap chikenPixmap;
    int price;

};

#endif // CHIKENBUTTON_H
