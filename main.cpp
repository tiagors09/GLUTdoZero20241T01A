#include <iostream>

using namespace std;

#include <gui.h>

Vetor3D posEsfera = Vetor3D(2,1,0);
float raioEsfera = 0.2;

Model3DS carro = Model3DS("../3ds/cartest.3DS");

void casa()
{
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    //frontal
    glBegin(GL_POLYGON);
        glNormal3f(0,0,1);
        glTexCoord2f(0,0); glVertex3f(0,0,1);
        glTexCoord2f(0.25,0); glVertex3f(1,0,1);
        glTexCoord2f(0.25,1); glVertex3f(1,1,1);
        glTexCoord2f(0,1); glVertex3f(0,1,1);
    glEnd();
    //direita
    glBegin(GL_POLYGON);
        glNormal3f(1,0,0);
        glTexCoord2f(0.25,0); glVertex3f(1,0,1);
        glTexCoord2f(0.5,0); glVertex3f(1,0,0);
        glTexCoord2f(0.5,1); glVertex3f(1,1,0);
        glTexCoord2f(0.25,1); glVertex3f(1,1,1);
    glEnd();
    //traseira
    glBegin(GL_POLYGON);
        glNormal3f(0,0,-1);
        glTexCoord2f(0.5,0); glVertex3f(1,0,0);
        glTexCoord2f(0.75,0); glVertex3f(0,0,0);
        glTexCoord2f(0.75,1); glVertex3f(0,1,0);
        glTexCoord2f(0.5,1); glVertex3f(1,1,0);
    glEnd();
    //esquerda
    glBegin(GL_POLYGON);
        glNormal3f(-1,0,0);
        glTexCoord2f(0.75,0); glVertex3f(0,0,0);
        glTexCoord2f(1.0,0); glVertex3f(0,0,1);
        glTexCoord2f(1.0,1); glVertex3f(0,1,1);
        glTexCoord2f(0.75,1); glVertex3f(0,1,0);
    glEnd();
    //superior
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glVertex3f(0,1,0);
        glVertex3f(0,1,1);
        glVertex3f(1,1,1);
        glVertex3f(1,1,0);
    glEnd();
    //inferior
    glBegin(GL_POLYGON);
        glNormal3f(0,-1,0);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glVertex3f(1,0,1);
        glVertex3f(0,0,1);
    glEnd();
    //teto esquerdo
    glBegin(GL_POLYGON);
        glNormal3f(-1,1,0);
        glVertex3f(0,1,0);
        glVertex3f(0,1,1);
        glVertex3f(0.5,1.5,1);
        glVertex3f(0.5,1.5,0);
    glEnd();
}

int idTexture = 3;

void usandoTexturas() {
    //Usando texturas

    GUI::habilitaTextura(true,false,0);
    GUI::selecionaTextura(idTexture);

    //objeto a ser aplicada a textura
    //GUI::drawBox(-1,-1,-1, 1,1,1);
    //GUI::drawSphere(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);
    //GUI::drawHalfSphere(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);

    GUI::setColor(0.7,0.7,0.7, 0.5);
    //glBegin(GL_POLYGON);
    //    glTexCoord2f(0,0); glVertex3f(0,0,0);
    //    glTexCoord2f(0.5,0); glVertex3f(1,0,0);
    //    glTexCoord2f(0.5,1); glVertex3f(1,1,0);
    //    glTexCoord2f(0,1); glVertex3f(0,1,0);
    //glEnd();
    //glBegin(GL_POLYGON);
    //    glTexCoord2f(0,0); glVertex3f(0,0,0);
    //    glTexCoord2f(0.5,0); glVertex3f(1,0,0);
    //    glTexCoord2f(0.25,1); glVertex3f(0.5,1,0);
    //glEnd();

    //casa();

    glRotatef(-90,1,0,0);
    GLUquadricObj *quad = gluNewQuadric();
    Desenha::gluClosedCylinder(quad,0.5,0,1,30,30);
    gluDeleteQuadric( quad );

    GUI::desabilitaTextura(true,false);
}

Vetor3D t(0,0,0);
Vetor3D r(0,0,0);
Vetor3D s(1,1,1);

Vetor3D rotacaoZ( Vetor3D v, float theta ) {
    Vetor3D vt;
    float thetaRad = theta*PI/180;
    vt.x = cos(thetaRad)*v.x - sin(thetaRad)*v.y;
    vt.y = sin(thetaRad)*v.x + cos(thetaRad)*v.y;
    vt.z = v.z;
    return vt;
}

