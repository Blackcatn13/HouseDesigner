#include "Model_old.h"
#include <QImage>
#include <QDebug>
#include <QGLWidget>

Model_old::Model_old(){
    scale = 1;
    LoadTexture("normal.png", "textura.png");
}

Model_old::~Model_old(){
	
}

void Model_old::Dibuixa(){

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glColor3f(1.0,1.0,1.0);
        glPushMatrix();
        glRotatef(90,1.0,0.0,0.0);
        glFrontFace(GL_CW);
        glBegin(GL_QUADS);
        glTexCoord2f( 0.0f, 0.0f);
        glVertex2f( 0.0f, 0.0f);
        glTexCoord2f( 0.0f, 1.0f);
        glVertex2f( 0.0f, 1.0f);
        glTexCoord2f( 1.0f, 1.0f);
        glVertex2f( 1.0f, 1.0f);
        glTexCoord2f( 1.0f, 0.0f);
        glVertex2f( 1.0f, 0.0f);
        glEnd();
        glFrontFace(GL_CCW);
    glPopMatrix();
}

void Model_old::Dibuixa2(){

    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glPushMatrix();
        glRotatef(90,1.0,0.0,0.0);
        glFrontFace(GL_CW);
        glScalef(scale, scale, scale);
        glutSolidTeapot(.3);
        glFrontFace(GL_CCW);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glPushMatrix();
        glTranslatef(1, 0, 0);
        glRotatef(90,1.0,0.0,0.0);
        glFrontFace(GL_CW);
        glScalef(scale, scale, scale);
        glutSolidTeapot(.3);
        glFrontFace(GL_CCW);
    glPopMatrix();
}

void Model_old::Eixos(){

    glDisable(GL_LIGHTING);

    // Eix X (vermell)
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(300.0,0.0,0.0);
    glEnd();

    // Eix Y (verd)
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,300.0,0.0);
    glEnd();

    // Eix Z (blau)
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,300.0);
    glEnd();

    glEnable(GL_LIGHTING);

}

void Model_old::LoadTexture(const char *name, const char *name1){
    QImage img;
    if( ! img.load( name ) )
    {
        qWarning("Not found image 1");
        exit( 1 );
    }

    QImage GL_formatted_image;
    GL_formatted_image = QGLWidget::convertToGLFormat(img);
    if( GL_formatted_image.isNull() )
    {
        qWarning("Not possible to format image 1");
        exit( 1 );
    }
    glGenTextures(2, textures);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
            GL_formatted_image.width(), GL_formatted_image.height(),
            0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    if( ! img.load( name1 ) )
    {
        qWarning("Not found image 2");
        exit( 1 );
    }

    GL_formatted_image = QGLWidget::convertToGLFormat(img);
    if( GL_formatted_image.isNull() )
    {
        qWarning("Not possible to format image 2");
        exit( 1 );
    }
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
            GL_formatted_image.width(), GL_formatted_image.height(),
            0, GL_RGBA, GL_UNSIGNED_BYTE, GL_formatted_image.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

}

 void Model_old::zoomIn()
{
    scale += 0.1;
}
void Model_old::zoomOut()
{
    scale -= 0.1;
}
