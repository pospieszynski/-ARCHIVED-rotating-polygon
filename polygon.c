#include "primlib.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define phase_shift 1
#define Radious_Change 100
#define sides 60
#define Dely 10

void ComputingCoordinates(float coordinates[sides][2], float angle, int R, float *phase_pointer);
void Drawing(float coordinates[sides][2]);

int main(int argc, char* argv[])
{		
	float angle=(float)(360/sides);
	float phase=0;
	float *phase_pointer=&phase;
	float coordinates[sides][2];
	int R=50;
	int i;
	int k = 1;
	bool j = true;

	if(initGraph())
	  exit(3);
	/* clear screen */

	while(pollkey() == -1){ 
		for(i=0; i<Radious_Change; i++){ 	
			filledRect(0, 0, screenWidth()-1, screenHeight()-1, BLACK);
			ComputingCoordinates(coordinates, angle, R, phase_pointer);
			Drawing(coordinates);
			updateScreen();
			SDL_Delay(Dely);

			if(k%50 == 0){
				k=0;
				j = !j;
			}
			if(j){
				R--;
			}
			else{
				R++;
			}
			k++;
		}
	}

	return 0;
}


void ComputingCoordinates(float coordinates[sides][2], float angle, int R, float *phase_pointer){
	int i;

	for(i=0; i<sides; i++){
		coordinates[i][0]=screenWidth()/2.0 + R*cos(((i*angle)+(*phase_pointer))*((M_PI)/(180.0)));	
		coordinates[i][1]=screenHeight()/2.0 + R*sin(((i*angle)+(*phase_pointer))*((M_PI)/(180.0)));
	}

	if(*phase_pointer == 360.0){
		 *phase_pointer=0;
	}
	
	*phase_pointer+=phase_shift;
}

void Drawing(float coordinates[sides][2]){
	int i;

	for(i=0; i<sides; i++){
		line(coordinates[i][0], coordinates[i][1], coordinates[(i+1)%sides][0], coordinates[(i+1)%sides][1], GREEN);
	}

}
