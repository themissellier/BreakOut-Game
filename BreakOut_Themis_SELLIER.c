// BREAKOUT , Themis SELLIER 4A-AVM

//  BIBLIOTHEQUES -----------------------------------------------
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// DEFINITION DES STRUCTURES --------------------------------
typedef struct {
    //Coordonnées en OpenGL
    double x; //position en x
    double y; //position en y
} Pos;

typedef struct {
    //Coordonnées dans le système RGB pour les couleurs
    double r; //rouge
    double g; //vert
    double b; //bleu
}RGB;

typedef struct {
    Pos pos; //Position du coin supérieur gauche
    int valeur; // 0, 1, 3, 5 ou 7 selon les points donnés au joueur lorsque la brique est détruite
    RGB rgb; // couleur de ces briques
    int is_display; //0 si la brique n'est pas affichée
}Brique;

typedef struct {
    Pos pos; //position de l'objet
    double w; //largeur de l'objet
    double speed; //vitesse linéaire de l'objet
}ObjetMouvant;

typedef struct {
    ObjetMouvant obj;
    int index; //index de la brique à laquelle le bonus/malus est attribue
    int move; //1 si l'objet bouge, 0 sinon
    RGB rgb; //Pour la couleur des bonus/malus
} Bonus;

typedef struct {
    double x; //position en x en OpenGL
    double y; //position en y en OpenGL
    int pageActuelle; //numero de la page affichee
} Mouse;

typedef struct {
    Pos pos;
    Pos v; // vitesse de déplacement (vx,vy)
    RGB rgb; //Couleur rgb de la balle
    double radius; // rayon de la balle
    int nbBalles; //nombre de vies restantes (nombre de balles restantes)
    int move; // 1 si la balle se deplace, 0 sinon
    int nbEcrans; //Nombre d'écrans nettoyés en entier par le joueur
} Balle;

//  VARIABLES GLOBALES --------------------------------------
const int false=0;
const int true=1;
int sizeWin_x=656;
int sizeWin_y=800;
Mouse mouse = {-2, -2, 0};
ObjetMouvant raquette = {{0,-0.85}, 0.07, 0.1};
Balle balle = {{0,0},{0,0},{0,0,0},0,3,0,0};
int score = 0;


//  SCORE ----------------------------------------------------
void draw0(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y+heightWriting); // Start point of the line
    glVertex2f(pos.x-heightWriting/2, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x-heightWriting/2, pos.y+heightWriting); // Start point of the line
    glVertex2f(pos.x-heightWriting/2, pos.y);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x-heightWriting/2, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y);  // End point of the line
    glEnd();
}

void draw1(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
}

void draw2(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y + heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y + heightWriting/2); // Start point of the line
    glVertex2f(pos.x, pos.y + heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y + heightWriting/2); // Start point of the line
    glVertex2f(pos.x, pos.y + heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y + heightWriting); // Start point of the line
    glVertex2f(pos.x- heightWriting/2, pos.y + heightWriting);  // End point of the line
    glEnd();
}

void draw3(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y + heightWriting/2); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y + heightWriting); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting);  // End point of the line
    glEnd();
}

void draw4(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y + heightWriting/2); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting/2); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting);  // End point of the line
    glEnd();
}

void draw5(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y + heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y + heightWriting/2); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y + heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y + heightWriting/2); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y + heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y + heightWriting); // Start point of the line
    glVertex2f(pos.x, pos.y + heightWriting);  // End point of the line
    glEnd();
}

void draw6(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y+heightWriting/2); // Start point of the line
    glVertex2f(pos.x- heightWriting/2, pos.y+heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x- heightWriting/2, pos.y);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x- heightWriting/2, pos.y); // Start point of the line
    glVertex2f(pos.x- heightWriting/2, pos.y + heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x- heightWriting/2, pos.y + heightWriting); // Start point of the line
    glVertex2f(pos.x, pos.y + heightWriting);  // End point of the line
    glEnd();
}

void draw7(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y+heightWriting); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting);  // End point of the line
    glEnd();
}

void draw8(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y+heightWriting); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting/2); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting/2);  // End point of the line
    glEnd();
}

void draw9(Pos pos, int widthWriting, double heightWriting)
{
    glLineWidth(widthWriting);

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x, pos.y+heightWriting); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting); // Start point of the line
    glVertex2f(pos.x - heightWriting/2, pos.y + heightWriting/2);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(pos.x - heightWriting/2, pos.y+heightWriting/2); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting/2);  // End point of the line
    glEnd();
}

