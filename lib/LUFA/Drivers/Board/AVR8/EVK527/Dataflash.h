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
 *  \brief Board specific Dataflash driver header for the Atmel EVK527.
 *  \copydetails Group_Dataflash_EVK527
 *
 *  \note This file should not be included directly. It is automatically included as needed by the dataflash driver
 *        dispatch header located in LUFA/Drivers/Board/Dataflash.h.
 */

/** \ingroup Group_Dataflash
 *  \defgroup Group_Dataflash_EVK527 EVK527
 *  \brief Board specific Dataflash driver header for the Atmel EVK527.
 *
 *  Board specific Dataflash driver header for the Atmel EVK527.
 *
 *  <table>
 *    <tr><th>Name</th><th>Info</th><th>Select Pin</th><th>SPI Port</th></tr>
 *    <tr><td>DATAFLASH_CHIP1</td><td>AT45DB321C (4MB)</td><td>PORTE.6</td><td>SPI0</td></tr>
 *  </table>
 *
 *  @{
 */

#ifndef __DATAFLASH_EVK527_H__
#define __DATAFLASH_EVK527_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../../../Misc/AT45DB321C.h"
		#include "../../../Peripheral/SPI.h"

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_DATAFLASH_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Dataflash.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define DATAFLASH_CHIPCS_MASK                DATAFLASH_CHIP1
			#define DATAFLASH_CHIPCS_DDR                 DDRE
			#define DATAFLASH_CHIPCS_PORT                PORTE
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Constant indicating the total number of dataflash ICs mounted on the selected board. */
			#define DATAFLASH_TOTALCHIPS                 1

			/** Mask for no dataflash chip selected. */
			#define DATAFLASH_NO_CHIP                    0

			/** Mask for the first dataflash chip selected. */
			#define DATAFLASH_CHIP1                      (1 << 6)

			/** Internal main memory page size for the board's dataflash IC. */
			#define DATAFLASH_PAGE_SIZE                  512

			/** Total number of pages inside the board's dataflash IC. */
			#define DATAFLASH_PAGES                      8192

		/* Inline Functions: */
			/** Initializes the dataflash driver so that commands and data may be sent to an attached dataflash IC.
			 *  The appropriate SPI interface will be automatically configured.
			 */
			static inline void Dataflash_Init(void)
			{
				DATAFLASH_CHIPCS_DDR  |= DATAFLASH_CHIPCS_MASK;
				DATAFLASH_CHIPCS_PORT |= DATAFLASH_CHIPCS_MASK;

				SPI_Init(SPI_SPEED_FCPU_DIV_2 | SPI_ORDER_MSB_FIRST | SPI_SCK_LEAD_FALLING | SPI_SAMPLE_TRAILING | SPI_MODE_MASTER);
			}

			/** Sends a byte to the currently selected dataflash IC, and returns a byte from the dataflash.
			 *
			 *  \param[in] Byte  Byte of data to send to the dataflash
			 *
			 *  \return Last response byte from the dataflash
			 */
			ATTR_ALWAYS_INLINE
			static inline uint8_t Dataflash_TransferByte(const uint8_t Byte)
			{
				return SPI_TransferByte(Byte);
			}

			/** Sends a byte to the currently selected dataflash IC, and ignores the next byte from the dataflash.
			 *
			 *  \param[in] Byte  Byte of data to send to the dataflash
			 */
			ATTR_ALWAYS_INLINE
			static inline void Dataflash_SendByte(const uint8_t Byte)
			{
				SPI_SendByte(Byte);
			}

			/** Sends a dummy byte to the currently selected dataflash IC, and returns the next byte from the dataflash.
			 *
			 *  \return Last response byte from the dataflash
			 */
			ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT
			static inline uint8_t Dataflash_ReceiveByte(void)
			{
				return SPI_ReceiveByte();
			}

			/** Determines the currently selected dataflash chip.
			 *
			 *  \return Mask of the currently selected Dataflash chip, either \ref DATAFLASH_NO_CHIP if no chip is selected
			 *          or a DATAFLASH_CHIPn mask (where n is the chip number).
			 */
			ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT
			static inline uint8_t Dataflash_GetSelectedChip(void)
			{
				return (~DATAFLASH_CHIPCS_PORT & DATAFLASH_CHIPCS_MASK);
			}

			/** Selects the given dataflash chip.
			 *
			 *  \param[in]  ChipMask  Mask of the Dataflash IC to select, in the form of a \c DATAFLASH_CHIPn mask (where n is
			 *              the chip number).
			 */
			ATTR_ALWAYS_INLINE
			static inline void Dataflash_SelectChip(const uint8_t ChipMask)
			{
				DATAFLASH_CHIPCS_PORT = ((DATAFLASH_CHIPCS_PORT | DATAFLASH_CHIPCS_MASK) & ~ChipMask);
			}

			/** Deselects the current dataflash chip, so that no dataflash is selected. */
			ATTR_ALWAYS_INLINE
			static inline void Dataflash_DeselectChip(void)
			{
				Dataflash_SelectChip(DATAFLASH_NO_CHIP);
			}

			/** Selects a dataflash IC from the given page number, which should range from 0 to
			 *  ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1). For boards containing only one
			 *  dataflash IC, this will select DATAFLASH_CHIP1. If the given page number is outside
			 *  the total number of pages contained in the boards dataflash ICs, all dataflash ICs
			 *  are deselected.
			 *
			 *  \param[in] PageAddress  Address of the page to manipulate, ranging from
			 *                          0 to ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1).
			 */
			static inline void Dataflash_SelectChipFromPage(const uint16_t PageAddress)
			{
				Dataflash_DeselectChip();

				if (PageAddress >= DATAFLASH_PAGES)
				  return;

				Dataflash_SelectChip(DATAFLASH_CHIP1);
			}

			/** Toggles the select line of the currently selected dataflash IC, so that it is ready to receive
			 *  a new command.
			 */
			static inline void Dataflash_ToggleSelectedChipCS(void)
			{
				uint8_t SelectedChipMask = Dataflash_GetSelectedChip();

				Dataflash_DeselectChip();
				Dataflash_SelectChip(SelectedChipMask);
			}

			/** Spin-loops while the currently selected dataflash is busy executing a command, such as a main
			 *  memory page program or main memory to buffer transfer.
			 */
			static inline void Dataflash_WaitWhileBusy(void)
			{
				Dataflash_ToggleSelectedChipCS();
				Dataflash_SendByte(DF_CMD_GETSTATUS);
				while (!(Dataflash_ReceiveByte() & DF_STATUS_READY));
				Dataflash_ToggleSelectedChipCS();
			}

			/** Sends a set of page and buffer address bytes to the currently selected dataflash IC, for use with
			 *  dataflash commands which require a complete 24-bit address.
			 *
			 *  \param[in] PageAddress  Page address within the selected dataflash IC
			 *  \param[in] BufferByte   Address within the dataflash's buffer
			 */
			static inline void Dataflash_SendAddressBytes(uint16_t PageAddress,
			                                              const uint16_t BufferByte)
			{
				Dataflash_SendByte(PageAddress >> 5);
				Dataflash_SendByte((PageAddress << 3) | (BufferByte >> 8));
				Dataflash_SendByte(BufferByte);
			}

#endif

/** @} */

