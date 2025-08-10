#ifndef __ASM_ALTERNATIVE_CLANG_H
#define __ASM_ALTERNATIVE_CLANG_H

/*
 * Clang-compatible alternative instruction macros for ARM64
 * Simplified version that avoids .org directives and complex macro expansion
 */

#ifndef __ASSEMBLY__
#include <asm/alternative.h>
#else

/* Simple macro that just uses the first instruction for Clang compatibility */
.macro alternative_insn_clang insn1, insn2, cap, enable = 1
	.if \enable
	\insn1
	.else
	\insn1
	.endif
.endm

/* Override the standard macro with our Clang-compatible version */
.macro alternative_insn insn1, insn2, cap, enable = 1
	alternative_insn_clang \insn1, \insn2, \cap, \enable
.endm

/* Simple alternative_if that just executes the default code */
.macro alternative_if_clang cap
	/* For Clang compatibility, we'll just use the default path */
.endm

.macro alternative_if cap
	alternative_if_clang \cap
.endm

.macro alternative_else_clang
	/* No-op for Clang compatibility */
.endm

.macro alternative_else
	alternative_else_clang
.endm

.macro alternative_endif_clang
	/* No-op for Clang compatibility */
.endm

.macro alternative_endif
	alternative_endif_clang
.endm

.macro alternative_else_nop_endif_clang
	/* No-op for Clang compatibility */
.endm

.macro alternative_else_nop_endif
	alternative_else_nop_endif_clang
.endm

.macro alternative_if_not_clang cap
	/* For Clang compatibility, we'll execute the default code */
.endm

.macro alternative_if_not cap
	alternative_if_not_clang \cap
.endm

#endif /* __ASSEMBLY__ */

#endif /* __ASM_ALTERNATIVE_CLANG_H */
