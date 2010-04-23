/**
 * @author Daniele Alessandrelli
 * @author Christian Nastasi
 */

#ifndef __INCLUDE_EE_CN_H__
#define __INCLUDE_EE_CN_H__

#ifdef __USE_CN__

//// portC
//#define BIT_CN0 Cbits.RC14
//#define BIT_CN1 PORTCbits.RC13
//// portB
//#define BIT_CN2 PORTBbits.RB0
//#define BIT_CN3 PORTBbits.RB1
//#define BIT_CN4 PORTBbits.RB2
//#define BIT_CN5 PORTBbits.RB3
//#define BIT_CN6 PORTBbits.RB4
//#define BIT_CN7 PORTBbits.RB5
//#define BIT_CN8 PORTBbits.RG6
//#define BIT_CN9 PORTBbits.RG7
//// portG
//#define BIT_CN10 PORTGbits.RG8
//#define BIT_CN11 PORTGbits.RG9
//// portB (again)
//#define BIT_CN12 PORTBbits.RB15
//// portD
//#define BIT_CN13 PORTDbits.RD4
//#define BIT_CN14 PORTDbits.RD5
//#define BIT_CN15 PORTDbits.RD6
//#define BIT_CN16 PORTDbits.RD7
//// portF
//#define BIT_CN17 PORTFbits.RF4
//#define BIT_CN18 PORTFbits.RF5
//// portD (again)
//#define BIT_CN19 PORTDbits.RD13
//#define BIT_CN20 PORTDbits.RD14
//#define BIT_CN21 PORTDbits.RD15
//// port used: B C D G F

#define CN_HANDLER(f) void CN_HANDLER_##f(void)

union EE_cn_status_bits_t {
	struct {
		unsigned CN0:1;
		unsigned CN1:1;
		unsigned CN2:1;
		unsigned CN3:1;
		unsigned CN4:1;
		unsigned CN5:1;
		unsigned CN6:1;
		unsigned CN7:1;
		unsigned CN8:1;
		unsigned CN9:1;
		unsigned CN10:1;
		unsigned CN11:1;
		unsigned CN12:1;
		unsigned CN13:1;
		unsigned CN14:1;
		unsigned CN15:1;
		unsigned CN16:1;
		unsigned CN17:1;
		unsigned CN18:1;
		unsigned CN19:1;
		unsigned CN20:1;
		unsigned CN21:1;
	};
	struct {
		unsigned w:32;
	};
};

extern union EE_cn_status_bits_t EE_cn_status_bits;

#define EE_CN_HANDLER(f) void EE_CN_HANDLER_##f(void)


#define CN0(m) pippo##m

#ifdef CN0
#define CN0_EN CN0(_EN)
#define CN0_DI CN0(_DI)

inline void CN0_EN()
{
	TRISCbits.RC14 = 1;
	EE_cn_status_bits.CN0 = PORTCbits.RC14;
	CNENbits.CN0 = 1;
}
#endif /* CN0 */

#define EE_CN_ENABLE(id) id##_EN()

#endif /* __USE_CN__ */

#endif /* __INCLUDE_EE_CN_H__ */
