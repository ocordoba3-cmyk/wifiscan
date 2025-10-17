/* ESP32 WiFi Scanning example */

#include "WiFi.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing WiFi...");
  WiFi.mode(WIFI_STA);
  Serial.println("Setup done!");
}

void loop() {
  Serial.println("Scanning...");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("Scan done!");
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.println();
    Serial.print(n);
    Serial.println(" networks found");

    //MEJORA: detectar red con mejor señal
    int mejorRSSI = -1000;
    String mejorSSID = "";

    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");

      //MEJORA: comparar señal
      if (WiFi.RSSI(i) > mejorRSSI) {
        mejorRSSI = WiFi.RSSI(i);
        mejorSSID = WiFi.SSID(i);
      }

      delay(10);
    }

    //MEJORA: mostrar red más potente
    Serial.print("Mejor señal: ");
    Serial.print(mejorSSID);
    Serial.print(" (");
    Serial.print(mejorRSSI);
    Serial.println(" dBm)");
  }

  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}
