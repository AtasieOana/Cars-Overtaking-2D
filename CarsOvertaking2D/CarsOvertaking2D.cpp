
#include <windows.h>  // biblioteci care urmeaza sa fie incluse
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <GL/glew.h> // glew apare inainte de freeglut
#include <GL/freeglut.h> // nu trebuie uitat freeglut.h

#include "loadShaders.h"

#include "glm/glm/glm.hpp"  
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtx/transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "SOIL.h"

using namespace std;
//////////////////////////////////////
GLuint
VaoId,
VboId,
EboId,
ColorBufferId,
ProgramId,
myMatrixLocation,
matrRotlLocation,
codColLocation;

GLuint texture1, texture2, texture3, texture4,texture5;
int codCol;
int width = 400, height = 500;

glm::mat4 myMatrix, matriceScalare, matriceTranslatieDreptunghiDepasit, matriceTranslatieDreptunghiCareDepaseste,
matriceTranslatieDreptunghiuriFundal, matriceTranslatieDreptunghiInDepasire, matriceRotatieGirofar, translatieInOrigineGirofar, translatieInCentruGirofar,
matriceRotatieDepasire, translatieInOrigineDepasire, translatieInCentruDepasire, matriceTranslatieSemnalizare, translatieInCentruSemn, translatieInOrigineSemn;

float deplasareYDreptunghiDepasit = 0.0f;
float deplasareYDreptunghiCareDepaseste = 0.0f;
float deplasareYDreptunghiuriInFundal = 0.0f;
float valoareYMinDreptunghiDepasit = -500.0f;
float valoareYMaxDreptunghiDepasit = -360.0f;
float valoareYMinDreptunghiCareDepaseste = -1000.0f;
float valoareYMaxDreptunghiCareDepaseste = -860.0f;
float distantaDintreDreptunghiDepasitSiCareDepasesteInainte = 360.0f;
float distantaDintreDreptunghiDepasitSiCareDepasesteDupa = -640.0f;
float deplasareXInDepasire = 0.0f;
float valoareXGirofar = 230.0f;
float valoareYGirofar = -920.0f;
float unghiRotatieGirofar = 0;
float valoareXCentruDepasire = 230.0f;
float valoareYCentruDepasire = -930.0f;
float unghiRotatieDepasire = 0;
int mersUniform = 1;
float semnalizareX = 0;
float semnalizareY = 0;

// functie care creste valoarea variabilelor care vor fi folosite la translatia dreptunghiurilor
void deplasareDreptunghiuri() {

	deplasareYDreptunghiDepasit += 0.07f;
	deplasareYDreptunghiCareDepaseste += 0.15f; // se misca mai repede pentru a putea "depasi"
	deplasareYDreptunghiuriInFundal -= 0.07f;
	valoareYMinDreptunghiDepasit += 0.07f;
	valoareYMaxDreptunghiDepasit += 0.07f;
	valoareYMaxDreptunghiCareDepaseste += 0.15f;
	valoareYMinDreptunghiCareDepaseste += 0.15f;
	distantaDintreDreptunghiDepasitSiCareDepasesteInainte = valoareYMinDreptunghiDepasit - valoareYMaxDreptunghiCareDepaseste;
	distantaDintreDreptunghiDepasitSiCareDepasesteDupa = valoareYMinDreptunghiCareDepaseste - valoareYMaxDreptunghiDepasit;
	unghiRotatieGirofar += 0.05;
}

