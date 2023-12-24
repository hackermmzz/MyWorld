#pragma once

#include <QObject>
#include"assimp/config.h"
#include<Headers.h>
#include<QKeyEvent>
#include"MyWorld/globalsource.h"
#include"MyWorld/EventProcess.h"
#include"MyWorld/Header.h"
#include"qthread.h"
class OpenGLWidget  : public QOpenGLWidget, OPENGLAPI
{
	Q_OBJECT

public:
	OpenGLWidget(QWidget *parent);
	~OpenGLWidget();
protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	virtual void keyPressEvent(QKeyEvent* event);
	virtual void keyReleaseEvent(QKeyEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void wheelEvent(QWheelEvent* event);
};
