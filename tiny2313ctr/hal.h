/* Automatically generated HAL from hal.xml */
/* NEVER EDIT MANUALLY */

/* Generated on: 2018-01-05 18:45:59 */

#ifndef __HAL_H__
#define __HAL_H__

#include <avr/io.h>

#define nop()                                    __asm__ __volatile__("nop")

/* CLICK -> PB5 (Output, Initially Inactive) */
#define CLICK_BIT                                5
#define CLICK_PIN                                PINB
#define CLICK_PORT                               PORTB
#define CLICK_DDR                                DDRB
#define CLICK_ModeOutput()                       CLICK_DDR |= _BV(CLICK_BIT)
#define CLICK_IsOutput()                         ((CLICK_DDR & _BV(CLICK_BIT)) != 0)
#define CLICK_SetHIGH()                          CLICK_PORT |= _BV(CLICK_BIT)
#define CLICK_SetLOW()                           CLICK_PORT &= ~_BV(CLICK_BIT)
#define CLICK_Get()                              (CLICK_PIN & _BV(CLICK_BIT))
#define CLICK_SetInactive()                      CLICK_SetLOW()
#define CLICK_SetActive()                        CLICK_SetHIGH()
#define CLICK_Toggle()                           CLICK_PORT ^= _BV(CLICK_BIT)
#define CLICK_SetConditional(condition)          if (condition) CLICK_SetActive(); else CLICK_SetInactive()
#define CLICK_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { CLICK_SetActive(); } else if (conditionoff) { CLICK_SetInactive(); } else if (conditiontoggle) { CLICK_Toggle(); }
#define CLICK_Pulse()                            { CLICK_SetActive(); CLICK_SetInactive(); }
#define CLICK_PulseNop()                         { CLICK_SetActive(); nop(); CLICK_SetInactive(); }
#define CLICK_IsInactive()                       (CLICK_Get() == 0)
#define CLICK_IsActive()                         (CLICK_Get() != 0)
#define CLICK_Init()                             { CLICK_SetInactive(); CLICK_ModeOutput(); }

/* LEDY -> PB4 (Output, Initially Inactive) */
#define LEDY_BIT                                 4
#define LEDY_PIN                                 PINB
#define LEDY_PORT                                PORTB
#define LEDY_DDR                                 DDRB
#define LEDY_ModeOutput()                        LEDY_DDR |= _BV(LEDY_BIT)
#define LEDY_IsOutput()                          ((LEDY_DDR & _BV(LEDY_BIT)) != 0)
#define LEDY_SetHIGH()                           LEDY_PORT |= _BV(LEDY_BIT)
#define LEDY_SetLOW()                            LEDY_PORT &= ~_BV(LEDY_BIT)
#define LEDY_Get()                               (LEDY_PIN & _BV(LEDY_BIT))
#define LEDY_SetInactive()                       LEDY_SetLOW()
#define LEDY_SetActive()                         LEDY_SetHIGH()
#define LEDY_Toggle()                            LEDY_PORT ^= _BV(LEDY_BIT)
#define LEDY_SetConditional(condition)           if (condition) LEDY_SetActive(); else LEDY_SetInactive()
#define LEDY_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { LEDY_SetActive(); } else if (conditionoff) { LEDY_SetInactive(); } else if (conditiontoggle) { LEDY_Toggle(); }
#define LEDY_Pulse()                             { LEDY_SetActive(); LEDY_SetInactive(); }
#define LEDY_PulseNop()                          { LEDY_SetActive(); nop(); LEDY_SetInactive(); }
#define LEDY_IsInactive()                        (LEDY_Get() == 0)
#define LEDY_IsActive()                          (LEDY_Get() != 0)
#define LEDY_Init()                              { LEDY_SetInactive(); LEDY_ModeOutput(); }

