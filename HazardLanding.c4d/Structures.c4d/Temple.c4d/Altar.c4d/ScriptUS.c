

protected GetString:
  var rnd;

  if (Par(0) eq "want") {
    rnd = Random(14);
    if (!--rnd) return("<c a82000>Chaos God: I'd like to get a portion of chips with especially much %s.</c>");
    if (!--rnd) return("<c a82000>* Chaos God is hungry for %s.</c>");
    if (!--rnd) return("<c a82000>Chaos God: Hey sweeeeeeter, are you going to build me a %s !!?</c>");
    if (!--rnd) return("<c a82000>Chaos God: Who of you gets me %s first?</c>");
    if (!--rnd) return("<c a82000>Chaos God: *wants %s*</c>");
    if (!--rnd) return("<c a82000>* Chaos God has lust for %s.</c>");
    if (!--rnd) return("<c a82000>* Chaos God searches everywhere for %s but can't seem to find it.</c>");
    if (!--rnd) return("<c a82000>* Chaos God commands you to fetch him %s.</c>");
    if (!--rnd) return("<c a82000>Chaos God: I want an object named %s.</c>");
    if (!--rnd) return("<c a82000>Chaos God: Is a thing like %s anywhere nearby?</c>");
    if (!--rnd) return("<c a82000>Chaos God: Fat gross %s, ay.</c>");
    if (!--rnd) return("<c a82000>Chaos God: Let's buy some %s !</c>");
    if (!--rnd) return("<c a82000>Chaos God: Do you have %s in your sortiment?</c>");
    return("<c a82000>Chaos God: Lust for %s; right now.</c>");
  }

  if (Par(0) eq "thanks") {
    rnd = Random(12);
    if (!--rnd) return("<c a82000>Chaos God: %s, now I don't want that anymore.</c>");
    if (!--rnd) return("<c a82000>Chaos God: Ah finally, %s. I've waited a long time for you.</c>");
    if (!--rnd) return("<c a82000>Chaos God: Every day a good deed. Eh, %s?</c>");
    if (!--rnd) return("<c a82000>Chaos God: Maybe oneday I'll make you immorant for that, %s.</c>");
    if (!--rnd) return("<c a82000>Chaos God: It's about time you got here, %s!</c>");
    if (!--rnd) return("<c a82000>Chaos God: %s, do you want to marry me?</c>");
    if (!--rnd) return("<c a82000>Chaos God: %s is soooo much better than everybody else!</c>");
    if (!--rnd) return("<c a82000>Chaos God: %s is soooo sweet... *drools*</c>");
    if (!--rnd) return("<c a82000>Chaos God: I love %s.</c>");
    if (!--rnd) return("<c a82000>Chaos God: %s is a worthy tributary.</c>");
    if (!--rnd) return("<c a82000>Chaos God: Uberwoot, %s!</c>");
    return("<c a82000>Chaos God: You have a golden heart because you also pay attention to the less wealthy, %s.</c>");
  }
  return(1);