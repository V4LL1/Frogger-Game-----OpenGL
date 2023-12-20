#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <stdio.h>
// Variáveis para as cores
float red[3] = {1.0, 0.0, 0.0};
float blue[3] = {0.0, 0.0, 1.0};
float green[3] = {0.0, 1.0, 0.0};
float yellow[3] = {1.0, 1.0, 0.0};

// Variáveis do sapo
//posição
float frogX = 0.0;
float frogY = -0.90;
float stepSize = 0.15f;  // Tamanho do passo para mover o sapo
//lógica
bool frogOnRoad = true;
bool frogOnStem = false;
bool frogOnGrass = false;

// Variáveis de lógica do jogo
bool gameOverFlag = false;
int score = 0;
bool isPaused = false;

// Variáveis de posição dos carros
float carX = -0.9; // Inicialmente, o carro começa mais à esquerda
float carY = -0.75;
float carSpeed = 0.022; // Velocidade do carro

float car2X = 0.9; // Inicialmente, o carro começa mais à direita
float car2Y = -0.6;
float carSpeed2 = -0.018; // Velocidade do carro 2

float car3X = -1.2; // Inicialmente, o carro começa mais à esquerda
float car3Y = -0.45;
float carSpeed3 = 0.014; // Velocidade do carro 3

float car4X = 1.2; // Inicialmente, o carro começa mais à direita
float car4Y = -0.30;
float carSpeed4 = -0.0235; // Velocidade do carro 4

float car5X = -1.5; // Inicialmente, o carro começa mais à esquerda
float car5Y = -0.15;
float carSpeed5 = 0.0165; // Velocidade do carro 5

float car6X = 1.5; // Inicialmente, o carro começa mais à direita
float car6Y = 0;
float carSpeed6 = -0.0500; // Velocidade do carro 5


// Variáveis de posição dos troncos
float stem1X = -1.2; // Inicialmente, o tronco começa mais à esquerda
float stem1Y = 0.15;
float stemSpeed1 = 0.022; // Velocidade do tronco

float stem1_2X = -2.4; // Inicialmente, o tronco começa mais à esquerda
float stem1_2Y = 0.15;
float stemSpeed1_2 = 0.022; // Velocidade do tronco

float stem2X = 1.2; // Inicialmente, o tronco começa mais à direita
float stem2Y = 0.30;
float stemSpeed2 = -0.036; // Velocidade do tronco

float stem2_2X = 2.4; // Inicialmente, o tronco começa mais à direita
float stem2_2Y = 0.30;
float stemSpeed2_2 = -0.036; // Velocidade do tronco

float stem3X = -1.2; // Inicialmente, o tronco começa mais à esquerda
float stem3Y = 0.45;
float stemSpeed3 = 0.016; // Velocidade do tronco

float stem3_2X = -2.4; // Inicialmente, o tronco começa mais à esquerda
float stem3_2Y = 0.45;
float stemSpeed3_2 = 0.016; // Velocidade do tronco

float stem4X = 1.2; // Inicialmente, o tronco começa mais à direita
float stem4Y = 0.60;
float stemSpeed4 = -0.018; // Velocidade do tronco

float stem4_2X = 2.4; // Inicialmente, o tronco começa mais à direita
float stem4_2Y = 0.60;
float stemSpeed4_2 = -0.018; // Velocidade do tronco

float stem5X = -1.2; // Inicialmente, o tronco começa mais à esquerda
float stem5Y = 0.75;
float stemSpeed5 = 0.016; // Velocidade do tronco

float stem5_2X = -2.4; // Inicialmente, o tronco começa mais à esquerda
float stem5_2Y = 0.75;
float stemSpeed5_2 = 0.016; // Velocidade do tronco

void menuHandler(int choice);


