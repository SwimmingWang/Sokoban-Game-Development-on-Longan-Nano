#include "lcd/lcd.h"
#include "utils.h"
#include "assembly/example.h"
#include <time.h>

void Inp_init(void)
{
  rcu_periph_clock_enable(RCU_GPIOA);
  rcu_periph_clock_enable(RCU_GPIOC);

  gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ,
            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
  gpio_init(GPIOC, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ,
            GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
}

void IO_init(void)
{
  Inp_init(); // inport init
  Lcd_Init(); // LCD init
}

int myinit()
{
  int b = draw(0);
  return b;
}

void choose_highlight(int choose_num)
{
  if (choose_num == 1)
  {
    LCD_ShowString(20, 40, "Easy", 65535);
    LCD_ShowString(20, 60, "Normal", 33840);
    LCD_ShowString(20, 80, "Hard", 33840);
  }
  else if (choose_num == 2)
  {
    LCD_ShowString(20, 40, "Easy", 33840);
    LCD_ShowString(20, 60, "Normal", 65535);
    LCD_ShowString(20, 80, "Hard", 33840);
  }
  else if (choose_num == 3)
  {
    LCD_ShowString(20, 40, "Easy", 33840);
    LCD_ShowString(20, 60, "Normal", 33840);
    LCD_ShowString(20, 80, "Hard", 65535);
  }
}

int push_button()
{
  if (Get_Button(JOY_CTR) || Get_Button(JOY_DOWN) || Get_Button(JOY_LEFT) || Get_Button(JOY_RIGHT) || Get_Button(JOY_UP))
    return 1;
  return 0;
}
int get_color(int unstop)
{
  if (unstop)
    return 2016;
  return 63488;
}
int get_horizon(int num)
{
  if (num == 1)
    return 30;
  else if (num == 2)
    return 25;
  else
    return 20;
}
void draw_fun(int life, int score)
{
  if (score >= 0 && score < 10)
    LCD_ShowNum(50, 0, score, 1, 65535);
  else if (score >= 10 && score < 100)
    LCD_ShowNum(50, 0, score, 2, 65535);
  if (life >= 0 && life < 10)
    LCD_ShowNum(50, 20, life, 1, 65535);
  else if (life >= 10 && life < 100)
    LCD_ShowNum(50, 20, life, 2, 65535);
}
int main(void)
{

  IO_init();
  int tmp = myinit();

  LCD_Clear(0);
  delay_1ms(300);
  int choose_number = 1;
  if (tmp == 1)
  {
    LCD_ShowString(0, 0, "Choose Difficulty:", 65535);
    choose_highlight(choose_number);
  }
  else
  {
    LCD_ShowString(0, 0, "Choose Difficulty:", 31);
    LCD_ShowString(0, 40, "Easy", 31);
    LCD_ShowString(0, 60, "Normal", 31);
    LCD_ShowString(0, 80, "Hard", 31);
  }
  while (1)
  {
    if (Get_Button(JOY_LEFT))
    {
      choose_number = choose_number - 1;
      if (choose_number == 0)
        choose_number = 3;
      choose_highlight(choose_number);
    }
    else if (Get_Button(JOY_RIGHT))
    {
      choose_number = choose_number + 1;
      if (choose_number == 4)
        choose_number = 1;
      choose_highlight(choose_number);
    }
    delay_1ms(300);
    if (Get_Button(JOY_CTR))
    {
      break;
    }
  }
  LCD_Clear(0);

  struct Ball
  {
    int _x;
    int _y;
    int _y_old;
    int unstop;
    int unstop_tick;
    int speed;
    int is_dead;
  };
  struct Wall
  {
    int _x;
    int _y_start;
    int _y_end;
  };
  struct Dot
  {
    int _x;
    int _y;
    int _y_old;
    int valid;
    int valid_old;
  } dot[15];
  for (int i = 0; i < 15; i++) // init dot
  {
    dot[i]._x = i;
    dot[i]._y = 80;
    dot[i]._y_old = 80;
    dot[i].valid = 0;
    dot[i].valid_old = 0;
  }
  int life = 9;
  int score = 0;
  LCD_ShowString(0, 0, "Score:", 65535);
  LCD_ShowString(0, 20, "Life:", 65535);
  struct Ball ball = {15, 80, 80, 1, 15, -3, 0};
  LCD_DrawPoint_big(ball._x, ball._y, get_color(ball.unstop));
  draw_fun(life, score);
  int rand_num1 = rand() % 10;
  struct Wall wall1 = {78, 60 + rand_num1, rand_num1 + 60 + get_horizon(choose_number)};
  rand_num1 = rand() % 10;
  struct Wall wall2 = {118, 60 + rand_num1, rand_num1 + 60 + get_horizon(choose_number)};
  uint64_t start_mtime, delta_mtime;
  while (1)
  {
    start_mtime = get_timer_value();
    // Wall
    {
      LCD_DrawLine(wall1._x, wall1._y_start, wall1._x, 40, 0);
      LCD_DrawLine(wall1._x, wall1._y_end, wall1._x, 160, 0);
      wall1._x--;
      if (wall2._x >= 79)
      {
        wall2._x--;
      }
      else
      {
        LCD_DrawLine(wall2._x, wall2._y_start, wall2._x, 40, 0);
        LCD_DrawLine(wall2._x, wall2._y_end, wall2._x, 157, 0);
        wall2._x--;
      }
      if (wall1._x <= 0)
      {
        LCD_DrawLine(wall1._x, wall1._y_start, wall1._x, 40, 0);
        LCD_DrawLine(wall1._x, wall1._y_end, wall1._x, 157, 0);
        wall1._x = 78;
        rand_num1 = rand() % 10;
        wall1._y_start = 60 + rand_num1;
        wall1._y_end = rand_num1 + 60 + get_horizon(choose_number);
      }

      if (wall2._x <= 0)
      {
        LCD_DrawLine(wall2._x, wall2._y_start, wall2._x, 40, 0);
        LCD_DrawLine(wall2._x, wall2._y_end, wall2._x, 157, 0);
        wall2._x = 78;
        rand_num1 = rand() % 10;
        wall2._y_start = rand_num1 + 60;
        wall2._y_end = rand_num1 + 60 + get_horizon(choose_number);
      }
    }

    // Ball
    {
      if (ball.speed == 3)
      {
        ball._y_old = ball._y;
        if (choose_number == 1)
        ball._y -= 4;
        else if (choose_number == 2)
          ball._y -= 5;
        else if (choose_number == 3)
          ball._y -= 6;
      }
      else if (ball.speed == 2)
      {
        ball._y_old = ball._y;
        ball._y -= 2;
      }
      else if (ball.speed == 1)
      {
        ball._y_old = ball._y;
        ball._y -= 1;
      }
      else if (ball.speed == -1)
      {
        ball._y_old = ball._y;
        ball._y += 1;
      }
      else if (ball.speed == -2)
      {
        ball._y_old = ball._y;
        ball._y += 2;
      }
      else if (ball.speed == -3)
      {
        ball._y_old = ball._y;
        if (choose_number == 1)
        ball._y += 4;
        else if (choose_number == 2)
          ball._y += 5;
        else if (choose_number == 3)
          ball._y += 6;
      }
      if (ball.is_dead)
      {
        ball.is_dead = 0;
      }
      if (push_button())
      {
        ball.speed = 3;
      }
      else
      {
        ball.speed--;
        if (ball.speed < -3)
        {
          ball.speed = -3;
        }
      }
      ball.unstop_tick--;
      if (ball.unstop_tick == 0)
      {
        ball.unstop = 0;
        ball.unstop_tick = 15;
      }

      if (!ball.unstop)
      {
        if (ball._y <= 40 || ball._y >= 160)
        {
          life--;
          draw_fun(life, score);
          ball._y = 80;
          ball.unstop = 1;
          ball.unstop_tick = 15;
          ball.is_dead = 1;
          ball.speed = -3;
        }
        else
        {
          if (ball._x == wall1._x)
          {
            if (ball._y <= wall1._y_end && ball._y >= wall1._y_start)
            {
              score++;
              draw_fun(life, score);
            }
            else
            {
              life--;
              draw_fun(life, score);
              ball._y = 80;
              ball.unstop = 1;
              ball.unstop_tick = 15;
              ball.is_dead = 1;
              ball.speed = -3;
            }
          }
          if (ball._x == wall2._x)
          {
            if (ball._y <= wall2._y_end && ball._y >= wall2._y_start)
            {
              score++;
              draw_fun(life, score);
            }
            else
            {
              life--;
              draw_fun(life, score);
              ball._y = 80;
              ball.unstop = 1;
              ball.unstop_tick = 15;
              ball.is_dead = 1;
              ball.speed = -3;
            }
          }
        }
      }
      else
      {
        if (ball._y <= 40 || ball._y >= 160)
        {
          ball._y = 80;
          ball.unstop = 1;
          ball.unstop_tick = 15;
          ball.is_dead = 1;
          ball.speed = -3;
        }
      }
      LCD_DrawPoint_big(ball._x, ball._y_old, 0);
      LCD_DrawPoint_big(ball._x, ball._y, get_color(ball.unstop));
    }
    
    // Dot
    {
      for (int i = 14; i >= 0; i--)
      {
        dot[i]._y_old = dot[i]._y;
        if (i == 14)
        {
          dot[i].valid_old = dot[i].valid;
          dot[i]._y = ball._y_old;
          if (ball.is_dead == 1)
            dot[i].valid = 0;
          else
            dot[i].valid = 1;
        }
        else
        {
          dot[i].valid_old = dot[i].valid;
          dot[i]._y = dot[i + 1]._y_old;
          if (ball.is_dead == 1)
            dot[i].valid = 0;
          else
            dot[i].valid = dot[i + 1].valid_old;
        }
      }
    }

    // Line
    {
      for (int i = 14; i >= 0; i--)
      {
        if (i == 14)
        {
          LCD_DrawLine(dot[i]._x, dot[i]._y_old, 15, ball._y_old, 0);
          if (dot[i].valid)
            LCD_DrawLine(dot[i]._x, dot[i]._y, 15, ball._y, get_color(ball.unstop));
        }
        else
        {
          LCD_DrawLine(dot[i]._x, dot[i]._y_old, dot[i + 1]._x, dot[i + 1]._y_old, 0);
          if (dot[i].valid)
            LCD_DrawLine(dot[i]._x, dot[i]._y, dot[i + 1]._x, dot[i + 1]._y, get_color(ball.unstop));
        }
      }
    }

    // Wall
    {
      LCD_DrawLine(wall1._x, wall1._y_start, wall1._x, 40, 65535);
      LCD_DrawLine(wall1._x, wall1._y_end, wall1._x, 157, 65535);
      if (wall2._x < 79)
      {
        LCD_DrawLine(wall2._x, wall2._y_start, wall2._x, 40, 65535);
        LCD_DrawLine(wall2._x, wall2._y_end, wall2._x, 157, 65535);
      }
      LCD_DrawRectangle(79, 158, 0, 40, 31);
    }

    if (life == 0)
    {
      life = 9;
    }
    if (score >= 99)
    {
      break;
    }
    do
    {
      delta_mtime = get_timer_value() - start_mtime;
    } while (delta_mtime < (SystemCoreClock / 4000.0 * 50));
  }
  return 0;
}
