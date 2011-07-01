#ifndef	__UTIL_H__
#define	__UTIL_H__

extern unsigned char	IsBufferEmpty(RingBuf * pBuf);
extern unsigned char	IsBufferFull(RingBuf * pBuf);
extern int				CountBuffer(RingBuf * pBuf);
extern void 			PushBuffer(RingBuf * pBuf, unsigned char byte);
extern unsigned char	PopBuffer(RingBuf * pBuf);
extern unsigned char	TopBuffer(RingBuf * pBuf);

extern void				TurnOnYellowLED();
extern void				TurnOffYellowLED();
extern void				ToggleYellowLED();
#endif
