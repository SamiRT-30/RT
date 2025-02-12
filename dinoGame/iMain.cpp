﻿#include "iGraphics.h"  // Include the iGraphics library for graphical operations
#include <cstdlib>  // For random number generation
#include <ctime>  // For time functions (needed for srand)
#include <windows.h> // For PlaySound (to play background music)


//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://



// Global variables for the main menu
int bgImage, dinoImage, buttonImage;  // Variables to hold image IDs for background, dinosaur, and button
int windowWidth = 1000, windowHeight = 600;  // Set the window size
int buttonX = 100, buttonY = 450;  // Set the position for the buttons on the main menu
bool gameStarted = false;  // Flag to check if the game has started



// Global variables for the game
const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 600;  // Set the screen size for the game
int dinoX = 150, dinoY = 50, dinoWidth = 100, dinoHeight = 100;  // Dino's initial position and size
bool isJumping = false;  // Flag to check if the dinosaur is jumping
int jumpSpeed = 20, gravity = -7, jumpHeight = 350, currentJumpHeight = 0;  // Jump and gravity properties
int fireX, fireY, fireWidth = 25, fireHeight = 25;  // Fire properties (position and size)
int fireSpeed = 20;  // Fire speed
bool isFireActive = false;  // Flag to check if the fire is active
int obsX = SCREEN_WIDTH, obsY = 30, obsWidth = 70, obsHeight = 70;  // Obstacle properties (position and size)
int birdX = SCREEN_WIDTH + 400, birdY = 300, birdWidth = 70, birdHeight = 70;  // Bird properties (position and size)
int gameSpeed = 5;  // Speed at which obstacles and birds move
int bgX = 0, bgSpeed = 5;  // Background scrolling speed
int score = 0, highScore = 0;  // Score and high score
char scoreText[20], highScoreText[20];  // Strings to store score and high score text
bool isGameOver = false;  // Flag to check if the game is over
int lives = 3;  // Number of lives
int backgroundImage, dinoImage2, birdImage, obsImage, heartImage, fireImage;  // Image variables for game elements



// Function declarations for the main menu
void iLoadMainMenuImages();  // Function to load images for the main menu
void iDrawMainMenu();  // Function to draw the main menu
void iMouseMainMenu(int button, int state, int mx, int my);  // Function to handle mouse events for the main menu



// Function declarations for the game
void jump();  // Function for jumping logic
void resetObstacle();  // Function to reset the obstacle
void resetBird();  // Function to reset the bird
void resetGame();  // Function to reset the game
void increaseGameSpeed();  // Function to increase the game's speed
void iTimer();  // Timer function for game logic
void loadGameImages();  // Function to load game images
bool detectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);  // Function to detect collision between two objects
void playBackgroundMusic();  // Function to play background music



// Main menu functions
void iLoadMainMenuImages() {
bgImage = iLoadImage("dino back 2.bmp");  // Load background image for main menu
dinoImage = iLoadImage("dino1.bmp");     // Load dinosaur image for main menu
buttonImage = iLoadImage("back.bmp");     // Load button image
}



void iDrawMainMenu() {
iClear();  // Clear the screen
iShowImage(0, 0, windowWidth, windowHeight, bgImage); // Show background image

// Display the dinosaur image on the main menu screen
iShowImage(350, -50, 500, 500, dinoImage);  // Adjusted dinosaur position and size

iSetColor(0, 128, 0);  // Set the color for text
iText(380, 550, "Dino Dash: Cactus Run", GLUT_BITMAP_TIMES_ROMAN_24); // Display the title
iShowImage(buttonX, buttonY, 250, 60, buttonImage);  // Display the Play button
iShowImage(buttonX, buttonY - 90, 250, 60, buttonImage);  // Display Instructions button
iShowImage(buttonX, buttonY - 180, 250, 60, buttonImage);  // Display Score button
iShowImage(buttonX, buttonY - 270, 250, 60, buttonImage);  // Display Exit button

iSetColor(225, 225, 225);  // Set the color for the button text
iText(buttonX + 100, buttonY + 20, "Play", GLUT_BITMAP_HELVETICA_18);  // Display Play text
iText(buttonX + 70, buttonY - 65, "Instructions", GLUT_BITMAP_HELVETICA_18);  // Display Instructions text
iText(buttonX + 90, buttonY - 155, "Score", GLUT_BITMAP_HELVETICA_18);  // Display Score text
iText(buttonX + 100, buttonY - 245, "Exit", GLUT_BITMAP_HELVETICA_18);  // Display Exit text
}



