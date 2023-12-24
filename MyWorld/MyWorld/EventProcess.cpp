#include"EventProcess.h"
void EventProcess()
{
    while(!EventQueue.empty()){
        auto& key = EventQueue.front();
        /////////////////////////////////
        switch (key) {
        case W_PRESS:
            EVENT_W_PRESS();
            break;
        case A_PRESS:
            EVENT_A_PRESS();
            break;
        case S_PRESS:
            EVENT_S_PRESS();
            break;
        case D_PRESS:
            EVENT_D_PRESS();
            break;
        case WINDOW_RESIZE:
            EVENT_WINDOW_RESIZE();
            break;
        case MOUSE_MOVE:
            EVENT_MOUSE_MOVE();
            break;
        case F3_PRESS:
            EVENT_F3_PRESS();
            break;
        case F5_PRESS:
            EVENT_F5_PRESS();
            break;
        case F6_PRESS:
            EVENT_F6_PRESS();
            break;
        case ESCAPE_PRESS:
            EVENT_ESCAPE_PRESS();
            break;
        case SPACE_PRESS:
            EVENT_SPACE_PRESS();
            break;
        case WSAD_RELEASE:
            EVENT_WSAD_RELEASE();
            break;
        case LEFT_MOUSE_CLICK:
            EVENT_LEFT_MOUSE_CLICK();
            break;
        case RIGHT_MOUSE_CLICK:
            EVENT_RIGHT_MOUSE_CLICK();
            break;
        case E_PRESS:
            EVENT_E_PRESS();
            break;
        }
        ///////////检测是否为1-9
        if (ONE_PRESS <= key && key <= NINE_PRESS)
            EVENT_ONE_TO_NINE_PRESS(key-ONE_PRESS);
        ///////////////////////////////////////////
        EventQueue.pop();
    }
}

void EVENT_W_PRESS()
{
    /*RoleMoveDirection|=FORWARD;
    rolecontroller.mvfsm.SwitchState(MOVE);*/
    camera.processKeyBoard(FORWARD, 1);
}

void EVENT_A_PRESS()
{
    RoleMoveDirection|=LEFT;
    rolecontroller.mvfsm.SwitchState(MOVE);
}

void EVENT_S_PRESS()
{
    RoleMoveDirection|=BACKWARD;
    rolecontroller.mvfsm.SwitchState(MOVE);
}

void EVENT_D_PRESS()
{
    RoleMoveDirection|=RIGHT;
    rolecontroller.mvfsm.SwitchState(MOVE);
}

void EVENT_WINDOW_RESIZE()
{
  //////////////更新视图矩阵
  UpdateCameraProjection();
  //////////////更新工作台大小
  float relativePosxy = 0.1, relativeSize = 0.8;
  float widgetWidth = relativeSize / BagColumn * window_width;
  float widgetHeight = relativeSize / BagRow * window_width;
  workSpaceBoard->move(relativePosxy * window_width, relativePosxy * window_height);
  workSpaceBoard->resize(relativeSize * window_width, relativeSize * window_height);
  auto& Bag = workSpaceBoard->ui->Bag;
  for (int r = 0; r < Bag->rowCount(); ++r)
  {
      Bag->verticalHeader()->setSectionResizeMode(r, QHeaderView::Fixed);
      Bag->verticalHeader()->resizeSection(r, widgetHeight);  // 设置行高为50像素
      for (int c = 0; c < Bag->columnCount(); ++c)
      {
          Bag->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Fixed);
          Bag->horizontalHeader()->resizeSection(c, widgetWidth);  // 设置行高为50像素
      }
  }
  //////////////////更新背包大小,和工作台一样大
  MyBag->move(relativePosxy * window_width, relativePosxy * window_height);
  MyBag->resize(relativeSize * window_width, relativeSize * window_height);
  auto& bag = MyBag->ui->bag;
  for (int r = 0; r < bag->rowCount(); ++r)
  {
      bag->verticalHeader()->setSectionResizeMode(r, QHeaderView::Fixed);
      bag->verticalHeader()->resizeSection(r, widgetHeight);  // 设置行高为50像素
      for (int c = 0; c < bag->columnCount(); ++c)
      {
          bag->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Fixed);
          bag->horizontalHeader()->resizeSection(c, widgetWidth);  // 设置行高为50像素
      }
  }
  /////////////////更新物品框大小
  float relativePosx = 0.05, relativePosy = 0.9, relativeWidth = 0.1*9, relativeHeight =0.1;
  int ItemBoardWidth = relativeWidth * window_width, ItemBoardHeight = relativeHeight * window_height;
  int ItemBasePosX = relativePosx * window_width, ItemBasePosyY = relativePosy * window_height;
  itemBoard->move(ItemBasePosX, ItemBasePosyY);
  itemBoard->resize(ItemBoardWidth, ItemBoardHeight);
  
}

