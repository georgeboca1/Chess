#include <cstdio>
#include <math.h>

#include "Game.h"
#include "TableHandler.h"
#include "Piece.h"
#include "Renderer.h"


Game::Game()
{
	this->renderer = new Renderer("Chess", 800, 700);
	this->table = new TableHandler();
    this->moveMade = false;
    this->renderer->getWindowSize(&this->windowWidth, &this->windowHeight);
    this->pieceSelected = false;
}

Game::~Game()
{
	delete this->renderer;
	delete this->table;
}

void Game::init()
{
    //this->table->arrangePiecesOnBoard();
}

void Game::loop()
{
    bool isRunning = true;
    SDL_Event event;
    Uint32 startTicks = SDL_GetTicks();
    int frameRateCount = 0;
    SDL_MouseButtonEvent mousePressed = {};
    // Main loop
    while (isRunning) 
    {
        // Handle events

        while (SDL_PollEvent(&event)) 
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == 1)
                    {
                        int x = event.button.x / (this->windowWidth / 8);
                        int y = event.button.y / (this->windowHeight / 8);
						if (pieceSelected) //&& this->table->getPieceAtCoordinate(y, x).getPieceType() == NONE)
                        {
                            this->renderer->drawValidMoves(this->selectedPiece, this->table->getBoard());
                            std::vector<std::vector<int>> moves = this->selectedPiece.getValidMoves(this->table->getBoard());
                            for (auto& move : moves)
                            {
                                if (move[0] == x && move[1] == y)
                                {
                                    this->table->removePieceAtCoordinate(this->selectedPiece.getX(), this->selectedPiece.getY());
                                    this->selectedPiece.changeCoordinates(x, y);
                                    /*this->renderer->clear();
                                    this->renderer->drawBoard();
                                    this->renderer->drawPieces(this->table->getBoard());*/
                                    /*this->renderer->present();*/
                                    this->table->putPieceAtCoordinate(this->selectedPiece, y, x);
                                    /*this->renderer->clear();
                                    this->renderer->drawBoard();
                                    this->renderer->drawPieces(this->table->getBoard());
                                    this->renderer->present();*/
                                    this->table->debug_printTable();
                                    this->moveMade = true;
                                    this->pieceSelected = false;
                                    this->selectedPiece = Piece();
                                }
                            }
                        }
                        else
                        {
                            this->renderer->drawPressedRectangle(event.button.x, event.button.y);
                            int x = event.button.x / (this->windowWidth / 8);
                            int y = event.button.y / (this->windowHeight / 8);
                            this->drawRedSquare = true;
                            this->redSquareX = event.button.x;
                            this->redSquareY = event.button.y;
                            this->selectedPiece = this->table->getPieceAtCoordinate(y, x);
                            this->pieceSelected = true;
                            this->renderer->drawValidMoves(this->selectedPiece, this->table->getBoard());
                        }
                    }
                    break;

            }
            
        }
        Uint64 start = SDL_GetPerformanceCounter();

        this->renderer->clear();
        this->renderer->drawBoard();
        this->renderer->drawPieces(this->table->getBoard());
        this->renderer->drawValidMoves(this->selectedPiece, this->table->getBoard());

        if (this->drawRedSquare)
            this->renderer->drawPressedRectangle(this->redSquareX, this->redSquareY);

        
            
        if (this->moveMade)
        {
            this->drawRedSquare = false;
            this->moveMade = false;
        }


        printf("%s", SDL_GetError());
        this->renderer->present();

        /*Uint64 end = SDL_GetPerformanceCounter();
        if (frameRateCount % 10 == 0) {
            float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
            printf("FPS: %f\n", 1 / elapsed);
        }*/

        frameRateCount++;
        SDL_Delay(6);
        
    }


}
