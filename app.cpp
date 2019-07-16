#include "ev3api.h"
#include "app.h"
#include "Clock.h"
#include "UI.h"
#include "RunManager.h"

using namespace ev3api;

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

/* Bluetooth */
static int32_t bt_cmd = 0; /* Bluetoothコマンド 1:リモートスタート */
static FILE *bt = NULL;    /* Bluetoothファイルハンドル */

#define CMD_START '1' /* リモートスタートコマンド */

/* 関数宣言 */
Clock *clock;
UI *ui;
RunManager *runManager;
ArmMotorDriver *armMotor;

int color[4];
int black[2];
int analogAnswer = 8;

const Course course = L;

/* メインタスク */
void main_task(intptr_t unused)
{

    /* 各オブジェクトを生成・初期化する */
    clock = new Clock();
    ui = new UI();
    runManager = new RunManager(course);
    armMotor = new ArmMotorDriver();

    /* Open Bluetooth file */
    bt = ev3_serial_open_file(EV3_SERIAL_BT);
    assert(bt != NULL);

    /* Bluetooth通信タスクの起動 */
    act_tsk(BT_TASK);

    armMotor->calibration();

    ev3_led_set_color(LED_ORANGE); /* 初期化完了通知 */

    /* スタート待機 */
    while (1)
    {
        armMotor->rotateDefault();
        runManager->init();

        if (ui->isTouched())
        {
            if(course == R){
                fprintf(bt, "%d\n", 5);
            }
            break; /* タッチセンサが押された */
        }

        clock->sleep(10);
    }

    ev3_led_set_color(LED_GREEN); /* スタート通知 */

    /* Main loop */
    while (1)
    {

        if (ev3_button_is_pressed(BACK_BUTTON))
            break;

        runManager->run();

        clock->sleep(4); /* 4msec周期 */
    }

    ter_tsk(BT_TASK);
    fclose(bt);

    ext_tsk();
}

void get_color(int color_pos[4], char all_pos[256])
{
    for (int i = 0; i < 4; i++)
    {
        if (all_pos[2 * i] == '0')
        {
            color_pos[i] = all_pos[(2 * i) + 1] - 48;
        }
        else
        {
            color_pos[i] = 10 + all_pos[(2 * i) + 1] - 48;
        }
    }
}

void get_black(int black_pos[2], char all_pos[256])
{
    for (int i = 0; i < 2; i++)
    {
        black_pos[i] = all_pos[i + 8] - 48;
    }
}

void bt_task(intptr_t unused)
{
    char tmp[256];
    int count = 0;

    while (1)
    {
        uint8_t c = fgetc(bt); /* 受信 */

        if (course == L)
        {
            if (c - 48 >= 0 && c - 48 <= 7){
                analogAnswer = c - 48;
                bt_cmd = 1;
                break;
            }
        }
        else if (course == R)
        {
            if (c - 48 >= 0 && c - 48 <= 9 && count <= 9)
            {
                if (count == 0)
                {
                    snprintf(tmp, 255, "%d", c - 48);
                }
                else
                {
                    snprintf(tmp, 255, "%s%d", tmp, c - 48);
                }
                count++;
            }
            else if (count == 10)
            {
                get_color(color, tmp);
                get_black(black, tmp);
                bt_cmd = 1;
                break;
            }
        }
        fputc(c, bt); /* エコーバック */
    }
}
