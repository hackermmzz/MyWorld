#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
	:QOpenGLWidget(parent)
{
	/////允许接受键盘事件
	setFocusPolicy(Qt::StrongFocus);
	//////鼠标移动事件
	setMouseTracking(true);
	EventQueue.push(ESCAPE_PRESS);
}

OpenGLWidget::~OpenGLWidget()
{

}

void OpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	SetOpenGLApi(this);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	::OpenglWidget = this;
	/////////////////////////////////////初始化
	GameInit();
}

void OpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	window_width = w;
	window_height = h;
	EventQueue.push(WINDOW_RESIZE);
}

void OpenGLWidget::paintGL()
{
	render_begin = QDateTime::currentMSecsSinceEpoch();//获取开始执行的毫秒时间戳
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/////////////////////////////////////////////////////
	Run();
	//////////////////////////////////////////
	glFinish();//刷新命令缓冲区
	update();//绘制
	////////////////////////////////////////////
	AfterRenderingProcess();
	///////////////////////////////////////////
	render_end = QDateTime::currentMSecsSinceEpoch();// 获取渲染结束的毫秒时间戳
	render_time = render_end - render_begin;
	render_time = render_time ? render_time : 1;
	fps = 1000.0 / render_time;
}

void OpenGLWidget::keyPressEvent(QKeyEvent* e)
{
	auto key = e->key();
	if (key == Qt::Key_W)EventQueue.push(W_PRESS);
	else if (key == Qt::Key_A)EventQueue.push(A_PRESS);
	else if (key == Qt::Key_D)EventQueue.push(D_PRESS);
	else if (key == Qt::Key_S)EventQueue.push(S_PRESS);
	else if (key == Qt::Key_Escape)EventQueue.push(ESCAPE_PRESS);
	else if (key == Qt::Key_Space)EventQueue.push(SPACE_PRESS);
	else if (key == Qt::Key_F3)EventQueue.push(F3_PRESS);
	else if (key == Qt::Key_F5)EventQueue.push(F5_PRESS);
	else if (key == Qt::Key_F6)EventQueue.push(F6_PRESS);
	else if(key == Qt::Key_E)EventQueue.push(E_PRESS);
	for(int i=0;i<9;++i)
	if (key == Qt::Key_1+i)EventQueue.push(ONE_PRESS+i);
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* e)
{
	auto key = e->key();
	if (e->isAutoRepeat())return;
	if (key == Qt::Key_A || key == Qt::Key_S || key == Qt::Key_W || key == Qt::Key_D)EventQueue.push(WSAD_RELEASE);

}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
	int mx = event->x(), my = event->y();
	static int last_posx = INT_MIN / 2, last_posy = INT_MIN / 2;
	int offsetx = mx - last_posx, offsety = last_posy - my;
	last_posx = mx;
	last_posy = my;
	static bool flag = 0;
	if (mx == 0 || my == 0 || mx >= width() - 10 || my >= height() - 10)
	{
		auto center = this->mapToGlobal(this->geometry().center());
		SetCursorPos(center.x(), center.y());
		flag = 1;
		return;
	}
	if (flag)
	{
		flag = 0;
		return;
	}
	mouse_movement_offset_x = offsetx;
	mouse_movement_offset_y = offsety;
	EventQueue.push(MOUSE_MOVE);
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
	auto  button = event->button();
	if (button== Qt::LeftButton)
		EventQueue.push(LEFT_MOUSE_CLICK);
	if (button == Qt::RightButton)
		EventQueue.push(RIGHT_MOUSE_CLICK);
}

void OpenGLWidget::wheelEvent(QWheelEvent* event)
{
	///////////////////////如果是第一人称就返回
	if (camera_mode == 0)return;
	///////////////////////如果是第三人称或者第二人称
	static float div = 360.0;
	auto delta = event->angleDelta().y()/div;
	auto temp = real_camera_distance;
	real_camera_distance -= delta;
	if (real_camera_distance < 0)real_camera_distance = temp;
	else if (real_camera_distance > 20)real_camera_distance = temp;
}
