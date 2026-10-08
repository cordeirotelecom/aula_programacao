// Elaborado pelo Prof. Vagner Cordeiro
// Calcula a razao de contraste WCAG entre duas cores "#rrggbb".

function luminancia(hex) {
  var canais = [1, 3, 5].map(function (i) {
    var c = parseInt(hex.substr(i, 2), 16) / 255;
    return c <= 0.03928 ? c / 12.92 : Math.pow((c + 0.055) / 1.055, 2.4);
  });
  return 0.2126 * canais[0] + 0.7152 * canais[1] + 0.0722 * canais[2];
}

function razaoContraste(corA, corB) {
  var a = luminancia(corA), b = luminancia(corB);
  var claro = Math.max(a, b), escuro = Math.min(a, b);
  return (claro + 0.05) / (escuro + 0.05);
}

if (typeof module !== "undefined") { module.exports = { luminancia: luminancia, razaoContraste: razaoContraste }; }

// Executar (PowerShell): powershell -ExecutionPolicy Bypass -File ".\ux_design\abrir.ps1" 05_cores_contraste_tipografia
