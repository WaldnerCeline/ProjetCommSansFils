#pragma comment(lib, "ODALID.lib")
#include "mafenetre.h"
#include "ui_mafenetre.h"
#include "ODALID.h"
#include <QtGui>

MaFenetre::MaFenetre(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MaFenetre)
{
    ui->setupUi(this);
}

MaFenetre::~MaFenetre()
{
    delete ui;
}

ReaderName MonLecteur;

char pszHost[] = "192.168.1.4";

void MaFenetre::on_Connect_clicked(){
    uint16_t status =0;
    //MonLecteur.Type = ReaderTCP;
    //strcpy(MonLecteur.IPReader, pszHost);
    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;
    status = OpenCOM (&MonLecteur);
    qDebug() << "OpenCOM1" << status;
}

