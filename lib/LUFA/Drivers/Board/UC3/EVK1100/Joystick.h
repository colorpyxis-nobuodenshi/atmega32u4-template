/*
             LUFA Library
     Copyright (C) Dean Camera, 2021.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2021  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief Board specific joystick driver header for the Atmel EVK1100.
 *  \copydetails Group_Joystick_EVK1100
 *
 *  \note This file should not be included directly. It is automatically included as needed by the joystick driver
 *        dispatch header located in LUFA/Drivers/Board/Joystick.h.
 */

/** \ingroup Group_Joystick
 *  \defgroup Group_Joystick_EVK1100 EVK1100
 *  \brief Board specific joystick driver header for the Atmel EVK1100.
 *
 *  Board specific joystick driver header for the Atmel EVK1100.
 *
 *  <table>
 *    <tr><th>Left Port Pin</th><th>Up Port Pin</th><th>Right Port Pin</th><th>Down Port Pin</th><th>Press Port Pin</th></tr>
 *    <tr><td>GPIO25</td><td>GPIO26</td><td>GPIO28</td><td>GPIO27</td><td>GPIO20</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __JOYSTICK_EVK1100_H__
#define __JOYSTICK_EVK1100_H__

	/* Includes: */
		#include "../../../../Common/Common.h"

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_JOYSTICK_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Joystick.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define JOY_PORT                 0
			#define JOY_MASK                ((1UL << 28) | (1UL << 27) | (1UL << 26) | (1UL << 25) | (1UL << 20))
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Mask for the joystick being pushed in the left direction. */
			#define JOY_LEFT                  (1UL << 25)

			/** Mask for the joystick being pushed in the upward direction. */
			#define JOY_UP                    (1UL << 26)

			/** Mask for the joystick being pushed in the right direction. */
			#define JOY_RIGHT                 (1UL << 28)

			/** Mask for the joystick being pushed in the downward direction. */
			#define JOY_DOWN                  (1UL << 27)

			/** Mask for the joystick being pushed inward. */
			#define JOY_PRESS                 (1UL << 20)

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Joystick_Init(void)
			{
				AVR32_GPIO.port[JOY_PORT].gpers = JOY_MASK;
				AVR32_GPIO.port[JOY_PORT].gpers = JOY_MASK;
			};

			static inline void Joystick_Disable(void)
			{
				AVR32_GPIO.port[JOY_PORT].gperc = JOY_MASK;
				AVR32_GPIO.port[JOY_PORT].gperc = JOY_MASK;
			};

			ATTR_WARN_UNUSED_RESULT
			static inline uint32_t Joystick_GetStatus(void)
			{
				return (uint32_t)(~(AVR32_GPIO.port[JOY_PORT].pvr & JOY_MASK));
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

