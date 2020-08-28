#strict
Initialize:
  SetAction("NoWater");
  return(1);

SplashWater1:
  if(GetMaterial(0,-7) == Material("Water")) return(SetAction("NoWater"));
  CastPXS("Water", 1, 0);
  CastPXS("Water", 1, 0,0,1);
  Local(0)++;
  if(Local(0)>=60)
  {
    SetLocal(0,0);
    SetAction("Water2");
  };
  return(1);

SplashWater2:
  if(GetMaterial(0,-7) == Material("Water")) return(SetAction("NoWater"));
  CastPXS("Water", 1, 0);
  
  CastPXS("Water", 1, 0,-1);
  CastPXS("Water", 1, 0,1);
  CastPXS("Water", 1, 0,0,-1);
  CastPXS("Water", 1, 0,0,1);
  CastPXS("Water", 1, 0,-1,1);
  CastPXS("Water", 1, 0,1,1);
  Local(0)++;
  if(Local(0)>=60)
  {
    SetLocal(0,0);
    SetAction("Water3");
  };
  return(1);

SplashWater3:
  if(GetMaterial(0,-7) == Material("Water")) return(SetAction("NoWater"));
  CastPXS("Water", 1, 0);
  
  CastPXS("Water", 1, 0,-1);
  CastPXS("Water", 1, 0,1);
  CastPXS("Water", 1, 0,0,-1);
  CastPXS("Water", 1, 0,0,1);

  CastPXS("Water", 1, 0,-2);
  CastPXS("Water", 1, 0,2);
  CastPXS("Water", 1, 0,-2,1);
  CastPXS("Water", 1, 0,2,1);
  CastPXS("Water", 1, 0,0,-2);
  CastPXS("Water", 1, 0,0,2);
  CastPXS("Water", 1, 0,1,1);
  CastPXS("Water", 1, 0,-1,-1);
  CastPXS("Water", 1, 0,1,-1);
  CastPXS("Water", 1, 0,-1,1);
  Local(0)++;
  if(Local(0)>=60)
  {
    SetLocal(0,0);
    SetAction("Water4");
  };
  return(1);

SplashWater4:
  if(GetMaterial(0,-7) == Material("Water")) return(SetAction("NoWater"));
  CastPXS("Water", 1, 0);
  
  CastPXS("Water", 1, 0,-1);
  CastPXS("Water", 1, 0,1);
  CastPXS("Water", 1, 0,0,-1);
  CastPXS("Water", 1, 0,0,1);

  CastPXS("Water", 1, 0,-2);
  CastPXS("Water", 1, 0,2);
  CastPXS("Water", 1, 0,0,-2);
  CastPXS("Water", 1, 0,0,2);
  CastPXS("Water", 1, 0,1,1);
  CastPXS("Water", 1, 0,-1,-1);
  CastPXS("Water", 1, 0,1,-1);
  CastPXS("Water", 1, 0,-1,1);

  CastPXS("Water", 1, 0,-2,-1);
  CastPXS("Water", 1, 0,-2,1);
  CastPXS("Water", 1, 0,2,-1);
  CastPXS("Water", 1, 0,2,1);
  CastPXS("Water", 1, 0,-1,-2);
  CastPXS("Water", 1, 0,1,-2);
  CastPXS("Water", 1, 0,-1,2);
  CastPXS("Water", 1, 0,1,2);
  return(1);
