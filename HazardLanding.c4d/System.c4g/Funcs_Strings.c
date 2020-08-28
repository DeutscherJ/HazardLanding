/*-- BAmS = Besseres Arbieten mit Strings --*/

#strict

// Besseres Arbeiten mit Strings
// =============================

//zwei Strings zusammenfügen
global func Merge(a,b,c)
{
	if(!b && !c) return(a);
	if(!c) c=="";
	return(Format("%s%s%s",a,b,c));
}
global func IsString(i)
{ // Any
  return(GetType(i)==C4V_String());
}
/*FindInString("aNap", "Nap")*/
global func FindInString(szText, szFindable)
{
	if(!IsString(szText)) return(false);
	if(!IsString(szFindable)) return(false);//Sind es auch strings?
	
	for(var iNum;iNum<GetStringLength(szText);iNum++)
	{
		if(GetChar(szText,iNum)==GetChar(szFindable))//der erste Buchstabe richitg?
		{
			var iNum2=0;
			Log("der erste Buchstabe ist gleich");
			Var(0)=GetChar(szFindable);
			for(iNum2;Var(iNum2)==GetChar(szText,iNum+iNum2);iNum2++)
			{
				Log("%d Buchstaben stimemn überein %d , %d",iNum2,Var(iNum2),GetChar(szText,iNum+iNum2));
				if(iNum2==GetStringLength(szFindable)) return(iNum);
				Var(iNum2)=GetChar(szFindable,iNum2);
				//if(Var(iNum2)==GetChar(szText,iNum+iNum2)) continue;
				//break;
			}
			Log("%d Buchstaben stimemn nicht überein %d , %d",iNum2,Var(iNum2),GetChar(szText,iNum+iNum2));
		}
	}
	return(false);
}

global func GetStringLength(szText)
{
  //if(!IsString(szText)) return();
  for(var i; GetChar(szText,i);i++){continue;}
  return(i);
}

/*Gibt die Position des String1 in String2*/
global Substring: // const char *szString1, const char *szString2
  if(!IsString(Par())) return();
  if(!IsString(Par(1))) return();
  for(Var()=0;Var()<GetStringLength(Par(1));++Var())
    if(GetChar(Par(1),Var())==GetChar(Par(),0)) {
      Var(2)=0;
      for(Var(1)=0;Var(1)<GetStringLength(Par());++Var(1))
        if(GetChar(Par(1),Var()+Var(1))==GetChar(Par(),Var(1)))
          ++Var(2);
      if(Var(2)==GetStringLength(Par())) return(Var()+1);
     }
 return();
