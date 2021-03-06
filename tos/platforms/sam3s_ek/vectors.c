/*
 * Copyright (c) 2009 Stanford University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the Stanford University nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL STANFORD
 * UNIVERSITY OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Startup code and interrupt and trap handlers for the SAM3U-EK board.
 *
 * @author Wanja Hofer <wanja@cs.fau.de>
 */

/* Section symbols defined in linker script
 * sam3u-ek-flash.x
 */
extern unsigned int _stext;
extern unsigned int _etext;
extern unsigned int _sdata;
extern unsigned int _edata;
extern unsigned int _svect;
extern unsigned int _evect;
extern unsigned int _sbss;
extern unsigned int _ebss;
extern unsigned int _estack;
extern unsigned int __relocate_vector;

/* main() symbol defined in RealMainP
 */
int main();

/* Start-up code called upon reset.
 * Definition see below.
 */
void __init();

/* Default handler for any IRQ or fault
 */
void DefaultHandler()
{
	// do nothing, just return
}

/* Default Hardfault Handler
 */
void DefaultHardFaultHandler()
{
    while(1) {}
}

/* Default Mpu Fault Handler
 */
void DefaultMpuFaultHandler()
{
    while(1) {}
}

/* Default Bus Fault Handler
 */
void DefaultBusFaultHandler()
{
    while(1) {}
}

/* Default Usage Fault Handler
 */
void DefaultUsageFaultHandler()
{
    while(1) {}
}

/* By default, every exception and IRQ is handled by the default handler.
 *
 * If OWN_FUNCTIONS_FOR_HANDLERS is defined, then the internal IRQ and fault
 * handlers will get a function of their own for debug purposes. Those
 * functions are provided by weak aliases; thus, a regular handler
 * definition will override this.
 */
#define OWN_FUNCTION_FOR_HANDLERS

#ifdef OWN_FUNCTION_FOR_HANDLERS
void NmiHandler() __attribute__((weak));
void MpuFaultHandler() __attribute__((weak));
void BusFaultHandler() __attribute__((weak));
void UsageFaultHandler() __attribute__((weak));
void SVCallHandler() __attribute__((weak));
void DebugHandler() __attribute__((weak));
void PendSVHandler() __attribute__((weak));
void SysTickHandler() __attribute__((weak));
void NmiHandler() { while(1) {} }
void MpuFaultHandler() { while(1) {} }
void BusFaultHandler() { while(1) {} }
void UsageFaultHandler() { while(1) {} }
void SVCallHandler() { while(1) {} }
void DebugHandler() { while(1) {} }
void PendSVHandler() { while(1) {} }
void SysTickHandler() { while(1) {} }
#else
void NmiHandler() __attribute__((weak, alias("DefaultHandler")));
void MpuFaultHandler() __attribute__((weak, alias("DefaultHandler")));
void BusFaultHandler() __attribute__((weak, alias("DefaultHandler")));
void UsageFaultHandler() __attribute__((weak, alias("DefaultHandler")));
void SVCallHandler() __attribute__((weak, alias("DefaultHandler")));
void DebugHandler() __attribute__((weak, alias("DefaultHandler")));
void PendSVHandler() __attribute__((weak, alias("DefaultHandler")));
void SysTickHandler() __attribute__((weak, alias("DefaultHandler")));
#endif

void HardFaultHandler() __attribute__((weak, alias("DefaultHardFaultHandler")));

void SupcIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void RstcIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void RtcIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void RttIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void WdtIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void PmcIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void EefcIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void UartIrqHandler() __attribute__((weak, alias("DefaultHandler"))); // Note: we removed the 0!
void Uart1IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void SmcIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void PioAIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void PioBIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void PioCIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void Usart0IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void Usart1IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void HsmciIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void Twi0IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void Twi1IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void SpiIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void SscIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void TC0IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void TC1IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void TC2IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void TC3IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void TC4IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void TC5IrqHandler() __attribute__((weak, alias("DefaultHandler")));
void AdcIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void DaccIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void PwmIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void CrccuIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void AccIrqHandler() __attribute__((weak, alias("DefaultHandler")));
void UdpIrqHandler() __attribute__((weak, alias("DefaultHandler")));

/* Stick at the top of the .text section in final binary so we can always
 *    jump back to the init routine at the top of the stack if we want */
__attribute__((section(".boot"))) unsigned int *__boot[] = {
    &_estack,
    (unsigned int *) __init,
};


