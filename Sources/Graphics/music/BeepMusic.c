// ����  С����



#include <windows.h>



enum fy {

	d1 = 262,

	d1_ = 277,

	d2 = 294,

	d2_ = 311,

	d3 = 330,

	d4 = 349,

	d5 = 392,

	d5_= 415,

	d6 = 440,

	d6_= 466,

	d7 = 494,

	z1 = 523,

	z1_ = 554,

	z2 = 578,

	z2_ = 622,

	z3 = 659,

	z4 = 698,

	z4_ = 740,

	z5 = 784,

	z5_ = 831,

	z6 = 880,

	z6_ = 932,

	z7 = 988,

	g1 = 1046,

	g1_ = 1109,

	g2 = 1175,

	g2_ = 1245,

	g3 = 1318,

	g4 = 1397,

	g4_ = 1480,

	g5 = 1568,

	g5_ = 1661,

	g6 = 1760,

	g6_ = 1865,

	g7 = 1976,

	yaya = 0

};



struct yf

{

	enum fy s;

	int t;

};



int main()

{

	int n = 0;



	struct yf a[1000]= {
		{z3,125},{z3,50},{z4,100},{z3,50},{z2,50}, //5

		{z2,125},{z2,50},{z5,100},{z2,50},{z1,50}, //10

		{z1,125},{z1,50},{z6,100},{z5,100},    //14

		{z3,125},{z4,25},{z3,25},{z2,100},{z2,100}, //19

		{z3,125},{z3,50},{z4,100},{z5,50},{z3,50}, //24

		{z5,125},{z5,50},{g2,100},{z7,50},{g1,50}, //29

		{g1,200},{g1,50},{z7,50},{z6,50},{z7,50}, //34

		{g1,125},{z7,50},{g1,200},      //37

		{g1,50},{z7,50},{g1,50},{z7,50},{g1,100},{z3,50},{z5,50}, //44

		{z5,250},{z6,50},{z7,50},      //47

		{g1,50},{z7,50},{g1,50},{z7,50},{g1,100},{g2,100},{g3,100}, //54

		{g3,300},{z6,50},{z7,50},   //57

		{g1,50},{z7,50},{g1,50},{z7,50},{g1,100},{g3,100}, //63

		{z7,50},{z6,50},{z7,50},{z6,50},{z7,50},{z5,50},{z5,50},{g1,50}, //71

		{g1,200},{g3,75},{g4,25},{g4,50},{g3,50}, //76

		{g2,200},{yaya,50},{z5,50},{g1,50},{g2,50}, //81

		{g3,50},{g1,50},{g1,50},{z5,50},{z5,100},{z5,50},{g3,50}, //88

		{g2,50},{g3,50},{g2,50},{g1,50},{z5,50},{z5,50},{z6,50},{z7,50}, //96

		{g1,50},{z6,50},{z6,50},{z3,50},{z3,100},{yaya,50},{z7,50}, //103

		{g1,50},{z7,50},{g1,50},{g2,50},{z6,50},{z5,50},{z5,100}, //110

		{z6,100},{z5,50},{z6,50},{z7,100},{g3,50},{g4,50}, //116

		{g3,50},{g4,50},{g3,50},{g2,50},{g2,50},{g1,100},{z5,50}, //123

		{z5,50},{z4,50},{z4,50},{g1,50},{g1,50},{g3,50},{g3,50},{g1,50}, //131

		{g2,200},{yaya,50},{z5,50},{g1,50},{g2,50}, //136

		{g3,50},{g1,50},{g1,50},{z5,50},{z5,100},{z5,50},{g3,50}, //143

		{g2,50},{g3,50},{g2,50},{g1,50},{z5,50},{z5,50},{z6,50},{z7,50}, //151

		{g1,50},{z6,50},{z6,50},{z3,50},{z3,100},{z3,50},{z7,50}, //158

		{g1,50},{z7,50},{g1,50},{g2,50},{z6,50},{z5,50},{z5,100}, //165

		{z6,50},{z7,50},{g1,50},{g2,100},{g3,50},{g4,50}, //171

		{g3,50},{g4,50},{g2,50},{g1,50},{g2,50},{g1,50},{g1,100}, //178

		{g2,50},{g1,50},{g2,50},{z6,50},{g1,100},{g2,50},{g1,50}, //185

		{g1,400},   //186

		{g2,50},{g1,50},{g2,50},{z6,50},{z7,100},{z7,50},{g1,50}, //193

		{g1,400},   //194

	};



	struct yf *atop;

	atop = a;

	n = 194;



	while(n--) {

		Beep(atop->s,atop->t*5);

		atop++;

	}

	return 0;

}