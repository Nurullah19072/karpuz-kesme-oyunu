/*NURULLAH YILDIRIM
 * 22100011045*/


#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sayac=30;
    zaman = new QTimer(this);
    hareket = new QTimer(this);
    bomba_sure=new QTimer(this);
    oyun_suresi = new QTimer(this);
    b_hareket=new QTimer(this);

    connect(zaman, SIGNAL(timeout()),this,SLOT(karpuzolustur()));
    connect(hareket, SIGNAL(timeout()),this,SLOT(karpuz_hareket()));
    connect(oyun_suresi, SIGNAL(timeout()),this,SLOT(oyun_bitis()));
    connect(bomba_sure, SIGNAL(timeout()),this,SLOT(bomba_olustur()));
    connect(b_hareket, SIGNAL(timeout()),this,SLOT(bomb_hareket()));

    bomba_sure->start(3000);
    oyun_suresi->start(1000);
    hareket->start(100);
    b_hareket->start(100);
    zaman->start(600);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::karpuzolustur(){
    /* Dosya Okuma İşlemi */
    QFile file("konumlar.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Dosya Hatası!", "konumlar.txt dosyasına ulaşılamıyor.");
        return;
    }

    QTextStream fileKonumlar(&file);
    QStringList konumlar;

    while (!fileKonumlar.atEnd())
    {
        QString line = fileKonumlar.readLine();
        konumlar.append(line);
    }

    file.close();
    /* ./Dosya Okuma İşlemi */

    int randomIndex = QRandomGenerator::global()->bounded(0, konumlar.size());
    QStringList konum = konumlar[randomIndex].split(" ");
    int x = konum[0].toInt();
    int y = konum[1].toInt();

    Karpuzbutton *karpuz = new Karpuzbutton(this);
    karpuz->setStyleSheet("border-image: url(':/resim/1.png');");
    karpuz->setGeometry(x,y,100,100);
    karpuzlar_list.append(karpuz);
    karpuz->show();

}

void MainWindow ::karpuz_hareket(){

    int sayisi=karpuzlar_list.size();
    for(int i=0;i<sayisi;i++)
    {

        karpuzlar_list[i]->setGeometry(karpuzlar_list[i]->x(),
                                       karpuzlar_list[i]->y()+10,
                                       karpuzlar_list[i]->width(),
                                       karpuzlar_list[i]->height());

        if (karpuzlar_list[i]->tiklandimi){

           karpuzlar_list[i]->setStyleSheet("border-image: url(':/resim/2.png');");
            if(karpuzlar_list[i]->eklendi_mi==false){
               kesilen_karpuzlar.append(karpuzlar_list[i]);
               ui->kesilen_karpuz_label->setText(QString::number(kesilen_karpuzlar.size()));
               karpuzlar_list[i]->eklendi_mi=true;


           }


        }

        else{

            if(karpuzlar_list[i]->y()>800){
                if(karpuzlar_list[i]->eklendi_mi==false){
                    kacirilan_karpuzlar.append(karpuzlar_list[i]);
                    ui->kacirilan_karpuz_label->setText(QString::number(kacirilan_karpuzlar.size()));
                    karpuzlar_list[i]->eklendi_mi=true;


                }




            }


        }



    }

}


void MainWindow ::oyun_bitis(){

    ui->sure_label->setText(QString::number(sayac));
    sayac-=1;
    int max=0,i=0;

    if(sayac==-1){
        oyun_suresi->stop();
        hareket->stop();
        b_hareket->stop();
        zaman->stop();
        bomba_sure->stop();


        QFile file("skorlar.txt");

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, "Dosya Hatası!", "Skorlar.txt dosyasına ulaşılamıyor.");
            return;
        }

        QTextStream fileKonumlar(&file);
        QStringList skorlar;

        while (!fileKonumlar.atEnd())
        {
            QString line = fileKonumlar.readLine();
            skorlar.append(line);
        }


        file.close();



        for( i=0 ;i<skorlar.size();i++){

            if(skorlar[i].toInt()>max){
                max=skorlar[i].toInt();
            }


        }

        skorlar.append(QString::number(kesilen_karpuzlar.size()));

        QFile file1("skorlar.txt");

        if (!file1.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Dosya açılamadı.";

        }

        // Dosya yazma işlemi için bir QTextStream oluştur
        QTextStream out(&file1);

        // Veri yaz
        for(i=0;i<skorlar.size();i++){
        out << skorlar[i] << Qt:: endl;

        }
        // Dosyayı kapat
        file1.close();



        if(max>(kesilen_karpuzlar.size()-patlayan_bomba.size())){

            QMessageBox::information(this,"Bilgi!","Oyun Bitti! Maksimum Skoru Geçemediniz! \n Kesilen Karpuz Sayısı: "+QString::number(kesilen_karpuzlar.size())
                                                         +"\nKaçırılan Karpuz Sayısı: "+QString::number(kacirilan_karpuzlar.size())
                                                         +"\nPatlatılan Bomba Sayısı :"+QString::number(patlayan_bomba.size())
                                                         +"\nSkorunuz:"+QString::number(kesilen_karpuzlar.size()-patlayan_bomba.size())
                                                         +"\nMaksimum Skor: "+QString::number(max),"Ok");
        }

        else{

           QMessageBox::information(this,"Bilgi!","Oyun Bitti! Tebrikler Maksimum Skor Sizde! \n Kesilen Karpuz Sayısı: "+QString::number(kesilen_karpuzlar.size())
                                                         +"\nKaçırılan Karpuz Sayısı: "+QString::number(kacirilan_karpuzlar.size())
                                                         +"\nPatlatılan Bomba Sayısı :"+QString::number(patlayan_bomba.size())
                                                         +"\nSkorunuz:"+QString::number(kesilen_karpuzlar.size()-patlayan_bomba.size())
                                                         +"\nMaksimum Skor: "+QString::number(max),"Ok");
        }


        this->close();

    }



}


void MainWindow::bomba_olustur(){
    /* Dosya Okuma İşlemi */
    QFile file("konumlar.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Dosya Hatası!", "konumlar.txt dosyasına ulaşılamıyor.");
        return;
    }

    QTextStream fileKonumlar(&file);
    QStringList konumlar;

    while (!fileKonumlar.atEnd())
    {
        QString line = fileKonumlar.readLine();
        konumlar.append(line);
    }

    file.close();
    /* ./Dosya Okuma İşlemi */

    int randomIndex = QRandomGenerator::global()->bounded(0, konumlar.size());
    QStringList konum = konumlar[randomIndex].split(" ");
    int x = konum[0].toInt();
    int y = konum[1].toInt();

    bomba *bomb = new bomba(this);
    bomb->setStyleSheet("border-image: url(':/resim/bomb.png');");
    bomb->setGeometry(x,y,100,100);
    bomb_list.append(bomb);
    bomb->show();

}


void MainWindow ::bomb_hareket(){

    int sayisi=bomb_list.size();
    for(int i=0;i<sayisi;i++)
    {

        bomb_list[i]->setGeometry(bomb_list[i]->x(),
                                       bomb_list[i]->y()+10,
                                       bomb_list[i]->width(),
                                       bomb_list[i]->height());

        if (bomb_list[i]->bomba_tiklandimi){

           bomb_list[i]->setStyleSheet("border-image: url(':/resim/bombefect.png');");
            if(bomb_list[i]->bomba_eklendi_mi==false){
                patlayan_bomba.append(bomb_list[i]);
                ui->patlayan_label->setText(QString::number(patlayan_bomba.size()));
                bomb_list[i]->bomba_eklendi_mi=true;


            }


        }





    }

}