Vetor3D translacao( Vetor3D v, Vetor3D desl ) {
    Vetor3D vt;
    vt.x = v.x + desl.x;
    vt.y = v.y + desl.y;
    vt.z = v.z + desl.z;
    return vt;
}

void transformsSemMatriz()
{
    //glTranslatef(t.x,t.y,t.z); //I.T.R.S
    //glRotatef(r.z, 0,0,1);

    //exemplo da face frontal da nossa piramide
    Vetor3D vN = Vetor3D(0,1,1);
    Vetor3D v1 = Vetor3D(1,0,1);
    Vetor3D v2 = Vetor3D(0,1,0);
    Vetor3D v3 = Vetor3D(-1,0,1);

    float theta = r.z;
    vN = rotacaoZ(vN,theta);
    v1 = rotacaoZ(v1,theta);
    v2 = rotacaoZ(v2,theta);
    v3 = rotacaoZ(v3,theta);

    Vetor3D desl = Vetor3D( t.x,t.y,t.z ); //          R.(T.vi)
    v1 = translacao(v1,desl);
    v2 = translacao(v2,desl);
    v3 = translacao(v3,desl);


    GUI::setColor(0.0,0.8,0.0, 0.5,true);
    glBegin(GL_POLYGON);
        glNormal3f( vN.x, vN.y, vN.z );
        glVertex3f( v1.x, v1.y, v1.z );
        glVertex3f( v2.x, v2.y, v2.z );
        glVertex3f( v3.x, v3.y, v3.z );
    glEnd();
}

void global2LocalCam( Vetor3D e, Vetor3D c, Vetor3D u ) {
    Vetor3D Oc = e;
    Vetor3D kc = e - c;
    !kc;
    Vetor3D ic = u ^ kc;
    !ic;
    Vetor3D jc = kc ^ ic;
    //!jc;

    float Tcam[16] = {
        ic.x, ic.y, ic.z,  ic * (Oc*(-1)),
        jc.x, jc.y, jc.z,  jc * (Oc*(-1)),
        kc.x, kc.y, kc.z,  kc * (Oc*(-1)),
         0.0,  0.0,  0.0,  1.0
    };

    glMultTransposeMatrixf( Tcam );
}

void desenha() {
    GUI::displayInit();

    const float ar = glutGUI::height>0 ? (float) glutGUI::width / (float) glutGUI::height : 1.0;
    //const float w = glutGUI::width;
    //const float h = glutGUI::height;
    //float orthof = glutGUI::orthof;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
        gluPerspective(30.,ar,0.1,1000.);
        //gluPerspective(150.,ar,0.1,1000.);
        //gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
        //float d = 2;
        {
            //float s = 5;
            //float near = 0;
            //float h = glutGUI::height;
            //float w = glutGUI::width;
            //glOrtho(-s, s, -s*h/w, s*h/w, near, 20);
        }
        //obliqua  //   S . T . T(0,0,-near) . Sh . T(0,0,near)








    glMatrixMode(GL_MODELVIEW); // Tcam . Tobj
    glLoadIdentity();
    //global2LocalCam(glutGUI::cam->e,glutGUI::cam->c,glutGUI::cam->u);
    gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
    //gluLookAt(olho,  centro,  up);
    //gluLookAt(0,1,10,  0,0,0,  0,1,0);
    //gluLookAt(10,1,0,  0,0,0,  0,1,0);
    //gluLookAt(0,1,10,  0,-1,0,  0,1,0);

    GUI::setLight(0, 0,2,2, true,false);

    //referencia
    GUI::drawOrigin(0.5);
    //GUI::drawOriginAL(5);
    GUI::setColor(0.8,0.0,0.0, 1,true);
    GUI::drawFloor(5,5);

    GUI::setColor(0.0,0.8,0.0, 1,true);
    //GUI::drawSphere(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);
    //posEsfera.x -= 0.001;
    //raioEsfera += 0.001;

    //GUI::drawBox(-1,-1,-1, 1,1,1, true);

    //GUI::setColor(0,0,0.8);
    //GUI::draw3ds(carro);


    //I.T.R.S
    //<------ interpretacao global
    //------> interpretacao local
    glTranslatef(t.x,t.y,t.z);
    glRotatef(r.x, 1,0,0);
    glRotatef(r.y, 0,1,0);
    glRotatef(r.z, 0,0,1);
    GUI::drawOrigin(0.5);
    glScalef(s.x,s.y,s.z);


    //GUI::glShearXf(t.x,0);
    //GUI::glShearYf(t.y,0);
    //GUI::glShearXYf(t.x,t.y);

    //GUI::drawOrigin(0.5);
    GUI::setColor(0.0,0.8,0.0, 1,true);
    GUI::drawBox(0,0,0, 1,1,1);



//    glPushMatrix();
//        GUI::glReflectPlaneXZf();
//        GUI::glReflectPlaneYZf();

//        glTranslatef(t.x,t.y,t.z);
//        glRotatef(r.z, 0,0,1);
//        glScalef(s.x,s.y,s.z);

//        GUI::drawOrigin(0.5);
//        //casa();
//        //usandoTexturas();
//        GUI::setColor(0.0,0.8,0.0, 1,true);
//        //glDisable(GL_CULL_FACE);
//        GUI::drawBox(0,0,0, 1,1,1);
//        //glEnable(GL_CULL_FACE);
//    glPopMatrix();

//    glPushMatrix();
//        glTranslatef(t.x,t.y,t.z);
//        glRotatef(r.z, 0,0,1);
//        glScalef(s.x,s.y,s.z);

//        GUI::setColor(0.0,0.8,0.0, 1,true);
//        glDisable(GL_CULL_FACE);
//        GUI::drawBox(0,0,0, 1,1,1);
//        glEnable(GL_CULL_FACE);
//    glPopMatrix();


    //transformsSemMatriz();

    //GUI::drawSphere(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);
    //GUI::drawHalfSphere(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);
    //GUI::drawSphereInsideBox222(posEsfera.x,posEsfera.y,posEsfera.z, raioEsfera);
    //GUI::drawSphereInsideBox222(0,0,0, raioEsfera);

    //interacao com o mouse
    //posEsfera.x += glutGUI::drx;
    //posEsfera.y += glutGUI::dry;
    //posEsfera.z += -0.1*glutGUI::dlrx;
    //raioEsfera += 0.01*glutGUI::dlx;
    t.x += glutGUI::drx;
    t.y += glutGUI::dry;
    t.z += glutGUI::dlry;
    r.x += glutGUI::dly;
    r.y += glutGUI::dlx;
    r.z += glutGUI::dlrx;
    s.x += glutGUI::dmx;
    s.y += glutGUI::dmy;
    s.z += glutGUI::dlmy;

    GUI::displayEnd();
}

