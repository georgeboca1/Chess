#include <stdio.h>
#include <math.h>
#include <string>

#include "Game.h"
#include "TableHandler.h"
#include "Piece.h"
#include "Renderer.h"
#include "Parser.h"



Game::Game()
{
	this->renderer = new Renderer("Chess", 800, 700);
	this->table = new TableHandler();
    this->moveMade = false;
    this->renderer->getWindowSize(&this->windowWidth, &this->windowHeight);
    this->pieceSelected = false;
    this->playerTurn = true;
    this->stockFishDelay = 0;
    stockfish.sendCommand("uci");
    stockfish.sendCommand("isready");
    while (!stockfish.isReady());
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
        Uint64 start = SDL_GetPerformanceCounter();

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
						bool validMove = false;
                        int x = event.button.x / (this->windowWidth / 8);
                        int y = event.button.y / (this->windowHeight / 8);
						if (pieceSelected && playerTurn)
                        {
                            this->renderer->drawValidMoves(this->selectedPiece, this->table->getBoard());
                            std::vector<std::vector<int>> moves = this->selectedPiece.getValidMoves(this->table->getBoard(), false);
                            for (auto& move : moves)
                            {
                                if (move[0] == x && move[1] == y)
                                {
                                    this->lastX = this->selectedPiece.getX();
                                    this->lastY = this->selectedPiece.getY();
                                    this->newX = y;
                                    this->newY = x;
                                    this->table->removePieceAtCoordinate(this->lastX, this->lastY);
                                    this->selectedPiece.changeCoordinates(x, y);
                                    this->table->putPieceAtCoordinate(this->selectedPiece, y, x);
                                    this->moveMade = true;
                                    this->pieceSelected = false;
                                    this->selectedPiece = Piece();
									this->playerTurn = !this->playerTurn;

                                    
									validMove = true;
                                }
                            }
                            if (!validMove)
                            {
                                this->renderer->drawPressedRectangle(event.button.x, event.button.y);
                                int x = event.button.x / (this->windowWidth / 8);
                                int y = event.button.y / (this->windowHeight / 8);
                                this->drawRedSquare = true;
                                this->redSquareX = event.button.x;
                                this->redSquareY = event.button.y;
                                this->selectedPiece = this->table->getPieceAtCoordinate(y, x);
                            }

                        }
						else if (this->table->getPieceAtCoordinate(y, x).getPieceType() != NONE && this->table->getPieceAtCoordinate(y, x).getPieceColor() != BLACK)
                        {
                            this->renderer->drawPressedRectangle(event.button.x, event.button.y);
                            int x = event.button.x / (this->windowWidth / 8);
                            int y = event.button.y / (this->windowHeight / 8);
                            this->drawRedSquare = true;
                            this->redSquareX = event.button.x;
                            this->redSquareY = event.button.y;
                            this->selectedPiece = this->table->getPieceAtCoordinate(y, x);
                            this->pieceSelected = true;
							/*if (this->selectedPiece.getPieceColor() != WHITE || this->selectedPiece.getPieceType() == NONE)
							{*/
								//this->pieceSelected = false;
								//this->drawRedSquare = false;
								//this->selectedPiece = Piece(NONE, NOCOLOR);
							//}
                            this->renderer->drawValidMoves(this->selectedPiece, this->table->getBoard());
                        }
                    }
                    break;

            }
            
        }

        this->renderer->clear();
        this->renderer->drawBoard();
        this->renderer->drawPieces(this->table->getBoard());
        
        if (playerTurn) this->renderer->drawValidMoves(this->selectedPiece, this->table->getBoard());

        if (this->drawRedSquare)
            this->renderer->drawPressedRectangle(this->redSquareX, this->redSquareY);

		if (isKinginCheck(this->table->getBoard(), WHITE))
		{
			std::vector<int> kingCoords = this->table->getPieceCoordinates(KING, WHITE);
			this->renderer->drawCheck(kingCoords[1], kingCoords[0]);
		}
        
            
        if (this->moveMade)
        {
            this->drawRedSquare = false;
            this->moveMade = false;
        }

        if (!this->playerTurn)
        {
            if (this->stockFishDelay < 75)
            {
                this->stockFishDelay++;
            }
            else
            {
                stockfish.sendMoves(Parser::coordinatesToAlphabeticForm(lastY, lastX, newX, newY));

                std::string str_response = stockfish.readResponse();
                std::vector<int> response = Parser::alphabeticFormToCoordinates(str_response);

                stockfish.addMove(Parser::getAlphabeticFormFromString(str_response));

                Piece opponentPiece = this->table->getPieceAtCoordinate(response[0], response[1]);
                this->table->removePieceAtCoordinate(response[0], response[1]);
                this->table->putPieceAtCoordinate(opponentPiece, response[2], response[3]);

                playerTurn = !playerTurn;
                this->stockFishDelay = 0;
            }
        }

        printf("%s", SDL_GetError());
        this->renderer->present();

        Uint64 end = SDL_GetPerformanceCounter();
        if (frameRateCount % 30 == 0) {
            float elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
            printf("FPS: %f\n", 1 / elapsed);
        }

        frameRateCount++;
        SDL_Delay(6);
        
    }


}
