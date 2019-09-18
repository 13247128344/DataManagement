#include "AbstractCmd.h"

QMap<QString, std::function<QSharedPointer<AbstractCmd>()> > AbstractCmd::constructors;

void AbstractCmd::Register(QString method, std::function<QSharedPointer<AbstractCmd>()> constructor)
{
	constructors[method] = constructor;
}

QSharedPointer<AbstractCmd> AbstractCmd::Get(QString method)
{
	if (!constructors.contains(method))
	{
		return QSharedPointer<AbstractCmd>();
	}
	return constructors[method]();
}