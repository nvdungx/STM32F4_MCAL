;*******************************************************************************
; The startup code must be linked at the start of ROM which is NOT necessarily
; address zero


                  AREA    |.text|, CODE, READONLY, CODEALIGN
; Reset handler, export, could be redefine(weak)
Reset_Handler     FUNCTION
                  EXPORT  Reset_Handler  [WEAK]
                  IMPORT  SystemInit     ; import SystemInit function(C)
                  IMPORT  __main         ; import __main(call user main)

                  LDR     R0, =SystemInit
                  BLX     R0
                  LDR     R0, =__main
                  BX      R0
                  ENDFUNC