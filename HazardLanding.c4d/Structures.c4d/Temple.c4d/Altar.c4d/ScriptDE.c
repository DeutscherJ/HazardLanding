

protected GetString:
  var rnd;

  if (Par(0) eq "want") {
    rnd = Random(13);
    if (!--rnd) return("<c a82000>Chaosgott: Ich hätte gerne eine Portion Pommes mit extra viel %s.</c>");
    if (!--rnd) return("<c a82000>* Chaosgott hat Hunger auf %s.</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Wer von euch beschafft mir als erstes %s?</c>");
    if (!--rnd) return("<c a82000>Chaosgott: *%s habbe will*</c>");
    if (!--rnd) return("<c a82000>* Chaosgott gelüstet es nach %s.</c>");
    if (!--rnd) return("<c a82000>* Chaosgott sucht überall nach %s aber kann es nicht finden.</c>");
    if (!--rnd) return("<c a82000>* Chaosgott befiehlt euch ihm %s zu beschaffen.</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Ich will ein Objekt namens %s.</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Gibt's hier irgendwo noch %s?</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Habt ihr %s im Sortiment?</c>");
    if (!--rnd) return("<c a82000>Chaosgott: %s jemand?</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Ein bisschen %s, bitte.</c>");
    return("<c a82000>Chaosgott: Bock auf %s; jetzt sofort!</c>");
  }

  if (Par(0) eq "thanks") {
    rnd = Random(12);
    if (!--rnd) return("<c a82000>Chaosgott: %s, jetzt habe ich keine Lust mehr darauf.</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Na endlich, %s. Hab schon die ganze Zeit auf dich gewartet.</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Jeden Tag eine gute Tat. Gell, %s?</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Vielleicht mach ich dich irgendwann mal unsterblich dafür, %s.</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Wurde aber auch Zeit, %s!</c>");
    if (!--rnd) return("<c a82000>Chaosgott: %s, heiraten wir?</c>");
    if (!--rnd) return("<c a82000>Chaosgott: %s ist ja soooo viel besser als alle anderen!</c>");
    if (!--rnd) return("<c a82000>Chaosgott: %s finde ich soooo süss... *schmacht*</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Ich liebe %s.</c>");
    if (!--rnd) return("<c a82000>Chaosgott: %s ist ein würdiger Untertan.</c>");
    if (!--rnd) return("<c a82000>Chaosgott: Geil, %s!</c>");
    return("<c a82000>Chaosgott: Finde ich gut von dir, dass du dich auch mal um die etwas weniger reichen kümmerst, %s.</c>");
  }
  return(1);