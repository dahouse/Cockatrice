#include <QApplication>
#include <QBoxLayout>
#include <QDebug>
#include <QFont>
#include <QPushButton>
#include <QTextStream>
#include <QTime>
#include <QThread>
#include "debugwidget.h"

QPlainTextEdit* DEBUG_MESSAGE_DISPLAY_TEXTEDIT = 0;

DebugWidget::DebugWidget()  {
	setWindowTitle(tr("Debug Log"));
	setAttribute(Qt::WA_QuitOnClose, false);

	QBoxLayout* layout = new QVBoxLayout();
	setLayout(layout);
	
	QPlainTextEdit *debugTextEdit = new QPlainTextEdit(this);
	QFont font = QFont("Monospace");
	font.setStyleHint(QFont::TypeWriter);
	debugTextEdit->setFont(font);
	debugTextEdit->setReadOnly(true);
	layout->addWidget(debugTextEdit);
	DEBUG_MESSAGE_DISPLAY_TEXTEDIT = debugTextEdit;

	QPushButton *saveBtn = new QPushButton("Save", this);
	layout->addWidget(saveBtn);

	connect(saveBtn, SIGNAL(clicked()), this, SLOT(dumpLog()));

	qInstallMessageHandler(debugMessageDisplayFunc);
}

DebugWidget::~DebugWidget() {
	delete DEBUG_MESSAGE_DISPLAY_TEXTEDIT;
}

void DebugWidget::dumpLog() {
	qDebug() << "Button pressed.";
	if (DEBUG_MESSAGE_DISPLAY_TEXTEDIT) {
		QDateTime dt = QDateTime::currentDateTime();
		QFile file("debug-" + dt.toString("dd-MM-yyyy_hh.mm.ss") + ".txt");
		file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
		QTextStream out(&file);
		out << DEBUG_MESSAGE_DISPLAY_TEXTEDIT->toPlainText();
		file.close();
	}
}

void debugMessageDisplayFunc(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString msgType;
	switch (type) {
	case QtDebugMsg:
		msgType = "Debug";
		break;
	case QtWarningMsg:
		msgType = "Warning";
		break;
	case QtCriticalMsg:
		msgType = "Critical";
		break;
	case QtFatalMsg:
		msgType = "Fatal";
		break;
	default:
		return;
	}

	QTime now = QTime::currentTime();
	QString formattedMessage = QString::fromLatin1("%1 %2 %3").arg(now.toString("hh:mm:ss:zzz")).arg(msgType).arg(msg);

	{
		bool isMainThread = QThread::currentThread() == QApplication::instance()->thread();
		if (DEBUG_MESSAGE_DISPLAY_TEXTEDIT) {
			if (isMainThread)
				DEBUG_MESSAGE_DISPLAY_TEXTEDIT->appendPlainText(formattedMessage);
			else
				QMetaObject::invokeMethod(DEBUG_MESSAGE_DISPLAY_TEXTEDIT, "appendPlainText", Qt::QueuedConnection, Q_ARG(QString, formattedMessage));
		}
	}
}