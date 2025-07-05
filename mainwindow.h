/*NURULLAH YILDIRIM
 * 22100011045*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QFile>
#include <QDialog>
#include <QList>
#include <QRandomGenerator>
#include "karpuzbutton.h"
#include "bomba.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
   void karpuzolustur();
   void karpuz_hareket();
   void bomb_hareket();
   void oyun_bitis();
   void bomba_olustur();
private:
    Ui::MainWindow *ui;
    QList<Karpuzbutton*> karpuzlar_list;
    QList<Karpuzbutton*> kesilen_karpuzlar;
    QList<bomba*> patlayan_bomba;
    QList<Karpuzbutton*> kacirilan_karpuzlar;
    QList <bomba*> bomb_list;
    int sayac;
    QTimer *zaman ;
    QTimer *hareket ;
    QTimer *oyun_suresi ;
    QTimer *bomba_sure;
    QTimer *b_hareket;
};
#endif // MAINWINDOW_H
