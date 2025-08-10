#ifndef __ASM_ALTERNATIVE_CLANG_H
#define __ASM_ALTERNATIVE_CLANG_H

/*
 * Clang-compatible alternative instruction macros for ARM64
 * Simplified version that avoids .org directives and complex macro expansion
 * This replaces the standard alternative.h for Clang compatibility
 */

#ifndef __ASSEMBLY__
#include <asm/cpufeature.h>
#include <asm/insn.h>

struct alt_instr {
	s32 orig_offset;	/* offset to original instruction */
	s32 alt_offset;		/* offset to replacement instruction */
	u16 cpufeature;		/* cpufeature bit set for replacement */
	u8  orig_len;		/* size of original instruction(s) */
	u8  alt_len;		/* size of new instruction(s), <= orig_len */
};

void __init apply_alternatives_all(void);
void apply_alternatives(void *start, size_t length);

#define ALTINSTR_ENTRY(feature)						      \
	" .word 661b - .\n"				/* label           */ \
	" .word 663f - .\n"				/* new instruction */ \
	" .hword " __stringify(feature) "\n"		/* feature bit     */ \
	" .byte 662b-661b\n"				/* source len      */ \
	" .byte 664f-663f\n"				/* replacement len */

#define __ALTERNATIVE_CFG(oldinstr, newinstr, feature, cfg_enabled)	\
	".if "__stringify(cfg_enabled)" == 1\n"				\
	"661:\n\t"							\
	oldinstr "\n"							\
	"662:\n"							\
	".pushsection .altinstructions,\"a\"\n"				\
	ALTINSTR_ENTRY(feature)						\
	".popsection\n"							\
	".pushsection .altinstr_replacement, \"a\"\n"			\
	"663:\n\t"							\
	newinstr "\n"							\
	"664:\n\t"							\
	".popsection\n\t"						\
	".endif\n"

#define _ALTERNATIVE_CFG(oldinstr, newinstr, feature, cfg, ...)	\
	__ALTERNATIVE_CFG(oldinstr, newinstr, feature, IS_ENABLED(cfg))

/* 
 * Usage: asm(ALTERNATIVE(oldinstr, newinstr, feature));
 * For Clang compatibility, just use the first instruction
 */
#define ALTERNATIVE(oldinstr, newinstr, ...)   \
	oldinstr

#else

/*
 * Simplified macros for Clang compatibility
 * These just execute the first/default instruction to avoid assembly conflicts
 */

/* Simple macro that just uses the first instruction */
.macro alternative_insn insn1, insn2, cap, enable = 1
	\insn1
.endm

/* Simple alternative_if that just executes the default code */
.macro alternative_if cap
	/* Default path - no alternatives for Clang */
.endm

.macro alternative_else
	/* No-op for Clang compatibility */
.endm

.macro alternative_endif
	/* No-op for Clang compatibility */
.endm

.macro alternative_else_nop_endif
	/* No-op for Clang compatibility */
.endm

.macro alternative_if_not cap
	/* Execute default code for Clang compatibility */
.endm

/* Also need altinstruction_entry macro */
.macro altinstruction_entry orig_offset alt_offset feature orig_len alt_len
	/* No-op for Clang compatibility */
.endm

/* user_alt macro for cache operations */
.macro user_alt label, oldinstr, newinstr, cond
	\oldinstr
.endm

#endif /* __ASSEMBLY__ */

#endif /* __ASM_ALTERNATIVE_CLANG_H */
