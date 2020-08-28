#strict

Initialize:
  SetAction("Fetzen");
  return(1);

Zeit:
  if(GetActTime()>10) RemoveObject();
  return(1);