/*NURULLAH YILDIRIM
 * 22100011045*/

#include "bomba.h"

bomba::bomba (QWidget *parrent):QPushButton(parrent) {

    bomba_tiklandimi=false;
    bomba_eklendi_mi=false;
    connect(this, SIGNAL(clicked()),this,SLOT(bomba_tikla()));

}


void bomba::bomba_tikla()
{
    bomba_tiklandimi=!bomba_tiklandimi;
}