void createMenu() {
    glutCreateMenu(menuHandler);
    glutAddMenuEntry("Pause/Resume", 1);
    glutAddMenuEntry("Quit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void menuHandler(int choice) {
    switch (choice) {
        case 1: // Pause/Resume
            isPaused = !isPaused;
            break;
        case 2: // Quit
            exit(0);
            break;
    }
}

void drawPauseScreen() {
    // Desenhe um quadrado preto na tela inteira
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1.0, 1.0);
    glEnd();

    // Configurar a cor do texto
    glColor3f(1.0, 1.0, 1.0);

    // Posição do texto no centro da tela
    float textX = -0.3;
    float textY = 0.0;

    // Definir o tamanho da fonte
    void* font = GLUT_BITMAP_TIMES_ROMAN_24; // Pode ajustar o tamanho da fonte

    // Renderize o texto "Paused"
    char pauseText[] = "Paused";
    glRasterPos2f(textX, textY);
    for (int i = 0; pauseText[i] != '\0'; i++) {
        glutBitmapCharacter(font, pauseText[i]);
    }
}


// Função para desenhar o cenário
void drawScene() {
    // Desenhe a metade do cenário do rio (azul)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 0.0);   // Canto inferior esquerdo
    glVertex2f(1.0, 0.0);    // Canto inferior direito
    glVertex2f(1.0, 1.0);    // Canto superior direito
    glVertex2f(-1.0, 1.0);   // Canto superior esquerdo
    glEnd();

	// Desenhe a metade do cenário da estrada (preta)
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -1.0);  // Canto inferior esquerdo
    glVertex2f(1.0, -1.0);   // Canto inferior direito
    glVertex2f(1.0, 0.085);    // Canto superior direito
    glVertex2f(-1.0, 0.085);   // Canto superior esquerdo
    glEnd();
	
    // Desenha a grama (verde)
    glColor3f(0.4, 1.0, 0.4);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, 0.825);  // Canto inferior esquerdo
    glVertex2f(1.0, 0.825);   // Canto inferior direito
    glVertex2f(1.0, 1.0);    // Canto superior direito
    glVertex2f(-1.0, 1.0);   // Canto superior esquerdo
    glEnd();
}

// Função para desenhar o sapo
void drawFrog() {
    glColor3f(0.0, 1.0, 0.0); // Verde

    // Corpo do sapo (quadrado verde)
    glBegin(GL_POLYGON);
    glVertex2f(frogX - 0.04, frogY - 0.04);
    glVertex2f(frogX + 0.04, frogY - 0.04);
    glVertex2f(frogX + 0.04, frogY + 0.04);
    glVertex2f(frogX - 0.04, frogY + 0.04);
    glEnd();

    // Olhos do sapo (círculos pretos)
    glColor3f(0.0, 0.0, 0.0); // Preto
    float radius = 0.01;

    // Olho esquerdo
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159265 / 180;
        float x = frogX - 0.015 + radius * cos(angle);
        float y = frogY + 0.02 + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    // Olho direito
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159265 / 180;
        float x = frogX + 0.015 + radius * cos(angle);
        float y = frogY + 0.02 + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Função para mover o sapo
void moveFrog(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            if (frogX - stepSize > -1.059){
            	frogX -= stepSize - 0.12;  // Move para a esquerda
			}
				break;
        
		case GLUT_KEY_RIGHT:
            if (frogX + stepSize < 1.059){
            	frogX += stepSize - 0.12;  // Move para a direita
			}
				break;
        
		case GLUT_KEY_UP:
            if (frogY + stepSize < 1.0){
            	frogY += stepSize;  // Move para cima
			}
			
            break;
        
		case GLUT_KEY_DOWN:
            if (frogY - stepSize > -1.0)
				frogY -= stepSize;  // Move para baixo
            break;
    }

    glutPostRedisplay();  // Solicita uma nova renderização da cena
}


