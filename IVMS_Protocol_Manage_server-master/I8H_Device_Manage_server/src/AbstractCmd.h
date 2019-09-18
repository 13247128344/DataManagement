#pragma once

#include <QMap>
#include <QSharedPointer>
#include <QString>
#include <functional>

class AbstractCmd {
public:
	virtual int process(char* req, int reqLength, char* &resp, int &respLength) = 0;
	virtual ~AbstractCmd() {};

	static void Register(QString method, std::function<QSharedPointer<AbstractCmd>()> constructor);
	static QSharedPointer<AbstractCmd> Get(QString method);

protected:
	AbstractCmd() {};

private:
	static QMap<QString, std::function<QSharedPointer<AbstractCmd>()> > constructors;
};