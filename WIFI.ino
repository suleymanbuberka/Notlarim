#include <ESP8266WiFi.h> // ESP8266 kütüphanesi dahil ediliyor

const char* ssid = "...";  // İnternet Ağının ismi
const char* password = "...."; // internet ağının şifresi
int RolePin1 = D0; // D0 pini RolePin1 ile eşleştiriliyor
int RolePin2 = D1; // D1 pini RolePin2 ile eşleştiriliyor
int RolePin3 = D2; // D2 pini RolePin3 ile eşleştiriliyor

 

int RoleDeger1= LOW; // 1.Rölenin durumu lojik-0 yapılıyor
int RoleDeger2= LOW; // 2.Rölenin durumu lojik-0 yapılıyor
int RoleDeger3= LOW; // 3.Rölenin durumu lojik-0 yapılıyor

WiFiServer server(80); // WiFi ağına 80. porttan bağlınılıyor

void setup() {
Serial.begin(115200);  //Seri iletişim başlatılıyor ve Baundrate hızı : 115200 
delay(10); // 10 ms bekleme

pinMode(RolePin1, OUTPUT); // D0 pini çıkış olarak ayarlanıyor
pinMode(RolePin2, OUTPUT); // D1 pini çıkış olarak ayarlanıyor
pinMode(RolePin3, OUTPUT); // D2 pini çıkış olarak ayarlanıyor
digitalWrite(RolePin1, LOW); // D0 pini lojik-0 olarak ayarlanıyor
digitalWrite(RolePin2, LOW); // D1 pini lojik-0 olarak ayarlanıyor
digitalWrite(RolePin3, LOW); // D2 pini lojik-0 olarak ayarlanıyor

// WiFi ağına bağlanma bölümü
Serial.println();
Serial.println();
Serial.print("Baglanilan ag :");
Serial.println(ssid);

WiFi.begin(ssid, password); // Bağlanılan Ağın adı ve şifresi girilen internet ağına bağlanılıp ardından  WiFi başlatılıyor 

while (WiFi.status() != WL_CONNECTED) { // Ağa bağlanılıncaya kadar “.” gönderilir
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi baglanildi…");

//Server başlatılıyor
server.begin();
Serial.println("Server baslatildi….");

// NodeMCU ait IP adresi alınıyor
Serial.print("Baglanmak icin kullanilacak IP : ");
Serial.print("http://");
Serial.print(WiFi.localIP()); // Yerel ağ içerisindeki IP alınıyor
Serial.println("/");

}

void loop() {
//NodeMCu WiFi agina baglanilip baglanilmadagi kontrol ediliyor
WiFiClient client = server.available();
if (!client) {
return;
}

// NodeMCU veri gelnceye kadar bekleme bölümü
Serial.println("Yeni cihaz");
while(!client.available()){
delay(1);
}

// Url Adresin ilk satırının alındığı bölüm
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();



// Node MCU yayımladığı Web sitesi 
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // do not forget this one
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<HEAD><TITLE>WI-FI Uygulamasi</TITLE>");
client.println("<BODY><H1>WI-FI ILE BMS VERI OKUMA PROJESINE HOSGELDINIZ</H1>");

  // Web sayfasında 1.Röleye ait kontrol paneli (bu kısımda bmsten gelen veri yazılacak.)
  client.println("<fieldset>");
  client.println("<legend>SOC OKUMA</legend>");
  client.print("SOC :");
  
delay(25);

client.println("<H2>PROJE DETAYLARI EKLENECEKTIR.</H2>");
client.println("</BODY>");
client.println("</HEAD>");
client.println("</html>");
delay(100);
Serial.println("Client bağlantı kapatıldı");
Serial.println("");
}

