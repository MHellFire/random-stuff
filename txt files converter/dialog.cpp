/*********************************************************************************
 * This file is part of TxtFilesConverter.                                       *
 *                                                                               *
 * Copyright © 2009 Mariusz Helfajer                                             *
 *                                                                               *
 * This software may be modified and distributed under the terms                 *
 * of the MIT license.  See the LICENSE files for details.                       *
 *                                                                               *
 * Permission is hereby granted, free of charge, to any person obtaining a copy  *
 * of this software and associated documentation files (the "Software"), to deal *
 * in the Software without restriction, including without limitation the rights  *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     *
 * copies of the Software, and to permit persons to whom the Software is         *
 * furnished to do so, subject to the following conditions:                      *
 *                                                                               *
 * The above copyright notice and this permission notice shall be included in    *
 * all copies or substantial portions of the Software.                           *
 *                                                                               *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     *
 * THE SOFTWARE.                                                                 *
 * *******************************************************************************/

#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    connect(ui.pushButtonOpen, SIGNAL(clicked()), this, SLOT(onOpenFile()));
    connect(ui.pushButtonSave, SIGNAL(clicked()), this, SLOT(onSaveFile()));
    connect(ui.pushButton1, SIGNAL(clicked()), this, SLOT(onConvert1()));
    connect(ui.pushButton2, SIGNAL(clicked()), this, SLOT(onConvert2()));
    connect(ui.pushButton3, SIGNAL(clicked()), this, SLOT(onConvert3()));
    connect(ui.pushButton4, SIGNAL(clicked()), this, SLOT(onConvert4()));

    ui.label->setText(tr("Please select files"));
}

Dialog::~Dialog()
{
}

void Dialog::onOpenFile()
{
    inFileName = "";

    inFileName = QFileDialog::getOpenFileName(this, tr("Load input file..."), QCoreApplication::applicationDirPath(), tr("Text files (*.txt);;All files (*.*)"));

    if (inFileName.isEmpty())
        return;

    ui.pushButtonSave->setEnabled(true);
}

void Dialog::onSaveFile()
{
    outFileName = "";

    outFileName = QFileDialog::getSaveFileName(this, tr("Save output file..."), QCoreApplication::applicationDirPath()+"/ports.txt", tr("Text files (*.txt);;All files (*.*)"));

    if (outFileName.isEmpty())
        return;

    ui.label->setText(tr("Ready to convert"));
    ui.pushButton1->setEnabled(true);
    ui.pushButton2->setEnabled(true);
    ui.pushButton3->setEnabled(true);
    ui.pushButton4->setEnabled(true);
}

// keyword
void Dialog::onConvert1()
{
    QFile inFile(inFileName);

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, tr("Unable to open input file"), inFile.errorString());
        return;
    }

    QFile outFile(outFileName);

    if (!outFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open output file"), outFile.errorString());
        return;
    }

    QString line, str, tmpStr, k;
    int x, y, z;

    QTextStream in(&inFile);
    //in.setCodec("UTF-8");

    QTextStream out(&outFile);
    out.setCodec("UTF-8");

    while (!in.atEnd())
    {
        line = in.readLine();

        if ((x = line.indexOf("/tcp", 0, Qt::CaseSensitive)) == -1)
            if ((x = line.indexOf("/udp", 0, Qt::CaseSensitive)) == -1)
                return;

        y = line.lastIndexOf(" ", x, Qt::CaseInsensitive);
        str = line.mid(y+1, (z = line.indexOf(" ", y+1, Qt::CaseInsensitive)) - y).simplified();
        QStringList strList = str.split("/");

        k = line.left(y).simplified();

        if (!k.isEmpty())
        {
            out << strList.at(1);
            out << " ";
            out << strList.at(0);
            out << "=";
            out << k;
            out << "\r\n";
        }
    }

    inFile.close();
    outFile.close();

    QMessageBox::information(this, tr("Information"), tr("Convertion successfully completed."));
}

