/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "mainwindow.h"
#include "scribblearea.h"

//! [0]
MainWindow::MainWindow()
{	
	srand((unsigned int)time(NULL));
	scribbleArea = new ScribbleArea;
	answerArea = new AnswerArea;
	setCentralWidget(answerArea);

	createActions();
	createMenus();

	setWindowTitle(tr("Experiment"));
	resize(1000, 360);

	showDialog();
}
//! [0]

void MainWindow::showDialog() {
	SubWindow subwindow;

	hide();

	if (QDialog::Accepted == subwindow.exec()) {
		qDebug() << "working accepted";
	}

	subwindow.getInformation(weight);

	qDebug() << "Modified : " << weight[0] << ", " << weight[1] << ", " << weight[2] << ", " << weight[3];

	answerArea->setWeight(weight);
	
	show();
}

//! [1]
void MainWindow::closeEvent(QCloseEvent *event)
//! [1] //! [2]
{
	if (maybeSave()) {
		event->accept();
	}
	else {
		event->ignore();
	}
}

//! [2]
/*
void MainWindow::keyPressEvent(QKeyEvent *event) {

	if (event->key() == Qt::Key_F1) {
		if (cnt >= data.getTotalNumberOfData() && repeat < 3) {
			repeat++;
			cnt = 0;
			data.generateRandomOrder();
			//QMessageBox::StandardButton ret;
			//ret = QMessageBox::warning(this, tr("Scribble"),
			//	tr("Experiment test set is finished.\n"
			//		"Thank you for your effort!"), QMessageBox::Close);
			//return;
		}
		else {
			qDebug() << "F1 pressed from main window";
			// generate file name by order
			data.generateFileName(data.getOrder(cnt));
			// retrieve data from existing file
			data.readfile();
			// normalize the amplitude for each actuator
			data.normalize(weight[0], weight[1], weight[2], weight[3]);
			// multiply max amplitude based on each users
			data.applyAmplitude(1.0);
			// create the task and initialize the default setting of daq
			daq.init();
			// set samping rate and size for channel on daq
			daq.setSampleClock(data.getSampRate(), data.getDataSize() / 2);
			// give data pointers to daq and write datas
			daq.write(data.getData1Ptr(), data.getData2Ptr());
			// actuate vibration
			daq.start();
			// after play, clear task and taskHandle to re-create
			daq.stop();
		}
	}
	else if (event->key() == Qt::Key_F2) {
		// check the pressed key
		qDebug() << "F2 pressed from main window";
		// check the actuated file number
		qDebug() << "File : " << data.getOrder(cnt);

		// making format for output filename
		// if order number is smaller then 10
		if (data.getOrder(cnt) < 10) {
			auto filename = QString("C:\\SDK\\Qt\\Examples\\Qt-5.10.1\\widgets\\widgets\\scribble-ver1.0\\Result\\00%1.jpg").arg(data.getOrder(cnt));

			// save image with name
			if (scribbleArea->saveImage(filename, "JPG"))
				qDebug() << "Successfully saved " << filename << "jpg";
		}
		// if order number is bigger then 10, smaller then 100
		else if (data.getOrder(cnt) < 100) {
			auto filename = QString("C:\\SDK\\Qt\\Examples\\Qt-5.10.1\\widgets\\widgets\\scribble-ver1.0\\Result\\0%1.jpg").arg(data.getOrder(cnt));

			// save image with name
			if (scribbleArea->saveImage(filename, "JPG"))
				qDebug() << "Successfully saved " << filename << "jpg";
		}

		cnt++;
	}
}
*/
//! [3]
void MainWindow::open()
//! [3] //! [4]
{
	if (maybeSave()) {
		QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File"), QDir::currentPath());
		if (!fileName.isEmpty())
			scribbleArea->openImage(fileName);
	}
}
//! [4]

//! [5]
void MainWindow::save()
//! [5] //! [6]
{
	QAction *action = qobject_cast<QAction *>(sender());
	QByteArray fileFormat = action->data().toByteArray();
	saveFile(fileFormat);
}
//! [6]

