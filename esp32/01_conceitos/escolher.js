// Elaborado pelo Prof. Vagner Cordeiro
// Logica do escolhedor de placa. Recebe as respostas e devolve {placa, motivos}.
// respostas: { wifi, bluetooth ('nenhum'|'ble'|'classic'), usbNativo, cameraIA, bateria, barato }
function recomendar(respostas) {
  var r = respostas || {};
  var motivos = [];
  var placa;

  if (r.bluetooth === 'classic') {
    placa = 'ESP32 classico (ESP32 Dev Module)';
    motivos.push('Bluetooth Classic (audio, serial) so existe no ESP32 classico.');
    if (r.usbNativo || r.cameraIA) {
      motivos.push('Atencao: USB nativo e IA ficam limitados no classico; o S3 nao tem Bluetooth Classic.');
    }
  } else if (r.usbNativo || r.cameraIA) {
    placa = 'ESP32-S3 (ESP32S3 Dev Module)';
    if (r.usbNativo) motivos.push('USB OTG nativo permite virar teclado, mouse ou pendrive.');
    if (r.cameraIA) motivos.push('Interface de camera e instrucoes vetoriais para IA.');
    if (r.wifi) motivos.push('Tem WiFi 2,4 GHz.');
    if (r.bluetooth === 'ble') motivos.push('Tem BLE 5.');
  } else if (!r.wifi && r.bluetooth !== 'ble') {
    placa = 'Arduino Uno';
    motivos.push('Sem WiFi nem Bluetooth: o Uno e simples, robusto e tem muito material.');
    if (r.barato) motivos.push('Para economizar ainda mais, considere uma Raspberry Pi Pico.');
  } else if (r.bateria) {
    placa = 'ESP32-C3';
    motivos.push('Consumo baixo e deep sleep, bom para bateria.');
    motivos.push('Tem WiFi e BLE 5.');
  } else if (r.barato) {
    placa = 'ESP32-C3 ou ESP32 Dev Module';
    motivos.push('Sao as opcoes mais baratas com WiFi e Bluetooth.');
  } else {
    placa = 'ESP32 classico (ESP32 Dev Module)';
    motivos.push('Equilibrio entre preco, WiFi, BLE e dois nucleos.');
  }
  return { placa: placa, motivos: motivos };
}

if (typeof module !== 'undefined' && module.exports) {
  module.exports = { recomendar: recomendar };
}
