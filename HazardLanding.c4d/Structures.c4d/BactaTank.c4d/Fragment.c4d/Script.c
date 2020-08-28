/*-- Neues Objekt --*/

#strict
local alpha;
	
func Set(i)
{
	if(i>=1)
		SetGraphics(Format("%d",i));
	var vertexArray = [15,5,52,6,7,9,9,22,22,22];
	if(i==1) vertexArray = [1,60,1,54,98,54,98,60];
	if(i==2) vertexArray = [45,13,52,7,64,0,78,0,93,9,84,19];
	if(i==3) vertexArray = [23,11,28,14,36,13,29,16,35,51];
	if(i==4) vertexArray = [49,14,55,11,65,11,70,17,56,27,58,40];
	if(i==5) vertexArray = [10,22,15,17,25,26,26,33,22,38,15,43,10,38];
	if(i==6) vertexArray = [36,27,44,12,56,28,53,43,46,42];
	if(i==7) vertexArray = [64,26,73,13,84,19,68,45];
	if(i==8) vertexArray = [77,31,88,15,89,37,87,41];
	if(i==9) vertexArray = [55,32,64,27,67,43,55,45];
	
	for(var vertex = 0; vertex<=7; vertex++)
	{
		var iV = vertex;
		if(vertex>GetLength(vertexArray)/2-1)
		{
			iV = GetLength(vertexArray)/2-1;
		}
		SetVertex(iV,0,vertexArray[iV*2]-50);
		SetVertex(iV,1,vertexArray[iV*2+1]-30);
	}
	SetRDir(RandomX(-5,5));
	SetSpeed(-RandomX(-20,20),RandomX(-20,20));
	return(1);
}

func Fade()
{
	alpha++;
	if(alpha==100)
		RemoveObject();
	return(1);
}

func Hit()
{
	Sound("GlassBreak");
	return(1);
}