//! [7]
void MainWindow::penColor()
//! [7] //! [8]
{
	QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
	if (newColor.isValid())
		scribbleArea->setPenColor(newColor);
}
//! [8]

//! [9]
void MainWindow::penWidth()
//! [9] //! [10]
{
	/*bool ok;
	int newAmp = QInputDialog::getDouble(this, tr("Scribble"),
		tr("Change amplitude :"),
//		data.getAmplitude(),
		0.01, 1.0, 0.01, &ok);
	if (ok)
//		data.applyAmplitude(newAmp);
*/}
//! [10]

//! [11]
void MainWindow::about()
//! [11] //! [12]
{
	QMessageBox::about(this, tr("About Scribble"),
		tr("<p>The <b>Scribble</b> example shows how to use QMainWindow as the "
			"base widget for an application, and how to reimplement some of "
			"QWidget's event handlers to receive the events generated for "
			"the application's widgets:</p><p> We reimplement the mouse event "
			"handlers to facilitate drawing, the paint event handler to "
			"update the application and the resize event handler to optimize "
			"the application's appearance. In addition we reimplement the "
			"close event handler to intercept the close events before "
			"terminating the application.</p><p> The example also demonstrates "
			"how to use QPainter to draw an image in real time, as well as "
			"to repaint widgets.</p>"));
}
//! [12]

//! [13]
void MainWindow::createActions()
//! [13] //! [14]
{
	openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	foreach(QByteArray format, QImageWriter::supportedImageFormats()) {
		QString text = tr("%1...").arg(QString(format).toUpper());

		QAction *action = new QAction(text, this);
		action->setData(format);
		connect(action, SIGNAL(triggered()), this, SLOT(save()));
		saveAsActs.append(action);
	}

	printAct = new QAction(tr("&Print..."), this);
	connect(printAct, SIGNAL(triggered()), scribbleArea, SLOT(print()));

	exitAct = new QAction(tr("E&xit"), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

	penColorAct = new QAction(tr("&Pen Color..."), this);
	connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

	penWidthAct = new QAction(tr("C&hange Amplitude..."), this);
	connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

	clearScreenAct = new QAction(tr("&Clear Screen"), this);
	connect(clearScreenAct, SIGNAL(triggered()),
		scribbleArea, SLOT(clearImage()));

	aboutAct = new QAction(tr("&About"), this);
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAct = new QAction(tr("About &Qt"), this);
	connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}
//! [14]

//! [15]
void MainWindow::createMenus()
//! [15] //! [16]
{
	saveAsMenu = new QMenu(tr("&Save As"), this);
	foreach(QAction *action, saveAsActs)
		saveAsMenu->addAction(action);

	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addMenu(saveAsMenu);
	fileMenu->addAction(printAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	optionMenu = new QMenu(tr("&Options"), this);
	optionMenu->addAction(penColorAct);
	optionMenu->addAction(penWidthAct);
	optionMenu->addSeparator();
	optionMenu->addAction(clearScreenAct);

	helpMenu = new QMenu(tr("&Help"), this);
	helpMenu->addAction(aboutAct);
	helpMenu->addAction(aboutQtAct);

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(optionMenu);
	menuBar()->addMenu(helpMenu);
}
//! [16]

//! [17]
bool MainWindow::maybeSave()
//! [17] //! [18]
{
	if (scribbleArea->isModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Scribble"),
			tr("The image has been modified.\n"
				"Do you want to save your changes?"),
			QMessageBox::Save | QMessageBox::Discard
			| QMessageBox::Cancel);
		if (ret == QMessageBox::Save) {
			return saveFile("png");
		}
		else if (ret == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}
//! [18]

//! [19]
bool MainWindow::saveFile(const QByteArray &fileFormat)
//! [19] //! [20]
{
	QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		initialPath,
		tr("%1 Files (*.%2);;All Files (*)")
		.arg(QString::fromLatin1(fileFormat.toUpper()))
		.arg(QString::fromLatin1(fileFormat)));
	if (fileName.isEmpty()) {
		return false;
	}
	else {
		return scribbleArea->saveImage(fileName, fileFormat.constData());
	}
}
//! [20]
