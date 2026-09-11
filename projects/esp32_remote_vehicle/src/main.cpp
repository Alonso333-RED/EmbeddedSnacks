#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>

#include "config.h"

WebServer server(80);

// Serve the main HTML page
void handleRoot() {
    File file = LittleFS.open("/index.html", "r");

    if (!file) {
        server.send(500, "text/plain", "Failed to open index.html");
        return;
    }

    server.streamFile(file, "text/html");
    file.close();
}

// Serve CSS files
void handleCSS() {
    File file = LittleFS.open("/css/style.css", "r");

    if (!file) {
        server.send(404, "text/plain", "CSS file not found");
        return;
    }

    server.streamFile(file, "text/css");
    file.close();
}

// Serve JavaScript files
void handleJS() {
    File file = LittleFS.open("/js/script.js", "r");

    if (!file) {
        server.send(404, "text/plain", "JavaScript file not found");
        return;
    }

    server.streamFile(file, "application/javascript");
    file.close();
}

// Vehicle commands
void handleForward() {
    Serial.println("Moving forward");
    server.send(200, "text/plain", "OK");
}

void handleBackward() {
    Serial.println("Moving backward");
    server.send(200, "text/plain", "OK");
}

void handleLeft() {
    Serial.println("Turning left");
    server.send(200, "text/plain", "OK");
}

void handleRight() {
    Serial.println("Turning right");
    server.send(200, "text/plain", "OK");
}

void handleStop() {
    Serial.println("Stopping");
    server.send(200, "text/plain", "OK");
}

void setup() {
    Serial.begin(115200);

    // Initialize LittleFS
    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS initialization failed");
        return;
    }

    Serial.println("LittleFS initialized");

    // Connect to Wi-Fi
    Serial.print("Connecting to Wi-Fi");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("Wi-Fi connected");

    Serial.print("ESP32 IP address: ");
    Serial.println(WiFi.localIP());

    // Web pages
    server.on("/", HTTP_GET, handleRoot);
    server.on("/css/style.css", HTTP_GET, handleCSS);
    server.on("/js/script.js", HTTP_GET, handleJS);

    // Vehicle API
    server.on("/forward", HTTP_GET, handleForward);
    server.on("/backward", HTTP_GET, handleBackward);
    server.on("/left", HTTP_GET, handleLeft);
    server.on("/right", HTTP_GET, handleRight);
    server.on("/stop", HTTP_GET, handleStop);

    // Start server
    server.begin();

    Serial.println("Web server started");

    Serial.print("LittleFS total: ");
    Serial.println(LittleFS.totalBytes());

    Serial.print("LittleFS used: ");
    Serial.println(LittleFS.usedBytes());

    File root = LittleFS.open("/");
    File file = root.openNextFile();

    while (file) {
        Serial.print("FILE: ");
        Serial.println(file.name());

        file = root.openNextFile();
    }
}

void loop() {
    server.handleClient();
}