void drawCar(float carX, float carY, float cor[]) {
	
    glColor3f(cor[0], cor[1], cor[2]); // Define a cor do carro
    glBegin(GL_POLYGON);
    glVertex2f(carX - 0.05, carY - 0.02);
    glVertex2f(carX + 0.05, carY - 0.02);
    glVertex2f(carX + 0.05, carY + 0.02);
    glVertex2f(carX - 0.05, carY + 0.02);
    glEnd();
    
    // Desenhe as quatro rodas do carro (retângulos)
    glColor3f(1.0, 1.0, 0.0); // Define a cor das rodas
    
    // Roda 1 (superior esquerda)
    glBegin(GL_POLYGON);
    glVertex2f(carX - 0.045, carY + 0.022);
    glVertex2f(carX - 0.025, carY + 0.022);
    glVertex2f(carX - 0.025, carY + 0.035);
    glVertex2f(carX - 0.045, carY + 0.035);
    glEnd();
    
    // Roda 2 (superior direita)
    glBegin(GL_POLYGON);
    glVertex2f(carX + 0.045, carY + 0.022);
    glVertex2f(carX + 0.025, carY + 0.022);
    glVertex2f(carX + 0.025, carY + 0.035);
    glVertex2f(carX + 0.045, carY + 0.035);
    glEnd();
    
    // Roda 3 (inferior esquerda)
    glBegin(GL_POLYGON);
    glVertex2f(carX - 0.045, carY - 0.022);
    glVertex2f(carX - 0.025, carY - 0.022);
    glVertex2f(carX - 0.025, carY - 0.040);
    glVertex2f(carX - 0.045, carY - 0.040);
    glEnd();
    
    // Roda 4 (inferior direita)
    glBegin(GL_POLYGON);
    glVertex2f(carX + 0.045, carY - 0.022);
    glVertex2f(carX + 0.025, carY - 0.022);
    glVertex2f(carX + 0.025, carY - 0.040);
    glVertex2f(carX + 0.045, carY - 0.040);
    glEnd();
	
}

void drawStem(float stemX, float stemY){
	
	glColor3f(0.46f, 0.24f, 0.2f); // Define a cor do tronco
	glBegin(GL_POLYGON);
    glVertex2f(stemX - 0.18, stemY - 0.055);
    glVertex2f(stemX + 0.18, stemY - 0.055);
    glVertex2f(stemX + 0.18, stemY + 0.055);
    glVertex2f(stemX - 0.18, stemY + 0.055);
    glEnd();
    
}

void gameOver(){
	gameOverFlag = true;
}

void drawGameOverScreen() {
    // Desenhe um quadrado preto na tela inteira
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0, -1.0);
    glVertex2f(1.0, -1.0);
    glVertex2f(1.0, 1.0);
    glVertex2f(-1.0, 1.0);
    glEnd();

	// Configurar a cor do texto
    glColor3f(1.0, 1.0, 1.0);

    // Posição do texto no centro da tela
    float textX = -0.2;
    float textY = 0.0;

    // Definir o tamanho da fonte
    void* font = GLUT_BITMAP_TIMES_ROMAN_24; // Pode ajustar o tamanho da fonte

    // Renderize o texto "Game Over"
    char gameOverText[] = "Game Over";
    glRasterPos2f(textX, textY);
    for (int i = 0; gameOverText[i] != '\0'; i++) {
        glutBitmapCharacter(font, gameOverText[i]);
    } 
}

void colideCarGameOver(float carLeft, float carRight, float carTop, float carBottom){

	// Dimensões do sapo
    float frogLeft = frogX - 0.04;
    float frogRight = frogX + 0.04;
    float frogTop = frogY + 0.04;
    float frogBottom = frogY - 0.04;

	if (frogRight >= carLeft && frogLeft <= carRight && frogTop >= carBottom && frogBottom <= carTop) {
        gameOver();
    }
}

