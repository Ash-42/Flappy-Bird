#include "gamestate.h"

const int WIDTH = 1200;
const int HEIGHT = 600;
int PIPES = 4;
int ACTIVE = 0;

SDL_Texture* LoadTexture(char* path, Gamestate* game)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* tempSurface = IMG_Load(path);
    if (tempSurface == NULL)
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	else {
        texture = SDL_CreateTextureFromSurface(game -> renderer, tempSurface);
        if (texture == NULL)
            printf("Unable to create texture from surface: %s! SDL_image Error: %s\n", path, IMG_GetError());
        SDL_FreeSurface(tempSurface);
    }
    return texture;
}

int LoadMedia(Gamestate *game)
{
	int success = 1;
	
	game -> bird_sprite = LoadTexture("graphics/fbird.png", game);
    if (game -> bird_sprite == NULL)
        success = 0;
	else printf("Bird loaded\n");

    game -> pipe_sprite = LoadTexture("graphics/pipe.png", game);
    if (game -> pipe_sprite == NULL)
        success = 0;
	else printf("Pipes loaded\n");

    game -> bkg_sprite = LoadTexture("graphics/bg.png", game);
	if (game -> bkg_sprite == NULL)
		success = 0;

    return success;
}

int InitGame(Gamestate *game)
{
    game -> running = 1;
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
      printf("Unable to initialize SDL: %s\n", SDL_GetError());
      return 1;
    }
	else if (TTF_Init() == -1) {
		printf("Unable to initialise TTF\n");
		return 1;
	}
    else {
        game -> window = SDL_CreateWindow("Flappy Bird with a Twist",                  // window title
                                                                          SDL_WINDOWPOS_UNDEFINED,  // initial x position
                                                                          SDL_WINDOWPOS_UNDEFINED,  // initial y position
                                                                          WIDTH,
                                                                          HEIGHT,                 
                                                                          SDL_WINDOW_OPENGL);               // flags    

        game -> renderer = SDL_CreateRenderer(game -> window, -1, SDL_RENDERER_ACCELERATED |        
SDL_RENDERER_PRESENTVSYNC);

        game -> TimeLast = 0;
        game-> TimeNow = SDL_GetPerformanceCounter();
        game-> WhichPipeToStart = 0;
        game-> PipeGenerationTimeLast = 0;  

		if (!LoadMedia(game)) 
			printf ("Unable to load media.\n");
      
		game -> font = TTF_OpenFont("graphics/fBirdFont.TTF", 50);
		if (game -> font == NULL) {
	    	printf("TTF_OpenFont: %s\n", TTF_GetError());
			exit(1);
		}

		TextInit(&game -> text, game -> font, 0);
		
		game -> bkg_window.x = 0;
		game -> bkg_window.y = 0;
		game -> bkg_window.w = WIDTH;
		game -> bkg_window.h = HEIGHT;
		
		BirdInit(&game -> bird);

		for (int i = 0; i < PIPES; ++i) 
			PipeInit(&game -> pipes[i]); 
    }
    return 0;
}

void ReceiveInput(Gamestate *game)
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
				game -> running = 0;
				SDL_Quit();
				exit(1);
		}
        else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
	        if(game -> window) {
                SDL_DestroyWindow(game -> window);
                game -> window = NULL;
                game -> running = 0;
            }
    }
}

void UpdateGame(Gamestate *game)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_SPACE]) 
		game -> bird.jump = 1;
       
    game -> TimeLast = game -> TimeNow;
    game -> TimeNow = SDL_GetPerformanceCounter();
    double deltaTime = ((game -> TimeNow - game -> TimeLast) * 1000 / (double) SDL_GetPerformanceFrequency()) / 1000;
    unsigned currentTime = SDL_GetTicks();
        
    if (game -> WhichPipeToStart < PIPES && currentTime > game -> PipeGenerationTimeLast + 4000) {
        if (game -> pipes[game -> WhichPipeToStart].isActive == 0) {
            game -> pipes[game -> WhichPipeToStart].isActive = 1;
            game -> WhichPipeToStart++;
            game -> PipeGenerationTimeLast = currentTime;
        }
        game -> WhichPipeToStart %= PIPES;
    }
	
	UpdateText(&game -> text);

	UpdateBird(&game -> bird);
	SetBoundary(&game -> bird);

    for (int i = 0; i < PIPES; ++i)
		UpdatePipe(&game -> pipes[i], deltaTime);

    for (int i = 0; i < PIPES; ++i)
            if (CheckCollision(&game -> pipes[i], &game -> bird))
                game -> bird.isAlive = 0;
}

void RenderDisplay(Gamestate *game)
{
    SDL_SetRenderDrawColor(game -> renderer, 0, 0, 0, 255);
    SDL_RenderClear(game -> renderer);
    
	SDL_RenderCopy(game -> renderer, game -> bkg_sprite, NULL, &game -> bkg_window);    

	if (ACTIVE == 0) {
		SDL_Texture *text = SDL_CreateTextureFromSurface(game -> renderer, game -> text.surface);			
		if (text == NULL) {
                printf("Unable to create texture from rendered text. SDL Error: %s\n", SDL_GetError());
				exit(1);
		}
		else {
			SDL_RenderCopy(game -> renderer, text, NULL, &game -> text.text_rect);
			SDL_DestroyTexture(text);
			text = NULL;
		}
	}

    for (int i = 0; i < PIPES; ++i) {
        if (game -> pipes[i].isActive) {
			if (ACTIVE == 0) 
				ACTIVE = 1;
			SDL_RenderCopyEx(game -> renderer, game -> pipe_sprite, NULL, &game -> pipes[i].top, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(game -> renderer, game -> pipe_sprite, NULL, &game -> pipes[i].bot, 0, NULL, SDL_FLIP_VERTICAL);
        }
    }

	if (game -> bird.isAlive)
		SDL_RenderCopy(game -> renderer, game -> bird_sprite, NULL, &game -> bird.b);
	else {
		SDL_FreeSurface(game -> text.surface);
		TextInit(&game -> text, game -> font, 1);

		SDL_Texture *text = SDL_CreateTextureFromSurface(game -> renderer, game -> text.surface);			
		if (text == NULL) {
                printf("Unable to create texture from rendered text. SDL Error: %s\n", SDL_GetError());
				exit(1);
		}
		else {
			SDL_RenderCopy(game -> renderer, text, NULL, &game -> text.text_rect);
			SDL_DestroyTexture(text);
			text = NULL;
		}
	}
	SDL_RenderPresent(game -> renderer);
}

void FreeResources(Gamestate *game)
{
	SDL_DestroyTexture(game -> bird_sprite);
   	game -> bird_sprite = NULL;
    
	SDL_DestroyTexture(game -> pipe_sprite);
    game -> pipe_sprite = NULL;

	SDL_DestroyTexture(game -> bkg_sprite);
    game -> bkg_sprite = NULL;

    SDL_DestroyRenderer(game -> renderer);
    SDL_DestroyWindow(game -> window);
	SDL_FreeSurface(game -> text.surface);
    SDL_Quit();
}
