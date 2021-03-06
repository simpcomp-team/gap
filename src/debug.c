#include "system.h"

#include "compiled.h"
#include "hookintrprtr.h"
#include "calls.h"
#include "fibhash.h"

#if defined(HAVE_BACKTRACE) && defined(PRINT_BACKTRACE)
#include <execinfo.h>
#include <signal.h>

static void BacktraceHandler(int sig) NORETURN;

static void BacktraceHandler(int sig)
{
    void *       trace[32];
    size_t       size;
    const char * sigtext = "Unknown signal";
    size = backtrace(trace, 32);
    switch (sig) {
    case SIGSEGV:
        sigtext = "Segmentation fault";
        break;
    case SIGBUS:
        sigtext = "Bus error";
        break;
    case SIGINT:
        sigtext = "Interrupt";
        break;
    case SIGABRT:
        sigtext = "Abort";
        break;
    case SIGFPE:
        sigtext = "Floating point exception";
        break;
    case SIGTERM:
        sigtext = "Program terminated";
        break;
    }
    fprintf(stderr, "%s\n", sigtext);
    backtrace_symbols_fd(trace, size, fileno(stderr));
    exit(1);
}

void InstallBacktraceHandlers(void)
{
    signal(SIGSEGV, BacktraceHandler);
    signal(SIGBUS, BacktraceHandler);
    signal(SIGINT, BacktraceHandler);
    signal(SIGABRT, BacktraceHandler);
    signal(SIGFPE, BacktraceHandler);
    signal(SIGTERM, BacktraceHandler);
}

#endif