void indentifyColideCar() {

    // Carro 1
    float car1Left = carX - 0.05;
    float car1Right = carX + 0.05;
    float car1Top = carY + 0.02;
    float car1Bottom = carY - 0.02;

    // Carro 2
    float car2Left = car2X - 0.05;
    float car2Right = car2X + 0.05;
    float car2Top = car2Y + 0.02;
    float car2Bottom = car2Y - 0.02;

    // Carro 3
    float car3Left = car3X - 0.05;
    float car3Right = car3X + 0.05;
    float car3Top = car3Y + 0.02;
    float car3Bottom = car3Y - 0.02;

    // Carro 4
    float car4Left = car4X - 0.05;
    float car4Right = car4X + 0.05;
    float car4Top = car4Y + 0.02;
    float car4Bottom = car4Y - 0.02;

    // Carro 5
    float car5Left = car5X - 0.05;
    float car5Right = car5X + 0.05;
    float car5Top = car5Y + 0.02;
    float car5Bottom = car5Y - 0.02;
    
    // Carro 6
    float car6Left = car6X - 0.05;
    float car6Right = car6X + 0.05;
    float car6Top = car6Y + 0.02;
    float car6Bottom = car6Y - 0.02;

    // Verifique se houve uma colisão com cada carro
	colideCarGameOver(car1Left, car1Right, car1Top, car1Bottom);
	colideCarGameOver(car2Left, car2Right, car2Top, car2Bottom);
	colideCarGameOver(car3Left, car3Right, car3Top, car3Bottom);
	colideCarGameOver(car4Left, car4Right, car4Top, car4Bottom);
	colideCarGameOver(car5Left, car5Right, car5Top, car5Bottom);
	colideCarGameOver(car6Left, car6Right, car6Top, car6Bottom);
    
}

void isFrogOnRiver(){
	if(!frogOnRoad && !frogOnStem && !frogOnGrass){
		gameOver();
	}
}


bool isFrogOnStem(float stemLeft, float stemRight, float stemTop, float stemBottom, float stemSpeed){
	
	// Dimensões do sapo
    float frogLeft = frogX - 0.04;
    float frogRight = frogX + 0.04;
    float frogTop = frogY + 0.04;
    float frogBottom = frogY - 0.04;
    
	if(frogY >= 0.085 && frogY <= 0.825){
		// se estiver na parte azul
		frogOnRoad = false;
		
		if (frogRight >= stemLeft && frogLeft <= stemRight && frogTop >= stemBottom && frogBottom <= stemTop) {
	    	// sapo está no tronco		
			frogOnStem = true;
			frogX += stemSpeed;
		
			return true;
		} 
	
	} else{
		// sapo está na estrada
		frogOnRoad = true;
		frogOnStem = false;
		
		return false;
	}
}

