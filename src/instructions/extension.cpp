/* This file is part of the sirit project.
 * Copyright (c) 2019 sirit
 * This software may be used and distributed according to the terms of the
 * 3-Clause BSD License
 */

#include <iterator>
#include <spirv/unified1/AMD_gcn_shader.h>
#include <spirv/unified1/GLSL.std.450.h>
#include <spirv/unified1/NonSemanticDebugPrintf.h>

#include "sirit/sirit.h"

#include "stream.h"

namespace Sirit {

Id Module::OpExtInst(Id result_type, Id set, u32 instruction, std::span<const Id> operands) {
    code->Reserve(5 + operands.size());
    return *code << OpId{spv::Op::OpExtInst, result_type} << set << instruction << operands
                 << EndOp{};
}

#define DEFINE_UNARY(funcname, opcode)                                                             \
    Id Module::funcname(Id result_type, Id operand) {                                              \
        return OpExtInst(result_type, GetGLSLstd450(), opcode, operand);                           \
    }

#define DEFINE_BINARY(funcname, opcode)                                                            \
    Id Module::funcname(Id result_type, Id operand_1, Id operand_2) {                              \
        return OpExtInst(result_type, GetGLSLstd450(), opcode, operand_1, operand_2);              \
    }

#define DEFINE_TRINARY(funcname, opcode)                                                           \
    Id Module::funcname(Id result_type, Id operand_1, Id operand_2, Id operand_3) {                \
        return OpExtInst(result_type, GetGLSLstd450(), opcode, operand_1, operand_2, operand_3);   \
    }

DEFINE_UNARY(OpFAbs, GLSLstd450FAbs)
DEFINE_UNARY(OpSAbs, GLSLstd450SAbs)
DEFINE_UNARY(OpRound, GLSLstd450Round)
DEFINE_UNARY(OpRoundEven, GLSLstd450RoundEven)
DEFINE_UNARY(OpTrunc, GLSLstd450Trunc)
DEFINE_UNARY(OpFSign, GLSLstd450FSign)
DEFINE_UNARY(OpSSign, GLSLstd450SSign)
DEFINE_UNARY(OpFloor, GLSLstd450Floor)
DEFINE_UNARY(OpCeil, GLSLstd450Ceil)
DEFINE_UNARY(OpFract, GLSLstd450Fract)
DEFINE_UNARY(OpSin, GLSLstd450Sin)
DEFINE_UNARY(OpCos, GLSLstd450Cos)
DEFINE_UNARY(OpAsin, GLSLstd450Asin)
DEFINE_UNARY(OpAcos, GLSLstd450Acos)
DEFINE_BINARY(OpPow, GLSLstd450Pow)
DEFINE_UNARY(OpExp, GLSLstd450Exp)
DEFINE_UNARY(OpLog, GLSLstd450Log)
DEFINE_UNARY(OpExp2, GLSLstd450Exp2)
DEFINE_UNARY(OpLog2, GLSLstd450Log2)
DEFINE_UNARY(OpSqrt, GLSLstd450Sqrt)
DEFINE_UNARY(OpInverseSqrt, GLSLstd450InverseSqrt)
DEFINE_BINARY(OpLdexp, GLSLstd450Ldexp)
DEFINE_BINARY(OpFMin, GLSLstd450FMin)
DEFINE_BINARY(OpUMin, GLSLstd450UMin)
DEFINE_BINARY(OpSMin, GLSLstd450SMin)
DEFINE_BINARY(OpNMin, GLSLstd450NMin)
DEFINE_BINARY(OpFMax, GLSLstd450FMax)
DEFINE_BINARY(OpUMax, GLSLstd450UMax)
DEFINE_BINARY(OpSMax, GLSLstd450SMax)
DEFINE_BINARY(OpNMax, GLSLstd450NMax)
DEFINE_TRINARY(OpFClamp, GLSLstd450FClamp)
DEFINE_TRINARY(OpUClamp, GLSLstd450UClamp)
DEFINE_TRINARY(OpSClamp, GLSLstd450SClamp)
DEFINE_TRINARY(OpFma, GLSLstd450Fma)
DEFINE_UNARY(OpFrexpStruct, GLSLstd450FrexpStruct)
DEFINE_UNARY(OpPackHalf2x16, GLSLstd450PackHalf2x16)
DEFINE_UNARY(OpUnpackHalf2x16, GLSLstd450UnpackHalf2x16)
DEFINE_UNARY(OpPackUnorm2x16, GLSLstd450PackUnorm2x16)
DEFINE_UNARY(OpUnpackUnorm2x16, GLSLstd450UnpackUnorm2x16)
DEFINE_UNARY(OpPackSnorm2x16, GLSLstd450PackSnorm2x16)
DEFINE_UNARY(OpUnpackSnorm2x16, GLSLstd450UnpackSnorm2x16)
DEFINE_UNARY(OpPackUnorm4x8, GLSLstd450PackUnorm4x8)
DEFINE_UNARY(OpUnpackUnorm4x8, GLSLstd450UnpackUnorm4x8)
DEFINE_UNARY(OpPackSnorm4x8, GLSLstd450PackSnorm4x8)
DEFINE_UNARY(OpUnpackSnorm4x8, GLSLstd450UnpackSnorm4x8)
DEFINE_UNARY(OpFindILsb, GLSLstd450FindILsb)
DEFINE_UNARY(OpFindSMsb, GLSLstd450FindSMsb)
DEFINE_UNARY(OpFindUMsb, GLSLstd450FindUMsb)
DEFINE_UNARY(OpInterpolateAtCentroid, GLSLstd450InterpolateAtCentroid)
DEFINE_BINARY(OpInterpolateAtSample, GLSLstd450InterpolateAtSample)
DEFINE_BINARY(OpInterpolateAtOffset, GLSLstd450InterpolateAtOffset)
DEFINE_UNARY(OpNormalize, GLSLstd450Normalize)
DEFINE_BINARY(OpCross, GLSLstd450Cross)
DEFINE_UNARY(OpLength, GLSLstd450Length)
DEFINE_TRINARY(OpFMix, GLSLstd450FMix)

Id Module::OpDebugPrintf(Id fmt, std::span<const Id> fmt_args) {
    std::vector<Id> operands;
    operands.push_back(fmt);
    std::copy(fmt_args.begin(), fmt_args.end(), std::back_inserter(operands));
    return OpExtInst(TypeVoid(), GetNonSemanticDebugPrintf(), NonSemanticDebugPrintfDebugPrintf,
                     operands);
}

Id Module::OpCubeFaceCoordAMD(Id result_type, Id cube_coords) {
    return OpExtInst(result_type, GetAmdGcnShader(), AMD_gcn_shaderCubeFaceCoordAMD, cube_coords);
}

Id Module::OpCubeFaceIndexAMD(Id result_type, Id cube_coords) {
    return OpExtInst(result_type, GetAmdGcnShader(), AMD_gcn_shaderCubeFaceIndexAMD, cube_coords);
}

Id Module::OpTimeAMD(Id result_type) {
    return OpExtInst(result_type, GetAmdGcnShader(), AMD_gcn_shaderTimeAMD);
}

} // namespace Sirit
