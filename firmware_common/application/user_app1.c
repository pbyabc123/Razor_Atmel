/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
1. Copy both user_app1.c and user_app1.h to the Application directory
2. Rename the files yournewtaskname.c and yournewtaskname.h
3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
7. Add a call to YourNewTaskNameInitialize() in the init section of main
8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
-

Promises:
- 
*/
void UserApp1Initialize(void)
{    //static u8 UserApp_au8MyName[] = "LCD Example";
  //LCDMessage(LINE1_START_ADDR, "Hello");
  //LCDMessage(LINE2_START_ADDR, "0");
  //LCDMessage(LINE2_START_ADDR + 6, "1");
  //LCDMessage(LINE2_START_ADDR + 13, "2");
  //LCDMessage(LINE2_END_ADDR, "3");
  LCDCommand(LCD_CLEAR_CMD);
  PWMAudioSetFrequency(BUZZER1, 500);
  //LCDCommand(LCD_HOME_CMD);  
  
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }
  
} /* end UserApp1Initialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();
  
} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
u8 t[]={0x50,0x31,0x20,0x20,0x20,0xB4,0xB7,0xBB,0xB2,0xC3,0xA8,0xDD,0xB8,0xDE,0x20,0x20,0x20,0x20,0x50,0x32,0x00,0xde};
u8 s[]={"****"};
u8 state=0;
unsigned long long bbb=0;
static void UserApp1SM_Idle(void)
{
  static char now=10;
  static bool bCursorOn = FALSE;
  
  switch(state){
  case 0:
    if(WasButtonPressed(BUTTON0))
    {
      ButtonAcknowledge(BUTTON0);
      LCDCommand(LCD_CLEAR_CMD);
      LCDMessage(LINE1_START_ADDR, t);
      
      //now++;
      if(now<19){
        now++;
        LCDMessage(0x40+now, "*");
      }else{
        
        LCDCommand(LCD_CLEAR_CMD);
        LCDMessage(0x03, "PLAYER 1 WIN!");
        state=1;
        break;
      }
      
    }
    if(WasButtonPressed(BUTTON3))
    {
      ButtonAcknowledge(BUTTON3);
      LCDCommand(LCD_CLEAR_CMD);
      LCDMessage(LINE1_START_ADDR, t);
      
      if(now>0){
        now--;
        LCDMessage(0x40+now, "*");
      }else{
        LCDCommand(LCD_CLEAR_CMD);
        LCDMessage(0x03, "PLAYER 2 WIN!");
        state=1;
        break;
      }  
    }
    break;
  case 1:
    bbb++;
    if(bbb>=500){
      bbb=0;
      state=2;
      break;
    }
    LedOn(WHITE);
    LedOn(PURPLE);
    LedOn(ORANGE);
    LedOn(RED);
    PWMAudioOn(BUZZER1);
    //LedBlink(RED, LED_2HZ);
    break;
  case 2:
    bbb++;
    if(bbb>=500){
      bbb=0;
      state=3;
      break;
    }
    LedOff(WHITE);
    LedOff(PURPLE);
    LedOff(ORANGE);
    LedOff(RED);
    PWMAudioOff(BUZZER1);
    break;
  case 3:
    bbb++;
    if(bbb>=500){
      bbb=0;
      state=4;
      break;
    }
    LedOn(BLUE);
    LedOn(CYAN);
    LedOn(GREEN);
    LedOn(YELLOW);
    PWMAudioSetFrequency(BUZZER1, 800);
    PWMAudioOn(BUZZER1);
    break;
    //LCDMessage(0x03, "PLAYER 1 WIN!");
    
  case 4:
    bbb++;
    if(bbb>=500){
      bbb=0;
      state=5;
      break;
    }
    LedOff(BLUE);
    LedOff(CYAN);
    LedOff(GREEN);
    LedOff(YELLOW);
    PWMAudioOff(BUZZER1);
    break; 
  case 5:
    bbb++;
    if(bbb>=500){
      bbb=0;
      state=6;
      break;
    }
    LedOn(WHITE);
    LedOn(PURPLE);
    LedOn(BLUE);
    LedOn(CYAN);
    LedOn(GREEN);
    LedOn(YELLOW);
    LedOn(ORANGE);
    LedOn(RED);
    PWMAudioSetFrequency(BUZZER1, 1100);
    PWMAudioOn(BUZZER1);
    //LedBlink(RED, LED_2HZ);
    break;
  case 6:
    bbb++;
    if(bbb>=500){
      bbb=0;
      state=1;
      break;
    }
    LedOff(WHITE);
    LedOff(PURPLE);
    LedOff(BLUE);
    LedOff(CYAN);
    LedOff(GREEN);
    LedOff(YELLOW);
    LedOff(ORANGE);
    LedOff(RED);
    PWMAudioOff(BUZZER1);
    break; 
    
    
    
  }
  
  ;;;;;;;;;;;;;;;
  
  
  
  //PWMAudioOn(BUZZER1);
  
  
  
} /* end UserApp1SM_Idle() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