bool indentifyColideStem(){
	
	// Dimensões do sapo
    float frogLeft = frogX - 0.04;
    float frogRight = frogX + 0.04;
    float frogTop = frogY + 0.04;
    float frogBottom = frogY - 0.04;

	// 	Dimensões dos troncos
	float stem1Left = stem1X - 0.18;
    float stem1Right = stem1X + 0.18;
    float stem1Top = stem1Y + 0.055;
    float stem1Bottom = stem1Y - 0.055;
    
    float stem1_2Left = stem1_2X - 0.18;
    float stem1_2Right = stem1_2X + 0.18;
    float stem1_2Top = stem1_2Y + 0.055;
    float stem1_2Bottom = stem1_2Y - 0.055;

	float stem2Left = stem2X - 0.18;
    float stem2Right = stem2X + 0.18;
    float stem2Top = stem2Y + 0.055;
    float stem2Bottom = stem2Y - 0.055;

	float stem2_2Left = stem2_2X - 0.18;
    float stem2_2Right = stem2_2X + 0.18;
    float stem2_2Top = stem2_2Y + 0.055;
    float stem2_2Bottom = stem2_2Y - 0.055;
    
    float stem3Left = stem3X - 0.18;
    float stem3Right = stem3X + 0.18;
    float stem3Top = stem3Y + 0.055;
    float stem3Bottom = stem3Y - 0.055;

	float stem3_2Left = stem3_2X - 0.18;
    float stem3_2Right = stem3_2X + 0.18;
    float stem3_2Top = stem3_2Y + 0.055;
    float stem3_2Bottom = stem3_2Y - 0.055;
    
    float stem4Left = stem4X - 0.18;
    float stem4Right = stem4X + 0.18;
    float stem4Top = stem4Y + 0.055;
    float stem4Bottom = stem4Y - 0.055;

	float stem4_2Left = stem4_2X - 0.18;
    float stem4_2Right = stem4_2X + 0.18;
    float stem4_2Top = stem4_2Y + 0.055;
    float stem4_2Bottom = stem4_2Y - 0.055;
    
    float stem5Left = stem5X - 0.18;
    float stem5Right = stem5X + 0.18;
    float stem5Top = stem5Y + 0.055;
    float stem5Bottom = stem5Y - 0.055;

	float stem5_2Left = stem5_2X - 0.18;
    float stem5_2Right = stem5_2X + 0.18;
    float stem5_2Top = stem5_2Y + 0.055;
    float stem5_2Bottom = stem5_2Y - 0.055;

	bool onStem1 = isFrogOnStem(stem1Left, stem1Right, stem1Top, stem1Bottom, stemSpeed1);
	bool onStem2 = isFrogOnStem(stem1_2Left, stem1_2Right, stem1_2Top, stem1_2Bottom, stemSpeed1_2);
	bool onStem3 = isFrogOnStem(stem2Left, stem2Right, stem2Top, stem2Bottom, stemSpeed2);
	bool onStem4 = isFrogOnStem(stem2_2Left, stem2_2Right, stem2_2Top, stem2_2Bottom, stemSpeed2_2);
	bool onStem5 = isFrogOnStem(stem3Left, stem3Right, stem3Top, stem3Bottom, stemSpeed3);
	bool onStem6 = isFrogOnStem(stem3_2Left, stem3_2Right, stem3_2Top, stem3_2Bottom, stemSpeed3_2);
	bool onStem7 = isFrogOnStem(stem4Left, stem4Right, stem4Top, stem4Bottom, stemSpeed4);
	bool onStem8 = isFrogOnStem(stem4_2Left, stem4_2Right, stem4_2Top, stem4_2Bottom, stemSpeed4_2);
	bool onStem9 = isFrogOnStem(stem5Left, stem5Right, stem5Top, stem5Bottom, stemSpeed5);
	bool onStem10 = isFrogOnStem(stem5_2Left, stem5_2Right, stem5_2Top, stem5_2Bottom, stemSpeed5_2);
	
	if (!onStem1 && !onStem2 && !onStem3 && !onStem4 && !onStem5 && !onStem6 && !onStem7 && !onStem8 && !onStem9 && !onStem10){
		frogOnStem = false;
		
	}
	
}

void isFrogOnGrass(){
	if(frogY > 0.825){
		frogOnGrass = true;
	} else {
		frogOnGrass = false;
	}
}

void increaseCarSpeed() {
    carSpeed += 0.003;
    carSpeed2 -= 0.003;
    carSpeed3 += 0.003;
    carSpeed4 -= 0.003;
    carSpeed5 += 0.003;
    carSpeed6 -= 0.003;
}

void scoreTrack(){
	if(frogOnGrass){
		// Aumenta a pontuação e dificulta o jogo
		score++;
		increaseCarSpeed();
		
		// retorna para a posição inicial	
		frogX = 0.0;
		frogY = -0.9;
	}
}

void drawScore(int score) {
    // Configurar a cor do texto
    glColor3f(1.0, 1.0, 1.0);

    // Posição do texto no centro da tela
    float textX = 0.72;
    float textY = -0.92;

    // Definir o tamanho da fonte
    void* font = GLUT_BITMAP_TIMES_ROMAN_24; // Pode ajustar o tamanho da fonte

    // Renderize o texto "Score: "
    char scoreText[] = "Score: ";
    glRasterPos2f(textX, textY);
    for (int i = 0; scoreText[i] != '\0'; i++) {
        glutBitmapCharacter(font, scoreText[i]);
    }

    // Converter o valor da variável score em uma string
    char scoreString[10]; // Ajuste o tamanho conforme necessário
    sprintf(scoreString, "%d", score);

    // Renderize a string do score
    textX += 0.18; // Ajuste manualmente a posição X para alinhar o score
    glRasterPos2f(textX, textY);
    for (int i = 0; scoreString[i] != '\0'; i++) {
        glutBitmapCharacter(font, scoreString[i]);
    }
}

