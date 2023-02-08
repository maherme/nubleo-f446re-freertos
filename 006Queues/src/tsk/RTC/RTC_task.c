/********************************************************************************************************//**
* @file RTC_task.c
*
* @brief File containing the APIs for managing the task regarding the real time clock.
*
* Public Functions:
*       - void rtc_task_handler(void* parameters)
*       - void rtc_report_callback(TimerHandle_t xTimer)
*
* @note
*       For further information about functions refer to the corresponding header file.
*/

#include "RTC_task.h"
#include "menu_cmd_task.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "timers.h"
#include "rtc_driver.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Enum for managing the states of the FSM for configuring the time
 */
typedef enum{
    RTC_HH_CONFIG,      /**< Hours configuration state */
    RTC_MM_CONFIG,      /**< Minutes configuration state */
    RTC_SS_CONFIG       /**< Seconds configuration state */
}RTC_TimeState_t;

/**
 * @brief Enum for managing the states of the FSM for configuring the date
 */
typedef enum{
    RTC_DATE_CONFIG,    /**< Date configuration state */
    RTC_MONTH_CONFIG,   /**< Month configuration state */
    RTC_DAY_CONFIG,     /**< Day of the week configuration state */
    RTC_YEAR_CONFIG     /**< Year configuration state */
}RTC_DateState_t;

/** @brief Variable for handling the queue used for printing */
extern QueueHandle_t q_print;
/** @brief Variable for storing the invalid option message */
extern const char* msg_invalid;
/** @brief Variable for storing and managing the possible states of the application */
extern state_t curr_state;
/** @brief Variable for handling the menu_task_handler task */
extern TaskHandle_t menu_task_handle;
/** @brief handler for managing the RTC timer */
extern TimerHandle_t rtc_timer;

/** @brief Message printed when the RTC date or time configuration is OK */
static const char *msg_conf = "Configuration successful\n";

/***********************************************************************************************************/
/*                                       Static Function Prototypes                                        */
/***********************************************************************************************************/

/**
 * @brief Function for processing the received RTC command
 * @param[in] cmd is a struct pointer with the received command information
 * @return None
 */
static void proc_rtc_cmd(command_s* cmd);

/**
 * @brief Function for configuring the RTC time
 * @param[in] cmd is a struct pointer with the received command information
 * @return None
 */
static void set_rtc_time(command_s* cmd);

/**
 * @brief Function for configuring the RTC date
 * @param[in] cmd is a struct pointer with the received command information
 * @return None
 */
static void set_rtc_date(command_s* cmd);

/**
 * @brief Function for enabling the RTC report
 * @param[in] cmd is a struct pointer with the received command information
 * @return None
 */
static void set_rtc_report(command_s* cmd);

/**
 * @brief Function for getting the current time and date of the RTC and sending to the print task via queue.
 * @return None
 */
static void show_time_date(void);

/**
 * @brief Function for converting an ascii number in an array to a binary number.
 * @param[in] p is a pointer to the array containing the number
 * @param[in] len is the leght of the array
 * @return The binary number
 */
static uint8_t getnumber(uint8_t* p, uint8_t len);

/**
 * @brief Function for checking if the values of time and date are valid
 * @param[in] time is a pointer to the structure containing the time information
 * @param[in] date is a pointer to the structure containing the date information
 * @return 0 is information is valid.
 *         1 is information is not valid
 */
static uint8_t validate_rtc_information(RTC_Time_t* time , RTC_Date_t* date);

/**
 * @brief Function for getting the current time and date of the RTC and sending to the ITM port using printf
 * @return None
 */
static void show_time_date_itm(void);

/***********************************************************************************************************/
/*                                       Public API Definitions                                            */
/***********************************************************************************************************/

void rtc_task_handler(void* parameters){

    const char* msg_rtc1 = "========================\n"
                           "|         RTC          |\n"
                           "========================\n";
    const char* msg_rtc2 = "Configure Time            ----> 0\n"
                           "Configure Date            ----> 1\n"
                           "Enable reporting          ----> 2\n"
                           "Exit                      ----> 3\n"
                           "Enter your choice here : ";
    uint32_t cmd_addr;
    command_s *cmd;

    for(;;){
        /* Notify wait (wait till someone notifies) */
        xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
        /* Print the menu and show current date and time information */
        xQueueSend(q_print, &msg_rtc1, portMAX_DELAY);
        show_time_date();
        xQueueSend(q_print, &msg_rtc2, portMAX_DELAY);

        while(curr_state != sMainMenu){
            /*Wait for command notification (Notify wait) */
            xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);
            cmd = (command_s*)cmd_addr;

            switch(curr_state){
                case sRtcMenu:
                    /* Process RTC menu commands */
                    proc_rtc_cmd(cmd);
                    break;
                case sRtcTimeConfig:
                    /* Get hh, mm, ss infor and configure RTC */
                    /* Take care of invalid entries */
                    set_rtc_time(cmd);
                    break;
                case sRtcDateConfig:
                    /* Get date, month, day, year info and configure RTC */
                    /* Take care of invalid entries */
                    set_rtc_date(cmd);
                    break;
                case sRtcReport:
                    /* Enable or disable RTC current time reporting over ITM printf */
                    set_rtc_report(cmd);
                    break;
                default:
                    break;
            }
        }

        /*Notify menu task */
        xTaskNotify(menu_task_handle, 0, eNoAction);
    }
}