void iMouseMainMenu(int button, int state, int mx, int my) {
if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {  // If the mouse left button is clicked
if (mx >= buttonX && mx <= buttonX + 250) {  // If mouse is over the button
if (my >= buttonY && my <= buttonY + 60) {  // If Play button is clicked
gameStarted = true;  // Start the game
}
}
}
}



// Game functions
void loadGameImages() {
backgroundImage = iLoadImage("background.bmp");  // Load background image for the game
dinoImage2 = iLoadImage("dino.bmp");  // Load dinosaur image for the game
birdImage = iLoadImage("enemy.bmp");  // Load bird image
obsImage = iLoadImage("cactus.bmp");  // Load obstacle image (cactus)
heartImage = iLoadImage("heart.bmp");  // Load heart image (for lives)
fireImage = iLoadImage("fire.bmp");  // Load fire image (for shooting)
}



bool detectCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
return !(x1 + w1 < x2 || x1 > x2 + w2 || y1 + h1 < y2 || y1 > y2 + h2);  // Return true if collision is detected
}



void playBackgroundMusic() {
PlaySound("C:\\Users\\student\\Documents\\Visual Studio 2010\\Projects\\dinoGame\\dinoGame\\dino music.wav", NULL, SND_LOOP | SND_ASYNC);  // Play background music in loop
}



void iDraw()
{


if (gameStarted) {  // If the game has started
iClear();  // Clear the screen
iShowImage(bgX, 0, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundImage);  // Show the background
iShowImage(bgX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, backgroundImage);  // Scroll background

iSetColor(139, 69, 19);  // Set ground color (brown)
iFilledRectangle(0, 30, SCREEN_WIDTH, 30);  // Draw the ground

iShowImage(dinoX, dinoY, dinoWidth, dinoHeight, dinoImage2);  // Show dinosaur

if (isFireActive) {  // If the fire is active
iShowImage(fireX, fireY, fireWidth, fireHeight, fireImage);  // Show the fire
}

iShowImage(obsX, obsY, obsWidth, obsHeight, obsImage);  // Show the obstacle
iShowImage(birdX, birdY, birdWidth, birdHeight, birdImage);  // Show the bird

sprintf_s(scoreText, sizeof(scoreText), "Score: %d", score);  // Format the score text
iSetColor(0, 0, 0);  // Set text color to black
iText(20, SCREEN_HEIGHT - 30, scoreText, GLUT_BITMAP_HELVETICA_18);  // Display score

sprintf_s(highScoreText, sizeof(highScoreText), "High Score: %d", highScore);  // Format the high score text
iText(20, SCREEN_HEIGHT - 50, highScoreText, GLUT_BITMAP_HELVETICA_18);  // Display high score

// Display hearts for lives
for (int i = 0; i < lives; i++) {
iShowImage(800 + (i * 40), SCREEN_HEIGHT - 50, 30, 30, heartImage);  // Adjust heart positions
}

// Display Game Over message
if (isGameOver) {
iSetColor(255, 0, 0);  // Set text color to red
iText(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, "Game Over! Press 'R' to Restart", GLUT_BITMAP_TIMES_ROMAN_24);  // Show Game Over message
iPauseTimer(0);  // Pause the timer
}
}
else {  // If the game is not started
iDrawMainMenu();  // Draw the main menu
}


}




// Jumping and other game logic follows...
void jump() {
if (isJumping) {  // If the dinosaur is jumping
dinoY += jumpSpeed;  // Move the dinosaur upwards
currentJumpHeight += jumpSpeed;  // Increment the jump height
if (currentJumpHeight >= jumpHeight) {  // If the jump height is reached
isJumping = false;  // Stop jumping
}
}
else if (dinoY > 30) {  // If not jumping and dinosaur is above ground
dinoY += gravity;  // Apply gravity to the dinosaur
}

if (dinoY < 30) {  // If dinosaur is below ground
dinoY = 30;  // Keep it on the ground
}
}



void resetObstacle() {
obsX = SCREEN_WIDTH + rand() % 400;  // Reset the obstacle position to the right side of the screen
}



