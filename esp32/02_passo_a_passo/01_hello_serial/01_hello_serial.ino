/* Elaborado pelo Prof. Vagner Cordeiro */
/*
  01 - Hello Serial
  Objetivo: enviar mensagens ao computador pelo cabo USB.
  Ligacao: nenhuma, so o cabo USB.
  Depois de carregar, abra Ferramentas > Monitor Serial em 115200 baud.
  S3: ligue "USB CDC On Boot: Enabled" em Ferramentas.
*/

int contador = 0;  // conta quantas mensagens foram enviadas

void setup() {
  Serial.begin(115200);  // inicia a serial na velocidade 115200
  delay(1000);           // espera o Monitor Serial abrir
  Serial.println("Ola, ESP32!");
}

void loop() {
  contador++;
  Serial.print("Mensagem numero ");
  Serial.println(contador);
  delay(1000);  // espera 1 segundo
}

/*
  EXERCICIOS
  1) Troque a mensagem por "Ola, <seu nome>!".
  2) Mude o delay para 500 e veja a diferenca.
  3) Imprima tambem o dobro do contador (contador * 2).
*/
// Executar: abra na Arduino IDE (veja 01_conceitos\05_instalar_arduino_ide.html), escolha a placa ESP32 Dev Module (ou ESP32S3 Dev Module) e clique em Carregar
