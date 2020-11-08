#include <raylib.h>
#include <string>



//-----------------------------------------------
//			Global Variables	
//-----------------------------------------------


typedef enum game_state {MENU = 0, GAME, SCORE} game_state;

int ballVelX = 3;
int ballVelY = 0;

int player1PaddleY = 165;
int player2PaddleY = 165;

int ballX = 195;
int ballY = 195;

int player1Score = 0;
int player2Score = 0;

int lastScore = 1;

game_state currentScreen = MENU;

// Reset the balls position
void resetBall() {
	ballX = 195;
	ballY = 195;
	ballVelY = 0;
	ballVelX = 3;
}

void resetPaddles() {
	player1PaddleY = 165;
	player2PaddleY = 165;
}


void drawMenu() {

	//-----------------------------------------------
	//			Draw Menu
	//-----------------------------------------------

	
	BeginDrawing();
	ClearBackground(RAYWHITE);

	DrawText("Pooong", (GetScreenWidth() / 2) - 75, 80, 40, BLACK);

	DrawText("Press Enter to Play", (GetScreenWidth() / 2) - 125, 200, 25, GRAY);

	if (IsKeyPressed(KEY_ENTER)) { 

		Sound boop = LoadSound("boop.wav");
		PlaySound(boop);

		currentScreen = GAME;
	}

	EndDrawing();
}

void drawScore() {
	
	//-----------------------------------------------
	//			Draw Score
	//-----------------------------------------------

	BeginDrawing();
	ClearBackground(RAYWHITE);

	// Generate response string
	std::string beginning = "Player ";
	std::string end = " Scored!";

	std::string final = beginning + std::to_string(lastScore) + end;

	DrawText(final.c_str(), 33, 120, 40, GRAY);
	DrawText("Press Enter to continue", 75, 220, 20, GRAY);
	
	// Check if player has pressed enter to continue
	if (IsKeyPressed(KEY_ENTER)) {
		resetBall();
		resetPaddles();
		currentScreen = GAME;
	}


	EndDrawing();
}
void drawGame() {

	ClearBackground(RAYWHITE);


	//-----------------------------------------------
	//			FPS Counter
	//-----------------------------------------------

	int FPS = GetFPS();
	std::string sFPS = std::to_string(FPS);
	DrawText(sFPS.c_str(), 10, 10, 25, GRAY);

	//-----------------------------------------------
	//			Draw Paddles
	//-----------------------------------------------

	Rectangle player1 = { 20, player1PaddleY, 10, 70 }; // Player 1
	Rectangle player2 = { 380, player2PaddleY, 10, 70 };  // Player 2

	DrawRectangleRec(player1, DARKBLUE);
	DrawRectangleRec(player2, RED);

	//-----------------------------------------------		
	//			Draw Ball
	//-----------------------------------------------

	Rectangle ball = { ballX, ballY, 10, 10 };
	DrawRectangleRec(ball, BLACK);

	//-----------------------------------------------
	//			Draw Score
	//-----------------------------------------------

	std::string strPlayer1 = std::to_string(player1Score);
	std::string strPlayer2 = std::to_string(player2Score);

	DrawText(strPlayer1.c_str(), 40, 40, 20, BLACK);
	DrawText(strPlayer2.c_str(), 360, 40, 20, BLACK);

	//-----------------------------------------------
	//			Physics
	//-----------------------------------------------

	ballX += ballVelX;
	ballY += ballVelY;

	// Player 1 Score
	if (ballX + 10 >= GetScreenWidth()) {
		player1Score++;
		currentScreen = SCORE;
		lastScore = 1;
		drawScore();

	}
	
	// Player 2 Score
	if (ballX <= 0) {
		player2Score++;
		currentScreen = SCORE;
		lastScore = 2;
		drawScore();
	}

	// Collision off the top or bottom of the screen
	if (ballY + 10 >= GetScreenHeight() || (ballY <= 0)) ballVelY *= -1;

	// Collision with paddles
	if (CheckCollisionRecs(player1, ball)) {
		if (ballVelY == 0) {
			int random = GetRandomValue(1, 2);

			switch (random) {
			case 1: {
				ballVelY = -3;		// Randomises the direction at the start of the game on the Y-Axis
			}break;
			case 2:
			{
				ballVelY = 3;
			}break;
			}
		}
			ballX += 10;
			ballVelX *= -1;
		
	}
	if (CheckCollisionRecs(player2, ball)) {
		if (ballVelY == 0) {
			int random = GetRandomValue(1, 2);

			switch (random) {
			case 1: {
				ballVelY = -3;
			}break;
			case 2:
			{
				ballVelY = 3;
			}break;
			}
		}

			ballX -= 10;
			ballVelX *= -1;
		
	}

	//-----------------------------------------------		
	//			Player Movement
	//-----------------------------------------------		

	// Player 1
	if (IsKeyDown(KEY_W) && !(player1PaddleY - 5 <= 0)) player1PaddleY -= 4;
	if (IsKeyDown(KEY_S) && !(player1PaddleY + 75 >= GetScreenHeight())) player1PaddleY += 4;

	//Player 2
	if (IsKeyDown(KEY_UP) && !(player2PaddleY - 5 <= 0)) player2PaddleY -= 4;
	if (IsKeyDown(KEY_DOWN) && !(player2PaddleY + 75 >= GetScreenHeight())) player2PaddleY += 4;

	EndDrawing();
}

int main() {
	
	

	//-----------------------------------------------
	//			Window Loop
	//-----------------------------------------------

	InitWindow(400, 400, "Poong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {

	//-----------------------------------------------
	//			Determine Current Screen
	//-----------------------------------------------
		
		switch (currentScreen) {
			case MENU:
			{
				drawMenu(); // Load the menu
			}break;

			case GAME:
			{
				drawGame();	// Load the main game view
			}break;

			case SCORE:
			{
				drawScore(); // Load the score page
			}break;
				
			default: break;
		}



	}

	CloseWindow();
}