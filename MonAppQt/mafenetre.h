#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>

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

private:
    Ui::MaFenetre *ui;
};
#endif // MAFENETRE_H
