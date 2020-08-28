#strict
Initialize:
  SetAction("NoWater");
  return(1);

EraseWater:
  if(Not(GBackLiquid(0,2))) return(SetAction("NoWater"));
  ExtractLiquid(0,0);
  ExtractLiquid(1,0);
  ExtractLiquid(-1,0);
  ExtractLiquid(0,-1);  
  ExtractLiquid(0,1);  
  
  ExtractLiquid(-2,0);
  ExtractLiquid(2,0);
  ExtractLiquid(0,-2);
  ExtractLiquid(0,2);
  ExtractLiquid(1,1);
  ExtractLiquid(-1,-1);
  ExtractLiquid(1,-1);
  ExtractLiquid(-1,1);

  ExtractLiquid(-2,-1);
  ExtractLiquid(-2,1);
  ExtractLiquid(2,-1);
  ExtractLiquid(2,1);
  ExtractLiquid(-1,-2);
  ExtractLiquid(1,-2);
  ExtractLiquid(-1,2);
  ExtractLiquid(1,2);

  return(1);