void moveObjects(){
	carX += carSpeed;
	car2X += carSpeed2;
	car3X += carSpeed3;
	car4X += carSpeed2;
	car5X += carSpeed3;
	car6X += carSpeed2;
	stem1X += stemSpeed1;
	stem1_2X += stemSpeed1;
	stem2X += stemSpeed2;
	stem2_2X += stemSpeed2;
	stem3X += stemSpeed3;
	stem3_2X += stemSpeed3_2;
	stem4X += stemSpeed4;
	stem4_2X += stemSpeed4_2;
	stem5X += stemSpeed5;
	stem5_2X += stemSpeed5_2;
}

void resetObjects() {
    // Crie um array de estruturas para armazenar as informações dos carros e troncos
    struct ObjectInfo {
        float *position;
        float resetValue;
        bool moveRight;
    };

    struct ObjectInfo objects[] = {
        {&carX, -1.2, false},
        {&car2X, 1.2, true},
        {&car3X, -1.2, false},
        {&car4X, 1.2, true},
        {&car5X, -1.2, false},
        {&car6X, 1.2, true},
        {&stem1X, -1.2, false},
        {&stem1_2X, -1.2, false},
        {&stem2X, 1.2, true},
        {&stem2_2X, 1.2, true},
        {&stem3X, -1.2, false},
        {&stem3_2X, -1.2, false},
        {&stem4X, 1.2, true},
        {&stem4_2X, 1.2, true},
        {&stem5X, -1.2, false},
        {&stem5_2X, -1.2, false}
    };

    // Itere sobre o array 
    for (int i = 0; i < sizeof(objects) / sizeof(objects[0]); i++) {
        if (objects[i].moveRight) {
            if (*objects[i].position < -1.2) {
                *objects[i].position = 1.2;
            }
        } else {
            if (*objects[i].position > 1.2) {
                *objects[i].position = -1.2;
            }
        }
    }
}



// Função de temporização para movimento
void update(int value) {

	if(!isPaused){
		moveObjects();
		resetObjects();
		
		glutPostRedisplay();
	}
    
	glutTimerFunc(100, update, 0);
}

void debug(){
	
	printf("A posicao Y do sapo e: %f\n", frogY);
	printf("o sapo esta na estrada? %d\n", frogOnRoad);
	printf("o sapo esta no tronco? %d\n", frogOnStem);
	printf("o sapo esta na grama? %d\n\n\n\n\n\n", frogOnGrass);
	printf("a pontuacao e: %d", score);
	
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
	
	debug();
	
	if (isPaused) {
        drawPauseScreen();
	}
	else if (gameOverFlag) {
        drawGameOverScreen();
    } else {
    	drawScene(); // Desenhar o cenário
    
		drawCar(carX, carY, blue);
	    drawCar(car2X, car2Y, green);
	    drawCar(car3X, car3Y, red);
	    drawCar(car4X, car4Y, blue);
	    drawCar(car5X, car5Y, red);
	    drawCar(car6X, car6Y, green);
	
		drawStem(stem1X, stem1Y);
		drawStem(stem1_2X, stem1_2Y);
		drawStem(stem2X, stem2Y);
		drawStem(stem2_2X, stem2_2Y);
		drawStem(stem3X, stem3Y);
		drawStem(stem3_2X, stem3_2Y);
		drawStem(stem4X, stem4Y);
		drawStem(stem4_2X, stem4_2Y);
		drawStem(stem5X, stem5Y);
		drawStem(stem5_2X, stem5_2Y);
		
		drawFrog();  
		
		drawScore(score);
		
		indentifyColideCar();	
		indentifyColideStem();
		scoreTrack();
		isFrogOnGrass();	
		isFrogOnRiver();
		
	}
    	
    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Frogger Game");

	glutSpecialFunc(moveFrog);  
    glutDisplayFunc(display);

    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Inicie a função de temporização para o movimento dos objetos
    glutTimerFunc(100, update, 0);
	
	createMenu();  
	
    glutMainLoop();
    return 0;
}


