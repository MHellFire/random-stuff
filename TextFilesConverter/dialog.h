#ifndef DIALOG_H
#define DIALOG_H

#include "ui_dialog.h"

#include <QtGui/QDialog>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::DialogClass ui;

    QString inFileName, outFileName;

private slots:
    void onOpenFile();
    void onSaveFile();
    void onConvert1();
    void onConvert2();
    void onConvert3();
    void onConvert4();
};

#endif // DIALOG_H
