#if 0
.global setup
.global loop

#define UDREn 5

setup:


loop:


USART_Init:
  ; Set baud rate
  out   UBRRnH, r17
  out   UBRRnL, r16
  ; Enable receiver and transmitter
  ldi   r16, (1<<RXENn)|(1<<TXENn)
  out   UCSRnB,r16
  ; Set frame format: 8data, 2stop bit
  ldi   r16, (1<<USBSn)|(3<<UCSZn0)
  out   UCSRnC,r16
ret


USART_Transmit:
  ; Wait for empty transmit buffer
  sbis UCSRnA,UDREn
  rjmp USART_Transmit
  ; Put data (r16) into buffer, sends the data
  out   UDRn,r16
  ret
#endif
