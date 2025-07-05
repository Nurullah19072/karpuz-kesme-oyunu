/*NURULLAH YILDIRIM
 * 22100011045*/

#include "karpuzbutton.h"

Karpuzbutton::Karpuzbutton (QWidget *parrent):QPushButton(parrent) {
    tiklandimi=false;
    eklendi_mi=false;
    connect(this, SIGNAL(clicked()),this,SLOT(tikla()));
}

void Karpuzbutton::tikla()
{
    tiklandimi=!tiklandimi;
}

