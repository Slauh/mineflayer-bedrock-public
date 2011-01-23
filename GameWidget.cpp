#include "GameWidget.h"

#include <QtGlobal>


uint qHash(GameWidget::ChunkCoord coord)
{
    return (coord.x * 8191 + coord.z) * 131071 + coord.y;
}

GameWidget::GameWidget(QWidget *parent) :
    QGLWidget(parent)
{
    this->setMouseTracking(true);
}

void GameWidget::start(QString user, QString password, QString server)
{
    // TODO
}

void GameWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    GLUquadric * quad = gluNewQuadric();
    gluSphere(quad, 0.3, 100, 10);
    gluDeleteQuadric(quad);
}

void GameWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void GameWidget::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_MULTISAMPLE);
    static GLfloat lightPosition[4] = { 0.5, 5.0, 7.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void GameWidget::mousePressEvent(QMouseEvent *)
{

}

void GameWidget::mouseMoveEvent(QMouseEvent *)
{

}

void GameWidget::mouseReleaseEvent(QMouseEvent *)
{

}

int GameWidget::Chunk::indexOf(GameWidget::ChunkCoord coord) const
{
    return coord.y + (coord.z * (m_size_y+1)) + (coord.x * (m_size_y+1) * (m_size_z+1));
}

int GameWidget::Chunk::getType(GameWidget::ChunkCoord coord) const
{
    return m_type.at(indexOf(coord));
}

int GameWidget::Chunk::getMetadata(GameWidget::ChunkCoord coord) const
{
    return m_metadata.at(indexOf(coord));
}

int GameWidget::Chunk::getLight(GameWidget::ChunkCoord coord) const
{
    return m_light.at(indexOf(coord));
}

int GameWidget::Chunk::getSkyLight(GameWidget::ChunkCoord coord) const
{
    return m_sky_light.at(indexOf(coord));
}


