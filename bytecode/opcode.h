#ifndef _OPCODE_H_
#define _OPCODE_H_

#define coercePrims()					\
	coerce (Real32, Real64, Real32, Real64)		\
	coerce (Real32, Word32, Real32, WordS32)	\
	coerce (Real64, Real32, Real64, Real32)		\
	coerce (Real64, Word32, Real64, WordS32)	\
	coerce (Word16, Real32, WordS16, Real32)	\
	coerce (Word16, Real64, WordS16, Real64)	\
	coerce (Word16, Word32, WordS16, Word32)	\
	coerce (Word16, Word64, WordS16, Word64)	\
	coerce (Word32, Real32, WordS32, Real32)	\
	coerce (Word32, Real64, WordS32, Real64)	\
	coerce (Word32, Word64, WordS32, Word64)	\
	coerce (Word8, Real32, WordS8, Real32)		\
	coerce (Word8, Real64, WordS8, Real64)		\
	coerce (Word8, Word16, WordS8, Word16)		\
	coerce (Word8, Word32, WordS8, Word32)		\
	coerce (Word8, Word64, WordS8, Word64)		\
	coerce (Word16, Word32, WordU16, Word32)	\
	coerce (Word16, Word64, WordU16, Word64)	\
	coerce (Word16, Word8, WordU16, Word8)		\
	coerce (Word32, Word16, WordU32, Word16)	\
	coerce (Word32, Word64, WordU32, Word64)	\
	coerce (Word32, Word8, WordU32, Word8)		\
	coerce (Word64, Word16, WordU64, Word16)	\
	coerce (Word64, Word32, WordU64, Word32)	\
	coerce (Word64, Word8, WordU64, Word8)		\
	coerce (Word8, Word16, WordU8, Word16)		\
	coerce (Word8, Word32, WordU8, Word32)		\
	coerce (Word8, Word64, WordU8, Word64)

#define loadStorePrimsOfSize(mode, ty, size)	\
	loadStoreArrayOffset (mode, ty, size)	\
	loadStoreContents (mode, ty, size)	\
	loadStoreGlobal (mode, ty, size)	\
	loadStoreOffset (mode, ty, size)	\
	loadStoreRegister (mode, ty, size)	\
	loadStoreStackOffset (mode, ty, size)

#define loadStorePrims(mode)			\
	loadStorePrimsOfSize (mode, Word, 8)	\
	loadStorePrimsOfSize (mode, Word, 16)	\
	loadStorePrimsOfSize (mode, Word, 32)	\
	loadStorePrimsOfSize (mode, Word, 64)	\
	loadStorePrimsOfSize (mode, Real, 32)	\
	loadStorePrimsOfSize (mode, Real, 64)	\
	loadStoreFrontier (mode)		\
	loadStoreStackTop (mode)

