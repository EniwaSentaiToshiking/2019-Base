#include "ev3api.h"
#include "app.h"
#include "Clock.h"
#include "UI.h"
#include "Block.h"
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

int cross[8];
int bonus[2];
int number = 8;

const Course course = R;

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
            fprintf(bt, "%d\n", 5);
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

        if (bt_cmd == 1)
        {
            Block &block = Block::singleton();
            block.cross1 = cross[0];
            block.cross2 = cross[1];
            block.cross3 = cross[2];
            block.cross4 = cross[3];
            block.cross5 = cross[4];
            block.cross6 = cross[5];
            block.cross7 = cross[6];
            block.cross8 = cross[7];

            block.bonus_pos = bonus[0];
            block.bonus_color = bonus[1];

            block.number = number;

            bt_cmd = -1;
        }

        runManager->run();

        clock->sleep(4); /* 4msec周期 */
    }

    ter_tsk(BT_TASK);
    fclose(bt);

    ext_tsk();
}

void get_cross(int cross_pos[8], char all_pos[256])
{
    for (int i = 1; i < 9; i++)
    {
        cross_pos[i] = all_pos[i] - 48;
    }
}

void get_bonus(int bonus_pos[2], char all_pos[256])
{
    for (int i = 9; i < 11; i++)
    {
        bonus_pos[i] = all_pos[i] - 48;
    }
}

void bt_task(intptr_t unused)
{
    char tmp[256];
    int count = 0;

    while (1)
    {   
        uint8_t c = fgetc(bt); /* 受信 */
        if (c - 48 >= 0 && c - 48 <= 9 && count <= 10)
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
        else if (count == 11)
        {
            get_cross(cross, tmp);
            get_bonus(bonus, tmp);
            number = tmp[0];
            bt_cmd = 1;

            break;
        }
        fputc(c, bt); /* エコーバック */
    }
}