void rtc_report_callback(TimerHandle_t xTimer){

   show_time_date_itm();
}

/***********************************************************************************************************/
/*                                       Static Function Definitions                                       */
/***********************************************************************************************************/

static void proc_rtc_cmd(command_s* cmd){

    const char *msg_rtc_hh = "Enter hour(1-12):";
    const char *msg_rtc_dd  = "Enter date(1-31):";
    const char *msg_rtc_report = "Enable time&date reporting(y/n)?: ";
    uint8_t menu_code;

    if(cmd->len == 1){
        menu_code = cmd->payload[0] - 48;
        switch(menu_code){
            case 0:
                curr_state = sRtcTimeConfig;
                xQueueSend(q_print, &msg_rtc_hh, portMAX_DELAY);
                break;
            case 1:
                curr_state = sRtcDateConfig;
                xQueueSend(q_print, &msg_rtc_dd, portMAX_DELAY);
                break;
            case 2 :
                curr_state = sRtcReport;
                xQueueSend(q_print, &msg_rtc_report, portMAX_DELAY);
                break;
            case 3 :
                curr_state = sMainMenu;
                break;
            default:
                curr_state = sMainMenu;
                xQueueSend(q_print ,&msg_invalid, portMAX_DELAY);
        }
    }
    else{
        curr_state = sMainMenu;
        xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
    }
}

static void set_rtc_time(command_s* cmd){

    const char *msg_rtc_mm = "Enter minutes(0-59):";
    const char *msg_rtc_ss = "Enter seconds(0-59):";
    static RTC_TimeState_t rtc_time_state = RTC_HH_CONFIG;
    uint8_t hour, min, sec;
    static RTC_Time_t time;

    switch(rtc_time_state){
        case RTC_HH_CONFIG:
            hour = getnumber(cmd->payload, cmd->len);
            time.HourUnits = hour % 10;
            time.HourTens = (hour - time.HourUnits)/10;
            rtc_time_state = RTC_MM_CONFIG;
            xQueueSend(q_print, &msg_rtc_mm, portMAX_DELAY);
            break;
        case RTC_MM_CONFIG:
            min = getnumber(cmd->payload , cmd->len);
            time.MinuteUnits = min % 10;
            time.MinuteTens = (min - time.MinuteUnits)/10;
            rtc_time_state = RTC_SS_CONFIG;
            xQueueSend(q_print, &msg_rtc_ss, portMAX_DELAY);
            break;
        case RTC_SS_CONFIG:
            sec = getnumber(cmd->payload, cmd->len);
            time.SecondUnits = sec % 10;
            time.SecondTens = (sec - time.SecondUnits)/10;
            if(!validate_rtc_information(&time, NULL)){
                RTC_SetTime(time);
                xQueueSend(q_print, &msg_conf, portMAX_DELAY);
                show_time_date();
            }
            else{
                xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
            }
            curr_state = sMainMenu;
            rtc_time_state = RTC_HH_CONFIG;
            break;
        default:
            break;
    }
}

static void set_rtc_date(command_s* cmd){

    const char *msg_rtc_mo  ="Enter month(1-12):";
    const char *msg_rtc_dow  = "Enter day(1-7 sun:1):";
    const char *msg_rtc_yr  = "Enter year(0-99):";
    static RTC_DateState_t rtc_date_state = RTC_HH_CONFIG;
    static RTC_Date_t date;
    uint8_t d, month, day, year;

    switch(rtc_date_state){
        case RTC_DATE_CONFIG:
            d = getnumber(cmd->payload, cmd->len);
            date.DateUnits = d % 10;
            date.DateTens = (d -date.DateUnits)/10;
            rtc_date_state = RTC_MONTH_CONFIG;
            xQueueSend(q_print, &msg_rtc_mo, portMAX_DELAY);
            break;
        case RTC_MONTH_CONFIG:
            month = getnumber(cmd->payload, cmd->len);
            date.MonthUnits = month % 10;
            date.MonthTens = (month - date.MonthUnits)/10;
            rtc_date_state = RTC_DAY_CONFIG;
            xQueueSend(q_print, &msg_rtc_dow, portMAX_DELAY);
            break;
        case RTC_DAY_CONFIG:
            day = getnumber(cmd->payload, cmd->len);
            date.WeekDayUnits = day;
            rtc_date_state = RTC_YEAR_CONFIG;
            xQueueSend(q_print, &msg_rtc_yr, portMAX_DELAY);
            break;
        case RTC_YEAR_CONFIG:
            year = getnumber(cmd->payload, cmd->len);
            date.YearUnits = year % 10;
            date.YearTens = (year - date.YearUnits)/10;
            if(!validate_rtc_information(NULL, &date)){
                RTC_SetDate(date);
                xQueueSend(q_print,&msg_conf, portMAX_DELAY);
                show_time_date();
            }
            else{
                xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
            }
            curr_state = sMainMenu;
            rtc_date_state = RTC_DATE_CONFIG;
            break;
        default:
            break;
    }
}