__attribute__((section(".vectors"))) unsigned int *__vectors[] = {
	// Defined by Cortex-M3
	// Defined in AT91 ARM Cortex-M3 based Microcontrollers, SAM3U Series, Preliminary, p. 78
	// See also The Definitive Guide to the ARM Cortex-M3, p. 331
	&_estack,
	(unsigned int *) __init,
    (unsigned int *) NmiHandler,
    (unsigned int *) HardFaultHandler,
    (unsigned int *) MpuFaultHandler,
    (unsigned int *) BusFaultHandler,
	(unsigned int *) UsageFaultHandler,
	(unsigned int *) 0, // Reserved
	(unsigned int *) 0, // Reserved
	(unsigned int *) 0, // Reserved
	(unsigned int *) 0, // Reserved
	(unsigned int *) SVCallHandler,
	(unsigned int *) DebugHandler,
	(unsigned int *) 0, // Reserved
	(unsigned int *) PendSVHandler,
	(unsigned int *) SysTickHandler,
	// Defined by SAM3U MCU
	// Defined in AT91 ARM Cortex-M3 based Microcontrollers, SAM3U Series, Preliminary, p. 41
	(unsigned int *) SupcIrqHandler,     // 0
	(unsigned int *) RstcIrqHandler,     // 1
	(unsigned int *) RtcIrqHandler,      // 2
	(unsigned int *) RttIrqHandler,      // 3
	(unsigned int *) WdtIrqHandler,      // 4
	(unsigned int *) PmcIrqHandler,      // 5
	(unsigned int *) EefcIrqHandler,     // 6
	(unsigned int *) 0,                  // 7 Reserved
	(unsigned int *) UartIrqHandler,     // 8 We remove the 0 as the Sam3u only has one UART
	(unsigned int *) Uart1IrqHandler,    // 9
	(unsigned int *) SmcIrqHandler,      // 10
	(unsigned int *) PioAIrqHandler,     // 11
	(unsigned int *) PioBIrqHandler,     // 12
	(unsigned int *) PioCIrqHandler,     // 13
	(unsigned int *) Usart0IrqHandler,   // 14
	(unsigned int *) Usart1IrqHandler,   // 15
	(unsigned int *) 0,                  // 16
	(unsigned int *) 0,                  // 17
	(unsigned int *) HsmciIrqHandler,    // 18
	(unsigned int *) Twi0IrqHandler,     // 19
	(unsigned int *) Twi1IrqHandler,     // 20
	(unsigned int *) SpiIrqHandler,      // 21
	(unsigned int *) SscIrqHandler,      // 22
	(unsigned int *) TC0IrqHandler,      // 23
	(unsigned int *) TC1IrqHandler,      // 24
	(unsigned int *) TC2IrqHandler,      // 25
	(unsigned int *) TC3IrqHandler,      // 26
	(unsigned int *) TC4IrqHandler,      // 27
	(unsigned int *) TC5IrqHandler,      // 28
	(unsigned int *) AdcIrqHandler,      // 29
	(unsigned int *) DaccIrqHandler,     // 30
	(unsigned int *) PwmIrqHandler,      // 31
	(unsigned int *) CrccuIrqHandler,    // 32
	(unsigned int *) AccIrqHandler,      // 33
	(unsigned int *) UdpIrqHandler       // 34
};

/* Start-up code to copy data into RAM
 * and zero BSS segment
 * and call main()
 * and "exit"
 */
void __init()
{
	unsigned int *from;
	unsigned int *to;
	unsigned int *i;
	volatile unsigned int *NVIC_VTOFFR = (volatile unsigned int *) 0xe000ed08;

    if(0 && __relocate_vector)
    {
        // Configure location of IRQ vector table
        // Vector table is in the beginning of text segment / Flash 0
        i = (unsigned int *) &_svect;
        *NVIC_VTOFFR = (unsigned int) i;
        // Set TBLBASE bit since vector table located in SRAM
        *NVIC_VTOFFR |= (1 << 29);
    }

	// Copy pre-initialized data into RAM.
	// Data lies in Flash after the text segment (_etext),
	// but is linked to be at _sdata.
	// Thus, we have to copy it to that place in RAM.
	from = &_etext;
	to = &_sdata;
	while (to < &_edata) {
		*to = *from;
		to++;
		from++;
	}

	// Fill BSS data with 0
	i = &_sbss;
	while (i < &_ebss) {
		*i = 0;
		i++;
	}

	// Call main()
	main();

	// "Exit"
	while (1);
}
