#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include "ODALID.h"
#include "MfErrNo.h"
#include <QtGui>

QT_BEGIN_NAMESPACE
namespace Ui { class MaFenetre; }
QT_END_NAMESPACE

class MaFenetre : public QWidget
{
    Q_OBJECT

    public:
        MaFenetre(QWidget *parent = nullptr);
        ~MaFenetre();

    private slots:
        void on_Connect_clicked();
        void on_Quitter_clicked();
        void on_Lecture_clicked();
        void on_Ecriture_clicked();
        void on_Plus_clicked();
        void on_Moins_clicked();


    private:
        Ui::MaFenetre *ui;
        int16_t status;
        uint8_t key_index;
        uint8_t key_ff[6]= {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
        ReaderName MonLecteur;
        BYTE atq[2];
        BYTE sak[1];
        BYTE uid[12];
        uint32_t valeur;
        uint16_t uid_len = 12;
        BYTE sect_count = 0;
};
#endif // MAFENETRE_H
