///                MentOS, The Mentoring Operating system project
/// @file   isr.h
/// @brief  Data structures concerning the Interrupt Service Routines (ISRs).
/// @copyright (c) 2019 This file is distributed under the MIT License.
/// See LICENSE.md for details.

#pragma once

#include "kernel.h"

// TODO: see interrupt_handler_t in Linux, it is quite different.
/// @brief      Interrupt handler definition.
/// @details    An interrupt handler is an interrupt service routine called
///             to manage interrupt requests, or CPU execptions.
/// @param f    An interrupt stack frame.
typedef void (*interrupt_handler_t)(pt_regs *f);

/// @brief For each exceptions isrs_init sets a default handler which
///        prints the rose exceptions and stops kernel execution.
void isrs_init();

/// @brief For each interrupt irqs_init sets a default handler which
///        prints the rose IRQ line and stops kernel execution.
void irqs_init();

/* Even if an interrupt service routine is called for exceptions and
 * interrupts, we use two distinct methods to logically setup an ISR to
 * handle theme. Tecnically speacking, exceptions are synchronous interrupts
 * generated by CPU. For an exception we have an ISR. Interrupts are
 * asynchronous events generated by PIC. Furthermore, multiple ISRs can be set
 * for a same IRQ.
 */

/// @brief                     Installs an ISR to handle an exception.
/// @param i                   Exception identifier.
/// @param handler             Exception handler.
/// @return 0                  On success, -1 otherwise.
int isr_install_handler(uint32_t i, interrupt_handler_t handler,
						char *description);

/// @brief                     Installs an ISR to handle an interrupt.
/// @param i                   Interrupt identifier.
/// @param handler             Interrupt handler.
/// @return 0                  On success, -1 otherwise.
int irq_install_handler(uint32_t i, interrupt_handler_t handler,
						char *description);

/// @brief      Method called by CPU to handle interrupts.
/// @param f    The interrupt stack frame.
extern void irq_handler(pt_regs *f);

/// @brief      Method called by CPU to handle exceptions.
/// @param f    The interrupt stack frame.
extern void isq_handler(pt_regs *f);

//==== List of exceptions generated internally by the CPU ======================
/// @brief DE Divide Error.
#define DIVIDE_ERROR 0

/// @brief DB Debug.
#define DEBUG_EXC 1

/// @brief Non Mascable Interrupt.
#define NMI_INTERRUPT 2

/// @brief BP Breakpoint.
#define BREAKPOINT 3

/// @brief OF Overflow.
#define OVERFLOW 4

/// @brief BR Bound Range Exception.
#define BOUND_RANGE_EXCEED 5

/// @brief UD Invalid OpCode Exception.
#define INVALID_OPCODE 6

/// @brief NM Device Not Available.
#define DEV_NOT_AVL 7

/// @brief DF Double Fault.
#define DOUBLE_FAULT 8

/// @brief Coprocessor Segment Overrun.
#define COPROC_SEG_OVERRUN 9

/// @brief TS Invalid TSS.
#define INVALID_TSS 10

/// @brief NP Segment Not Present.
#define SEGMENT_NOT_PRESENT 11

/// @brief SS Stack Segment Fault.
#define STACK_SEGMENT_FAULT 12

/// @brief GP General Protection.
#define GENERAL_PROTECTION 13

/// @brief PF Page Fault.
#define PAGE_FAULT 14

/// @brief XX Reserverd.
#define INT_RSV 15

/// @brief MF Floating Point.
#define FLOATING_POINT_ERR 16

/// @brief AC Alignment Check.
#define ALIGNMENT_CHECK 17

/// @brief MC Machine Check.
#define MACHINE_CHECK 18

/// @brief XF Streaming SIMD Exception.
#define SIMD_FP_EXC 19

/// @brief Virtualization Exception.
#define VIRT_EXC 20

/// @brief Reserved [21-29].
/// @brief Security Exception.
#define SECURITY_EXC 30

/// @brief Triple Fault
#define TRIPLE_FAULT 31

/// @brief System call interrupt.
#define SYSTEM_CALL 80
//==============================================================================
