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
