/*                07/12/2020
 *    Code écrit par Axel Coutisson et Celine Waldner
 *
 *
 */

//Includes
//========================================//
#include "mafenetre.h"
#include "ui_mafenetre.h"
#include <cstring>
//========================================//


//Constructeur /destructeur
//========================================//
MaFenetre::MaFenetre(QWidget *parent): QWidget(parent), ui(new Ui::MaFenetre)
{
    ui->setupUi(this);
}

MaFenetre::~MaFenetre()
{
    delete ui;
}
//========================================//



//variable global
//========================================//

//========================================//



//Fonction Onclicked
//========================================//
void MaFenetre::on_Connect_clicked()
{
    qDebug() << "[Connect]:Lancement de la fonction";
    status = 0;
    MonLecteur.Type = ReaderCDC;
    MonLecteur.device = 0;
    qDebug() << "[Connect]:OpenCom du Lecteur, veuillez attendre ...";
    status = OpenCOM(&MonLecteur);
    if(status == MI_OK)
        qDebug() << "[Connect]: OPENCOM retourne " << status << " Connection établie";
    else
    {
        qDebug() << "[Connect]: OPENCOM retourne " << status << " ECHEC ";
        return;
    }

    char version[30];
    uint8_t serial[4];
    char stackReader[20];

    status = Version(&MonLecteur, version, serial, stackReader);
    if (status == MI_OK)
    {
        ui->Affichage->setText(version);
        ui->Affichage->update();
    }
    else
        qDebug() << "[Connect]: une erreur s'est produite lors de l'appelle de la version";


    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &valeur,Auth_KeyB, 3);
    on_Lecture_clicked();
    ui->fenetreValeur->setText(QString::number(valeur));
    ui->Pas->setValue(0);

}

void MaFenetre::on_Quitter_clicked()
{
    int16_t status = 0;
    RF_Power_Control (&MonLecteur, FALSE, 0);
    status = LEDBuzzer(&MonLecteur, LED_OFF);
    status = CloseCOM(&MonLecteur);
    qApp->quit();
}



//=============Lecture Ecriture================//
void MaFenetre::on_Lecture_clicked()
{
    int status = 0;
    status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);

    RF_Power_Control(&MonLecteur, TRUE, 0);
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);

    unsigned char dataNom[10];
    unsigned char dataPrenom[10];

    status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 10, dataNom, Auth_KeyA, 2);
    status = Mf_Classic_Read_Block(&MonLecteur, TRUE, 9, dataPrenom, Auth_KeyA, 2);

    QString nom = "";
    QString prenom = "";

    for (int i = 0; i < 10; i++){
        nom += dataNom[i];
        prenom += dataPrenom[i];
    }
    ui->fenetreNom->setText(nom);
    ui->fenetrePrenom->setText(prenom);
    status = LEDBuzzer(&MonLecteur, LED_RED_OFF);

}

void MaFenetre::on_Ecriture_clicked(){
    char nom[10];
    char prenom[10];
    for(int i = 0; i<10; i++)
    {
        nom[i] = ' ';
        prenom[i] = ' ';
    }

    unsigned char u_nom[10];
    unsigned char u_prenom[10];
    status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);

    RF_Power_Control(&MonLecteur, TRUE, 0);
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);

    sprintf(nom, ui->fenetreNom->toPlainText().toUtf8().data(), 10);
    sprintf(prenom, ui->fenetrePrenom->toPlainText().toUtf8().data(), 10);
    for(int i = 0; i<10; i++)
    {
        u_nom[i] = nom[i];
        u_prenom[i] = prenom[i];
    }
    status = Mf_Classic_Write_Block(&MonLecteur, TRUE, 10, u_nom, Auth_KeyB, 2);
    status = Mf_Classic_Write_Block(&MonLecteur, TRUE, 9, u_prenom, Auth_KeyB, 2);
    status = LEDBuzzer(&MonLecteur, LED_RED_OFF);

}
//========================================//



//===============INCREMENT=================//

void MaFenetre::on_Plus_clicked(){
    status = 0;
    status = LEDBuzzer(&MonLecteur, LED_RED_ON);

    RF_Power_Control(&MonLecteur, TRUE, 0);
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    uint32_t valeur;
    status = Mf_Classic_Increment_Value(&MonLecteur ,TRUE, 14, ui->Pas->value(), 14, Auth_KeyB, 3);
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &valeur,Auth_KeyB, 3);

    ui->fenetreValeur->setText(QString::number((int)valeur));
    status = LEDBuzzer(&MonLecteur, LED_RED_OFF);
}

void MaFenetre::on_Moins_clicked(){
    status = 0;
    status = LEDBuzzer(&MonLecteur, LED_RED_ON);
    RF_Power_Control(&MonLecteur, TRUE, 0);
    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    uint32_t valeur;
    status = Mf_Classic_Decrement_Value(&MonLecteur ,TRUE, 14, ui->Pas->value(), 14, Auth_KeyB, 3);
    status = Mf_Classic_Read_Value(&MonLecteur, TRUE, 14, &valeur,Auth_KeyB, 3);

    ui->fenetreValeur->setText(QString::number((int)valeur));
    status = LEDBuzzer(&MonLecteur, LED_RED_OFF);
}

//========================================//