static void set_rtc_report(command_s* cmd){

    if(cmd->len == 1){
        if(cmd->payload[0] == 'y'){
            if(xTimerIsTimerActive(rtc_timer) == pdFALSE)
                xTimerStart(rtc_timer, portMAX_DELAY);
        }
        else if(cmd->payload[0] == 'n'){
            xTimerStop(rtc_timer, portMAX_DELAY);
        }
        else{
            xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
        }
    }
    else{
        xQueueSend(q_print, &msg_invalid, portMAX_DELAY);
    }
    curr_state = sMainMenu;
}

static void show_time_date(void){

    static char showtime[50];
    static char showdate[40];
    static char *current_time = showtime;
    static char *current_date = showdate;
    const char* pm_am = NULL;
    const char pm[3] = {'P', 'M', '\0'};
    const char am[3] = {'A', 'M', '\0'};
    RTC_Time_t time = {0};
    RTC_Date_t date = {0};

    memset(&date, 0, sizeof(date));
    memset(&time, 0, sizeof(time));

    /* Wait until the RTC time and date register are synchronized */
    while(!RTC_GetRSF());
    /* Get the RTC current Time */
    RTC_GetTime(&time);
    /* Get the RTC current Date */
    RTC_GetDate(&date);

    if(time.PM){
        pm_am = pm;
    }
    else{
        pm_am = am;
    }

    /* Display time Format : hh:mm:ss [AM/PM] */
    sprintf((char*)showtime, "%s:\t%d%d:%d%d:%d%d [%s]\n" ,
            "\nCurrent Time&Date",
            time.HourTens, time.HourUnits,
            time.MinuteTens, time.MinuteUnits,
            time.SecondTens, time.SecondUnits,
            pm_am);
    xQueueSend(q_print, &current_time, portMAX_DELAY);

    /* Display date Format : date-month-year */
    sprintf((char*)showdate, "%d%d-%d%d-%d%d\n",
            date.YearTens, date.YearUnits,
            date.MonthTens, date.MonthUnits,
            date.DateTens, date.DateUnits);
    xQueueSend(q_print, &current_date, portMAX_DELAY);
}

static uint8_t getnumber(uint8_t* p, uint8_t len){

    uint8_t value;

    if(len > 1)
        value =  (((p[0]-48)*10) + (p[1]-48));
    else
        value = p[0] - 48;

    return value;
}

static uint8_t validate_rtc_information(RTC_Time_t* time , RTC_Date_t* date){

    uint8_t temp = 0;

    if(time){
        temp = time->HourTens*10 + time->HourUnits;
        if(temp > 12)
            return 1;
        temp = time->MinuteTens*10 + time->MinuteUnits;
        if(temp > 59)
            return 1;
        temp = time->SecondTens*10 + time->SecondUnits;
        if(temp > 59)
            return 1;
    }

    if(date){
        temp = date->YearTens*10 + date->YearUnits;
        if(temp > 99)
            return 1;
        temp = date->MonthTens*10 + date->MonthUnits;
        if(temp > 12)
            return 1;
        temp = date->DateTens*10 + date->DateUnits;
        if(temp > 31)
            return 1;
        if(date->WeekDayUnits > 7)
            return 1;
    }

    return 0;
}

static void show_time_date_itm(void){

    const char pm[3] = {'P', 'M', '\0'};
    const char am[3] = {'A', 'M', '\0'};
    const char* pm_am = NULL;
    RTC_Date_t date;
    RTC_Time_t time;

    memset(&date, 0, sizeof(date));
    memset(&time, 0, sizeof(time));

    /* Get the RTC current Time */
    RTC_GetTime(&time);
    /* Get the RTC current Date */
    RTC_GetDate(&date);

    if(time.PM){
        pm_am = pm;
    }
    else{
        pm_am = am;
    }

    /* Display time Format : hh:mm:ss [AM/PM] */
    printf("%s:\t%d%d:%d%d:%d%d [%s]\n" ,
           "\nCurrent Time&Date",
           time.HourTens, time.HourUnits,
           time.MinuteTens, time.MinuteUnits,
           time.SecondTens, time.SecondUnits,
           pm_am);

    /* Display date Format : date-month-year */
    printf("%d%d-%d%d-%d%d\n",
           date.YearTens, date.YearUnits,
           date.MonthTens, date.MonthUnits,
           date.DateTens, date.DateUnits);
}