// description
void Dialog::onConvert2()
{
    QFile inFile(inFileName);

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, tr("Unable to open input file"), inFile.errorString());
        return;
    }

    QFile outFile(outFileName);

    if (!outFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open output file"), outFile.errorString());
        return;
    }

    QString line, str, tmpStr, d;
    int x, y, z;

    QTextStream in(&inFile);
    //in.setCodec("UTF-8");

    QTextStream out(&outFile);
    out.setCodec("UTF-8");

    while (!in.atEnd())
    {
        line = in.readLine();

        if ((x = line.indexOf("/tcp", 0, Qt::CaseSensitive)) == -1)
            if ((x = line.indexOf("/udp", 0, Qt::CaseSensitive)) == -1)
                return;

        y = line.lastIndexOf(" ", x, Qt::CaseInsensitive);
        str = line.mid(y+1, (z = line.indexOf(" ", y+1, Qt::CaseInsensitive)) - y).simplified();
        QStringList strList = str.split("/");

        d = line.right(line.length() - z).simplified();

        if (!d.isEmpty())
        {
            out << strList.at(1);
            out << " ";
            out << strList.at(0);
            out << "=";
            out << d;
            out << "\r\n";
        }
    }

    inFile.close();
    outFile.close();

    QMessageBox::information(this, tr("Information"), tr("Convertion successfully completed."));
}

// keyword [description]
void Dialog::onConvert3()
{
    QFile inFile(inFileName);

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, tr("Unable to open input file"), inFile.errorString());
        return;
    }

    QFile outFile(outFileName);

    if (!outFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open output file"), outFile.errorString());
        return;
    }

    QString line, str, tmpStr;
    int x, y, z;

    QTextStream in(&inFile);
    //in.setCodec("UTF-8");

    QTextStream out(&outFile);
    out.setCodec("UTF-8");

    while (!in.atEnd())
    {
        line = in.readLine();

        if ((x = line.indexOf("/tcp", 0, Qt::CaseSensitive)) == -1)
            if ((x = line.indexOf("/udp", 0, Qt::CaseSensitive)) == -1)
                return;

        y = line.lastIndexOf(" ", x, Qt::CaseInsensitive);
        str = line.mid(y+1, (z = line.indexOf(" ", y+1, Qt::CaseInsensitive)) - y).simplified();
        QStringList strList = str.split("/");

        out << strList.at(1);
        out << " ";
        out << strList.at(0);
        out << "=";
        out << line.left(y).simplified();
        out << " [";
        out << line.right(line.length() - z).simplified();
        out << "]";
        out << "\r\n";
    }

    inFile.close();
    outFile.close();

    QMessageBox::information(this, tr("Information"), tr("Convertion successfully completed."));
}

// description [keyword]
void Dialog::onConvert4()
{
    QFile inFile(inFileName);

    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this, tr("Unable to open input file"), inFile.errorString());
        return;
    }

    QFile outFile(outFileName);

    if (!outFile.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(this, tr("Unable to open output file"), outFile.errorString());
        return;
    }

    QString line, str, tmpStr;
    int x, y, z;

    QTextStream in(&inFile);
    //in.setCodec("UTF-8");

    QTextStream out(&outFile);
    out.setCodec("UTF-8");

    while (!in.atEnd())
    {
        line = in.readLine();

        if ((x = line.indexOf("/tcp", 0, Qt::CaseSensitive)) == -1)
            if ((x = line.indexOf("/udp", 0, Qt::CaseSensitive)) == -1)
                return;

        y = line.lastIndexOf(" ", x, Qt::CaseInsensitive);
        str = line.mid(y+1, (z = line.indexOf(" ", y+1, Qt::CaseInsensitive)) - y).simplified();
        QStringList strList = str.split("/");

        out << strList.at(1);
        out << " ";
        out << strList.at(0);
        out << "=";
        out << line.right(line.length() - z).simplified();
        out << " [";
        out << line.left(y).simplified();
        out << "]";
        out << "\r\n";
    }

    inFile.close();
    outFile.close();

    QMessageBox::information(this, tr("Information"), tr("Convertion successfully completed."));
}
