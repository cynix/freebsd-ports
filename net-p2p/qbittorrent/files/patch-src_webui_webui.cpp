--- src/base/preferences.cpp
+++ src/base/preferences.cpp
@@ -449,6 +449,11 @@ void Preferences::setServerDomains(const QString &str)
     setValue("Preferences/WebUI/ServerDomains", str);
 }
 
+QString Preferences::getWebUiAddress() const
+{
+    return value("Preferences/WebUI/Address", "").toString();
+}
+
 quint16 Preferences::getWebUiPort() const
 {
     return value("Preferences/WebUI/Port", 8080).toInt();
--- src/base/preferences.h
+++ src/base/preferences.h
@@ -177,6 +177,7 @@ public:
     void setWebUiLocalAuthEnabled(bool enabled);
     QString getServerDomains() const;
     void setServerDomains(const QString &str);
+    QString getWebUiAddress() const;
     quint16 getWebUiPort() const;
     void setWebUiPort(quint16 port);
     bool useUPnPForWebUIPort() const;
--- src/webui/webui.cpp
+++ src/webui/webui.cpp
@@ -88,7 +88,9 @@ void WebUI::init()
 #endif
 
         if (!m_httpServer->isListening()) {
-            bool success = m_httpServer->listen(QHostAddress::Any, m_port);
+            const QString ifaceAddr = pref->getWebUiAddress();
+            const QHostAddress addr = ifaceAddr.isEmpty() ? QHostAddress::Any : QHostAddress(ifaceAddr);
+            bool success = m_httpServer->listen(addr, m_port);
             if (success)
                 logger->addMessage(tr("Web UI: Now listening on port %1").arg(m_port));
             else