void CreateVBO(void)
{
    // varfurile + culori + coordonate de texturare
    GLfloat Vertices[] = {
		// varfurile pentru dreptunghiul ce formeaza strada
		-300.0f, -500.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		300.0f,  -500.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		300.0f, 500.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-300.0f, 500.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		// varfurile ce marcheaza mijlocul "strazii" 
		0.0f, 500.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.0f, -500.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		// varfurile ce marcheaza sensul "strazii" din stanga 
		-150.0f, 500.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	    -150.0f, 200.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-150.0f, 100.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-150.0f, -100.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-150.0f, -200.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-150.0f, -500.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		// varfurile ce marcheaza sensul "strazii" din dreapta 
		150.0f, 500.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		150.0f, 200.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	    150.0f, 100.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		150.0f, -100.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		150.0f, -200.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		150.0f, -500.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		// varfurile dreptunghiului care va fi "depasit"
		200.0f, -500.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		260.0f, -500.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		260.0f, -360.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		200.0f, -360.0f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		// varfurile dreptunghiului care "depaseste"
		// dreptunghiul care va "depasi" initial nu se vede in cadru
		200.0f, -1000.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		260.0f, -1000.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		260.0f, -860.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		200.0f, -860.0f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 
		// varfurile a doua dreptunghiuri de pe strada care doar se deplaseaza
		-260.0f, 360.0f,  0.0f, 1.0f, 0.5f, 0.7f, 0.0f, 0.0f, 0.0f,
		-200.0f, 360.0f,  0.0f, 1.0f, 0.5f, 0.7f, 0.0f, 1.0f, 0.0f,
		-200.0f, 500.0f,  0.0f, 1.0f, 0.5f, 0.7f, 0.0f, 1.0f, 1.0f,
		-260.0f, 500.0f,  0.0f, 1.0f, 0.5f, 0.7f, 0.0f, 0.0f, 1.0f,
		-100.0f, 360.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-40.0f, 360.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
		-40.0f, 500.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-100.0f, 500.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// varfurile "girofarului" dreptunghiului care depaseste
		220.0f, -930.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	    240.0f, -930.0f, 0.0f, 1.0f, 0.8f, 0.0f, 0.0f, 1.0f, 0.0f,
		240.0f, -910.0f, 0.0f, 1.0f, 0.6f, 0.0f, 0.0f, 1.0f, 1.0f,
		220.0f, -910.0f, 0.0f, 1.0f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f,
        // varfurile spatiul verde de pe marginea strazii
		-400.0f, -500.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-400.0f, 500.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 400.0f, -500.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 400.0f, 500.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 
		 // varfurile pentru plantele de pe margine
		-380.0f, 420.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-320.0f, 420.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	    -320.0f, 480.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-380.0f, 480.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
		-380.0f, 220.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-320.0f, 220.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-320.0f, 280.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-380.0f, 280.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-380.0f, 40.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-320.0f, 40.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-320.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-380.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-380.0f, -140.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-320.0f, -140.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-320.0f, -80.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-380.0f, -80.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-380.0f, -320.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-320.0f, -320.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-320.0f, -260.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-380.0f, -260.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-380.0f, -480.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-320.0f, -480.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-320.0f, -420.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-380.0f, -420.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		380.0f, 420.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		320.0f, 420.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	    320.0f, 480.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		380.0f, 480.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		380.0f, 220.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		320.0f, 220.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		320.0f, 280.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		380.0f, 280.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		380.0f, 40.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		320.0f, 40.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		320.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		380.0f, 100.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		380.0f, -140.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		320.0f, -140.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		320.0f, -80.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		380.0f, -80.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		380.0f, -320.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		320.0f, -320.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		320.0f, -260.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		380.0f, -260.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		380.0f, -480.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		320.0f, -480.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		320.0f, -420.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		380.0f, -420.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		// varfurile pentru semnalizare
		225.0f, -875.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.2f, 0.0f, 0.0f,
		235.0f, -875.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.8f, 1.0f, 0.0f,
		235.0f, -865.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.8f, 1.0f, 1.0f,
		225.0f, -865.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.8f, 0.0f, 1.0f,
};
	// indicii
	GLuint Indices[] = {
    0, 1, 2, 3,
	4, 5,
	6, 7, 8, 9, 10, 11,
	12, 13, 14, 15, 16, 17,
	18, 19, 20, 21,
	22, 23, 24, 25,
	26, 27, 28, 29,
	30, 31, 32, 33,
	34, 35, 36, 37,
	38, 0, 3, 39,
	1, 40, 41, 2,
	42, 43, 44, 45,
	46, 47, 48, 49,
	50, 51, 52, 53,
	54, 55, 56, 57, 
	58, 59, 60, 61,
	62, 63, 64, 65,
	66, 67, 68, 69,
	70, 71, 72, 73, 
	74, 75, 76, 77,
	78, 79, 80, 81,
	82, 83, 84, 85,
	86, 87, 88, 89,
	90, 91, 92, 93
	};

    // se creeaza un VAO (Vertex Array Object) 
    glGenVertexArrays(1, &VaoId);
    // se creeaza un buffer nou (atribute)
    glGenBuffers(1, &VboId);
	// se creeaza un buffer nou (indici)
	glGenBuffers(1, &EboId);

	// legarea VAO 
	glBindVertexArray(VaoId);

	// legarea buffer-ului "Array"
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	// punctele sunt "copiate" in bufferul curent
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	// legarea buffer-ului "Element" (indicii)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EboId);
	// indicii sunt "copiati" in bufferul curent
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    // se activeaza lucrul cu atribute
	// atributul 0 = pozitie
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);

    // atributul 1 = culoare
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));

    // atributul 2 = coordonate de texturare
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(7 * sizeof(GLfloat)));
}

