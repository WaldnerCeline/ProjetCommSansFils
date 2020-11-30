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


void MaFenetre::on_Connect_clicked()
{
    int16_t status = 0;
    //MonLecteur.Type = ReaderTCP;
    //strcpy(MonLecteur.IPReader, pszHost);
    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;
    status = OpenCOM(&MonLecteur);
    qDebug() << "OPENCOM1" << status;

    char version[30];
    uint8_t serial[4];
    char stackReader[20];

    status = Version(&MonLecteur, version, serial, stackReader);
    ui->Affichage->setText(version);
    ui->Affichage->update();


}

void MaFenetre::on_saisi_clicked()
{
    QString Text = ui->fenetre_saisi->toPlainText();
    qDebug() << "Text : " << Text;

}

void MaFenetre::on_Quitter_clicked()
{
    int16_t status = 0;
    RF_Power_Control (&MonLecteur, FALSE, 0);
    status = LEDBuzzer(&MonLecteur, LED_OFF);
    status = CloseCOM(&MonLecteur);
    qApp->quit();
}

