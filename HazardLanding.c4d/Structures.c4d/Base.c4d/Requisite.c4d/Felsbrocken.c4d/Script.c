#strict
Initialize:
  return(SetAction(Format("Stand%d",Random(7)+1)));
Damage:
 if(LessThan(90,GetDamage())) RemoveObject();
 return(1);

Stand1:
  SetSolidMask(0,0,10,10);
  SetVertex(0,0,-6); SetVertex(0,1,0);
  SetVertex(1,0,6); SetVertex(1,1,0);
  SetVertex(2,0,0); SetVertex(2,1,-6);
  SetVertex(3,0,0); SetVertex(3,1,6);
  return(1);
Stand2:
  SetSolidMask(10,0,13,10,-1);
  SetVertex(0,0,-7); SetVertex(0,1,0);
  SetVertex(1,0,7); SetVertex(1,1,0);
  SetVertex(2,0,0); SetVertex(2,1,-6);
  SetVertex(3,0,0); SetVertex(3,1,6);
  return(1);
Stand3:
  SetSolidMask(23,0,12,10,-1);
  SetVertex(0,0,-7); SetVertex(0,1,0);
  SetVertex(1,0,7); SetVertex(1,1,0);
  SetVertex(2,0,0); SetVertex(2,1,-7);
  SetVertex(3,0,0); SetVertex(3,1,6);
  return(1);
Stand4:
  SetSolidMask(0,10,11,10);
  SetVertex(0,0,-6); SetVertex(0,1,0);
  SetVertex(1,0,6); SetVertex(1,1,0);
  SetVertex(2,0,0); SetVertex(2,1,-6);
  SetVertex(3,0,0); SetVertex(3,1,6);
  return(1);
Stand5:
  SetSolidMask(11,10,9,10,1);
  SetVertex(0,0,-6); SetVertex(0,1,0);
  SetVertex(1,0,5); SetVertex(1,1,0);
  SetVertex(2,0,0); SetVertex(2,1,-7);
  SetVertex(3,0,0); SetVertex(3,1,6);
  return(1);
Stand6:
  SetSolidMask(20,10,16,10,-3);
  SetVertex(0,0,-9); SetVertex(0,1,0);
  SetVertex(1,0,9); SetVertex(1,1,0);
  SetVertex(2,0,0); SetVertex(2,1,-6);
  SetVertex(3,0,0); SetVertex(3,1,6);
  return(1);
Stand7:
  SetSolidMask(36,0,14,20,-2,-5);
  SetVertex(0,0,-8); SetVertex(0,1,0);
  SetVertex(1,0,8); SetVertex(1,1,0);
  SetVertex(2,0,0); SetVertex(2,1,-12);
  SetVertex(3,0,0); SetVertex(3,1,11);
  return(1);
