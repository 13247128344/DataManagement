#pragma once

#include "ivms_public_global.h"
#include "ivms_public.h"
#include <QJsonArray>
#include <QJsonObject>

void insertDeviceNode(CMS_CONNECT_PARSE_NodeType type, CMS_CONNECT_PARSE_Node *pNode, QJsonArray array);
void insertAIandAO(CMS_CONNECT_PARSE_DeviceNode *pNode);
bool IVMS_PUBLIC_EXPORT InitTreeModel(QJsonObject obj);
QString IVMS_PUBLIC_EXPORT sendGrpcRequestToIVmsServer(QString from,QString topic,QString cmd,QString data, int connectTime = 12 ,int bufferSize = 1024);