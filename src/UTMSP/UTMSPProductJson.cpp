#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

class UTMSPProductJson {
public:
    QString utmspName;
    QString utmspLogoUrl;
    QString utmspSupportUrl;
    QString utmspDocumentationUrl;
    QString baseUrl;
    QMap<QString, QString> availableScopes;
    QVector<QJsonObject> availableServices;

    void parseJson(const QString &jsonFilePath) {
        QFile file(jsonFilePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Failed to open file:" << jsonFilePath;
            return;
        }

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (doc.isNull() || !doc.isObject()) {
            qWarning() << "Invalid JSON format";
            return;
        }

        QJsonObject root = doc.object();
        utmspName = root.value("utmsp_name").toString();
        utmspLogoUrl = root.value("utmsp_logo_url").toString();
        utmspSupportUrl = root.value("utmsp_support_url").toString();
        utmspDocumentationUrl = root.value("utmsp_documentation_url").toString();
        baseUrl = root.value("base_url").toString();

        QJsonObject availableScopesObj = root.value("available_scopes").toObject();
        for (auto it = availableScopesObj.begin(); it != availableScopesObj.end(); ++it) {
            availableScopes[it.key()] = it.value().toString();
        }

        QJsonArray availableServicesArray = root.value("available_services").toArray();
        for (const QJsonValue &serviceValue : availableServicesArray) {
            availableServices.append(serviceValue.toObject());
        }
    }
};