void DestroyVBO(void)
{
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &VboId);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &VaoId);
}

void LoadTexture(void)
{
	int width, height;
	unsigned char* image;

	// prima textura
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	image = SOIL_load_image("Masina1.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);

	// a doua textura
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	image = SOIL_load_image("Masina2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	// a treia textura
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	image = SOIL_load_image("Masina3.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	// a patra textura
	glGenTextures(1, &texture4);
	glBindTexture(GL_TEXTURE_2D, texture4);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	image = SOIL_load_image("Masina4.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	// a cincea textura
	glGenTextures(1, &texture5);
	glBindTexture(GL_TEXTURE_2D, texture5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	image = SOIL_load_image("Planta.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CreateShaders(void)
{
    ProgramId = LoadShaders("Project_Shader.vert", "Project_Shader.frag");
    glUseProgram(ProgramId);
}
void DestroyShaders(void)
{
    glDeleteProgram(ProgramId);
}

void reluareDepasire() {
	valoareYMinDreptunghiDepasit = -500.0f;
	valoareYMaxDreptunghiDepasit = -360.0f;
	valoareYMinDreptunghiCareDepaseste = -1000.0f;
	valoareYMaxDreptunghiCareDepaseste = -860.0f;
	distantaDintreDreptunghiDepasitSiCareDepasesteInainte = 360.0f;
	distantaDintreDreptunghiDepasitSiCareDepasesteDupa = -640.0f;
	deplasareYDreptunghiDepasit = deplasareYDreptunghiCareDepaseste = deplasareYDreptunghiuriInFundal = 0.0f;
	deplasareXInDepasire = 0.0f;
	valoareXGirofar = 230.0f;
	valoareYGirofar = -920.0f;
	unghiRotatieGirofar = 0;
	unghiRotatieDepasire = 0;
	valoareXCentruDepasire = 230.0f;
	valoareYCentruDepasire = -930.0f;
	semnalizareX = 0;
	mersUniform = 1;
	semnalizareY = 0;
}

void Initialize(void)
{
	// creare varfuri si shadere
	CreateVBO();
	CreateShaders();
	// incarcam texturile pentru dreptunghiuri
 	LoadTexture();
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // culoarea de fond a ecranului
}
void RenderFunction(void)
{
	// scalam [-400,400]x[-500,500] in [-1,1]x[-1,1]
	// width = 400, height = 500
	matriceScalare = glm::scale(glm::mat4(1.0f), glm::vec3(1.f / width, 1.f / height, 1.0));
	// deplasarea pe axa OY prin translatie a dreptunghiului depasit
	matriceTranslatieDreptunghiDepasit = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, deplasareYDreptunghiDepasit, 0.0));
	//  deplasarea dreptunghiului care depaseste
	matriceTranslatieDreptunghiCareDepaseste = glm::translate(glm::mat4(1.0f), glm::vec3(deplasareXInDepasire, deplasareYDreptunghiCareDepaseste, 0.0));
	//  deplasarea pe axa OY prin translatie a dreptunghiurilor din fundal
	matriceTranslatieDreptunghiuriFundal = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, deplasareYDreptunghiuriInFundal, 0.0));
	// rotatia dreptunghiului care depaseste
	matriceRotatieDepasire = rotate(glm::mat4(1.0f), unghiRotatieDepasire, glm::vec3(0.0, 0.0, 1.0));
	// deoarece rotatia are loc in origine trebuie sa translatam centrul dreptunghiului in origine
	translatieInOrigineDepasire = glm::translate(glm::mat4(1.0f), glm::vec3(-valoareXCentruDepasire, -valoareYCentruDepasire, 0.0));
	// translatam inapoi in centrul dreptunghiului din origine
	translatieInCentruDepasire = glm::translate(glm::mat4(1.0f), glm::vec3(valoareXCentruDepasire, valoareYCentruDepasire, 0.0));
	// rotatia girofarului
	matriceRotatieGirofar = rotate(glm::mat4(1.0f), unghiRotatieGirofar, glm::vec3(0.0, 0.0, 1.0));
	// deoarece rotatia are loc in origine trebuie sa translatam centrul "girofarului" in origine
	translatieInOrigineGirofar = glm::translate(glm::mat4(1.0f), glm::vec3(-valoareXGirofar, -valoareYGirofar, 0.0));
	// translatam inapoi in centrul "girofarului" din origine
	translatieInCentruGirofar = glm::translate(glm::mat4(1.0f), glm::vec3(valoareXGirofar, valoareYGirofar, 0.0));
	// translatie pentru a muta dreptunghiul folosit pe post de semnalizare
	matriceTranslatieSemnalizare = glm::translate(glm::mat4(1.0f), glm::vec3(semnalizareX, 0.0, 0.0));
	// translatam in origine din centrul triunghiului pentru semnalizar
	translatieInOrigineSemn = glm::translate(glm::mat4(1.0f), glm::vec3(-230.0, 870.0, 0.0));
	// translatam inapoi in centrul triunghiului pentru semnalizare din origine
	translatieInCentruSemn = glm::translate(glm::mat4(1.0f), glm::vec3(230.0, -870.0, 0.0));
    
	glClear(GL_COLOR_BUFFER_BIT);

	// daca dreptunghiul care a fost depasit iese din ecran, se reinitializeaza varfurile si variabilele
	if (valoareYMinDreptunghiDepasit > 500.0f) {
		reluareDepasire();
	}

	codCol = 0;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);

	myMatrix = matriceScalare;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// desenam "strada"
	glLineWidth(6.0);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, (GLvoid*)(2 * sizeof(GLfloat)));
	glLineWidth(2.0);
	glDrawElements(GL_LINES, 12, GL_UNSIGNED_INT, (GLvoid*)(6 * sizeof(GLfloat)));

	codCol = 2;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);

	// desenam spatiul verde de pe marginea strazii
	glDrawElements(GL_QUADS, 8, GL_UNSIGNED_INT, (GLvoid*)(38 * sizeof(GLfloat)));

	codCol = 1;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);

	myMatrix = matriceScalare;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// textura pentru plante
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture5);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	// plantele de pe spatiul verde 
	glDrawElements(GL_QUADS, 48, GL_UNSIGNED_INT, (GLvoid*)(46 * sizeof(GLfloat)));

	////////

	// textura pentru dreptunghiul depasit
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	// matricea pentru dreptunghiul depasit
	myMatrix = matriceScalare * matriceTranslatieDreptunghiDepasit;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// desenam dreptunghiul depasit
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (GLvoid*)(18 * sizeof(GLfloat)));

	mersUniform = 1;
	semnalizareX = 0.0f;

	// daca distanta pe OY dintre latura de jos a dreptunghiului depasit si latura de sus a dreptunghiului care depaseste
    // este mai mica decat 100 atunci va incepe depasirea 
	// deplasarea pe OX va dura pana cand aceasta distanta va ajunge sa fie mai mica decat 0
	if (distantaDintreDreptunghiDepasitSiCareDepasesteInainte <= 100.0f && distantaDintreDreptunghiDepasitSiCareDepasesteInainte > 0.0f) {
		deplasareXInDepasire -= 0.12f;
		unghiRotatieDepasire = 0.2f;
		mersUniform = 0;
		semnalizareX = -25.0f;
	}
	else {
		if (distantaDintreDreptunghiDepasitSiCareDepasesteInainte > 100.0f && distantaDintreDreptunghiDepasitSiCareDepasesteInainte <= 125.0f) {
			semnalizareX = -18.0f;
		}
	}

	// daca distanta pe OY dintre latura de jos a dreptunghiului care depaseste si latura de sus a dreptunghiului depasit
	// este pozitiva atunci dreptunghiul poate reinta pe prima banda
	// deplasarea pe OX va dura pana cand dreptunghiul va ajunge pe aceasi valoare pe OX din care a plecat
	if (distantaDintreDreptunghiDepasitSiCareDepasesteDupa >= 0.0f && deplasareXInDepasire <= 0.0f) {
		deplasareXInDepasire += 0.12f;
		unghiRotatieDepasire = -0.2f;
		mersUniform = 0;
		semnalizareX = 25.0f;
	}
	else {
		if (distantaDintreDreptunghiDepasitSiCareDepasesteDupa >= -25.0f && distantaDintreDreptunghiDepasitSiCareDepasesteDupa < 0.0f) {
			semnalizareX = 18.0f;
		}
	}

	if (mersUniform == 1) {
		unghiRotatieDepasire = 0.0;
	}

	// textura pentru dreptunghiul care depaseste
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	// matricea pentru dreptunghiul care depaseste
	myMatrix = matriceScalare * matriceTranslatieDreptunghiCareDepaseste*translatieInCentruDepasire*
		       matriceRotatieDepasire*translatieInOrigineDepasire;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// desenam dreptunghiul care depaseste
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (GLvoid*)(22 * sizeof(GLfloat)));


	// matricea pentru dreptunghiurile din fundal
	myMatrix = matriceScalare * matriceTranslatieDreptunghiuriFundal;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// 	textura pentru dreptunghiul din fundal 1
	glBindTexture(GL_TEXTURE_2D, texture3);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	// desenam dreptunghiul din fundal 1
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (GLvoid*)(26 * sizeof(GLfloat)));

	// 	textura pentru dreptunghiul din fundal 2
	glBindTexture(GL_TEXTURE_2D, texture4);
	glUniform1i(glGetUniformLocation(ProgramId, "myTexture"), 0);

	// desenam dreptunghiul din fundal 2
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (GLvoid*)(30 * sizeof(GLfloat)));

	////////
	codCol = 0;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	glUniform1i(codColLocation, codCol);

	// matricea pentru girofarul masinii care depaseste
	myMatrix = matriceScalare * matriceTranslatieDreptunghiCareDepaseste*translatieInCentruGirofar*matriceRotatieGirofar*
		       translatieInOrigineGirofar;
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	// desenam girofarul masinii care depaseste
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (GLvoid*)(34 * sizeof(GLfloat)));

	if (semnalizareX != 0.0f){
		// matricea pentru semnalizare
		myMatrix = matriceScalare * matriceTranslatieDreptunghiCareDepaseste*matriceTranslatieSemnalizare*translatieInCentruSemn*
			matriceRotatieDepasire* translatieInOrigineSemn;;
		myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
		glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

		// desenam semnalizarea masinii care depaseste
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, (GLvoid*)(94 * sizeof(GLfloat)));
	}

	// modificam variabilele pentru translatie
	deplasareDreptunghiuri();

    glutSwapBuffers();
    glFlush();
}

void Cleanup(void)
{
    DestroyShaders();
    DestroyVBO();
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(200, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Atasie Oana-Andreea - Depasire 2D");
    glewInit();
    Initialize();
    glutDisplayFunc(RenderFunction);
    glutIdleFunc(RenderFunction);
    glutCloseFunc(Cleanup);
    glutMainLoop();
}

