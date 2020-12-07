/*                07/12/2020
 *    Code écrit par Axel Coutisson et Celine Waldner
 *
 *
 */

//Includes
//========================================//
#include "mafenetre.h"
#include "ui_mafenetre.h"
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

void MaFenetre::on_Acquisition_clicked()
{
    qDebug() << "[Acquisition]: Lancement de la fonction";
    qDebug() << "[Acquisition]: affichage de la data avant appelle de la fonction:" << key_ff;
    status = LEDBuzzer(&MonLecteur, LED_YELLOW_ON);
    if(status !=MI_OK)
    {
        qDebug() << "[Acquisition]: ERREUR affichage de la led jaune";
    }
    key_index = 0;
    status = Mf_Classic_LoadKey(&MonLecteur, TRUE , key_ff, key_index);//Auth_KeyA = true
    if (status != MI_OK){
        qDebug() << "Load Key [FAILED]\n";
        return;
    }
    // RF field ON
    RF_Power_Control(&MonLecteur, TRUE, 0);

    status = ISO14443_3_A_PollCard(&MonLecteur, atq, sak, uid, &uid_len);
    if (status != MI_OK){
        qDebug() << "No available tag in RF field\n";
        return;
    }

    qDebug() <<"Tag found: UID=";
    for (int i = 0; i < uid_len; i++)
        qDebug() << uid[i];
    qDebug() <<" ATQ= " << atq[1] << ' ' << atq[0] <<" SAK=" <<sak[0];

}
//========================================//