#define realPrimsOfSize(size)				\
	binary (Real##size, Real##size##_add)		\
	binary (Real##size, Real##size##_div)		\
	compare (Real##size, Real##size##_equal)	\
	compare (Real##size, Real##size##_ge)		\
	compare (Real##size, Real##size##_gt)		\
	compare (Real##size, Real##size##_le)		\
	compare (Real##size, Real##size##_lt)		\
	binary (Real##size, Real##size##_mul)		\
	ternary (Real##size, Real##size##_muladd)	\
	ternary (Real##size, Real##size##_mulsub)	\
	unary (Real##size, Real##size##_neg)		\
	unary (Real##size, Real##size##_round)		\
	binary (Real##size, Real##size##_sub)

#define wordPrimsOfSizeNoMul(size)			\
	binary (Word##size, Word##size##_add)		\
	binary (Word##size, Word##size##_andb)		\
	compare (Word##size, Word##size##_equal)	\
	compare (Word##size, WordS##size##_ge)		\
	compare (Word##size, WordU##size##_ge)		\
	compare (Word##size, WordS##size##_gt)		\
	compare (Word##size, WordU##size##_gt)		\
	compare (Word##size, WordS##size##_le)		\
	compare (Word##size, WordU##size##_le)		\
	compare (Word##size, WordS##size##_lt)		\
	compare (Word##size, WordU##size##_lt)		\
	shift (Word##size, Word##size##_lshift)		\
	binary (Word##size, WordS##size##_mul)		\
	binary (Word##size, WordU##size##_mul)		\
	unary (Word##size, Word##size##_neg)		\
	unary (Word##size, Word##size##_notb)		\
	binary (Word##size, Word##size##_orb)		\
	binary (Word##size, WordS##size##_quot)		\
	binary (Word##size, WordU##size##_quot)		\
	binary (Word##size, WordS##size##_rem)		\
	binary (Word##size, WordU##size##_rem)		\
	shift (Word##size, Word##size##_rol)		\
	shift (Word##size, Word##size##_ror)		\
	shift (Word##size, WordS##size##_rshift)	\
	shift (Word##size, WordU##size##_rshift)	\
	binary (Word##size, Word##size##_sub)		\
	binary (Word##size, Word##size##_xorb)		\
	binaryCheck (Word##size, WordS##size##_addCheck)	\
	binaryCheck (Word##size, WordU##size##_addCheck)	\
	unaryCheck (Word##size, Word##size##_negCheck)		\
	binaryCheck (Word##size, WordS##size##_subCheck)	\
	loadWord (size)

#define wordPrimsOfSize(size)					\
	wordPrimsOfSizeNoMul(size)				\
	binaryCheck (Word##size, WordS##size##_mulCheck)	\
	binaryCheck (Word##size, WordU##size##_mulCheck)	\

#define prims()						\
	coercePrims ()					\
	loadGCState ()					\
	loadStorePrims (load)				\
	loadStorePrims (store)				\
	realPrimsOfSize (32)				\
	realPrimsOfSize (64)				\
	wordPrimsOfSize (8)				\
	wordPrimsOfSize (16)				\
	wordPrimsOfSize (32)				\
	wordPrimsOfSizeNoMul (64)

#define opcodes()				\
	prims()					\
	opcodeGen (CallC)			\
	opcodeGen (Goto)			\
	opcodeGen (JumpOnOverflow)		\
	opcodeGen (ProfileLabel)		\
	opcodeGen (Raise)			\
	opcodeGen (Return)			\
	opcodeGen (Switch8)			\
	opcodeGen (Switch16)			\
	opcodeGen (Switch32)			\
	opcodeGen (Switch64)			\
        opcodeGen (Thread_returnToC)

#define opcodeSym(z)  OPCODE_##z
#define opcodeSymOfTy(ty, size, name)  opcodeSym (ty##size##_##name)
#define opcodeName(ty, size, name) opcodeGen (ty##size##_##name)

#define binary(ty, f)  opcodeGen (f)
#define binaryCheck(ty, f)  opcodeGen (f)
#define compare(ty, f)  opcodeGen (f)
#define loadStoreArrayOffset(mode, ty, size) \
	opcodeName (ty, size, mode##ArrayOffset)
#define	loadStoreContents(mode, ty, size) \
	opcodeName (ty, size, mode##Contents)
#define loadStoreFrontier(mode) opcodeGen (mode##Frontier)
#define loadGCState() opcodeGen (loadGCState)
#define	loadStoreGlobal(mode, ty, size)  opcodeName (ty, size, mode##Global)
#define	loadStoreOffset(mode, ty, size)  opcodeName (ty, size, mode##Offset)
#define	loadStoreRegister(mode, ty, size)  opcodeName (ty, size, mode##Register)
#define	loadStoreStackOffset(mode, ty, size) \
	opcodeName (ty, size, mode##StackOffset)
#define loadStoreStackTop(mode)  opcodeGen (mode##StackTop)
#define loadWord(size)  opcodeName (Word, size, loadWord)
#define shift(ty, f)  opcodeGen (f)
#define ternary(ty, f)  opcodeGen (f)
#define unary(ty, f)  opcodeGen (f)
#define unaryCheck(ty, f)  opcodeGen (f)

#define coerceOp(f, t)  opcodeGen (f##_to##t)

#define coerce(f1, t1, f2, t2)  coerceOp (f2, t2)

// Define the opcode strings.

#define opcodeGen(z)  #z,

char *opcodeStrings [] = {
	opcodes ()
};

#undef opcodeGen

// Define the Opcode enum.

#define opcodeGen(z) opcodeSym (z),

enum {
	opcodes ()
};

typedef Word16 Opcode;

#undef coerce
#undef coerceOp
#undef binary
#undef binaryCheck
#undef compare
#undef loadGCState
#undef loadStoreArrayOffset
#undef loadStoreContents
#undef loadStoreFrontier
#undef loadStoreGlobal
#undef loadStoreOffset
#undef loadStoreRegister
#undef loadStoreStackOffset
#undef loadStoreStackTop
#undef loadWord
#undef shift
#undef ternary
#undef unary
#undef unaryCheck

// At this point the opcodes() macro is still defined.

#endif