// Global array of function pointers to static inline functions.
//
// This is a trick to force compilers to emit explicit code for these
// functions at least once, so that they can be used from debuggers like
// gdb or lldb.
typedef void (*VoidFunc)(void);
VoidFunc debug_func_pointers[] = {
    (VoidFunc)ActiveGAPState,
    (VoidFunc)ADDR_INT,
    (VoidFunc)ADDR_OBJ,
    (VoidFunc)ADDR_PERM2,
    (VoidFunc)ADDR_PERM4,
    (VoidFunc)ADDR_PPERM2,
    (VoidFunc)ADDR_PPERM4,
    (VoidFunc)ADDR_TRANS2,
    (VoidFunc)ADDR_TRANS4,
    (VoidFunc)AINV_MUT,
    (VoidFunc)AINV,
    (VoidFunc)AlwaysNo,
    (VoidFunc)AlwaysYes,
    (VoidFunc)ARE_INTOBJS,
    (VoidFunc)ASS_LIST,
    (VoidFunc)ASS_LVAR_WITH_CONTEXT,
    (VoidFunc)ASS_LVAR,
    (VoidFunc)ASS_REC,
    (VoidFunc)AssConstantGVar,
    (VoidFunc)AssReadOnlyGVar,
    (VoidFunc)ASSS_LIST,
    (VoidFunc)BAG_HEADER,
    (VoidFunc)BASE_PTR_PLIST,
    (VoidFunc)BLOCK_ELM_BLIST_PTR,
    (VoidFunc)BLOCKS_BLIST,
    (VoidFunc)BODY_FUNC,
    (VoidFunc)BODY_HEADER,
    (VoidFunc)C_MAKE_INTEGER_BAG,
    (VoidFunc)C_MAKE_MED_INT,
    (VoidFunc)C_NORMALIZE_64BIT,
    (VoidFunc)C_SET_LIMB4,
    (VoidFunc)C_SET_LIMB8,
    (VoidFunc)CACHE_OPER,
    (VoidFunc)CAPACITY_PLIST,
    (VoidFunc)CAPACITY_PREC,
    (VoidFunc)CHANGED_BAG,
    (VoidFunc)CHAR_SINT,
    (VoidFunc)CHAR_VALUE,
    (VoidFunc)CHARS_STRING,
    (VoidFunc)CLEAR_BAG_FLAG,
    (VoidFunc)CLEAR_BIT_BLIST,
    (VoidFunc)CLEAR_OBJ_FLAG,
    (VoidFunc)CODEG_PPERM,
    (VoidFunc)COMM,
    (VoidFunc)CONST_ADDR_INT,
    (VoidFunc)CONST_ADDR_OBJ,
    (VoidFunc)CONST_ADDR_PERM2,
    (VoidFunc)CONST_ADDR_PERM4,
    (VoidFunc)CONST_ADDR_PPERM2,
    (VoidFunc)CONST_ADDR_PPERM4,
    (VoidFunc)CONST_ADDR_TRANS2,
    (VoidFunc)CONST_ADDR_TRANS4,
    (VoidFunc)CONST_BLOCK_ELM_BLIST_PTR,
    (VoidFunc)CONST_BLOCKS_BLIST,
    (VoidFunc)CONST_CHARS_STRING,
    (VoidFunc)CONST_CSTR_STRING,
    (VoidFunc)CONST_FUNC,
    (VoidFunc)CONST_OPER,
    (VoidFunc)CONST_PTR_BAG,
    (VoidFunc)COPY_CHARS,
    (VoidFunc)COUNT_TRUES_BLOCK,
    (VoidFunc)COUNT_TRUES_BLOCKS,
    (VoidFunc)CSTR_STRING,
    (VoidFunc)CURR_FUNC,
    (VoidFunc)DEG_PERM2,
    (VoidFunc)DEG_PERM4,
    (VoidFunc)DEG_PPERM,
    (VoidFunc)DEG_PPERM2,
    (VoidFunc)DEG_PPERM4,
    (VoidFunc)DEG_TRANS,
    (VoidFunc)DEG_TRANS2,
    (VoidFunc)DEG_TRANS4,
    (VoidFunc)DEN_RAT,
    (VoidFunc)DETECT_INTOBJ_OVERFLOW,
    (VoidFunc)DIFF,
    (VoidFunc)ELM_BLIST,
    (VoidFunc)ELM_DEFAULT_LIST,
    (VoidFunc)ELM_LIST,
    (VoidFunc)ELM_PLIST,
    (VoidFunc)ELM_REC,
    (VoidFunc)ELM0_LIST,
    (VoidFunc)ELMS_LIST,
    (VoidFunc)ELMV_LIST,
    (VoidFunc)ELMV0_LIST,
    (VoidFunc)ELMW_LIST,
    (VoidFunc)ENABLED_ATTR,
    (VoidFunc)ENVI_FUNC,
    (VoidFunc)EQ,
    (VoidFunc)FEXS_FUNC,
    (VoidFunc)FibHash,
    (VoidFunc)FLAG1_FILT,
    (VoidFunc)FLAG2_FILT,
    (VoidFunc)FLAGS_FILT,
    (VoidFunc)FUNC_LVARS_PTR,
    (VoidFunc)FUNC_LVARS,
    (VoidFunc)FUNC,
    (VoidFunc)GET_ELM_PREC,
    (VoidFunc)GET_ELM_RANGE,
    (VoidFunc)GET_INC_RANGE,
    (VoidFunc)GET_LEN_RANGE,
    (VoidFunc)GET_LEN_STRING,
    (VoidFunc)GET_LOW_RANGE,
    (VoidFunc)GET_RNAM_PREC,
    (VoidFunc)GROW_PLIST,
    (VoidFunc)GROW_STRING,
    (VoidFunc)HDLR_FUNC,
    (VoidFunc)HookedLineIntoFunction,
    (VoidFunc)HookedLineOutFunction,
    (VoidFunc)IN,
    (VoidFunc)INT_INTOBJ,
    (VoidFunc)INTOBJ_INT,
    (VoidFunc)INV_MUT,
    (VoidFunc)INV,
    (VoidFunc)IS_BAG_REF,
    (VoidFunc)IS_BLIST_REP,
    (VoidFunc)IS_COMOBJ,
    (VoidFunc)IS_COPYABLE_OBJ,
    (VoidFunc)IS_DATOBJ,
    (VoidFunc)IS_DENSE_LIST,
    (VoidFunc)IS_DENSE_PLIST,
    (VoidFunc)IS_EVEN_INT,
    (VoidFunc)IS_FFE,
    (VoidFunc)IS_FILTER,
    (VoidFunc)IS_HOMOG_LIST,
    (VoidFunc)IS_INT,
    (VoidFunc)IS_INTOBJ,
    (VoidFunc)IS_LARGEINT,
    (VoidFunc)IS_LIST,
    (VoidFunc)IS_LVARS_OR_HVARS,
    (VoidFunc)IS_MACFLOAT,
    (VoidFunc)IS_MODULE_BUILTIN,
    (VoidFunc)IS_MODULE_DYNAMIC,
    (VoidFunc)IS_MODULE_STATIC,
    (VoidFunc)IS_MUTABLE_OBJ,
    (VoidFunc)IS_MUTABLE_PLAIN_OBJ,
    (VoidFunc)IS_NEG_INT,
    (VoidFunc)IS_NONNEG_INTOBJ,
    (VoidFunc)IS_ODD_INT,
    (VoidFunc)IS_OPERATION,
    (VoidFunc)IS_PLIST_MUTABLE,
    (VoidFunc)IS_PLIST_OR_POSOBJ,
    (VoidFunc)IS_PLIST,
    (VoidFunc)IS_POS_INT,
    (VoidFunc)IS_POS_INTOBJ,
    (VoidFunc)IS_POSOBJ,
    (VoidFunc)IS_POSS_LIST,
    (VoidFunc)IS_PPERM,
    (VoidFunc)IS_PREC_OR_COMOBJ,
    (VoidFunc)IS_PREC,
    (VoidFunc)IS_RANGE,
    (VoidFunc)IS_REC,
    (VoidFunc)IS_SMALL_LIST,
    (VoidFunc)IS_SSORT_LIST,
    (VoidFunc)IS_STRING_REP,
    (VoidFunc)IS_STRING,
    (VoidFunc)IS_TABLE_LIST,
    (VoidFunc)IS_TRANS,
    (VoidFunc)ISB_LIST,
    (VoidFunc)ISB_REC,
    (VoidFunc)IsIdent,
    (VoidFunc)LEN_BLIST,
    (VoidFunc)LEN_FLAGS,
    (VoidFunc)LEN_LIST,
    (VoidFunc)LEN_PLIST,
    (VoidFunc)LEN_PREC,
    (VoidFunc)LENGTH,
    (VoidFunc)LQUO,
    (VoidFunc)LT,
    (VoidFunc)MakeHighVars,
    (VoidFunc)MakeImmString,
    (VoidFunc)MakeImmutableString,
    (VoidFunc)MakeString,
    (VoidFunc)MarkBag,
    (VoidFunc)MASK_POS_BLIST,
    (VoidFunc)MaskForCopyBits,
    (VoidFunc)METHS_OPER,
    (VoidFunc)MOD,
    (VoidFunc)NAME_FUNC,
    (VoidFunc)NAME_LVAR_WITH_CONTEXT,
    (VoidFunc)NAME_LVAR,
    (VoidFunc)NAMS_FUNC,
    (VoidFunc)NARG_FUNC,
    (VoidFunc)NEW_FLAGS,
    (VoidFunc)NEW_PERM2,
    (VoidFunc)NEW_PERM4,
    (VoidFunc)NEW_PLIST_IMM,
    (VoidFunc)NEW_PLIST_WITH_MUTABILITY,
    (VoidFunc)NEW_PLIST,
    (VoidFunc)NEW_RANGE_NSORT,
    (VoidFunc)NEW_RANGE_SSORT,
    (VoidFunc)NEW_TRANS,
    (VoidFunc)NEW_TRANS2,
    (VoidFunc)NEW_TRANS4,
    (VoidFunc)NewWord,
    (VoidFunc)NewWordSizedBag,
    (VoidFunc)NLOC_FUNC,
    (VoidFunc)NRB_FLAGS,
    (VoidFunc)NUM_RAT,
    (VoidFunc)NUMBER_BLOCKS_BLIST,
    (VoidFunc)OBJ_LVAR_WITH_CONTEXT,
    (VoidFunc)OBJ_LVAR,
    (VoidFunc)ONE_MUT,
    (VoidFunc)ONE,
    (VoidFunc)OPER,
    (VoidFunc)PARENT_LVARS_PTR,
    (VoidFunc)PARENT_LVARS,
    (VoidFunc)PLAIN_LIST,
    (VoidFunc)PopPlist,
    (VoidFunc)POS_LIST,
    (VoidFunc)POW,
    (VoidFunc)PROD,
    (VoidFunc)PROF_FUNC,
    (VoidFunc)PTR_BAG,
    (VoidFunc)PushPlist,
    (VoidFunc)QUO,
    (VoidFunc)RANK_PPERM,
    (VoidFunc)RANK_TRANS,
    (VoidFunc)RegisterStatWithHook,
    (VoidFunc)ResizeWordSizedBag,
    (VoidFunc)SAFE_C_ELM_FLAGS,
    (VoidFunc)SET_BAG_FLAG,
    (VoidFunc)SET_BIT_BLIST,
    (VoidFunc)SET_BODY_FUNC,
    (VoidFunc)SET_CACHE_OPER,
    (VoidFunc)SET_CHAR_VALUE,
    (VoidFunc)SET_DEN_RAT,
    (VoidFunc)SET_ELM_PLIST,
    (VoidFunc)SET_ELM_PREC,
    (VoidFunc)SET_ENABLED_ATTR,
    (VoidFunc)SET_ENVI_FUNC,
    (VoidFunc)SET_FEXS_FUNC,
    (VoidFunc)SET_FLAG1_FILT,
    (VoidFunc)SET_FLAG2_FILT,
    (VoidFunc)SET_FLAGS_FILT,
    (VoidFunc)SET_HDLR_FUNC,
    (VoidFunc)SET_INC_RANGE,
    (VoidFunc)SET_IS_FILTER,
    (VoidFunc)SET_LEN_BLIST,
    (VoidFunc)SET_LEN_PLIST,
    (VoidFunc)SET_LEN_PREC,
    (VoidFunc)SET_LEN_RANGE,
    (VoidFunc)SET_LEN_STRING,
    (VoidFunc)SET_LOW_RANGE,
    (VoidFunc)SET_METHS_OPER,
    (VoidFunc)SET_NAMS_FUNC,
    (VoidFunc)SET_NARG_FUNC,
    (VoidFunc)SET_NLOC_FUNC,
    (VoidFunc)SET_NUM_RAT,
    (VoidFunc)SET_OBJ_FLAG,
    (VoidFunc)SET_PROF_FUNC,
    (VoidFunc)SET_PTR_BAG,
    (VoidFunc)SET_RNAM_PREC,
    (VoidFunc)SET_SETTR_FILT,
    (VoidFunc)SET_STOREDINV_PERM,
    (VoidFunc)SET_TESTR_FILT,
    (VoidFunc)SET_TYPE_COMOBJ,
    (VoidFunc)SET_TYPE_DATOBJ,
    (VoidFunc)SET_TYPE_OBJ,
    (VoidFunc)SET_TYPE_POSOBJ,
    (VoidFunc)SET_VAL_MACFLOAT,
    (VoidFunc)SETTR_FILT,
    (VoidFunc)SHALLOW_COPY_OBJ,
    (VoidFunc)SHRINK_PLIST,
    (VoidFunc)SHRINK_STRING,
    (VoidFunc)SINT_CHAR,
    (VoidFunc)SIZE_BAG_CONTENTS,
    (VoidFunc)SIZE_BAG,
    (VoidFunc)SIZE_INT,
    (VoidFunc)SIZE_OBJ,
    (VoidFunc)SIZE_PLEN_BLIST,
    (VoidFunc)SIZEBAG_PERM2,
    (VoidFunc)SIZEBAG_PERM4,
    (VoidFunc)SIZEBAG_STRINGLEN,
    (VoidFunc)STAT_LVARS_PTR,
    (VoidFunc)STAT_LVARS,
    (VoidFunc)StateSlotsAtOffset,
    (VoidFunc)STOREDINV_PERM,
    (VoidFunc)SUM,
    (VoidFunc)SWITCH_TO_OLD_LVARS_AND_FREE,
    (VoidFunc)SWITCH_TO_OLD_LVARS,
    (VoidFunc)SwitchToNewLvars,
    (VoidFunc)TEST_BAG_FLAG,
    (VoidFunc)TEST_BIT_BLIST,
    (VoidFunc)TEST_OBJ_FLAG,
    (VoidFunc)TESTR_FILT,
    (VoidFunc)TNAM_OBJ,
    (VoidFunc)TNUM_BAG,
    (VoidFunc)TNUM_OBJ,
    (VoidFunc)TYPE_COMOBJ,
    (VoidFunc)TYPE_DATOBJ,
    (VoidFunc)TYPE_OBJ,
    (VoidFunc)TYPE_POSOBJ,
    (VoidFunc)UNB_LIST,
    (VoidFunc)UNB_REC,
    (VoidFunc)VAL_MACFLOAT,
    (VoidFunc)VisitStatIfHooked,
    (VoidFunc)ZERO_MUT,
    (VoidFunc)ZERO,
#ifdef HPCGAP
    (VoidFunc)ATOMIC_ELM_PLIST,
    (VoidFunc)ATOMIC_SET_ELM_PLIST_ONCE,
    (VoidFunc)ATOMIC_SET_ELM_PLIST,
    (VoidFunc)GetTLS,
    (VoidFunc)LCKS_FUNC,
    (VoidFunc)SET_LCKS_FUNC,
#endif
};