void draw_chiffre(int chf, Pos pos, int widthWriting, double heightWriting)
{
    if (chf == 0){
        draw0(pos, widthWriting, heightWriting);
    }
    else {
        if (chf == 1){
            draw1(pos, widthWriting, heightWriting);
        }
        else {
            if (chf == 2){
                draw2(pos, widthWriting, heightWriting);
            }
            else {
                if (chf == 3){
                    draw3(pos, widthWriting, heightWriting);
                }
                else {
                    if (chf == 4){
                        draw4(pos, widthWriting, heightWriting);
                    }
                    else {
                        if (chf == 5){
                            draw5(pos, widthWriting, heightWriting);
                        }
                        else {
                            if (chf == 6){
                                draw6(pos, widthWriting, heightWriting);
                            }
                            else {
                                if (chf == 7){
                                    draw7(pos, widthWriting, heightWriting);
                                }
                                else {
                                    if (chf == 8){
                                        draw8(pos, widthWriting, heightWriting);
                                    }
                                    else {
                                        draw9(pos, widthWriting, heightWriting);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void draw_number(Pos pos, int nb)
{
    if(nb>999 || nb<0){
        printf("Nombre non valide pour ecriture\n");
    }
    else{
        int temp;
        for (int i = 0; i<3; i++){
            temp = nb%10;
            nb = (nb - temp)/10;
            draw_chiffre(temp, pos, 5, 0.1);
            pos.x = pos.x - 0.1;
        }
    }
}


//  TEXTE ---------------------------------------------------------------------
void drawA(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //A
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);  // End point of the line
    glVertex2f(pos.x+heightWriting/4 - heightWriting/8, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y);  // End point of the line
    glVertex2f(pos.x+heightWriting/4 + heightWriting/8, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/4 - heightWriting/8, pos.y+heightWriting);  // End point of the line
    glVertex2f(pos.x+heightWriting/4 + heightWriting/8, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting*1/16, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x + heightWriting*7/16, pos.y+heightWriting/2); // Start point of the line
    glEnd();
}

void drawB(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);

    //B
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glVertex2f(pos.x+heightWriting/2-heightWriting/10, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2-heightWriting/10, pos.y+heightWriting);  // End point of the line
    glVertex2f(pos.x+heightWriting/2-heightWriting/10, pos.y+heightWriting/2); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x, pos.y+heightWriting/2); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y);  // End point of the line
    glVertex2f(pos.x, pos.y); // Start point of the line
    glEnd();
}

void drawC(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //C
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x+heightWriting/2, pos.y);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting);
    glEnd();
}

void drawE(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //E
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);  // End point of the line
    glVertex2f(pos.x, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x+heightWriting/2- heightWriting/8, pos.y+heightWriting/2); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y); // Start point of the line
    glEnd();
}

void drawG(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //G
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting/2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting/2);
    glVertex2f(pos.x+heightWriting/4, pos.y+heightWriting/2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();
}

void drawK(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //K
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting/2);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting/2+heightWriting/8);
    glVertex2f(pos.x + heightWriting/2, pos.y);
    glEnd();
}

void drawL(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //P
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);  // End point of the line
    glVertex2f(pos.x, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y); // Start point of the line
    glEnd();
}

void drawM(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //M
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);
    glVertex2f(pos.x+heightWriting/4, pos.y+heightWriting/2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/4, pos.y+heightWriting/2);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();
}

void drawO(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //O
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();

}

void drawP(Pos pos , int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //P
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);  // End point of the line
    glVertex2f(pos.x, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting/2); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x, pos.y+heightWriting/2); // Start point of the line
    glEnd();
}

void drawR(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //R
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y); // Start point of the line
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting/2); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x, pos.y+heightWriting/2); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2 - heightWriting/8, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y); // Start point of the line
    glEnd();
}

void drawS(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //S
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x+heightWriting/2, pos.y);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting/2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting/2);
    glVertex2f(pos.x, pos.y+heightWriting/2);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting/2);
    glVertex2f(pos.x, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting);
    glEnd();
}

void drawT(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //T
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/4, pos.y);
    glVertex2f(pos.x+heightWriting/4, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();
}

void drawU(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //U
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/2, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y);
    glEnd();
}

void drawV(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //V
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y+heightWriting);
    glVertex2f(pos.x+heightWriting/4, pos.y);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/4, pos.y);
    glVertex2f(pos.x + heightWriting/2, pos.y+heightWriting);
    glEnd();
}

void drawY(Pos pos, int widthWriting, double heightWriting, RGB rgb)
{
    glLineWidth(widthWriting);
    //Y
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/4, pos.y);  // End point of the line
    glVertex2f(pos.x+heightWriting/4, pos.y+heightWriting/2); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/4, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x, pos.y+heightWriting); // Start point of the line
    glEnd();
    glBegin(GL_LINES);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x+heightWriting/4, pos.y+heightWriting/2);  // End point of the line
    glVertex2f(pos.x+heightWriting/2, pos.y+heightWriting); // Start point of the line
    glEnd();
}