void resetBird() {
birdX = SCREEN_WIDTH + rand() % 600;  // Reset bird position to the right side of the screen
}



void resetGame() {
dinoY = 30;  // Reset dinosaur position to the ground
isJumping = false;  // Stop jumping
isFireActive = false;  // Deactivate fire
obsX = SCREEN_WIDTH;  // Reset obstacle position
birdX = SCREEN_WIDTH + 400;  // Reset bird position
score = 0;  // Reset score
bgX = 0;  // Reset background position
isGameOver = false;  // Reset game over flag
iResumeTimer(0);  // Resume the timer
}



void increaseGameSpeed() {
if (score % 100 == 0 && gameSpeed < 25) {  // Increase game speed after every 100 points
gameSpeed++;  // Increase the speed
}
}



void iTimer() {
if (gameStarted && !isGameOver) {  // If the game has started and is not over
bgX -= bgSpeed;  // Move the background left
if (bgX <= -SCREEN_WIDTH) {  // If background has moved out of screen
bgX = 0;  // Reset the background position
}

obsX -= gameSpeed;  // Move the obstacle left
birdX -= gameSpeed;  // Move the bird left

if (isFireActive) {  // If the fire is active
fireX += fireSpeed;  // Move the fire right
if (fireX > SCREEN_WIDTH || detectCollision(fireX, fireY, fireWidth, fireHeight, birdX, birdY, birdWidth, birdHeight)) {
resetBird();  // Reset bird if it collides with fire
isFireActive = false;  // Deactivate fire
}
}

if (obsX < 0) resetObstacle();  // Reset the obstacle if it moves out of the screen
if (birdX < 0) resetBird();  // Reset the bird if it moves out of the screen

// Check for collisions with obstacles and birds
if (detectCollision(dinoX, dinoY, dinoWidth, dinoHeight, obsX, obsY, obsWidth, obsHeight) || detectCollision(dinoX, dinoY, dinoWidth, dinoHeight, birdX, birdY, birdWidth, birdHeight)) {
lives--;  // Decrease lives if collision occurs
if (lives > 0) {
resetGame();  // Reset the game if lives are left
}
else {
isGameOver = true;  // End the game if no lives are left
if (score > highScore) {
highScore = score;  // Update high score if necessary
}
}
}

score++;  // Increment the score
increaseGameSpeed();  // Increase game speed as score increases
}
jump();  // Call the jump function to handle jumping
}




/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my)
{

}
//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{

}



void iMouse(int button, int state, int mx, int my)
{

if (gameStarted)
{
if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // If left mouse button is clicked
{

if (!isGameOver && dinoY == 30) // If dinosaur is on the ground
{  
isJumping = true;  // Make the dinosaur jump
currentJumpHeight = 0;  // Reset jump height
}

else if ((mx >= dinoX && mx <= dinoX + dinoWidth && my >= dinoY && my <= dinoY + dinoHeight)) // If fire button is clicked
{  
if (!isFireActive) // If fire is not active
{  
isFireActive = true;  // Activate fire
fireX = dinoX + dinoWidth;  // Set fire position to right of dinosaur
fireY = dinoY + (dinoHeight / 2);  // Set fire's vertical position to mid of dinosaur
}
}
}
}

else
{
iMouseMainMenu(button, state, mx, my);  // Handle mouse events in main menu
}


}




/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/


// Keyboard functions (solve the linker errors)
void iKeyboard(unsigned char key)
{
if (gameStarted)
{
if (key == 'r' || key == 'R') // If the user presses 'R' to restart the game
{  
resetGame();  // Reset the game
}
}
}





/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key)
{


if (key == GLUT_KEY_RIGHT)
{

}
if (key == GLUT_KEY_LEFT)
{

}

if (key == GLUT_KEY_HOME)
{

}

}


int main()
{


///srand((unsigned)time(NULL));
iInitialize(windowWidth, windowHeight, "Project Title" );  // Initialize the game window with specified size

srand(time(0));  // Seed the random number generator with current time

iLoadMainMenuImages();  // Load images for the main menu

loadGameImages();  // Load images for the game

playBackgroundMusic();  // Play the background music

iSetTimer(30, iTimer);  // Set a timer to call iTimer function every 30 ms

///updated see the documentations
iStart();  // Start the iGraphics library and begin the game loop
return 0;



}