// protect.js - czytelna wersja
(function () {
  // blokuj prawy przycisk myszy
  document.addEventListener('contextmenu', function (e) {
    e.preventDefault();
  }, false);

  // blokuj F12, Ctrl+U, Ctrl+Shift+I / J (najczęściej używane skróty devtools / view-source)
  document.addEventListener('keydown', function (e) {
    // F12 (klucz numerowy)
    if (e.key === 'F12' || e.keyCode === 123) {
      e.preventDefault();
      e.stopPropagation();
      return false;
    }

    // Ctrl+U (view source) — obsługujemy duże i małe U
    if (e.ctrlKey && (e.key === 'u' || e.key === 'U')) {
      e.preventDefault();
      return false;
    }

    // Ctrl+Shift+I / J (otwieranie devtools)
    if (e.ctrlKey && e.shiftKey && (e.key === 'I' || e.key === 'i' || e.key === 'J' || e.key === 'j')) {
      e.preventDefault();
      return false;
    }
  }, false);
})();
