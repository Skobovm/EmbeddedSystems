/*******************************************************************************
File name       : BubbleSort.s
Description     : Assembly language function to sort an array using Bubble Sort
Author          :     
Created         : 11/2/2016 by Mikhail Skobov
Revision History



*******************************************************************************/
  
  PUBLIC bubbleSort                 /* Make function name visible to linker */
  SECTION `.text`:CODE:NOROOT(1)
  THUMB

/*******************************************************************************
Function Name   : bubbleSort
Description     : Sorts an array using Bubble Sort
C Prototype     : void InitXa(int A[], int cnt, int descending)
                : Where int A[] is the array to sort
                : cnt is the size of A, and descending == 1 implies sort
                : in descending order, else sort ascending
Parameters      : R0: Address of A
                : R1: cnt, number of elements
                : R2: descending, direction of sort
Return value    : None
*******************************************************************************/
bubbleSort:
  PUSH  {R4-R7}                  ;; push the registers being used
  SUB   R1, R1, #1               ;; subtract 1 from cnt for 0-indexed value

bubbleSort_loop_reset:
  MOV   R3, #0                   ;; r3 will be tracking the current index
  MOV   R6, #0                   ;; R6 is tracking whether or not we had a swap in this pass
bubbleSort_loop:
  CMP   R3, R1                   ;; Ensure that we have not reached the end of the array
  BGE   bubbleSort_swap_check    ;; If we have reached the end, check if we swapped
  LDR   R4, [R0, R3, LSL #+2]    ;; r4 -> @(r0 [r3 * 4] on word boundary
  ADD   R3, R3, #+1              ;; Next element number
  LDR   R5, [R0, R3, LSL #+2]    ;; r5 -> @(r0 [r3 * 4] on word boundary
  SUB   R3, R3, #+1              ;; Set R3 back to current index
  
  CMP   R2, #0
  BNE   bubbleSort_descending    ;; Compare descending order        
  CMP   R4, R5                   ;; Compare ascending order
  B     bubbleSort_swap
bubbleSort_descending:
  CMP   R5, R4                   ;; Compare elements
bubbleSort_swap
  BLE   bubbleSort_no_swap       ;; Do not swap if the above conditions are true
                                 ;; Swap the elements
  STR   R5, [R0, R3, LSL #+2]    ;; Store the value if it needs to be switched
  ADD   R3, R3, #+1              ;; Next element number
  STR   R4, [R0, R3, LSL #+2]    ;; Store the value if it needs to be switched
  MOV   R6, #+1                  ;; R6 will track any swaps
  B     bubbleSort_loop
bubbleSort_no_swap:
  ADD   R3, R3, #+1
  B     bubbleSort_loop
bubbleSort_swap_check:
  CMP   R6, #0                   ;; Check to see if we have swapped
  BGT   bubbleSort_loop_reset    ;; Reset the counter
  
  POP   {R4-R7}                  ;; Restore the variables from the stack
  MOV   pc,lr                    ;; return
 
  END