void EVENT_MOUSE_MOVE()
{
  camera.processMouseMovement(mouse_movement_offset_x,mouse_movement_offset_y,0.5);
}

void EVENT_F3_PRESS()
{
  static bool is_show=1;
  Show_Info=is_show;
  is_show=!is_show;
}

void EVENT_F5_PRESS()
{
    camera_mode = (camera_mode + 1) % 3;
}

void EVENT_F6_PRESS()
{
    static ExposureAdjust* widget = 0;
    static bool show = 0;
    if (!widget)
    {
        widget = new ExposureAdjust(OpenglWidget);
        widget->move(0, 0);
        QApplication::connect(widget->ui->Exposure, &QSlider::valueChanged, [&](){
            exposure = widget->ui->Exposure->value()/10.0;
            });
    }
    show = !show;
    if (show)
    {
        widget->show();
        widget->resize(window_width * 0.3, window_height * 0.05);
        EventQueue.push(ESCAPE_PRESS);
    }
    else {
        widget->hide();
        EventQueue.push(ESCAPE_PRESS);
    }
    
}

void EVENT_ESCAPE_PRESS()
{
  static bool release_mouse=0;
  if(release_mouse)
  {
    OpenglWidget->setCursor(Qt::ArrowCursor);
    OpenglWidget->setMouseTracking(false);
    ClipCursor(0);
  }
  else{
  OpenglWidget->setCursor(Qt::BlankCursor);
  OpenglWidget->setMouseTracking(true);
  QPoint topleft = OpenglWidget->mapToGlobal(OpenglWidget->rect().topLeft());
  RECT rect;
  rect.bottom=topleft.y()+window_height;
  rect.top=topleft.y();
  rect.left=topleft.x();
  rect.right=topleft.x()+window_width;
  ClipCursor(&rect);
  }
  release_mouse=!release_mouse;
}



void EVENT_SPACE_PRESS()
{
  rolecontroller.jdfsm.SwitchState(JUMP);
}

void EVENT_WSAD_RELEASE()
{
  RoleMoveDirection&=0;
 rolecontroller.mvfsm.SwitchState(STOP);
}

void EVENT_LEFT_MOUSE_CLICK()
{
    rolecontroller.buildfsm.SwitchState(DESTROY_BLOCK);
}

void EVENT_RIGHT_MOUSE_CLICK()
{
    rolecontroller.buildfsm.SwitchState(FUNCTION_BLOCK);
}

void EVENT_ONE_TO_NINE_PRESS(int id)
{
    auto& items = itemBoard->ui->item;
    /////////先将之前的框去掉
    items[ItemBoardCurrentSelectedItem]->setStyleSheet("");
    items[id]->setStyleSheet("QPushButton { border: 2px solid black; }");
    ItemBoardCurrentSelectedItem = id;
}

void EVENT_E_PRESS()
{
    static bool is_show = 1;
    /////////将之前选中的item设置为0
    MyBagCurrentSelectedItem = 0;
    DrawBag(is_show);
    is_show = !is_show;
}

