/*NURULLAH YILDIRIM
 * 22100011045*/

#ifndef BOMBA_H
#define BOMBA_H

#include <QPushButton>
#include <QWidget>
class bomba : public QPushButton
{
    Q_OBJECT
public:
    bomba(QWidget *parrent = 0);
    bool bomba_tiklandimi;
    bool bomba_eklendi_mi;

public slots:
    void bomba_tikla();

};

#endif // BOMBA_H