void teclado(unsigned char tecla, int x, int y) {
    GUI::keyInit(tecla, x, y);

    switch (tecla) {
    case 'a':
        posEsfera.x -= 0.1;
        break;
    case 'd':
        posEsfera.x += 0.1;
        break;
    case 's':
        posEsfera.y -= 0.1;
        break;
    case 'w':
        posEsfera.y += 0.1;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;
    case 'p':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        break;
    case 't':
        idTexture ++;
        idTexture = idTexture%7;
        break;
    default:
        break;
    }
}

int main()
{
    cout << "Hello World!" << endl;

//    glutGUI::cam->e = Vetor3D(0,1,10);
//    glutGUI::cam->c = Vetor3D(0,0,0);
//    glutGUI::cam->u = Vetor3D(0,1,0);

    GUI gui = GUI(800,600,desenha,teclado);
}

//inicializando OpenGL
//while(true) {
//    desenha();
//    interacaoUsuario();
//    //if () {
//    //    break;
//    //}
//}

//void cortandoObjetos() {
//    //glRotatef(90,1,0,0);

//    //clipping
//    //GLdouble plane[4] = { 0.0, 1.0, 0.0, 1}; //deixa a parte acima (y) do plano aparecendo (plano posicionado no y=-1, d desloca o plano no sentido oposto à normal) (corta o y<-1)
//    //GLdouble plane[4] = { 0.0, -1.0, 0.0, 1}; //deixa a parte abaixo (y) do plano aparecendo (plano posicionado no y=1, d desloca o plano no sentido oposto à normal) (corta o y>1)
//    GLdouble plane[4] = { -1.0, 0.0, 1.0, 0.0 }; //deixa a parte à frente do plano (z) do plano aparecendo (plano posicionado no z=0, d desloca o plano no sentido oposto à normal) (corta o z<0)
//    glClipPlane(GL_CLIP_PLANE0, plane);
//    glEnable(GL_CLIP_PLANE0);

//    //    ax + by + cz + d = 0
//    //            n = (a,b,c)
//    //            d = deslocamento a partir da origem

//    //glRotatef(90,1,0,0);

//    //objeto a ser cortado
//    //GUI::drawSphere(0,0,0,raioEsfera);
//    casa();

//    //clipping
//    glDisable(GL_CLIP_PLANE0);
//}


