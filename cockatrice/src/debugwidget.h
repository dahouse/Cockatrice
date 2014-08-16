#ifndef DEBUGWIDGET_H
#define DEBUGWIDGET_H

#include <QPlainTextEdit>
#include <QString>
#include <QWidget>

void debugMessageDisplayFunc(QtMsgType type, const QMessageLogContext &context, const QString &msg);

class DebugWidget : public QWidget {
	Q_OBJECT
public: 
	DebugWidget();
	~DebugWidget();
private slots:
	void dumpLog();
};

#endif