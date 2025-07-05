/*NURULLAH YILDIRIM
 * 22100011045*/

#ifndef KARPUZBUTTON_H
#define KARPUZBUTTON_H

#include <QPushButton>
#include <QWidget>

class Karpuzbutton : public QPushButton
{
    Q_OBJECT
public:
    Karpuzbutton(QWidget *parrent = 0);
    bool tiklandimi;
    bool eklendi_mi;

public slots:
    void tikla();
};


#endif // KARPUZBUTTON_H