/*
global MakeLetter: // int iValue

  // Blödes System, aber es gibt zur Zeit keine bessere Möglichkeit. :(
  if(Par()==0) return("");
  if(Par()==32) return(" ");

  if(Par()==101) return("e");
  if(Par()==97) return("a");
  if(Par()==111) return("o");
  if(Par()==117) return("u");
  if(Par()==105) return("i");
  if(Par()==98) return("b");
  if(Par()==99) return("c");
  if(Par()==100) return("d");
  if(Par()==102) return("f");
  if(Par()==103) return("g");
  if(Par()==104) return("h");
  if(Par()==106) return("j");
  if(Par()==107) return("k");
  if(Par()==108) return("l");
  if(Par()==109) return("m");
  if(Par()==110) return("n");
  if(Par()==112) return("p");
  if(Par()==114) return("r");
  if(Par()==115) return("s");
  if(Par()==116) return("t");
  if(Par()==118) return("v");
  if(Par()==119) return("w");
  if(Par()==121) return("y");
  if(Par()==122) return("z");
  if(Par()==120) return("x");
  if(Par()==113) return("q");
  if(Par()==228) return("ä");
  if(Par()==246) return("ö");
  if(Par()==252) return("ü");

  if(Par()==69) return("E");
  if(Par()==65) return("A");
  if(Par()==79) return("O");
  if(Par()==85) return("U");
  if(Par()==73) return("I");
  if(Par()==66) return("B");
  if(Par()==67) return("C");
  if(Par()==68) return("D");
  if(Par()==70) return("F");
  if(Par()==71) return("G");
  if(Par()==72) return("H");
  if(Par()==74) return("J");
  if(Par()==75) return("K");
  if(Par()==76) return("L");
  if(Par()==77) return("M");
  if(Par()==78) return("N");
  if(Par()==80) return("P");
  if(Par()==82) return("R");
  if(Par()==83) return("S");
  if(Par()==84) return("T");
  if(Par()==86) return("V");
  if(Par()==87) return("W");
  if(Par()==89) return("Y");
  if(Par()==90) return("Z");
  if(Par()==88) return("X");
  if(Par()==81) return("Q");
  if(Par()==196) return("Ä");
  if(Par()==214) return("Ö");
  if(Par()==220) return("Ü");

  if(Par()==223) return("ß");

  if(Par()==48) return("0");
  if(Par()==49) return("1");
  if(Par()==50) return("2");
  if(Par()==51) return("3");
  if(Par()==52) return("4");
  if(Par()==53) return("5");
  if(Par()==54) return("6");
  if(Par()==55) return("7");
  if(Par()==56) return("8");
  if(Par()==57) return("9");

  if(Par()==46) return(".");
  if(Par()==44) return(",");
  if(Par()==48) return(":");
  if(Par()==49) return(";");
  if(Par()==33) return("!");
  if(Par()==63) return("?");
  if(Par()==124) return("|");
  if(Par()==37) return("%");
  if(Par()==38) return("&");
  if(Par()==45) return("-");
  if(Par()==42) return("*");
  if(Par()==43) return("+");
  if(Par()==61) return("=");
  if(Par()==34) return("\"");
  if(Par()==60) return("<");
  if(Par()==62) return(">");
  if(Par()==39) return("'");
  if(Par()==95) return("_");
  if(Par()==40) return("(");
  if(Par()==41) return(")");
  if(Par()==47) return("/");

  if(Par()==224) return("à");
  if(Par()==225) return("á");
  if(Par()==226) return("â");
  if(Par()==232) return("è");
  if(Par()==233) return("é");
  if(Par()==234) return("ê");
  if(Par()==236) return("ì");
  if(Par()==237) return("í");
  if(Par()==238) return("î");
  if(Par()==242) return("ò");
  if(Par()==243) return("ó");
  if(Par()==244) return("ô");
  if(Par()==249) return("ù");
  if(Par()==250) return("ú");
  if(Par()==251) return("û");
  if(Par()==231) return("ç");
  if(Par()==241) return("ñ");
  if(Par()==192) return("À");
  if(Par()==193) return("Á");
  if(Par()==194) return("Â");
  if(Par()==200) return("È");
  if(Par()==201) return("É");
  if(Par()==202) return("Ê");
  if(Par()==204) return("Ì");
  if(Par()==205) return("Í");
  if(Par()==206) return("Î");
  if(Par()==210) return("Ò");
  if(Par()==211) return("Ó");
  if(Par()==212) return("Ô");
  if(Par()==217) return("Ù");
  if(Par()==218) return("Ú");
  if(Par()==219) return("Û");
  if(Par()==199) return("Ç");
  if(Par()==209) return("Ñ");

  if(Par()==64) return("@");
  if(Par()==36) return("$");
  if(Par()==35) return("#");
  if(Par()==126) return("~");
  if(Par()==167) return("§");
  if(Par()==92) return("\\");
  if(Par()==94) return("^");
  if(Par()==91) return("[");
  if(Par()==93) return("]");
  if(Par()==123) return("{");
  if(Par()==125) return("}");
  if(Par()==176) return("°");
  if(Par()==128) return("€");
  if(Par()==178) return("²");
  if(Par()==179) return("³");
  if(Par()==169) return("©");
  if(Par()==169) return("®");
  if(Par()==153) return("™");

 return(Log("xJulian-funcs (MakeLetter): Fehler oder unbekanntes Zeichen."));

//macht eine Zahl im String zur richitgen Zahl:-( z.B. String2Int(9) gibt heraus 9

global String2Int: // const char *szString 
  if(!IsString(Par())) return();
  for(Var()=0;Var()<GetStringLength(Par());++Var()) {
    if((GetChar(Par(),Var())-48)<0) return();
    if((GetChar(Par(),Var())-48)>9) return();
    Var(1)=Var(1)*10+(GetChar(Par(),Var())-48);
   }
 return(Var(1));

global StringSave2Globals: // const char *szString, [int iStartGlobal]
  if(!IsString(Par())) return();
  Var()=Par(1);
  while(Var(1)=GetChar(Par(),Var()-Par(1))) {
    Global(Var())=Var(1);
    ++Var();
   }
 return(Var()-1);

//Sezt einen String aus den GLobals von iStartGlobal bis iEndGlobal zusammen
global func StringLoadFromGlobals(int iStartGlobal, int iEndGlobal) // int iStartGlobal, int iEndGlobal
{
  var szString=""; // Muss als String klassifiziert werden.
  for(var i=iStartGlobal;i<=iEndGlobal;i)
    szString=Format("%s%s",szString,MakeLetter(Global(i)));
 return(szString);
}

global StringAdd: // const char *szString1, const char *szString2, ...
  var String="";
  for(Var()=0;Var()<=9;++Var())
    if(Par(Var())) {
      if(!IsString(Par(Var())))
        return();
      String=Format("%s%s",String,"%_s");
     }
  while(Substring("_",String)) String=StringRemoveFrom("_",String);
 return(Format(String,Par(),Par(1),Par(2),Par(3),Par(4),Par(5),Par(6),Par(7),Format("%s%s",Par(8),Par(9))));

global StringTakeFrom: // const char *szString, int iStart, int iLength or REST
  var FullString=Format("%s___",Par()); // Notlösung, weil die letzten 3 Zeichen nicht wieder abrufbar sind. Wenigstens funzt's...
  for(Var()=3;Var()<GetStringLength(FullString);++Var())
    Var(Var())=GetChar(FullString,Var()-3);
  Var(2)=Par(2);
  if(Par(2)==REST) Var(2)=GetStringLength(FullString)-1-Par(1);
  var String="";
  for(Var(1)=3+Par(1);Var(1)-3<Var(2)+Par(1);++Var(1))
    String=Format("%s%s",String,MakeLetter(Var(Var(1))));
 return(String);

global StringRemoveFrom: // const char *szPart, const char *szString, [const char *szReplace]
  if(!IsString(Par())) return();
  if(!IsString(Par(1))) return();
  if(!Substring(Par(),Par(1))) return();
  var FirstString="";
  var LastString="";
  for(Var()=0;Var()<Substring(Par(),Par(1))-1;++Var())
    FirstString=Format("%s%s",FirstString,MakeLetter(GetChar(Par(1),Var())));
  for(Var()=Substring(Par(),Par(1))+GetStringLength(Par())-1;Var()<GetStringLength(Par(1));++Var())
    LastString=Format("%s%s",LastString,MakeLetter(GetChar(Par(1),Var())));
 return(Format("%s%s%s",FirstString,Par(2),LastString));

global StringRemoveFromX: // const char *szString, int iStart, int iLength, [const char *szReplace]
  if(!IsString(Par())) return();
  if(IsString(Par(1))) return();
  if(IsString(Par(2))) return();
  if(Par(3))
    if(!IsString(Par(3))) return();
  if(GetStringLength(Par())<Par(1)) return();
  if(GetStringLength(Par())<Par(2)) return();
  var Part="";
  if(Par(3)) Part=Par(3);
 return(Format("%s%s%s",StringTakeFrom(Par(),0,Par(1)),Part,StringTakeFrom(Par(),Par(2)+Par(1),REST)));

global StringInsertInto: // const char *szPart, int iPosition, const char *szString
  if(!IsString(Par())) return();
  if(IsString(Par(1))) return();
  if(!IsString(Par(2))) return();
 return(Format("%s%s%s",StringTakeFrom(Par(2),0,Par(1)),Par(),StringTakeFrom(Par(2),Par(1),REST)));
