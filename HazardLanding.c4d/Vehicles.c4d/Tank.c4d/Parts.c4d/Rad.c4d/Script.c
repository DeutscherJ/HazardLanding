/*-- Rad --*/

#strict

func Initialize() {
  SetAction("Walk");
  return(1);
}

public func Tanksize() {return(50);}

local Radfreund,radrang,Chef;

public func BeRad1(){
  radrang = 1;
  return(1);
}

public func Set(OtherRad,chef){
  Chef = chef;
  if (OtherRad != 0) return(Radfreund = OtherRad);
  var rad2 = CreateObject(CEWE,10);   
  rad2 -> Set(this(),Chef);
  Set(rad2,Chef);
  return(rad2);
}

public func Drive(){
  if (!Radfreund) return(1);
    var angel = Angle(GetX(),GetY(),GetX(Radfreund),GetY(Radfreund));
    if (!PosInside()) SetPosition(GetX(Radfreund) - Sin(angel,Tanksize()),GetY(Radfreund) - Cos(angel,-Tanksize()));
    var do = 1;
    //Wenn das andere rad auf dem boden ist, das rad hier aber nicht, dann wird das fallen ein wenig anders geregelt:
    if (!GBackSolid(0,4)) if (Radfreund -> GBackSolid(0,4)) {
    var r = Angle(GetX(Radfreund),GetY(Radfreund),GetX(),GetY());  
    if (Inside(r,-10,10)) SetXDir(RandomX(-15,15));
    SetYDir(GetYDir(Radfreund) + 30);
    //soll es nach rechts oder links pendeln?
    }                                        
    //if (GBackSolid()) if (!Radfreund-> GBackSolid()) do = 0;
    //SetSpeed(GetXDir(),GetYDir() * do +  do * GetYDir(Radfreund));
    if (GBackSolid(0,-15)) return(1);
    //nach oben bringen
    while(GBackSolid(0,0)) SetPosition(GetX(),GetY()-1); 
    //nach links bringen
    while(GBackSolid(5,-18)) SetPosition(GetX() - 1,GetY());
    //häng ich in der erde?
    if (GBackSolid(0,-10)) return(1);
    //nach rechts bringen
    while(GBackSolid(-5,-18)) SetPosition(GetX() + 1,GetY());
     
  return(1);
}

public func IsRight(){
if (GetX() > GetX(Radfreund)) return(1);
return(0);
}

public func Change(){
  var xl,yl;
  xl = GetX(Radfreund);
  yl = GetY(Radfreund);
  Radfreund -> SetPosition(GetX(),GetY());
  SetPosition(xl,yl);
  return(1);
}

func PosInside(){
  if (Inside(ObjectDistance(this(),Radfreund),Tanksize() - 3,Tanksize() + 3)) return(1);
  return(0);
}
func IsCEVehilce() {return(1);}

public func AttachTargetLost(){
  return(RemoveObject());
}

public func Hit(){
  Sound("PanzerCrash");
}





