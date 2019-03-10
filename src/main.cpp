/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#include "Led.h"
#include "Button.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F1 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[]) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	Led led1(GPIOB, GPIO_Pin_9);
	Led led2(GPIOB, GPIO_Pin_8);
	Led led3(GPIOB, GPIO_Pin_5);

	Button btn2(GPIOA, GPIO_Pin_2);
	Button btn3(GPIOA, GPIO_Pin_3);

	bool btn2in, btn3in;
	unsigned int ledTime = 250000;
	unsigned int currentTime = 0;

	while (1) {
		currentTime += 1;

		if (currentTime >= ledTime) {
			led1.invert();
			led2.invert();
			led3.invert();
			currentTime = 0;
		}

		btn2in = btn2.read();
		btn3in = btn3.read();

		if (btn2in) {
			if (ledTime < 2500000) {
				ledTime += 1;
			}
		}
		else if (btn3in) {
			if (ledTime > 0) {
				ledTime -= 1;
			}
		}



//		if (btn2in && btn3in) {
//			led1.on();
//			led2.off();
//			led3.off();
//		}
//		else if (btn3in) {
//			led1.off();
//			led2.on();
//			led3.on();
//		}
//		else {
//			led1.off();
//			led2.off();
//			led3.off();
//		}
	}
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
