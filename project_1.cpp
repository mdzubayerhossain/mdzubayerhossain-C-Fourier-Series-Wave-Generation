//####################################################################
//#       Fourier Series Wave Generation By Zubayer Hossain Patowari #
//####################################################################
#include <iostream>
#include <vector>
#include <math.h>
#include <SDL2/SDL.h>

using namespace std;

#define TWO_PI 2 * 3.1416  // PI Values
#define PI 3.1416 // PI Values

void print(string str){
    cout<<str;
}
void println(string str){
    cout<<str<<endl;
}
void drawCircle(SDL_Renderer *ren, int x, int y, int r){ // Function to draw circles with line
    float px = r * cos(0.04);
    float py = r * sin(0.04);
    for(float i = 0; i < TWO_PI; i += 0.04){
	float cx = r * cos(i);
	float cy = r * sin(i);
        if(px != 0 && py != 0){
		SDL_RenderDrawLine(ren, x + cx, y + cy, x + px, y + py);
	}
	px = cx;
	py = cy;
    }
}
int main(int argc, char **argv){
	// 	SDL Window Creation
    SDL_Window *win = SDL_CreateWindow("Fourier Series Wave Generation | Abthahi Ahmed Rifat", 100,100, 1000, 600, SDL_WINDOW_SHOWN);
    if(!win){
        cout<<"Error in creating Window"<<endl;
        exit(1);
    }
	// 	SDL Renderer Creation
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
    if(!ren){
        cout<<"Error in creating Renderer"<<endl;
        exit(1);
    }

    SDL_Event event;

	int x = 300, y = 300; // Initial Value "Position of the circle orbit"
	float r = 100; // Basic Radius
	bool running = true; // Program run state
	float time = 0; // initial value that will increase
	vector<float> waves; // Vector of float numbers
	int n = 1; // A value of equation

	while(running){
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

		float cx = 0;
		float cy = 0;

		for (int i = 0; i < 12; i++){
			float prevx = cx;
			float prevy = cy;
			n = i * 2 + 1;

			r = 100 * (4 / (n * PI)); //     4
			cx +=  r * cos(n * time); //   ----- x cos(n * time) "Theta is time here";
			cy +=  r * sin(n * time); //	nPI


			drawCircle(ren, x + prevx, y + prevy, r);


			SDL_RenderDrawLine(ren, x + cx, y + cy, x + prevx, y + prevy);

		}
		SDL_RenderDrawLine(ren, x + cx, y + cy, 700 , y+cy);
		waves.insert(waves.begin(), cy); // Insert value of last circle's y axis into wave vector

		float vpx = 700, vpy = y+cy;
		for (unsigned int i=0; i < waves.size(); i++){
			SDL_RenderDrawLine(ren, vpx, vpy, 700 + i, y + waves[i]); // Draw the Wave /\/\/\/\/\/\
			vpx = 700 + i;
			vpy = y + waves[i];
		}

		if(waves.size() > 400){
			waves.pop_back(); //delete last value of wave vector when the size of it more than 400;
		}



		SDL_PollEvent(&event); // Event Listener;
		if(event.type == SDL_QUIT){
		    running = false;
		}
		SDL_RenderPresent(ren); // Render the graphics

		if(time > TWO_PI){
			time = 0;
		}


		time += 0.05;
		cout<<time<<endl;
    }
    if(running == false){
        print("Program Terminated.");
    }
    return 0;
}