void draw_title(Pos pos, int widthWriting, double heightWriting)
{
    RGB rgb = {1, 1, 1};
    drawB(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawR(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawE(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawA(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawK(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawO(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawU(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawT(pos, widthWriting, heightWriting, rgb);
}

void draw_play(Pos pos, int widthWriting, double heightWriting)
{
    RGB rgb = {0, 0, 0};
    drawP(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawL(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawA(pos, widthWriting, heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawY(pos, widthWriting, heightWriting, rgb);
}

void draw_game_over(Pos pos, int widthWriting, double heightWriting)
{
    RGB rgb = {1, 0, 0};
    drawG(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawA(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawM(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawE(pos,widthWriting,heightWriting, rgb);

    pos.x += 2*(heightWriting*4/5);

    drawO(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawV(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawE(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawR(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
}

void draw_score(Pos pos, int widthWriting, double heightWriting)
{
    RGB rgb = {1, 1, 1};
    drawS(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawC(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawO(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawR(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawE(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;

    glLineWidth(widthWriting);
    glBegin( GL_POINTS);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    glVertex2f(pos.x, pos.y +heightWriting/2);
    glEnd();
}

void draw_restart(Pos pos, int widthWriting, double heightWriting)
{
    RGB rgb = {0, 0, 0};
    drawR(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawE(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawS(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawT(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawA(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawR(pos,widthWriting,heightWriting, rgb);
    pos.x += heightWriting*4/5;
    drawT(pos,widthWriting,heightWriting, rgb);
}


//  ELEMENTS GRAPHIQUES ECRAN DE JEU --------------------------------------------------------
void bouton_croix()
{
    //Bouton quitter la partie
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(0.8, 0.85); // Coin inférieur gauche
    glVertex2f(0.9, 0.85);  // Coin inférieur droit
    glVertex2f(0.9, 0.95);   // Coin supérieur droit
    glVertex2f(0.8, 0.95);  // Coin supérieur gauche
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(0.8, 0.85);
    glVertex2f(0.9, 0.85);
    glVertex2f(0.9, 0.85);
    glVertex2f(0.9, 0.95);
    glVertex2f(0.9, 0.95);
    glVertex2f(0.8, 0.95);
    glVertex2f(0.8, 0.95);
    glVertex2f(0.8, 0.85);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(0.81, 0.94);
    glVertex2f(0.89, 0.86);
    glVertex2f(0.81, 0.86);
    glVertex2f(0.89, 0.94);
    glEnd();
}

void delimitations_terrain()
{
    glColor3f(0.5,0.5,0.5);

    //Barre horizontale haut de terrain
    glBegin(GL_QUADS);
    glVertex2f(-1, 0.75); // Coin inférieur gauche
    glVertex2f(1, 0.75);  // Coin inférieur droit
    glVertex2f(1, 0.8);   // Coin supérieur droit
    glVertex2f(-1, 0.8);  // Coin supérieur gauche
    glEnd();

    //Barre verticale gauche
    glBegin(GL_QUADS);
    glVertex2f(-1, 1); // Coin inférieur gauche
    glVertex2f(-0.97, 1);  // Coin inférieur droit
    glVertex2f(-0.97, -1);   // Coin supérieur droit
    glVertex2f(-1, -1);  // Coin supérieur gauche
    glEnd();

    //Barre verticale droite
    glBegin(GL_QUADS);
    glVertex2f(0.97, 1); // Coin inférieur gauche
    glVertex2f(1, 1);  // Coin inférieur droit
    glVertex2f(1, -1);   // Coin supérieur droit
    glVertex2f(0.97, -1);  // Coin supérieur gauche
    glEnd();
}

void draw_raquette()
{
    glBegin(GL_QUADS);
    glColor3f(0,0.72,1); //couleur bleue
    glVertex2f(raquette.pos.x -raquette.w, raquette.pos.y + 0.02); // Coin inférieur gauche
    glVertex2f(raquette.pos.x +raquette.w, raquette.pos.y + 0.02);  // Coin inférieur droit
    glVertex2f(raquette.pos.x +raquette.w, raquette.pos.y - 0.02);   // Coin supérieur droit
    glVertex2f(raquette.pos.x -raquette.w, raquette.pos.y - 0.02);  // Coin supérieur gauche
    glEnd();
}

void drawCircle(Pos pos, double radius, RGB rgb)
{
    int nbSegments = 100;
    glBegin(GL_LINE_LOOP);
    glColor3f(rgb.r, rgb.g, rgb.b);
    for (int i = 0; i < nbSegments; i++) {
        double angle = 2.0 * 3.1415 * (double)i / (double)nbSegments; // Angle in radians
        double x = radius * cos(angle); // Calculate the x component
        double y = radius * sin(angle); // Calculate the y component

        glVertex2f(x + pos.x, y + pos.y); // Output vertex
    }
    glEnd();
}

void drawDisc(Pos pos, double radius, RGB rgb)
{
    int nbSegments = 100;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(rgb.r, rgb.g, rgb.b);
    glVertex2f(pos.x, pos.y);
    for (int i = 0; i < nbSegments+1; i++) {
        double angle = 2.0 * 3.1415 * (double)i / (double)nbSegments; // Angle in radians
        double x = radius * cos(angle); // Calculate the x component
        double y = radius * sin(angle); // Calculate the y component

        // Outputs
        glVertex2f(x + pos.x, y + pos.y);
    }
    glEnd();
}


//  BRIQUES -------------------------------------------------------------------
void init_briques(Brique* briques, int nbBriques)
{
    //Les briques sont entrees dans le tableau dans l'ordre de lecture (de gauche a droite et de haut en bas)
    int point = 7;
    for (int i= 0; i<nbBriques; i++){
        if (i%28==0 && i!=0){point -= 2;} // pour les couleurs
        briques[i].pos.x = -1 + 0.03 + ((i%14)+1)*6.4/(656.0) + (i%14)*42.0/656.0 * 2; //position calculée en fonction de la position de la brique dans le tableau de briques et la largeur initiale de la fenêtre
        briques[i].pos.y = 0.74 + (int)i/14*(-0.04); //toutes les 14 briques, on change de ligne
        briques[i].valeur = point; //affectation de la valeur de la brique
        //chois de la couleur rgb de la brique en fonction de sa valeur attribuée precedemment
        if(point == 1){
            briques[i].rgb.r = 0.95;
            briques[i].rgb.g = 0.9;
            briques[i].rgb.b = 0;
        }
        else if (point == 3){
            briques[i].rgb.r = 0;
            briques[i].rgb.g = 1;
            briques[i].rgb.b = 0;
        }
        else if (point == 5){
            briques[i].rgb.r = 1;
            briques[i].rgb.g = 0.5;
            briques[i].rgb.b = 0;
        }
        else if (point == 7){
            briques[i].rgb.r = 1;
            briques[i].rgb.g = 0;
            briques[i].rgb.b = 0;
        }
        // à l'initialisation, toutes les briques sont affichées
        briques [i].is_display = true;
    }
}

void draw_brique(Brique brique)
{
    if (brique.is_display>=1){
        // Dessiner un rectangle plein
        glBegin(GL_QUADS); // Utilise des quadrilatères
        glColor3f(brique.rgb.r, brique.rgb.g, brique.rgb.b);
        glVertex2f(brique.pos.x, brique.pos.y - 0.03); // Coin inférieur gauche
        glVertex2f(brique.pos.x + 42.0/656.0 * 2, brique.pos.y - 0.03);  // Coin inférieur droit
        glVertex2f(brique.pos.x + 42.0/656.0 * 2, brique.pos.y);   // Coin supérieur droit
        glVertex2f(brique.pos.x, brique.pos.y);  // Coin supérieur gauche
        glEnd();
        if(brique.is_display>1){
            Pos position = {brique.pos.x + 42.0/656.0, brique.pos.y - 0.025};
            draw_chiffre(brique.is_display, position, 1, 0.02);
        }
    }
}

void draw_briques(Brique* briques, int nbBriques)
{
    //dessin de chaque brique du tableau de briques
    for (int i=0; i<nbBriques; i++){
        draw_brique(briques[i]);
    }
}

void hidden_briques(Brique* briques, int nbBriques)
{
    //compte le nombre de briques cachées après avoir été en collision avec la balle
    int cpt = 0;
    int cpt_mur = 0;
    int cpt_orange = 0; //5 points
    int cpt_rouge = 0; // 7 points
    for (int i=0; i<nbBriques; i++){
        if(briques[i].valeur == 0){
            cpt_mur += 1;
        }
        if(briques[i].is_display == 0){
            cpt += 1;
            if(briques[i].valeur==5){
                cpt_orange +=1;
            }
            else if(briques[i].valeur == 7){
                cpt_rouge += 1;
            }
        }
    }
    if(cpt==4 || cpt==12){
        balle.v.x = 1.19*balle.v.x;
        balle.v.y = 1.19*balle.v.y;
    }
    if(cpt_orange==1 || cpt_rouge==1){
        balle.v.x *=1.19;
        balle.v.y *=1.19;
    }
    //si l ecran est nettoyé entierement
    if(cpt+cpt_mur == 112){
        init_briques(briques, nbBriques);
        balle.nbEcrans +=1;
        init_balle();
        if(balle.nbEcrans>2){mouse.pageActuelle = 2;}//le joueur a fini la partie et gagne
    }
}

void init_briques_murs(Brique* briques)
{
    //deux briques murs (grises) aux extremites de la rangee jaune inferieure
    //brique de gauche
    briques[14*7].rgb.r = 0.5;
    briques[14*7].rgb.g = 0.5;
    briques[14*7].rgb.b = 0.5;
    briques[14*7].valeur = 0;
    //brique de droite
    briques[14*8-1].rgb.r = 0.5;
    briques[14*8-1].rgb.g = 0.5;
    briques[14*8-1].rgb.b = 0.5;
    briques[14*8-1].valeur = 0;


    //deux briques retroreflectives (blanches) a trois briques de distance des extremites de la rangee verte superieure
    //brique de gauche
    briques[59].rgb.r = 1;
    briques[59].rgb.g = 1;
    briques[59].rgb.b = 1;
    briques[59].valeur = 0;
    //brique de droite
    briques[66].rgb.r = 1;
    briques[66].rgb.g = 1;
    briques[66].rgb.b = 1;
    briques[66].valeur = 0;
}

void init_briques_compteurs(Brique* briques)
{
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            int temp = 33+i*14+j;
            if(temp == 48||temp == 49 || temp == 62 || temp == 63){
                briques[temp].is_display = 4;
            }
            else {
                briques[temp].is_display = 2;
            }
        }
    }
}

void init_bonus(Bonus* tabBonus, Brique* briques, int nbBriques)
{
    srand(time(NULL));
    for (int i = 0; i<8; i++){
        int sameIndex = true;
        tabBonus[i].index= 0;

        //si il y a deja un bonus sur la brique ou si la brique est une brique mur, on change d'index pour le bonus
        while(sameIndex==true || briques[tabBonus[i].index].valeur == 0){

            tabBonus[i].index= ((double)rand() / RAND_MAX)*8*14;
            sameIndex = false;

            for(int j = 0; j<i; j++){
                if(tabBonus[i].index==tabBonus[j].index){
                    sameIndex = true;
                }
            }

        }
        tabBonus[i].move=0;
        tabBonus[i].obj.speed = 0.5/50.0;
        tabBonus[i].obj.w = 0.015;
        //placement du bonus au milieu de la brique
        tabBonus[i].obj.pos.x = briques[tabBonus[i].index].pos.x +42.0/656.0;
        tabBonus[i].obj.pos.y = briques[tabBonus[i].index].pos.y + 0.015;
    }

    //Initialisation des couleurs des bonus/malus
    tabBonus[0].rgb.r = 1;
    tabBonus[0].rgb.g = 0.5;
    tabBonus[0].rgb.b = 0;

    tabBonus[1].rgb.r = 1;
    tabBonus[1].rgb.g = 0;
    tabBonus[1].rgb.b = 0;

    tabBonus[2].rgb.r = 0.95;
    tabBonus[2].rgb.g = 0.9;
    tabBonus[2].rgb.b = 0;

    tabBonus[3].rgb.r = 0;
    tabBonus[3].rgb.g = 1;
    tabBonus[3].rgb.b = 0;

    tabBonus[4].rgb.r = 0;
    tabBonus[4].rgb.g = 1;
    tabBonus[4].rgb.b = 1;

    tabBonus[5].rgb.r = 0;
    tabBonus[5].rgb.g = 0.4;
    tabBonus[5].rgb.b = 1;

    tabBonus[6].rgb.r = 1;
    tabBonus[6].rgb.g = 1;
    tabBonus[6].rgb.b = 1;

    tabBonus[7].rgb.r = 0.5;
    tabBonus[7].rgb.g = 0.5;
    tabBonus[7].rgb.b = 0.5;
}

void init_briques_spe(Brique*briques, int nbBriques, Bonus* tabBonus)
{
        //initialisation de toutes les briques speciales
        init_briques_compteurs(briques);
        init_briques_murs(briques);
        init_bonus(tabBonus, briques, nbBriques);
}


//  BALLE ---------------------------------------------------------------------
void init_balle()
{
    balle.radius = 0.02;
    balle.pos.x = 0;
    balle.pos.y = -0.82 + balle.radius;
    balle.rgb.r = 1;
    balle.rgb.g = 1;
    balle.rgb.b = 1;
    if(balle.nbEcrans>1){
        balle.v.x = (0.5-balle.pos.y)/4.0/25.0 * 2; //si un ecran a deja ete nettoyé en entier
    }
    else {
        balle.v.x = (0.5-balle.pos.y)/4.0/25.0; //distance/temps en secondes * images par seconde
    }
    balle.v.y = fabs(balle.v.x);
    balle.move = 0; //balle immobile quand elle vient d etre initialisee
}

double norme_vitesse()
{
    //calcule la norme du vecteur vitesse de la balle
    double d = sqrt(balle.v.x*balle.v.x + balle.v.y*balle.v.y);
    return d;
}

int collision_ball_brique(Brique* briques, int nbBriques)
{
    // verifie s'il y a collision entre la balle et une brique et gere le score et le parametre d'affichage des briques
    for (int i= 0; i<nbBriques; i++){
            if(briques[i].is_display>=1){
                if(((briques[i].pos.y-0.03<=balle.pos.y+balle.radius && briques[i].pos.y>=balle.pos.y+balle.radius && balle.v.y>=0) ||
                    (briques[i].pos.y>=balle.pos.y-balle.radius && briques[i].pos.y-0.03<=balle.pos.y-0.03 && balle.v.y<=0)) &&
                    briques[i].pos.x<=balle.pos.x && briques[i].pos.x+ 42.0/656.0 * 2>=balle.pos.x){
                    //si les briques sont indestructibles
                    if(briques[i].valeur == 0){
                        if(briques[i].rgb.r==1 && briques[i].rgb.g==1 && briques[i].rgb.b==1){
                            balle.v.x = -balle.v.x;
                       }
                    }
                    //sinon
                    else{
                        briques[i].is_display = briques[i].is_display - 1;
                        if(briques[i].is_display <1){
                            score = score + briques[i].valeur; //ajout de la valeur de la brique detruite au score
                        }
                        hidden_briques(briques,nbBriques);//appele seulement si une brique est detruite pour compter le nombre de briques detruites
                    }
                    return 1;
                }
            }
    }
    return 0;
}

void update_balle(Brique* briques, int nbBriques)
{
    if(balle.move==1){
        //mise à jour de la position de la balle en fonction de sa vitesse
        balle.pos.x += balle.v.x;
        balle.pos.y += balle.v.y;
        double d = norme_vitesse();

        //rebond sur les bords droit et gauche
        if(balle.pos.x - balle.radius<= -0.97 || balle.pos.x+balle.radius>=0.97){
            balle.v.x = -balle.v.x;
        }
        //Rebond sur le haut du terrain
        if(balle.pos.y+balle.radius >= 0.75){
            balle.v.y = -balle.v.y;
            raquette.w = 42.0/656.0; //malus appliqué sur la raquette (taille d'une brique) a l'impact avec le haut du terrain
        }
        if(balle.pos.y< -1.3){ //On prend la position -1.3 pour le confort visuel
            balle.nbBalles -= 1;
            if(balle.nbBalles>=1){
                init_balle();//initialisation de la balle s'il reste des vies
            }
        }
        else {
            //si la balle touche la raquette sur la zone centrale
            if(balle.pos.y-balle.radius <= raquette.pos.y+0.02 && balle.pos.y-balle.radius>=raquette.pos.y-0.02 &&
                balle.pos.x >= raquette.pos.x-raquette.w/2 && balle.pos.x <=raquette.pos.x+raquette.w/2){
                balle.v.y = -balle.v.y;
            }
            //si la balle touche la raquette sur la zone droite
            else if(balle.pos.y-balle.radius <= raquette.pos.y+0.02 && balle.pos.y-balle.radius>=raquette.pos.y-0.02 &&
                    balle.pos.x <= raquette.pos.x+raquette.w && balle.pos.x >=raquette.pos.x+raquette.w/2){
                //si la balle vient de la droite
                if(balle.v.x<0){
                    balle.v.x = abs(balle.v.x) - 0.007;
                    //balle.v.y = sqrt(abs(d*d-balle.v.x*balle.v.x)); //Pour garder la meme norme du vecteur vitesse de la balle (somme des vecteurs vx et vy)
                }
                //si la balle vient de la gauche
                else{
                    balle.v.x = balle.v.x + 0.007;
                    //balle.v.y = sqrt(abs(d*d-balle.v.x*balle.v.x));
                    //printf("%g, %g , d=%g\n",balle.v.x, balle.v.y,d); //test pour trouver le probleme d'indefinition du calcul (racine d'un nb negatif)
                }
                balle.v.y = -balle.v.y;
            }
            //si la balle touche la raquette sur la zone gauche
            else if(balle.pos.y-balle.radius <= raquette.pos.y+0.02 && balle.pos.y-balle.radius>=raquette.pos.y-0.02 &&
                    balle.pos.x <= raquette.pos.x-raquette.w/2 && balle.pos.x >=raquette.pos.x-raquette.w){
                //si la balle vient de la gauche
                if(balle.v.x>=0){
                    balle.v.x = -1*(balle.v.x - 0.007);
                    //balle.v.y = sqrt(abs(d*d-balle.v.x*balle.v.x));
                }
                //si la balle vient de la droite
                else{
                    balle.v.x = -1*(abs(balle.v.x) + 0.007);
                    //balle.v.y = sqrt(abs(d*d-balle.v.x*balle.v.x));
                }
                balle.v.y = -balle.v.y;
            }
        }

        //si collision de la balle avec une brique
        if(collision_ball_brique(briques, nbBriques)){
            balle.v.y = -balle.v.y;
        }
    }
}


//  GESTION DES BONUS ET MALUS --------------------------------------------------
void collision_bonus_raquette(Bonus* tabBonus)
{
    for(int i = 0; i<8; i++){
        if(tabBonus[i].move==1){
            if(tabBonus[i].obj.pos.y-tabBonus[i].obj.w<= raquette.pos.y+0.02 && tabBonus[i].obj.pos.y-tabBonus[i].obj.w>=raquette.pos.y-0.02 &&
               tabBonus[i].obj.pos.x >= raquette.pos.x-raquette.w && tabBonus[i].obj.pos.x <=raquette.pos.x+raquette.w){
               tabBonus[i].move=0;
                if(tabBonus[i].rgb.r == 1 && tabBonus[i].rgb.g==0.5 && tabBonus[i].rgb.b==0){
                    //ajoute une vie seulement si le joueur en a moins que 3
                    if(balle.nbBalles <3){
                        balle.nbBalles+=1;
                    }
                }
                else if(tabBonus[i].rgb.r == 1 && tabBonus[i].rgb.g==0 && tabBonus[i].rgb.b==0){
                    balle.nbBalles-=1;
                }
                else if(tabBonus[i].rgb.r == 0.95 && tabBonus[i].rgb.g==0.9 && tabBonus[i].rgb.b==0){
                    raquette.w += 0.02;
                }
                else if(tabBonus[i].rgb.r == 0 && tabBonus[i].rgb.g==1 && tabBonus[i].rgb.b==0){
                    raquette.w -= 0.02;
                }
                else if(tabBonus[i].rgb.r == 0 && tabBonus[i].rgb.g==1 && tabBonus[i].rgb.b==1){
                    balle.v.y = 0.84*balle.v.y;
                }
                else if(tabBonus[i].rgb.r == 0 && tabBonus[i].rgb.g==0 && tabBonus[i].rgb.b==1){
                    balle.v.y = 1.19*balle.v.y;
                }
                else if(tabBonus[i].rgb.r == 1 && tabBonus[i].rgb.g==1 && tabBonus[i].rgb.b==1){
                    double d = norme_vitesse();
                    balle.v.x = balle.v.x - 0.02;
                }
                else if(tabBonus[i].rgb.r == 0.5 && tabBonus[i].rgb.g==0.5 && tabBonus[i].rgb.b==0.5){
                    //double d = norme_vitesse();
                    balle.v.x = balle.v.x + 0.02;
                }
            }
            else if(tabBonus[i].obj.pos.y + tabBonus[i].obj.w < -1){//balle sortie de l ecran
                tabBonus[i].move = 0;
            }
        }
    }
}


// GESTION DES INTERACTIONS ----------------------------------------------------------
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  //lorsque l'on clique
  if(button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    // on recupere les coordonnes sur l ecran de la souris
    mouse.x = (xpos/sizeWin_x)*2-1; //pour passer en systeme de coordonnées openGL
    mouse.y = (ypos/sizeWin_y)*2-1;

    //printf("pointer: %g, %g (%g,%g)\n",xpos, ypos, mouse.x, mouse.y);
    }
}

void cursor_position_callback(GLFWwindow* window, int button, int action, int mods)
{
    //la fonction s'effectue seulement si on est sur la page de jeu
    if(mouse.pageActuelle==1){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        //si la souris se situe sur l'écran de jeu (le bandeau supérieur est exclu)
        if (mouse.x != (xpos/sizeWin_x)*2-1 && (ypos/sizeWin_y)*2-1>-0.75){
            //On fait suivre la souris par la raquette seulement si la souris bouge dans la zone de jeu
            mouse.x = (xpos/sizeWin_x)*2-1; //pour passer en systeme de coordonnées openGL
            mouse.y = (ypos/sizeWin_y)*2-1; //pour passer en systeme de coordonnées openGL

            //gestion de la raquette avec les bords de l'ecran et la position de la souris
            //evite de faire sortir la raquette du terrain de jeu
            if (mouse.x>0.95 -raquette.w){raquette.pos.x = 0.95 -raquette.w;}
            else if (mouse.x<-0.95 +raquette.w){raquette.pos.x = -0.95 +raquette.w;}
            else{raquette.pos.x = mouse.x;}
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    //permet de contrôler la position de la raquette en fonction des appuis sur les fleches du clavier
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        // deplacer la raquette a droite
        if (key == GLFW_KEY_RIGHT) {
            if(raquette.pos.x + raquette.speed > 0.95 -raquette.w){raquette.pos.x = 0.95 -raquette.w;}
            else{raquette.pos.x += raquette.speed;}
        }
        // deplacer la raquette a gauche
        if (key == GLFW_KEY_LEFT) {
            if(raquette.pos.x - raquette.speed <-0.95 +raquette.w){raquette.pos.x = -0.95 +raquette.w;}
            else{raquette.pos.x -= raquette.speed;}
        }
        // mettre la balle en mouvement
        if(key == GLFW_KEY_SPACE){
            balle.move = 1;
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // yoffset > 0 indicates scrolling up, yoffset < 0 indicates scrolling down
    if (yoffset < 0 && raquette.pos.x< 0.95 - raquette.w) {
        raquette.pos.x += raquette.speed/5; //deplacement vers la droite
    } else if (yoffset > 0 && raquette.pos.x> -0.95 + raquette.w) {
        raquette.pos.x -= raquette.speed/5; //deplacement vers la gauche
    }
}


// GESTION DU JEU --------------------------------------------------
void init_game(Brique* briques, int nbBriques, Bonus* tabBonus)
{
    init_balle();
    init_briques(briques, nbBriques);
    init_briques_spe(briques, nbBriques, tabBonus);
    score = 0;
    raquette.w = 42.0/656.0 * 2;
    balle.nbBalles=3;
}

void update_bonus(Brique* briques, int nbBriques, Bonus* tabBonus)
{
    //parcours du tableau de bonus
    for(int i = 0; i<8; i++){
        //si la brique attribuée au bonus/malus est détruite
        if(briques[tabBonus[i].index].is_display==0 && tabBonus[i].obj.pos.y==briques[tabBonus[i].index].pos.y+0.015){
            tabBonus[i].move=1; //on active le mouvement et l'affichage du bonus
        }
        //si le bonus n'a pas ete rattrappe par la raquette et qu'il est sorti de l'ecran par le bas
        if(tabBonus[i].obj.pos.y<=-1.2 && tabBonus[i].move==1){
            tabBonus[i].move = 0; //on desactive son mouvement pour eviter les calculs
        }
        //si le bonus se deplace et est affiche
        if(tabBonus[i].move==1){
            tabBonus[i].obj.pos.y -= tabBonus[i].obj.speed; //on deplace l'objet vers le bas de l ecran
            drawDisc(tabBonus[i].obj.pos,tabBonus[i].obj.w, tabBonus[i].rgb); // on dessine le bonus avec sa couleur
        }
    }
    collision_bonus_raquette(tabBonus);// on regarde s'il y a collision entre la raquette et le bonus/malus
}

void update(Brique* briques, int nbBriques, Bonus* tabBonus)
{
    update_balle(briques, nbBriques);
    update_bonus(briques, nbBriques, tabBonus);
}


// GESTION DE LA FENETRE --------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    sizeWin_x = width;
    sizeWin_y = height;

    // Calculate the aspect ratio
    double aspect = (double)width / (double)height;

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (aspect >= 1.0) {
        // Wider than tall - expand the x-coordinate range
        glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
    } else {
        // Taller than wide - expand the y-coordinate range
        glOrtho(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect, -1.0, 1.0);
    }

    // Reset the model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// LES DIFFERENTES PAGES ------------------------------------------------------
/** Page d'accueil */
void display_welcome_page(GLFWwindow* window)
{
    // affichage du titre
    Pos pos = {-0.75, 0.2};
    draw_title(pos, 10, 0.25);

    // Creation du bouton
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-0.33, -0.23); // Coin inférieur gauche
    glVertex2f(0.33, -0.23);  // Coin inférieur droit
    glVertex2f(0.33, 0.05);   // Coin supérieur droit
    glVertex2f(-0.33, 0.05);  // Coin supérieur gauche
    glEnd();

    // Texte du bouton
    pos.x = -0.29;
    pos.y = -0.2;
    draw_play(pos, 4, 0.2);
}

/** Page de jeu */
void display_game_page(GLFWwindow* window, int nbBriques, Brique* briques, Bonus* tabBonus)
{
    //gestion du score
    Pos posScore = {-0.5, 0.85};
    draw_number(posScore, score);

    // dessin des elements et gestion des objets du jeu
    delimitations_terrain(); //dessiner les limitations du terrain
    bouton_croix(); //pour revenir au menu principal pendant le jeu

    draw_briques(briques, nbBriques);// dessiner les briques encore en jeu

    draw_raquette(); // dessiner la raquette du joueur

    // dessin du nombre de balles restantes avant la fin de la partie
    for (int i =0; i<3; i++)
    {
        Pos pos = { -0.13 + i*0.13, 0.90};
        if (i <= balle.nbBalles-1){
            drawDisc(pos, 0.05, balle.rgb);
        }
        else {drawCircle(pos, 0.05, balle.rgb);}
    }
    drawDisc(balle.pos, balle.radius, balle.rgb);

    // mise à jour de la partie
    update(briques, nbBriques, tabBonus); //mise à jour de la position de la balle et des bonus
}

/** Page fin de partie */
void display_game_over_page(GLFWwindow* window)
{
    // affichage de game over
    Pos pos = {-0.85,0.3};
    draw_game_over(pos, 10, 0.25);
    //Affichage du score
    pos.x = -0.35;
    pos.y = 0;
    draw_score(pos, 4, 0.1);
    pos.x = 0.35;
    draw_number(pos, score);

    // Creation du bouton
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-0.33, -0.33); // Coin inférieur gauche
    glVertex2f(0.33, -0.33);  // Coin inférieur droit
    glVertex2f(0.33, -0.15);   // Coin supérieur droit
    glVertex2f(-0.33, -0.15);  // Coin supérieur gauche
    glEnd();

    //texte du bouton pour recommencer une partie
    pos.x = -0.26;
    pos.y = -0.295;
    draw_restart(pos, 4, 0.1);
}

// FONCTION D'AFFICHAGE PRINCIPALE ---------------------------------------------
int display(GLFWwindow* window, int pageActuelle, int nbBriques, Brique* briques, Bonus* tabBonus)
{
    // couleur de fond de la fenetre (noir)
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // page d'accueil
    if (mouse.pageActuelle == 0){
        display_welcome_page(window);
        // si le bouton play est cliqué par la souris
        if (mouse.x>=-0.33 && mouse.x<=0.33 && mouse.y<=0.23 && mouse.y>=-0.05)
        {
            //on initialise le jeu pour une partie
            init_game(briques, nbBriques, tabBonus);
            return 1;
        }
        //sinon on reste sur la page d'accueil
        else{return 0;}
    }
    else {
        // page de jeu
        if (mouse.pageActuelle == 1){
            display_game_page(window, nbBriques, briques, tabBonus);
            // si la croix est cliquee
            if (mouse.x>=0.8 && mouse.x<=0.9 && mouse.y<=-0.85 && mouse.y>=-0.95)
            {
                return 0;
            }
            else if (balle.nbBalles<1){return 2;} //Si le joueur n'a plus de vies, la partie est terminee
            //sinon on reste sur la page de jeu
            else {return 1;}
        }
        else {
            // page de game over
            if (mouse.pageActuelle == 2){
                display_game_over_page(window);
                //si le bouton restart est clique, on recommence une partie
                if (mouse.x>=-0.33 && mouse.x<=0.33 && mouse.y<=0.33 && mouse.y>=0.15)
                {
                    //initialisation des variables pour une nouvelle partie
                    init_game(briques, nbBriques, tabBonus);
                    balle.nbEcrans=0;
                    return 1;
                }
                //sinon on reste sur la page de game over
                else{return 2;}
            }
            else {
                return 0;
            }
        }
    }

}


////////////////////////////////////////////////////////////////
//  PROGRAMME PRINCIPAL ---------------------------------------
////////////////////////////////////////////////////////////////

int main(void)
{
    // au cas ou ...
    srand(time(NULL));

    // initialisation du sous-systeme graphique
    if(!glfwInit())
    return -1;

    //cree une fenetre
    GLFWwindow* window=glfwCreateWindow(sizeWin_x,sizeWin_y,"Breakout Game - Themis SELLIER", NULL, NULL);
    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    //fenetre active
    glfwMakeContextCurrent(window);

    //Initialisation des variables
    int score = 0;
    int nbBriques = 14*8;
    Brique* briques = (Brique*)malloc(nbBriques * sizeof(Brique));
    Bonus* tabBonus = (Bonus*)malloc(8*sizeof(Bonus));

    init_game(briques, nbBriques, tabBonus);

    //recuperation des evenements de la souris ou du clavier
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, resize);
    glfwSetWindowSizeCallback(window, resize);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    //main loop
    double speed=1./50.; //en secondes
    double last_update=glfwGetTime();
    double next_update=glfwGetTime()+speed;

    int do_redisplay=true;

    while(!glfwWindowShouldClose(window))
    {
        if(do_redisplay)
        {
          mouse.pageActuelle = display(window, mouse.pageActuelle, nbBriques, briques, tabBonus);
          do_redisplay=false;
          glfwSwapBuffers(window);
            //void glfwSwapBuffers ( GLFWwindow * window )
        }

        //process events
        glfwPollEvents();

        // animation automatique (si necessaire)
        double now = glfwGetTime();

        if(now>=next_update)
        {
          last_update=now;
          next_update=last_update+speed;
          do_redisplay=1;
        }
    }

    glfwTerminate();
    free(briques);

    return 0;
}
