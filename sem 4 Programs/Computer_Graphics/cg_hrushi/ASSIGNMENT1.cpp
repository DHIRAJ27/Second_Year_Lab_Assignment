/*
	PROBLEM STATEMENT:
	Write C++ program to draw line using DDA and Bresenham's algorithm. Inherit pixel class and use
	function overloading.

*/
/*
	DIGITAL DIFFERENTIAL ANALYZER LINE DRAWING ALGORITHM:
	LET (X1,Y1)(X2,Y2) BE THE TWO END POINTS
	THEREFORE SLPOE OF THE GIVEN LINE IS
	M=(Y2-Y1)/(X2-X1)
	LET DY(DIFFERENCE IN Y)=(Y2-Y1)
	AND DX(DIFFERENCE IN X)-=(X2-X1)
	M=DY/DX
	IF
	DX>=DY : GENTLE SLOPE
	DX<DY : STEEP SLOPE

	IF
	GENTLE SLOPE IS THERE THEN WE STEP THROUGH EACH COLUMN AND CALCULATE ROW VALUE PIXEL TO BE ILLUMINATED
		X=X+1
		Y=Y+M

	ELSE
	STEEP SLOPE IS THERE THEN WE STEP THROUGH EACH ROW AND CALCULATE CORRESSPONDING COLUMN PIXEL VALUE TO BE ILLUMINATED
		Y=Y+1
		X=X+(1/M)

	WE DON'T WANT FRACTIONAL PART WHILE PUTTING PIXEL SO WE USE CEILING AND THE FLOOR FUNCTIONS TO CONVERT FRACTIONAL POINTS TO INTEGER

*/
/*
	BRESENHAM'S LINE DRAWING ALGORITHM:
	LET (X1,Y1)(X2,Y2) BE THE TWO END POINTS
	THEREFORE SLOPE OF THE GIVEN LINE IS
	M=(Y2-Y1)/(X2-X1)      DY=Y2-Y1     DX=X2-X1

	LET THE ERROR BE P
	IF P>0.5
		WE SELECT THE PIXEL HAVING HIGHER VALUE
	ELSE 
		WE SELECT THE PIXEL HAVING LOWER VALUE

	THEREFORE
		P>0.5
		2P>1

		2P-1>0 IS THE DECISION FACTOR
		IF GREATER HIGHER PIXEL
		ELSE LOWER PIXEL

	WE INCREMENT P AS
		P=P+M
		P=P+M-1

	BUT M=DY/DX
		2P-1>0
	BECOMES
		2DX*P-DX>0
	NOW WE DEFINE G AS 2*DX*P-DX
	SO
		G>0 HIGHER PIXEL
		G<0 LOWER PIXEL

		G=2*DX*P-DX
		P=G+DX/2*DX

	INSERT THIS P IN P=P+M
		G+DX/2*DX= (G+DX/2*DX) + (DY/DX)
		G+DX=G+DX +2*DY
		G=G+2*DY

	AFTER INSERTING P IN P=P+M-1
	 WE GET G=G+2*DY-2*DX

	INITAIL VALUE OF G
	G=2*DX*P-DX
		WHERE P=DY/DX
	G=2*DY-DX
*/
#include<iostream>
#include<graphics>
using namespace std;
class DDA
{
		float X1,Y1,X2,Y2,DX,DY,X,Y,X_INC,Y_INC;int X0,Y0,STEPS;int gd=DETECT,gm;
	public:
	DDA()
	{
		X0=0;
		Y0=0;
	}
	void getCOORDINATES();     //GETS THE CO-ORDINATES OF LINES FROM THE USER
	void putCOORDINATES();		//PUTS THE CO-ORDINATES ENTERED BY THE USER
	void drawLINE();				//DRAWS A LINE USING DDA LINE DRAWING ALGORITHM
};
void DDA::getCOORDINATES()
{
	X1=Y1=X2=Y2=DX=DY=0;
	cout<<"PLEASE ENTER THE CO-ORDINATES OF THE ENDPOINTS OF THE LINE TO BE DRAWN"<<endl;
	cout<<"END POINT 1:"<<endl<<"X = ";cin>>X1;		//TAKING ENDPOINTS OF STARTING VERTEX
	cout<<"Y = ";cin>>Y1;
	cout<<"END POINT 1:"<<endl<<"X = ";cin>>X2;		//TAKING ENDPOINTS OF ENDING VERTEX
	cout<<"Y = ";cin>>Y2;
}
void DDA::putCOORDINATES()
{
	cout<<"DRAWING A LINE FROM ("<<X1<<","<<Y1<<") TO ("<<X2<<","<<Y2<<")"<<endl;		//PUTING LINE ENDPOINTS
}
void DDA::drawLINE()
{
	initgraph(&gd,&gm,NULL);							//INITALIZING GRAPH
	X0=getmaxx()/2;Y0=getmaxy()/2;					//FOR GETTING MIDPOINT OF THE SCREEN
	putpixel(X0,Y0,WHITE);								//PUTTING MIDPOINT
	DX=X2-X1;
	DY=Y2-Y1;
	if(DX<0)
		DX=-DX;
	if(DY<0)
		DY=-DY;
	if(DX>=DY)												//TO DECIDE: COLUMN /ROW STEPING
		STEPS=DX;
	else
		STEPS=DY;
	DX=X2-X1;
	DY=Y2-Y1;
	X_INC=(float)DX/STEPS;								//X INCREMENTATION VALUE CORRESSPONDING TO THE SLOPE
	Y_INC=(float)DY/STEPS;								//Y INCREMENTATION VALUE CORRESSPONDING TO THE SLOPE
	X=X1;Y=Y1;
	while(STEPS)											//LOOP EXECUTES "STEPS" TIMES
	{
		putpixel(X0+X+0.5,Y0+Y+0.5,WHITE);//PUT PIXEL WITH RESPECT TO MIDPOINT OF THE SCREEN & ALSO USING CEILING AND FLOOR FUNC
		X+=X_INC;											//X INCREMENTATION
		Y+=Y_INC;											//Y INCREMENTATION
		STEPS--;
	}
	putpixel(X0,Y0,WHITE);
	delay(10000);											//DELAY FOR DISPLAY
	closegraph();											//CLOSING THE GRAPH
}
class BRESENHAM
{
		int X1,Y1,X2,Y2,DX,DY,TEMP,G,X0,Y0,STEPS,X,Y,X_INC,Y_INC,gd=DETECT,gm;
	public:
	BRESENHAM()
	{
		X0=0;
		Y0=0;
	}
	void getCOORDINATES();     //GETS THE CO-ORDINATES OF LINES FROM THE USER
	void putCOORDINATES();		//PUTS THE CO-ORDINATES ENTERED BY THE USER
	void drawLINE();				//DRAWS A LINE USING DDA LINE DRAWING ALGORITHM
};
void BRESENHAM::getCOORDINATES()
{
	X1=Y1=X2=Y2=DX=DY=0;
	cout<<"PLEASE ENTER THE CO-ORDINATES OF THE ENDPOINTS OF THE LINE TO BE DRAWN"<<endl;
	cout<<"END POINT 1:"<<endl<<"X = ";cin>>X1;		//TAKING ENDPOINTS OF STARTING VERTEX
	cout<<"Y = ";cin>>Y1;
	cout<<"END POINT 1:"<<endl<<"X = ";cin>>X2;		//TAKING ENDPOINTS OF ENDING VERTEX
	cout<<"Y = ";cin>>Y2;
}
void BRESENHAM::putCOORDINATES()
{
	cout<<"DRAWING A LINE FROM ("<<X1<<","<<Y1<<") TO ("<<X2<<","<<Y2<<")"<<endl;		//PUTING LINE ENDPOINTS
}
void BRESENHAM::drawLINE()
{
	initgraph(&gd,&gm,NULL);							//INITALIZING GRAPH
	X0=getmaxx()/2;Y0=getmaxy()/2;					//FOR GETTING MIDPOINT OF THE SCREEN
	putpixel(X0,Y0,WHITE);								//PUTTING MIDPOINT
	DX=X2-X1;
	DY=Y2-Y1;
	X_INC=1;
	Y_INC=1;
	if(DX<0)
	{
		DX=-DX;
		X_INC=-1;												//IF DX NEG DEC X
	}
	if(DY<0)
	{
		DY=-DY;
		Y_INC=-1;												//IF DY NEG DEC X
	}
	if(DX>=DY) 													//DECIDING STEEP OR GENTLE
	{
		STEPS=DX;
		X=X1;Y=Y1;
		putpixel(X0+X,Y0+Y,WHITE);							//PLOTING STARTING POINT

		G=2*DY-DX;												//INITIAL DECISION FACTOR
		while(STEPS)
		{
			if(G<0)
			{
				X+=X_INC;
				putpixel(X0+X,Y0+Y,WHITE);
				G=G+2*DY;
			}
			else
			{
				X+=X_INC;
				Y+=Y_INC;
				putpixel(X0+X,Y0+Y,WHITE);
				G=G+2*DY-2*DX;
			}
			STEPS--;
		}
	}
	else
	{
		STEPS=DY;
		X=X1;Y=Y1;
		TEMP=DY;
		DY=DX;
		DX=TEMP;
		putpixel(X0+X,Y0+Y,WHITE);							//PLOTING STARTING POINT

		G=2*DY-DX;												//INITIAL DECISION FACTOR
		while(STEPS)
		{
			if(G<0)
			{
				Y+=Y_INC;
				putpixel(X0+X,Y0+Y,WHITE);
				G=G+2*DY;
			}
			else
			{
				Y+=Y_INC;
				X+=X_INC;
				putpixel(X0+X,Y0+Y,WHITE);
				G=G+2*DY-2*DX;
			}
			STEPS--;
		}
	}

	putpixel(X0,Y0,WHITE);
	delay(10000);											//DELAY FOR DISPLAY
	closegraph();											//CLOSING THE GRAPH
}


int main()													//MAIN FUNCTION
{
	cout<<"DRAWING USING DDA LINE DRAWING ALGORITHM"<<endl;
	char c_ch;
	DDA L1;												//CREATING OBJECT OF CLASS DDA WHER ALL DATA IS STORED
	L1.getCOORDINATES();
	L1.putCOORDINATES();
	L1.drawLINE();
	cout<<endl<<"LINE DRAWN SUCCESSFULLY"<<endl;
	cout<<"DRAWING USING BRESENHAM'S LINE DRAWING ALGORITHM"<<endl;
	BRESENHAM L2;												//CREATING OBJECT OF CLASS DDA WHER ALL DATA IS STORED
	L2.getCOORDINATES();
	L2.putCOORDINATES();
	L2.drawLINE();
	cout<<endl<<"LINE DRAWN SUCCESSFULLY"<<endl;
	return 0;
}	