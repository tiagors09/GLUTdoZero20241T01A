#include <iostream>

using namespace std;

#include <gui.h>

class Pyramid {
    private:
        // Floor
        Vetor3D floorV1;
        Vetor3D floorV2;
        Vetor3D floorV3;
        Vetor3D floorV4;

        // Face 1
        Vetor3D face1V1;
        Vetor3D face1V2;
        Vetor3D face1V3;

        // Face 2
        Vetor3D face2V1;
        Vetor3D face2V2;
        Vetor3D face2V3;

        // Face 3
        Vetor3D face3V1;
        Vetor3D face3V2;
        Vetor3D face3V3;

        // Face 4
        Vetor3D face4V1;
        Vetor3D face4V2;
        Vetor3D face4V3;

        float baseSize;
        float height;
    public:

        Pyramid(float baseSize, float height) {
            this->baseSize = baseSize;
            this->height = height;

            // Floor
            this->floorV1 = Vetor3D(0.0,0.0,-baseSize);
            this->floorV2 = Vetor3D(baseSize,0.0,-baseSize);
            this->floorV3 = Vetor3D(baseSize,0.0,0.0);
            this->floorV4 = Vetor3D(0.0,0.0,0.0);

            // Face 1
            this->face1V1 = Vetor3D(0.0,0.0,0.0);
            this->face1V2 = Vetor3D(baseSize,0.0,0.0);
            this->face1V3 = Vetor3D(baseSize/2,height,-0.5);

            // Face 2
            this->face2V1 = Vetor3D(baseSize,0.0,0.0);
            this->face2V2 = Vetor3D(baseSize,0.0,-baseSize);
            this->face2V3 = Vetor3D(baseSize/2,height,-0.5);

            // Face 3
            this->face3V1 = Vetor3D(baseSize,0.0,-baseSize);
            this->face3V2 = Vetor3D(0.0,0.0,-baseSize);
            this->face3V3 = Vetor3D(baseSize/2,height,-0.5);

            // Face 4
            this->face4V1 = Vetor3D(0.0,0.0,-baseSize);
            this->face4V2 = Vetor3D(0.0,0.0,0.0);
            this->face4V3 = Vetor3D(baseSize/2,height,-0.5);
        }

        void draw() {
            GUI::drawOriginAL(1.0,1.0);

            // base
            glBegin(GL_POLYGON);
                // Eixo normal
                // definir
                glNormal3f(0.0,-1.0,0.0);
                // Faces
                glVertex3f(floorV1.x,floorV1.y,floorV1.z);
                glVertex3f(floorV2.x,floorV2.y,floorV2.z);
                glVertex3f(floorV3.x,floorV3.y,floorV3.z);
                glVertex3f(floorV4.x,floorV4.y,floorV4.z);
            glEnd();

            //face 1
            GUI::setColor(255 / 255.0, 0 / 255.0, 127 / 255.0, 1.0, true);
            glBegin(GL_POLYGON);
                // Eixo normal
                // definir
                glNormal3f(0.0,0.0,1);
                // Faces
                glVertex3f(face1V1.x,face1V1.y,face1V1.z);
                glVertex3f(face1V2.x,face1V2.y,face1V2.z);
                glVertex3f(face1V3.x,face1V3.y,face1V3.z);
            glEnd();

            //face 2
            GUI::setColor(0 / 255.0, 255 / 255.0, 0 / 255.0, 1.0, true);
            glBegin(GL_POLYGON);
                // Eixo normal
                // definir
                glNormal3f(1.0,0.0,0.0);
                // Faces
                glVertex3f(face2V1.x,face2V1.y,face2V1.z);
                glVertex3f(face2V2.x,face2V2.y,face2V2.z);
                glVertex3f(face2V3.x,face2V3.y,face2V3.z);
            glEnd();

            //face 3
            GUI::setColor(0 / 255.0, 0 / 255.0, 255 / 255.0, 1.0, true);
            glBegin(GL_POLYGON);
                // Eixo normal
                // definir
                glNormal3f(0.0,0.0,-1.0);
                // Faces
                glVertex3f(face3V1.x,face3V1.y,face3V1.z);
                glVertex3f(face3V2.x,face3V2.y,face3V2.z);
                glVertex3f(face3V3.x,face3V3.y,face3V3.z);
            glEnd();

            //face 4
            GUI::setColor(255 / 255.0, 255 / 255.0, 0 / 255.0, 1.0, true);
            glBegin(GL_POLYGON);
                // Eixo normal
                // definir
                glNormal3f(-1.0,0.0,0.0);
                // Faces
                glVertex3f(face4V1.x,face4V1.y,face4V1.z);
                glVertex3f(face4V2.x,face4V2.y,face4V2.z);
                glVertex3f(face4V3.x,face4V3.y,face4V3.z);
            glEnd();
        }

        void translate(float x, float y, float z) {
            glTranslatef(x,y,z);
        }

        void rotate(float angle) {
            glRotatef(angle, 0.0, 0.0, 1);
        }
};

void desenha() {
    GUI::displayInit();

    const float ar = glutGUI::height>0 ? (float) glutGUI::width / (float) glutGUI::height : 1.0;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        gluPerspective(30.,ar,0.1,1000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
    GUI::setLight(0, 0,2,2, true,false);

    GUI::drawOrigin(0.5);
    GUI::setColor(0.8,0.0,0.0, 1,true);
    GUI::drawFloor(5,5);

    GUI::setColor(0.0,0.8,0.0, 1,true);

    Pyramid pyramid1(2,2);
    pyramid1.rotate(30.0);
    pyramid1.draw();

    GUI::displayEnd();
}

void teclado(unsigned char tecla, int x, int y) {
    GUI::keyInit(tecla, x, y);

    switch (tecla) {
    case 'a':
        break;
    case 'd':
        break;
    case 's':
        break;
    case 'w':
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
    case 'p':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 't':
        break;
    default:
        break;
    }
}

int main()
{
    GUI gui = GUI(800,600,desenha,teclado);
}

