/*-- 4Z-Falle --*/

#strict

local randFac;
local iTimer;
local bOn;

func Initialize() {
  SetAction("Init");
  bOn=false;
  return(1);
}

func Initialized()
{
 randFac=1+Random(3);
}

func DoPunch()
{
 if(!bOn)return();
 iTimer++;
 if(iTimer % randFac == 0)
 {
  ExecPunch();
  iTimer=0;
 }
}

func IsPunching()
{
 if(GetPhase() != 10)return();
 
 Sound("Combo5",0,this(),200);
 
 for(var cnt=0;cnt<20;cnt++)
  CreateParticle("FSpark",0,15,RandomX(-10,10),RandomX(-3,3),40+Random(20),RGB(255,255,255),this(),0);
 
 for(var obj in FindObjects(Find_Distance(13,0,12),Find_OCF(OCF_Alive())))
  Punch(obj,20+Random(10));
}

public func Activate()
{
 bOn=!bOn;
}

func ExecPunch()
{
 if(ActIdle())
 SetAction("DoPunch");
}
