#strict

protected Initialize:
  SetAction("Process");
  return(1);

Precipitation:

  if (Not(GameCall("Rain"))) return(0);
  InsertMaterial(Material("Water"), RandomX(10,LandscapeWidth()-10)-GetX(),-GetY());
  InsertMaterial(Material("Water"), RandomX(10,LandscapeWidth()-10)-GetX(),-GetY());
  InsertMaterial(Material("Water"), RandomX(10,LandscapeWidth()-10)-GetX(),-GetY());
  InsertMaterial(Material("Water"), RandomX(10,LandscapeWidth()-10)-GetX(),-GetY());
  InsertMaterial(Material("Water"), RandomX(10,LandscapeWidth()-10)-GetX(),-GetY());
  InsertMaterial(Material("Water"), RandomX(10,LandscapeWidth()-10)-GetX(),-GetY());

  return(1);

//Movement:
//  SetXDir( RandomX(-10,10) );
//  if (GetX()>LandscapeWidth()-20) SetPosition(25,-1);
//  if (GetX()<20) SetPosition(LandscapeWidth()-25,-1);
//  return(1);


