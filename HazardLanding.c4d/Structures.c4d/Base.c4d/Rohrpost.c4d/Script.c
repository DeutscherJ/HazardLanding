/*-- Rohrpost --*/

#strict
#include PIPL


public func CreatePipe(int dir, id pipeId) {
  var x=0, y=0;

  if(dir == PIPE_Left)  { x -= GetDefWidth(); }
  if(dir == PIPE_Right) { x += GetDefWidth(); }
  if(dir == PIPE_Up)    { y -= GetDefHeight(); }
  if(dir == PIPE_Down)  { y += GetDefHeight(); }

  x = x*GetCon()/100;
  y = y*GetCon()/100;

  var pipe = CreateObject(RRPS,50,50,GetOwner());
  pipe->DoCon(GetCon()-100);
  pipe->SetCategory(GetCategory());

  pipe->SetPosition(GetX()+x,GetY()+y);

  return(pipe);
}