/* SWITCH -> PB3 (Input, Initially Pullup On, Active-Low) */
#define SWITCH_BIT                               3
#define SWITCH_PIN                               PINB
#define SWITCH_PORT                              PORTB
#define SWITCH_DDR                               DDRB
#define SWITCH_SetPullupActive()                 SWITCH_PORT |= _BV(SWITCH_BIT)
#define SWITCH_SetPullupInactive()               SWITCH_PORT &= ~_BV(SWITCH_BIT)
#define SWITCH_ModeInput()                       SWITCH_DDR &= ~_BV(SWITCH_BIT)
#define SWITCH_IsInput()                         ((SWITCH_DDR & _BV(SWITCH_BIT)) == 0)
#define SWITCH_Get()                             (SWITCH_PIN & _BV(SWITCH_BIT))
#define SWITCH_GetBit()                          (SWITCH_Get() >> SWITCH_BIT)
#define SWITCH_IsInactive()                      (SWITCH_Get() != 0)
#define SWITCH_IsActive()                        (SWITCH_Get() == 0)
#define SWITCH_Init()                            { SWITCH_SetPullupActive(); SWITCH_ModeInput(); }

/* EVENT -> PD2 (Input, Initially Pullup On) */
#define EVENT_BIT                                2
#define EVENT_PIN                                PIND
#define EVENT_PORT                               PORTD
#define EVENT_DDR                                DDRD
#define EVENT_SetPullupActive()                  EVENT_PORT |= _BV(EVENT_BIT)
#define EVENT_SetPullupInactive()                EVENT_PORT &= ~_BV(EVENT_BIT)
#define EVENT_ModeInput()                        EVENT_DDR &= ~_BV(EVENT_BIT)
#define EVENT_IsInput()                          ((EVENT_DDR & _BV(EVENT_BIT)) == 0)
#define EVENT_Get()                              (EVENT_PIN & _BV(EVENT_BIT))
#define EVENT_GetBit()                           (EVENT_Get() >> EVENT_BIT)
#define EVENT_IsInactive()                       (EVENT_Get() == 0)
#define EVENT_IsActive()                         (EVENT_Get() != 0)
#define EVENT_Init()                             { EVENT_SetPullupActive(); EVENT_ModeInput(); }

/* TX -> PD1 (Output, Initially Inactive) */
#define TX_BIT                                   1
#define TX_PIN                                   PIND
#define TX_PORT                                  PORTD
#define TX_DDR                                   DDRD
#define TX_ModeOutput()                          TX_DDR |= _BV(TX_BIT)
#define TX_IsOutput()                            ((TX_DDR & _BV(TX_BIT)) != 0)
#define TX_SetHIGH()                             TX_PORT |= _BV(TX_BIT)
#define TX_SetLOW()                              TX_PORT &= ~_BV(TX_BIT)
#define TX_Get()                                 (TX_PIN & _BV(TX_BIT))
#define TX_SetInactive()                         TX_SetLOW()
#define TX_SetActive()                           TX_SetHIGH()
#define TX_Toggle()                              TX_PORT ^= _BV(TX_BIT)
#define TX_SetConditional(condition)             if (condition) TX_SetActive(); else TX_SetInactive()
#define TX_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { TX_SetActive(); } else if (conditionoff) { TX_SetInactive(); } else if (conditiontoggle) { TX_Toggle(); }
#define TX_Pulse()                               { TX_SetActive(); TX_SetInactive(); }
#define TX_PulseNop()                            { TX_SetActive(); nop(); TX_SetInactive(); }
#define TX_IsInactive()                          (TX_Get() == 0)
#define TX_IsActive()                            (TX_Get() != 0)
#define TX_Init()                                { TX_SetInactive(); TX_ModeOutput(); }

/* RX -> PD0 (Input, Initially Pullup On) */
#define RX_BIT                                   0
#define RX_PIN                                   PIND
#define RX_PORT                                  PORTD
#define RX_DDR                                   DDRD
#define RX_SetPullupActive()                     RX_PORT |= _BV(RX_BIT)
#define RX_SetPullupInactive()                   RX_PORT &= ~_BV(RX_BIT)
#define RX_ModeInput()                           RX_DDR &= ~_BV(RX_BIT)
#define RX_IsInput()                             ((RX_DDR & _BV(RX_BIT)) == 0)
#define RX_Get()                                 (RX_PIN & _BV(RX_BIT))
#define RX_GetBit()                              (RX_Get() >> RX_BIT)
#define RX_IsInactive()                          (RX_Get() == 0)
#define RX_IsActive()                            (RX_Get() != 0)
#define RX_Init()                                { RX_SetPullupActive(); RX_ModeInput(); }

#define initHAL() {\
		CLICK_Init();\
		LEDY_Init();\
		SWITCH_Init();\
		EVENT_Init();\
		TX_Init();\
		RX_Init();\
}

#endif
