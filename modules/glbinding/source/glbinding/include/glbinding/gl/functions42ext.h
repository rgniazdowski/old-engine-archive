#pragma once

#include <glbinding/gl/nogl.h>

#include <glbinding/gl/values.h>
#include <glbinding/gl/boolean.h>

namespace gl42ext
{

#include <glbinding/gl/types.inl>
#include <glbinding/gl/boolean.inl>
#include <glbinding/gl/values.inl>

} // namespace gl42ext

#include <glbinding/Binding.h>


namespace gl42ext
{

inline void glAccumxOES(GLenum op, GLfixed value)
{
    return glbinding::Binding::AccumxOES(op, value);
}

inline void glActiveProgramEXT(GLuint program)
{
    return glbinding::Binding::ActiveProgramEXT(program);
}

inline void glActiveStencilFaceEXT(GLenum face)
{
    return glbinding::Binding::ActiveStencilFaceEXT(face);
}

inline void glActiveTextureARB(GLenum texture)
{
    return glbinding::Binding::ActiveTextureARB(texture);
}

inline void glActiveVaryingNV(GLuint program, const GLchar * name)
{
    return glbinding::Binding::ActiveVaryingNV(program, name);
}

inline void glAlphaFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod)
{
    return glbinding::Binding::AlphaFragmentOp1ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod);
}

inline void glAlphaFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod)
{
    return glbinding::Binding::AlphaFragmentOp2ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod);
}

inline void glAlphaFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod)
{
    return glbinding::Binding::AlphaFragmentOp3ATI(op, dst, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
}

inline void glAlphaFuncxOES(GLenum func, GLfixed ref)
{
    return glbinding::Binding::AlphaFuncxOES(func, ref);
}

inline void glApplyTextureEXT(GLenum mode)
{
    return glbinding::Binding::ApplyTextureEXT(mode);
}

inline GLboolean glAreProgramsResidentNV(GLsizei n, const GLuint * programs, GLboolean * residences)
{
    return glbinding::Binding::AreProgramsResidentNV(n, programs, residences);
}

inline GLboolean glAreTexturesResidentEXT(GLsizei n, const GLuint * textures, GLboolean * residences)
{
    return glbinding::Binding::AreTexturesResidentEXT(n, textures, residences);
}

inline void glArrayElementEXT(GLint i)
{
    return glbinding::Binding::ArrayElementEXT(i);
}

inline void glArrayObjectATI(GLenum array, GLint size, GLenum type, GLsizei stride, GLuint buffer, GLuint offset)
{
    return glbinding::Binding::ArrayObjectATI(array, size, type, stride, buffer, offset);
}

inline void glAsyncMarkerSGIX(GLuint marker)
{
    return glbinding::Binding::AsyncMarkerSGIX(marker);
}

inline void glAttachObjectARB(GLhandleARB containerObj, GLhandleARB obj)
{
    return glbinding::Binding::AttachObjectARB(containerObj, obj);
}

inline void glBeginConditionalRenderNV(GLuint id, GLenum mode)
{
    return glbinding::Binding::BeginConditionalRenderNV(id, mode);
}

inline void glBeginConditionalRenderNVX(GLuint id)
{
    return glbinding::Binding::BeginConditionalRenderNVX(id);
}

inline void glBeginFragmentShaderATI()
{
    return glbinding::Binding::BeginFragmentShaderATI();
}

inline void glBeginOcclusionQueryNV(GLuint id)
{
    return glbinding::Binding::BeginOcclusionQueryNV(id);
}

inline void glBeginPerfMonitorAMD(GLuint monitor)
{
    return glbinding::Binding::BeginPerfMonitorAMD(monitor);
}

inline void glBeginPerfQueryINTEL(GLuint queryHandle)
{
    return glbinding::Binding::BeginPerfQueryINTEL(queryHandle);
}

inline void glBeginQueryARB(GLenum target, GLuint id)
{
    return glbinding::Binding::BeginQueryARB(target, id);
}

inline void glBeginTransformFeedbackEXT(GLenum primitiveMode)
{
    return glbinding::Binding::BeginTransformFeedbackEXT(primitiveMode);
}

inline void glBeginTransformFeedbackNV(GLenum primitiveMode)
{
    return glbinding::Binding::BeginTransformFeedbackNV(primitiveMode);
}

inline void glBeginVertexShaderEXT()
{
    return glbinding::Binding::BeginVertexShaderEXT();
}

inline void glBeginVideoCaptureNV(GLuint video_capture_slot)
{
    return glbinding::Binding::BeginVideoCaptureNV(video_capture_slot);
}

inline void glBindAttribLocationARB(GLhandleARB programObj, GLuint index, const GLcharARB * name)
{
    return glbinding::Binding::BindAttribLocationARB(programObj, index, name);
}

inline void glBindBufferARB(GLenum target, GLuint buffer)
{
    return glbinding::Binding::BindBufferARB(target, buffer);
}

inline void glBindBufferBaseEXT(GLenum target, GLuint index, GLuint buffer)
{
    return glbinding::Binding::BindBufferBaseEXT(target, index, buffer);
}

inline void glBindBufferBaseNV(GLenum target, GLuint index, GLuint buffer)
{
    return glbinding::Binding::BindBufferBaseNV(target, index, buffer);
}

inline void glBindBufferOffsetEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset)
{
    return glbinding::Binding::BindBufferOffsetEXT(target, index, buffer, offset);
}

inline void glBindBufferOffsetNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset)
{
    return glbinding::Binding::BindBufferOffsetNV(target, index, buffer, offset);
}

inline void glBindBufferRangeEXT(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
    return glbinding::Binding::BindBufferRangeEXT(target, index, buffer, offset, size);
}

inline void glBindBufferRangeNV(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
    return glbinding::Binding::BindBufferRangeNV(target, index, buffer, offset, size);
}

inline void glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers)
{
    return glbinding::Binding::BindBuffersBase(target, first, count, buffers);
}

inline void glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes)
{
    return glbinding::Binding::BindBuffersRange(target, first, count, buffers, offsets, sizes);
}

inline void glBindFragDataLocationEXT(GLuint program, GLuint color, const GLchar * name)
{
    return glbinding::Binding::BindFragDataLocationEXT(program, color, name);
}

inline void glBindFragmentShaderATI(GLuint id)
{
    return glbinding::Binding::BindFragmentShaderATI(id);
}

inline void glBindFramebufferEXT(GLenum target, GLuint framebuffer)
{
    return glbinding::Binding::BindFramebufferEXT(target, framebuffer);
}

inline void glBindImageTextureEXT(GLuint index, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLint format)
{
    return glbinding::Binding::BindImageTextureEXT(index, texture, level, layered, layer, access, format);
}

inline void glBindImageTextures(GLuint first, GLsizei count, const GLuint * textures)
{
    return glbinding::Binding::BindImageTextures(first, count, textures);
}

inline GLuint glBindLightParameterEXT(GLenum light, GLenum value)
{
    return glbinding::Binding::BindLightParameterEXT(light, value);
}

inline GLuint glBindMaterialParameterEXT(GLenum face, GLenum value)
{
    return glbinding::Binding::BindMaterialParameterEXT(face, value);
}

inline void glBindMultiTextureEXT(GLenum texunit, GLenum target, GLuint texture)
{
    return glbinding::Binding::BindMultiTextureEXT(texunit, target, texture);
}

inline GLuint glBindParameterEXT(GLenum value)
{
    return glbinding::Binding::BindParameterEXT(value);
}

inline void glBindProgramARB(GLenum target, GLuint program)
{
    return glbinding::Binding::BindProgramARB(target, program);
}

inline void glBindProgramNV(GLenum target, GLuint id)
{
    return glbinding::Binding::BindProgramNV(target, id);
}

inline void glBindRenderbufferEXT(GLenum target, GLuint renderbuffer)
{
    return glbinding::Binding::BindRenderbufferEXT(target, renderbuffer);
}

inline void glBindSamplers(GLuint first, GLsizei count, const GLuint * samplers)
{
    return glbinding::Binding::BindSamplers(first, count, samplers);
}

inline GLuint glBindTexGenParameterEXT(GLenum unit, GLenum coord, GLenum value)
{
    return glbinding::Binding::BindTexGenParameterEXT(unit, coord, value);
}

inline void glBindTextureEXT(GLenum target, GLuint texture)
{
    return glbinding::Binding::BindTextureEXT(target, texture);
}

inline void glBindTextureUnit(GLuint unit, GLuint texture)
{
    return glbinding::Binding::BindTextureUnit(unit, texture);
}

inline GLuint glBindTextureUnitParameterEXT(GLenum unit, GLenum value)
{
    return glbinding::Binding::BindTextureUnitParameterEXT(unit, value);
}

inline void glBindTextures(GLuint first, GLsizei count, const GLuint * textures)
{
    return glbinding::Binding::BindTextures(first, count, textures);
}

inline void glBindTransformFeedbackNV(GLenum target, GLuint id)
{
    return glbinding::Binding::BindTransformFeedbackNV(target, id);
}

inline void glBindVertexArrayAPPLE(GLuint array)
{
    return glbinding::Binding::BindVertexArrayAPPLE(array);
}

inline void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
    return glbinding::Binding::BindVertexBuffer(bindingindex, buffer, offset, stride);
}

inline void glBindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides)
{
    return glbinding::Binding::BindVertexBuffers(first, count, buffers, offsets, strides);
}

inline void glBindVertexShaderEXT(GLuint id)
{
    return glbinding::Binding::BindVertexShaderEXT(id);
}

inline void glBindVideoCaptureStreamBufferNV(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLintptrARB offset)
{
    return glbinding::Binding::BindVideoCaptureStreamBufferNV(video_capture_slot, stream, frame_region, offset);
}

inline void glBindVideoCaptureStreamTextureNV(GLuint video_capture_slot, GLuint stream, GLenum frame_region, GLenum target, GLuint texture)
{
    return glbinding::Binding::BindVideoCaptureStreamTextureNV(video_capture_slot, stream, frame_region, target, texture);
}

inline void glBinormal3bEXT(GLbyte bx, GLbyte by, GLbyte bz)
{
    return glbinding::Binding::Binormal3bEXT(bx, by, bz);
}

inline void glBinormal3bvEXT(const GLbyte * v)
{
    return glbinding::Binding::Binormal3bvEXT(v);
}

inline void glBinormal3dEXT(GLdouble bx, GLdouble by, GLdouble bz)
{
    return glbinding::Binding::Binormal3dEXT(bx, by, bz);
}

inline void glBinormal3dvEXT(const GLdouble * v)
{
    return glbinding::Binding::Binormal3dvEXT(v);
}

inline void glBinormal3fEXT(GLfloat bx, GLfloat by, GLfloat bz)
{
    return glbinding::Binding::Binormal3fEXT(bx, by, bz);
}

inline void glBinormal3fvEXT(const GLfloat * v)
{
    return glbinding::Binding::Binormal3fvEXT(v);
}

inline void glBinormal3iEXT(GLint bx, GLint by, GLint bz)
{
    return glbinding::Binding::Binormal3iEXT(bx, by, bz);
}

inline void glBinormal3ivEXT(const GLint * v)
{
    return glbinding::Binding::Binormal3ivEXT(v);
}

inline void glBinormal3sEXT(GLshort bx, GLshort by, GLshort bz)
{
    return glbinding::Binding::Binormal3sEXT(bx, by, bz);
}

inline void glBinormal3svEXT(const GLshort * v)
{
    return glbinding::Binding::Binormal3svEXT(v);
}

inline void glBinormalPointerEXT(GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::BinormalPointerEXT(type, stride, pointer);
}

inline void glBitmapxOES(GLsizei width, GLsizei height, GLfixed xorig, GLfixed yorig, GLfixed xmove, GLfixed ymove, const GLubyte * bitmap)
{
    return glbinding::Binding::BitmapxOES(width, height, xorig, yorig, xmove, ymove, bitmap);
}

inline void glBlendBarrierKHR()
{
    return glbinding::Binding::BlendBarrierKHR();
}

inline void glBlendBarrierNV()
{
    return glbinding::Binding::BlendBarrierNV();
}

inline void glBlendColorEXT(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    return glbinding::Binding::BlendColorEXT(red, green, blue, alpha);
}

inline void glBlendColorxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
    return glbinding::Binding::BlendColorxOES(red, green, blue, alpha);
}

inline void glBlendEquationEXT(GLenum mode)
{
    return glbinding::Binding::BlendEquationEXT(mode);
}

inline void glBlendEquationIndexedAMD(GLuint buf, GLenum mode)
{
    return glbinding::Binding::BlendEquationIndexedAMD(buf, mode);
}

inline void glBlendEquationSeparateEXT(GLenum modeRGB, GLenum modeAlpha)
{
    return glbinding::Binding::BlendEquationSeparateEXT(modeRGB, modeAlpha);
}

inline void glBlendEquationSeparateIndexedAMD(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
    return glbinding::Binding::BlendEquationSeparateIndexedAMD(buf, modeRGB, modeAlpha);
}

inline void glBlendEquationSeparateiARB(GLuint buf, GLenum modeRGB, GLenum modeAlpha)
{
    return glbinding::Binding::BlendEquationSeparateiARB(buf, modeRGB, modeAlpha);
}

inline void glBlendEquationiARB(GLuint buf, GLenum mode)
{
    return glbinding::Binding::BlendEquationiARB(buf, mode);
}

inline void glBlendFuncIndexedAMD(GLuint buf, GLenum src, GLenum dst)
{
    return glbinding::Binding::BlendFuncIndexedAMD(buf, src, dst);
}

inline void glBlendFuncSeparateEXT(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
    return glbinding::Binding::BlendFuncSeparateEXT(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

inline void glBlendFuncSeparateINGR(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)
{
    return glbinding::Binding::BlendFuncSeparateINGR(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

inline void glBlendFuncSeparateIndexedAMD(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
    return glbinding::Binding::BlendFuncSeparateIndexedAMD(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

inline void glBlendFuncSeparateiARB(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
    return glbinding::Binding::BlendFuncSeparateiARB(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

inline void glBlendFunciARB(GLuint buf, GLenum src, GLenum dst)
{
    return glbinding::Binding::BlendFunciARB(buf, src, dst);
}

inline void glBlendParameteriNV(GLenum pname, GLint value)
{
    return glbinding::Binding::BlendParameteriNV(pname, value);
}

inline void glBlitFramebufferEXT(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, ClearBufferMask mask, GLenum filter)
{
    return glbinding::Binding::BlitFramebufferEXT(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

inline void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, ClearBufferMask mask, GLenum filter)
{
    return glbinding::Binding::BlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

inline void glBufferAddressRangeNV(GLenum pname, GLuint index, GLuint64EXT address, GLsizeiptr length)
{
    return glbinding::Binding::BufferAddressRangeNV(pname, index, address, length);
}

inline void glBufferDataARB(GLenum target, GLsizeiptrARB size, const void * data, GLenum usage)
{
    return glbinding::Binding::BufferDataARB(target, size, data, usage);
}

inline void glBufferPageCommitmentARB(GLenum target, GLintptr offset, GLsizeiptr size, GLboolean commit)
{
    return glbinding::Binding::BufferPageCommitmentARB(target, offset, size, commit);
}

inline void glBufferParameteriAPPLE(GLenum target, GLenum pname, GLint param)
{
    return glbinding::Binding::BufferParameteriAPPLE(target, pname, param);
}

inline void glBufferStorage(GLenum target, GLsizeiptr size, const void * data, MapBufferUsageMask flags)
{
    return glbinding::Binding::BufferStorage(target, size, data, flags);
}

inline void glBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, const void * data)
{
    return glbinding::Binding::BufferSubDataARB(target, offset, size, data);
}

inline GLenum glCheckFramebufferStatusEXT(GLenum target)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::CheckFramebufferStatusEXT(target));
}

inline GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::CheckNamedFramebufferStatus(framebuffer, target));
}

inline GLenum glCheckNamedFramebufferStatusEXT(GLuint framebuffer, GLenum target)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::CheckNamedFramebufferStatusEXT(framebuffer, target));
}

inline void glClampColorARB(GLenum target, GLenum clamp)
{
    return glbinding::Binding::ClampColorARB(target, clamp);
}

inline void glClearAccumxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
    return glbinding::Binding::ClearAccumxOES(red, green, blue, alpha);
}

inline void glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ClearBufferData(target, internalformat, format, type, data);
}

inline void glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ClearBufferSubData(target, internalformat, offset, size, format, type, data);
}

inline void glClearColorIiEXT(GLint red, GLint green, GLint blue, GLint alpha)
{
    return glbinding::Binding::ClearColorIiEXT(red, green, blue, alpha);
}

inline void glClearColorIuiEXT(GLuint red, GLuint green, GLuint blue, GLuint alpha)
{
    return glbinding::Binding::ClearColorIuiEXT(red, green, blue, alpha);
}

inline void glClearColorxOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
    return glbinding::Binding::ClearColorxOES(red, green, blue, alpha);
}

inline void glClearDepthdNV(GLdouble depth)
{
    return glbinding::Binding::ClearDepthdNV(depth);
}

inline void glClearDepthfOES(GLclampf depth)
{
    return glbinding::Binding::ClearDepthfOES(depth);
}

inline void glClearDepthxOES(GLfixed depth)
{
    return glbinding::Binding::ClearDepthxOES(depth);
}

inline void glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ClearNamedBufferData(buffer, internalformat, format, type, data);
}

inline void glClearNamedBufferDataEXT(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ClearNamedBufferDataEXT(buffer, internalformat, format, type, data);
}

inline void glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizei size, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
}

inline void glClearNamedBufferSubDataEXT(GLuint buffer, GLenum internalformat, GLsizeiptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ClearNamedBufferSubDataEXT(buffer, internalformat, offset, size, format, type, data);
}

inline void glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, const GLfloat depth, GLint stencil)
{
    return glbinding::Binding::ClearNamedFramebufferfi(framebuffer, buffer, depth, stencil);
}

inline void glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value)
{
    return glbinding::Binding::ClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
}

inline void glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value)
{
    return glbinding::Binding::ClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
}

inline void glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value)
{
    return glbinding::Binding::ClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
}

inline void glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ClearTexImage(texture, level, format, type, data);
}

inline void glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
}

inline void glClientActiveTextureARB(GLenum texture)
{
    return glbinding::Binding::ClientActiveTextureARB(texture);
}

inline void glClientActiveVertexStreamATI(GLenum stream)
{
    return glbinding::Binding::ClientActiveVertexStreamATI(stream);
}

inline void glClientAttribDefaultEXT(ClientAttribMask mask)
{
    return glbinding::Binding::ClientAttribDefaultEXT(mask);
}

inline void glClipControl(GLenum origin, GLenum depth)
{
    return glbinding::Binding::ClipControl(origin, depth);
}

inline void glClipPlanefOES(GLenum plane, const GLfloat * equation)
{
    return glbinding::Binding::ClipPlanefOES(plane, equation);
}

inline void glClipPlanexOES(GLenum plane, const GLfixed * equation)
{
    return glbinding::Binding::ClipPlanexOES(plane, equation);
}

inline void glColor3fVertex3fSUN(GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::Color3fVertex3fSUN(r, g, b, x, y, z);
}

inline void glColor3fVertex3fvSUN(const GLfloat * c, const GLfloat * v)
{
    return glbinding::Binding::Color3fVertex3fvSUN(c, v);
}

inline void glColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue)
{
    return glbinding::Binding::Color3hNV(red, green, blue);
}

inline void glColor3hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::Color3hvNV(v);
}

inline void glColor3xOES(GLfixed red, GLfixed green, GLfixed blue)
{
    return glbinding::Binding::Color3xOES(red, green, blue);
}

inline void glColor3xvOES(const GLfixed * components)
{
    return glbinding::Binding::Color3xvOES(components);
}

inline void glColor4fNormal3fVertex3fSUN(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::Color4fNormal3fVertex3fSUN(r, g, b, a, nx, ny, nz, x, y, z);
}

inline void glColor4fNormal3fVertex3fvSUN(const GLfloat * c, const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::Color4fNormal3fVertex3fvSUN(c, n, v);
}

inline void glColor4hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue, GLhalfNV alpha)
{
    return glbinding::Binding::Color4hNV(red, green, blue, alpha);
}

inline void glColor4hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::Color4hvNV(v);
}

inline void glColor4ubVertex2fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y)
{
    return glbinding::Binding::Color4ubVertex2fSUN(r, g, b, a, x, y);
}

inline void glColor4ubVertex2fvSUN(const GLubyte * c, const GLfloat * v)
{
    return glbinding::Binding::Color4ubVertex2fvSUN(c, v);
}

inline void glColor4ubVertex3fSUN(GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::Color4ubVertex3fSUN(r, g, b, a, x, y, z);
}

inline void glColor4ubVertex3fvSUN(const GLubyte * c, const GLfloat * v)
{
    return glbinding::Binding::Color4ubVertex3fvSUN(c, v);
}

inline void glColor4xOES(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
    return glbinding::Binding::Color4xOES(red, green, blue, alpha);
}

inline void glColor4xvOES(const GLfixed * components)
{
    return glbinding::Binding::Color4xvOES(components);
}

inline void glColorFormatNV(GLint size, GLenum type, GLsizei stride)
{
    return glbinding::Binding::ColorFormatNV(size, type, stride);
}

inline void glColorFragmentOp1ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod)
{
    return glbinding::Binding::ColorFragmentOp1ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod);
}

inline void glColorFragmentOp2ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod)
{
    return glbinding::Binding::ColorFragmentOp2ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod);
}

inline void glColorFragmentOp3ATI(GLenum op, GLuint dst, GLuint dstMask, GLuint dstMod, GLuint arg1, GLuint arg1Rep, GLuint arg1Mod, GLuint arg2, GLuint arg2Rep, GLuint arg2Mod, GLuint arg3, GLuint arg3Rep, GLuint arg3Mod)
{
    return glbinding::Binding::ColorFragmentOp3ATI(op, dst, dstMask, dstMod, arg1, arg1Rep, arg1Mod, arg2, arg2Rep, arg2Mod, arg3, arg3Rep, arg3Mod);
}

inline void glColorMaskIndexedEXT(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
{
    return glbinding::Binding::ColorMaskIndexedEXT(index, r, g, b, a);
}

inline void glColorPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer)
{
    return glbinding::Binding::ColorPointerEXT(size, type, stride, count, pointer);
}

inline void glColorPointerListIBM(GLint size, GLenum type, GLint stride, const void ** pointer, GLint ptrstride)
{
    return glbinding::Binding::ColorPointerListIBM(size, type, stride, pointer, ptrstride);
}

inline void glColorPointervINTEL(GLint size, GLenum type, const void ** pointer)
{
    return glbinding::Binding::ColorPointervINTEL(size, type, pointer);
}

inline void glColorSubTable(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ColorSubTable(target, start, count, format, type, data);
}

inline void glColorSubTableEXT(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const void * data)
{
    return glbinding::Binding::ColorSubTableEXT(target, start, count, format, type, data);
}

inline void glColorTable(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void * table)
{
    return glbinding::Binding::ColorTable(target, internalformat, width, format, type, table);
}

inline void glColorTableEXT(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const void * table)
{
    return glbinding::Binding::ColorTableEXT(target, internalFormat, width, format, type, table);
}

inline void glColorTableParameterfv(GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::ColorTableParameterfv(target, pname, params);
}

inline void glColorTableParameterfvSGI(GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::ColorTableParameterfvSGI(target, pname, params);
}

inline void glColorTableParameteriv(GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::ColorTableParameteriv(target, pname, params);
}

inline void glColorTableParameterivSGI(GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::ColorTableParameterivSGI(target, pname, params);
}

inline void glColorTableSGI(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void * table)
{
    return glbinding::Binding::ColorTableSGI(target, internalformat, width, format, type, table);
}

inline void glCombinerInputNV(GLenum stage, GLenum portion, GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage)
{
    return glbinding::Binding::CombinerInputNV(stage, portion, variable, input, mapping, componentUsage);
}

inline void glCombinerOutputNV(GLenum stage, GLenum portion, GLenum abOutput, GLenum cdOutput, GLenum sumOutput, GLenum scale, GLenum bias, GLboolean abDotProduct, GLboolean cdDotProduct, GLboolean muxSum)
{
    return glbinding::Binding::CombinerOutputNV(stage, portion, abOutput, cdOutput, sumOutput, scale, bias, abDotProduct, cdDotProduct, muxSum);
}

inline void glCombinerParameterfNV(GLenum pname, GLfloat param)
{
    return glbinding::Binding::CombinerParameterfNV(pname, param);
}

inline void glCombinerParameterfvNV(GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::CombinerParameterfvNV(pname, params);
}

inline void glCombinerParameteriNV(GLenum pname, GLint param)
{
    return glbinding::Binding::CombinerParameteriNV(pname, param);
}

inline void glCombinerParameterivNV(GLenum pname, const GLint * params)
{
    return glbinding::Binding::CombinerParameterivNV(pname, params);
}

inline void glCombinerStageParameterfvNV(GLenum stage, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::CombinerStageParameterfvNV(stage, pname, params);
}

inline void glCompileShaderARB(GLhandleARB shaderObj)
{
    return glbinding::Binding::CompileShaderARB(shaderObj);
}

inline void glCompileShaderIncludeARB(GLuint shader, GLsizei count, const GLchar *const* path, const GLint * length)
{
    return glbinding::Binding::CompileShaderIncludeARB(shader, count, path, length);
}

inline void glCompressedMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedMultiTexImage1DEXT(texunit, target, level, internalformat, width, border, imageSize, bits);
}

inline void glCompressedMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedMultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, imageSize, bits);
}

inline void glCompressedMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedMultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, imageSize, bits);
}

inline void glCompressedMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedMultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, imageSize, bits);
}

inline void glCompressedMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, imageSize, bits);
}

inline void glCompressedMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits);
}

inline void glCompressedTexImage1DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTexImage1DARB(target, level, internalformat, width, border, imageSize, data);
}

inline void glCompressedTexImage2DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data);
}

inline void glCompressedTexImage3DARB(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTexImage3DARB(target, level, internalformat, width, height, depth, border, imageSize, data);
}

inline void glCompressedTexSubImage1DARB(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTexSubImage1DARB(target, level, xoffset, width, format, imageSize, data);
}

inline void glCompressedTexSubImage2DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

inline void glCompressedTexSubImage3DARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTexSubImage3DARB(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

inline void glCompressedTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedTextureImage1DEXT(texture, target, level, internalformat, width, border, imageSize, bits);
}

inline void glCompressedTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedTextureImage2DEXT(texture, target, level, internalformat, width, height, border, imageSize, bits);
}

inline void glCompressedTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedTextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, imageSize, bits);
}

inline void glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
}

inline void glCompressedTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedTextureSubImage1DEXT(texture, target, level, xoffset, width, format, imageSize, bits);
}

inline void glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
}

inline void glCompressedTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, imageSize, bits);
}

inline void glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data)
{
    return glbinding::Binding::CompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

inline void glCompressedTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * bits)
{
    return glbinding::Binding::CompressedTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits);
}

inline void glConvolutionFilter1D(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void * image)
{
    return glbinding::Binding::ConvolutionFilter1D(target, internalformat, width, format, type, image);
}

inline void glConvolutionFilter1DEXT(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const void * image)
{
    return glbinding::Binding::ConvolutionFilter1DEXT(target, internalformat, width, format, type, image);
}

inline void glConvolutionFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * image)
{
    return glbinding::Binding::ConvolutionFilter2D(target, internalformat, width, height, format, type, image);
}

inline void glConvolutionFilter2DEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * image)
{
    return glbinding::Binding::ConvolutionFilter2DEXT(target, internalformat, width, height, format, type, image);
}

inline void glConvolutionParameterf(GLenum target, GLenum pname, GLfloat params)
{
    return glbinding::Binding::ConvolutionParameterf(target, pname, params);
}

inline void glConvolutionParameterfEXT(GLenum target, GLenum pname, GLfloat params)
{
    return glbinding::Binding::ConvolutionParameterfEXT(target, pname, params);
}

inline void glConvolutionParameterfv(GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::ConvolutionParameterfv(target, pname, params);
}

inline void glConvolutionParameterfvEXT(GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::ConvolutionParameterfvEXT(target, pname, params);
}

inline void glConvolutionParameteri(GLenum target, GLenum pname, GLint params)
{
    return glbinding::Binding::ConvolutionParameteri(target, pname, params);
}

inline void glConvolutionParameteriEXT(GLenum target, GLenum pname, GLint params)
{
    return glbinding::Binding::ConvolutionParameteriEXT(target, pname, params);
}

inline void glConvolutionParameteriv(GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::ConvolutionParameteriv(target, pname, params);
}

inline void glConvolutionParameterivEXT(GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::ConvolutionParameterivEXT(target, pname, params);
}

inline void glConvolutionParameterxOES(GLenum target, GLenum pname, GLfixed param)
{
    return glbinding::Binding::ConvolutionParameterxOES(target, pname, param);
}

inline void glConvolutionParameterxvOES(GLenum target, GLenum pname, const GLfixed * params)
{
    return glbinding::Binding::ConvolutionParameterxvOES(target, pname, params);
}

inline void glCopyColorSubTable(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyColorSubTable(target, start, x, y, width);
}

inline void glCopyColorSubTableEXT(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyColorSubTableEXT(target, start, x, y, width);
}

inline void glCopyColorTable(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyColorTable(target, internalformat, x, y, width);
}

inline void glCopyColorTableSGI(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyColorTableSGI(target, internalformat, x, y, width);
}

inline void glCopyConvolutionFilter1D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyConvolutionFilter1D(target, internalformat, x, y, width);
}

inline void glCopyConvolutionFilter1DEXT(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyConvolutionFilter1DEXT(target, internalformat, x, y, width);
}

inline void glCopyConvolutionFilter2D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyConvolutionFilter2D(target, internalformat, x, y, width, height);
}

inline void glCopyConvolutionFilter2DEXT(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyConvolutionFilter2DEXT(target, internalformat, x, y, width, height);
}

inline void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
{
    return glbinding::Binding::CopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

inline void glCopyImageSubDataNV(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth)
{
    return glbinding::Binding::CopyImageSubDataNV(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth);
}

inline void glCopyMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
    return glbinding::Binding::CopyMultiTexImage1DEXT(texunit, target, level, internalformat, x, y, width, border);
}

inline void glCopyMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    return glbinding::Binding::CopyMultiTexImage2DEXT(texunit, target, level, internalformat, x, y, width, height, border);
}

inline void glCopyMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyMultiTexSubImage1DEXT(texunit, target, level, xoffset, x, y, width);
}

inline void glCopyMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyMultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, x, y, width, height);
}

inline void glCopyMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyMultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

inline void glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizei size)
{
    return glbinding::Binding::CopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
}

inline void glCopyPathNV(GLuint resultPath, GLuint srcPath)
{
    return glbinding::Binding::CopyPathNV(resultPath, srcPath);
}

inline void glCopyTexImage1DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
    return glbinding::Binding::CopyTexImage1DEXT(target, level, internalformat, x, y, width, border);
}

inline void glCopyTexImage2DEXT(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    return glbinding::Binding::CopyTexImage2DEXT(target, level, internalformat, x, y, width, height, border);
}

inline void glCopyTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyTexSubImage1DEXT(target, level, xoffset, x, y, width);
}

inline void glCopyTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyTexSubImage2DEXT(target, level, xoffset, yoffset, x, y, width, height);
}

inline void glCopyTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyTexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

inline void glCopyTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
    return glbinding::Binding::CopyTextureImage1DEXT(texture, target, level, internalformat, x, y, width, border);
}

inline void glCopyTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    return glbinding::Binding::CopyTextureImage2DEXT(texture, target, level, internalformat, x, y, width, height, border);
}

inline void glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyTextureSubImage1D(texture, level, xoffset, x, y, width);
}

inline void glCopyTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
    return glbinding::Binding::CopyTextureSubImage1DEXT(texture, target, level, xoffset, x, y, width);
}

inline void glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
}

inline void glCopyTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, x, y, width, height);
}

inline void glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
}

inline void glCopyTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::CopyTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

inline void glCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void * paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat * transformValues)
{
    return glbinding::Binding::CoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues);
}

inline void glCoverFillPathNV(GLuint path, GLenum coverMode)
{
    return glbinding::Binding::CoverFillPathNV(path, coverMode);
}

inline void glCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void * paths, GLuint pathBase, GLenum coverMode, GLenum transformType, const GLfloat * transformValues)
{
    return glbinding::Binding::CoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, coverMode, transformType, transformValues);
}

inline void glCoverStrokePathNV(GLuint path, GLenum coverMode)
{
    return glbinding::Binding::CoverStrokePathNV(path, coverMode);
}

inline void glCoverageModulationNV(GLenum components)
{
    return glbinding::Binding::CoverageModulationNV(components);
}

inline void glCoverageModulationTableNV(GLsizei n, const GLfloat * v)
{
    return glbinding::Binding::CoverageModulationTableNV(n, v);
}

inline void glCreateBuffers(GLsizei n, GLuint * buffers)
{
    return glbinding::Binding::CreateBuffers(n, buffers);
}

inline void glCreateFramebuffers(GLsizei n, GLuint * framebuffers)
{
    return glbinding::Binding::CreateFramebuffers(n, framebuffers);
}

inline void glCreatePerfQueryINTEL(GLuint queryId, GLuint * queryHandle)
{
    return glbinding::Binding::CreatePerfQueryINTEL(queryId, queryHandle);
}

inline GLhandleARB glCreateProgramObjectARB()
{
    return glbinding::Binding::CreateProgramObjectARB();
}

inline void glCreateProgramPipelines(GLsizei n, GLuint * pipelines)
{
    return glbinding::Binding::CreateProgramPipelines(n, pipelines);
}

inline void glCreateQueries(GLenum target, GLsizei n, GLuint * ids)
{
    return glbinding::Binding::CreateQueries(target, n, ids);
}

inline void glCreateRenderbuffers(GLsizei n, GLuint * renderbuffers)
{
    return glbinding::Binding::CreateRenderbuffers(n, renderbuffers);
}

inline void glCreateSamplers(GLsizei n, GLuint * samplers)
{
    return glbinding::Binding::CreateSamplers(n, samplers);
}

inline GLhandleARB glCreateShaderObjectARB(GLenum shaderType)
{
    return glbinding::Binding::CreateShaderObjectARB(shaderType);
}

inline GLuint glCreateShaderProgramEXT(GLenum type, const GLchar * string)
{
    return glbinding::Binding::CreateShaderProgramEXT(type, string);
}

inline GLsync glCreateSyncFromCLeventARB(_cl_context * context, _cl_event * event, UnusedMask flags)
{
    return glbinding::Binding::CreateSyncFromCLeventARB(context, event, flags);
}

inline void glCreateTextures(GLenum target, GLsizei n, GLuint * textures)
{
    return glbinding::Binding::CreateTextures(target, n, textures);
}

inline void glCreateTransformFeedbacks(GLsizei n, GLuint * ids)
{
    return glbinding::Binding::CreateTransformFeedbacks(n, ids);
}

inline void glCreateVertexArrays(GLsizei n, GLuint * arrays)
{
    return glbinding::Binding::CreateVertexArrays(n, arrays);
}

inline void glCullParameterdvEXT(GLenum pname, GLdouble * params)
{
    return glbinding::Binding::CullParameterdvEXT(pname, params);
}

inline void glCullParameterfvEXT(GLenum pname, GLfloat * params)
{
    return glbinding::Binding::CullParameterfvEXT(pname, params);
}

inline void glCurrentPaletteMatrixARB(GLint index)
{
    return glbinding::Binding::CurrentPaletteMatrixARB(index);
}

inline void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam)
{
    return glbinding::Binding::DebugMessageCallback(callback, userParam);
}

inline void glDebugMessageCallbackAMD(GLDEBUGPROCAMD callback, void * userParam)
{
    return glbinding::Binding::DebugMessageCallbackAMD(callback, userParam);
}

inline void glDebugMessageCallbackARB(GLDEBUGPROCARB callback, const void * userParam)
{
    return glbinding::Binding::DebugMessageCallbackARB(callback, userParam);
}

inline void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled)
{
    return glbinding::Binding::DebugMessageControl(source, type, severity, count, ids, enabled);
}

inline void glDebugMessageControlARB(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled)
{
    return glbinding::Binding::DebugMessageControlARB(source, type, severity, count, ids, enabled);
}

inline void glDebugMessageEnableAMD(GLenum category, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled)
{
    return glbinding::Binding::DebugMessageEnableAMD(category, severity, count, ids, enabled);
}

inline void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf)
{
    return glbinding::Binding::DebugMessageInsert(source, type, id, severity, length, buf);
}

inline void glDebugMessageInsertAMD(GLenum category, GLenum severity, GLuint id, GLsizei length, const GLchar * buf)
{
    return glbinding::Binding::DebugMessageInsertAMD(category, severity, id, length, buf);
}

inline void glDebugMessageInsertARB(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf)
{
    return glbinding::Binding::DebugMessageInsertARB(source, type, id, severity, length, buf);
}

inline void glDeformSGIX(FfdMaskSGIX mask)
{
    return glbinding::Binding::DeformSGIX(mask);
}

inline void glDeformationMap3dSGIX(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, GLdouble w1, GLdouble w2, GLint wstride, GLint worder, const GLdouble * points)
{
    return glbinding::Binding::DeformationMap3dSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points);
}

inline void glDeformationMap3fSGIX(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, GLfloat w1, GLfloat w2, GLint wstride, GLint worder, const GLfloat * points)
{
    return glbinding::Binding::DeformationMap3fSGIX(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, w1, w2, wstride, worder, points);
}

inline void glDeleteAsyncMarkersSGIX(GLuint marker, GLsizei range)
{
    return glbinding::Binding::DeleteAsyncMarkersSGIX(marker, range);
}

inline void glDeleteBuffersARB(GLsizei n, const GLuint * buffers)
{
    return glbinding::Binding::DeleteBuffersARB(n, buffers);
}

inline void glDeleteFencesAPPLE(GLsizei n, const GLuint * fences)
{
    return glbinding::Binding::DeleteFencesAPPLE(n, fences);
}

inline void glDeleteFencesNV(GLsizei n, const GLuint * fences)
{
    return glbinding::Binding::DeleteFencesNV(n, fences);
}

inline void glDeleteFragmentShaderATI(GLuint id)
{
    return glbinding::Binding::DeleteFragmentShaderATI(id);
}

inline void glDeleteFramebuffersEXT(GLsizei n, const GLuint * framebuffers)
{
    return glbinding::Binding::DeleteFramebuffersEXT(n, framebuffers);
}

inline void glDeleteNamedStringARB(GLint namelen, const GLchar * name)
{
    return glbinding::Binding::DeleteNamedStringARB(namelen, name);
}

inline void glDeleteNamesAMD(GLenum identifier, GLuint num, const GLuint * names)
{
    return glbinding::Binding::DeleteNamesAMD(identifier, num, names);
}

inline void glDeleteObjectARB(GLhandleARB obj)
{
    return glbinding::Binding::DeleteObjectARB(obj);
}

inline void glDeleteOcclusionQueriesNV(GLsizei n, const GLuint * ids)
{
    return glbinding::Binding::DeleteOcclusionQueriesNV(n, ids);
}

inline void glDeletePathsNV(GLuint path, GLsizei range)
{
    return glbinding::Binding::DeletePathsNV(path, range);
}

inline void glDeletePerfMonitorsAMD(GLsizei n, GLuint * monitors)
{
    return glbinding::Binding::DeletePerfMonitorsAMD(n, monitors);
}

inline void glDeletePerfQueryINTEL(GLuint queryHandle)
{
    return glbinding::Binding::DeletePerfQueryINTEL(queryHandle);
}

inline void glDeleteProgramsARB(GLsizei n, const GLuint * programs)
{
    return glbinding::Binding::DeleteProgramsARB(n, programs);
}

inline void glDeleteProgramsNV(GLsizei n, const GLuint * programs)
{
    return glbinding::Binding::DeleteProgramsNV(n, programs);
}

inline void glDeleteQueriesARB(GLsizei n, const GLuint * ids)
{
    return glbinding::Binding::DeleteQueriesARB(n, ids);
}

inline void glDeleteRenderbuffersEXT(GLsizei n, const GLuint * renderbuffers)
{
    return glbinding::Binding::DeleteRenderbuffersEXT(n, renderbuffers);
}

inline void glDeleteTexturesEXT(GLsizei n, const GLuint * textures)
{
    return glbinding::Binding::DeleteTexturesEXT(n, textures);
}

inline void glDeleteTransformFeedbacksNV(GLsizei n, const GLuint * ids)
{
    return glbinding::Binding::DeleteTransformFeedbacksNV(n, ids);
}

inline void glDeleteVertexArraysAPPLE(GLsizei n, const GLuint * arrays)
{
    return glbinding::Binding::DeleteVertexArraysAPPLE(n, arrays);
}

inline void glDeleteVertexShaderEXT(GLuint id)
{
    return glbinding::Binding::DeleteVertexShaderEXT(id);
}

inline void glDepthBoundsEXT(GLclampd zmin, GLclampd zmax)
{
    return glbinding::Binding::DepthBoundsEXT(zmin, zmax);
}

inline void glDepthBoundsdNV(GLdouble zmin, GLdouble zmax)
{
    return glbinding::Binding::DepthBoundsdNV(zmin, zmax);
}

inline void glDepthRangedNV(GLdouble zNear, GLdouble zFar)
{
    return glbinding::Binding::DepthRangedNV(zNear, zFar);
}

inline void glDepthRangefOES(GLclampf n, GLclampf f)
{
    return glbinding::Binding::DepthRangefOES(n, f);
}

inline void glDepthRangexOES(GLfixed n, GLfixed f)
{
    return glbinding::Binding::DepthRangexOES(n, f);
}

inline void glDetachObjectARB(GLhandleARB containerObj, GLhandleARB attachedObj)
{
    return glbinding::Binding::DetachObjectARB(containerObj, attachedObj);
}

inline void glDetailTexFuncSGIS(GLenum target, GLsizei n, const GLfloat * points)
{
    return glbinding::Binding::DetailTexFuncSGIS(target, n, points);
}

inline void glDisableClientStateIndexedEXT(GLenum array, GLuint index)
{
    return glbinding::Binding::DisableClientStateIndexedEXT(array, index);
}

inline void glDisableClientStateiEXT(GLenum array, GLuint index)
{
    return glbinding::Binding::DisableClientStateiEXT(array, index);
}

inline void glDisableIndexedEXT(GLenum target, GLuint index)
{
    return glbinding::Binding::DisableIndexedEXT(target, index);
}

inline void glDisableVariantClientStateEXT(GLuint id)
{
    return glbinding::Binding::DisableVariantClientStateEXT(id);
}

inline void glDisableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
    return glbinding::Binding::DisableVertexArrayAttrib(vaobj, index);
}

inline void glDisableVertexArrayAttribEXT(GLuint vaobj, GLuint index)
{
    return glbinding::Binding::DisableVertexArrayAttribEXT(vaobj, index);
}

inline void glDisableVertexArrayEXT(GLuint vaobj, GLenum array)
{
    return glbinding::Binding::DisableVertexArrayEXT(vaobj, array);
}

inline void glDisableVertexAttribAPPLE(GLuint index, GLenum pname)
{
    return glbinding::Binding::DisableVertexAttribAPPLE(index, pname);
}

inline void glDisableVertexAttribArrayARB(GLuint index)
{
    return glbinding::Binding::DisableVertexAttribArrayARB(index);
}

inline void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
{
    return glbinding::Binding::DispatchCompute(num_groups_x, num_groups_y, num_groups_z);
}

inline void glDispatchComputeGroupSizeARB(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z, GLuint group_size_x, GLuint group_size_y, GLuint group_size_z)
{
    return glbinding::Binding::DispatchComputeGroupSizeARB(num_groups_x, num_groups_y, num_groups_z, group_size_x, group_size_y, group_size_z);
}

inline void glDispatchComputeIndirect(GLintptr indirect)
{
    return glbinding::Binding::DispatchComputeIndirect(indirect);
}

inline void glDrawArraysEXT(GLenum mode, GLint first, GLsizei count)
{
    return glbinding::Binding::DrawArraysEXT(mode, first, count);
}

inline void glDrawArraysInstancedARB(GLenum mode, GLint first, GLsizei count, GLsizei primcount)
{
    return glbinding::Binding::DrawArraysInstancedARB(mode, first, count, primcount);
}

inline void glDrawArraysInstancedEXT(GLenum mode, GLint start, GLsizei count, GLsizei primcount)
{
    return glbinding::Binding::DrawArraysInstancedEXT(mode, start, count, primcount);
}

inline void glDrawBuffersARB(GLsizei n, const GLenum * bufs)
{
    return glbinding::Binding::DrawBuffersARB(n, bufs);
}

inline void glDrawBuffersATI(GLsizei n, const GLenum * bufs)
{
    return glbinding::Binding::DrawBuffersATI(n, bufs);
}

inline void glDrawElementArrayAPPLE(GLenum mode, GLint first, GLsizei count)
{
    return glbinding::Binding::DrawElementArrayAPPLE(mode, first, count);
}

inline void glDrawElementArrayATI(GLenum mode, GLsizei count)
{
    return glbinding::Binding::DrawElementArrayATI(mode, count);
}

inline void glDrawElementsInstancedARB(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei primcount)
{
    return glbinding::Binding::DrawElementsInstancedARB(mode, count, type, indices, primcount);
}

inline void glDrawElementsInstancedEXT(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei primcount)
{
    return glbinding::Binding::DrawElementsInstancedEXT(mode, count, type, indices, primcount);
}

inline void glDrawMeshArraysSUN(GLenum mode, GLint first, GLsizei count, GLsizei width)
{
    return glbinding::Binding::DrawMeshArraysSUN(mode, first, count, width);
}

inline void glDrawRangeElementArrayAPPLE(GLenum mode, GLuint start, GLuint end, GLint first, GLsizei count)
{
    return glbinding::Binding::DrawRangeElementArrayAPPLE(mode, start, end, first, count);
}

inline void glDrawRangeElementArrayATI(GLenum mode, GLuint start, GLuint end, GLsizei count)
{
    return glbinding::Binding::DrawRangeElementArrayATI(mode, start, end, count);
}

inline void glDrawRangeElementsEXT(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices)
{
    return glbinding::Binding::DrawRangeElementsEXT(mode, start, end, count, type, indices);
}

inline void glDrawTextureNV(GLuint texture, GLuint sampler, GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat z, GLfloat s0, GLfloat t0, GLfloat s1, GLfloat t1)
{
    return glbinding::Binding::DrawTextureNV(texture, sampler, x0, y0, x1, y1, z, s0, t0, s1, t1);
}

inline void glDrawTransformFeedbackNV(GLenum mode, GLuint id)
{
    return glbinding::Binding::DrawTransformFeedbackNV(mode, id);
}

inline void glEdgeFlagFormatNV(GLsizei stride)
{
    return glbinding::Binding::EdgeFlagFormatNV(stride);
}

inline void glEdgeFlagPointerEXT(GLsizei stride, GLsizei count, const GLboolean * pointer)
{
    return glbinding::Binding::EdgeFlagPointerEXT(stride, count, pointer);
}

inline void glEdgeFlagPointerListIBM(GLint stride, const GLboolean ** pointer, GLint ptrstride)
{
    return glbinding::Binding::EdgeFlagPointerListIBM(stride, pointer, ptrstride);
}

inline void glElementPointerAPPLE(GLenum type, const void * pointer)
{
    return glbinding::Binding::ElementPointerAPPLE(type, pointer);
}

inline void glElementPointerATI(GLenum type, const void * pointer)
{
    return glbinding::Binding::ElementPointerATI(type, pointer);
}

inline void glEnableClientStateIndexedEXT(GLenum array, GLuint index)
{
    return glbinding::Binding::EnableClientStateIndexedEXT(array, index);
}

inline void glEnableClientStateiEXT(GLenum array, GLuint index)
{
    return glbinding::Binding::EnableClientStateiEXT(array, index);
}

inline void glEnableIndexedEXT(GLenum target, GLuint index)
{
    return glbinding::Binding::EnableIndexedEXT(target, index);
}

inline void glEnableVariantClientStateEXT(GLuint id)
{
    return glbinding::Binding::EnableVariantClientStateEXT(id);
}

inline void glEnableVertexArrayAttrib(GLuint vaobj, GLuint index)
{
    return glbinding::Binding::EnableVertexArrayAttrib(vaobj, index);
}

inline void glEnableVertexArrayAttribEXT(GLuint vaobj, GLuint index)
{
    return glbinding::Binding::EnableVertexArrayAttribEXT(vaobj, index);
}

inline void glEnableVertexArrayEXT(GLuint vaobj, GLenum array)
{
    return glbinding::Binding::EnableVertexArrayEXT(vaobj, array);
}

inline void glEnableVertexAttribAPPLE(GLuint index, GLenum pname)
{
    return glbinding::Binding::EnableVertexAttribAPPLE(index, pname);
}

inline void glEnableVertexAttribArrayARB(GLuint index)
{
    return glbinding::Binding::EnableVertexAttribArrayARB(index);
}

inline void glEndConditionalRenderNV()
{
    return glbinding::Binding::EndConditionalRenderNV();
}

inline void glEndConditionalRenderNVX()
{
    return glbinding::Binding::EndConditionalRenderNVX();
}

inline void glEndFragmentShaderATI()
{
    return glbinding::Binding::EndFragmentShaderATI();
}

inline void glEndOcclusionQueryNV()
{
    return glbinding::Binding::EndOcclusionQueryNV();
}

inline void glEndPerfMonitorAMD(GLuint monitor)
{
    return glbinding::Binding::EndPerfMonitorAMD(monitor);
}

inline void glEndPerfQueryINTEL(GLuint queryHandle)
{
    return glbinding::Binding::EndPerfQueryINTEL(queryHandle);
}

inline void glEndQueryARB(GLenum target)
{
    return glbinding::Binding::EndQueryARB(target);
}

inline void glEndTransformFeedbackEXT()
{
    return glbinding::Binding::EndTransformFeedbackEXT();
}

inline void glEndTransformFeedbackNV()
{
    return glbinding::Binding::EndTransformFeedbackNV();
}

inline void glEndVertexShaderEXT()
{
    return glbinding::Binding::EndVertexShaderEXT();
}

inline void glEndVideoCaptureNV(GLuint video_capture_slot)
{
    return glbinding::Binding::EndVideoCaptureNV(video_capture_slot);
}

inline void glEvalCoord1xOES(GLfixed u)
{
    return glbinding::Binding::EvalCoord1xOES(u);
}

inline void glEvalCoord1xvOES(const GLfixed * coords)
{
    return glbinding::Binding::EvalCoord1xvOES(coords);
}

inline void glEvalCoord2xOES(GLfixed u, GLfixed v)
{
    return glbinding::Binding::EvalCoord2xOES(u, v);
}

inline void glEvalCoord2xvOES(const GLfixed * coords)
{
    return glbinding::Binding::EvalCoord2xvOES(coords);
}

inline void glEvalMapsNV(GLenum target, GLenum mode)
{
    return glbinding::Binding::EvalMapsNV(target, mode);
}

inline void glExecuteProgramNV(GLenum target, GLuint id, const GLfloat * params)
{
    return glbinding::Binding::ExecuteProgramNV(target, id, params);
}

inline void glExtractComponentEXT(GLuint res, GLuint src, GLuint num)
{
    return glbinding::Binding::ExtractComponentEXT(res, src, num);
}

inline void glFeedbackBufferxOES(GLsizei n, GLenum type, const GLfixed * buffer)
{
    return glbinding::Binding::FeedbackBufferxOES(n, type, buffer);
}

inline void glFinalCombinerInputNV(GLenum variable, GLenum input, GLenum mapping, GLenum componentUsage)
{
    return glbinding::Binding::FinalCombinerInputNV(variable, input, mapping, componentUsage);
}

inline GLint glFinishAsyncSGIX(GLuint * markerp)
{
    return glbinding::Binding::FinishAsyncSGIX(markerp);
}

inline void glFinishFenceAPPLE(GLuint fence)
{
    return glbinding::Binding::FinishFenceAPPLE(fence);
}

inline void glFinishFenceNV(GLuint fence)
{
    return glbinding::Binding::FinishFenceNV(fence);
}

inline void glFinishObjectAPPLE(GLenum object, GLint name)
{
    return glbinding::Binding::FinishObjectAPPLE(object, name);
}

inline void glFinishTextureSUNX()
{
    return glbinding::Binding::FinishTextureSUNX();
}

inline void glFlushMappedBufferRangeAPPLE(GLenum target, GLintptr offset, GLsizeiptr size)
{
    return glbinding::Binding::FlushMappedBufferRangeAPPLE(target, offset, size);
}

inline void glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizei length)
{
    return glbinding::Binding::FlushMappedNamedBufferRange(buffer, offset, length);
}

inline void glFlushMappedNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
    return glbinding::Binding::FlushMappedNamedBufferRangeEXT(buffer, offset, length);
}

inline void glFlushPixelDataRangeNV(GLenum target)
{
    return glbinding::Binding::FlushPixelDataRangeNV(target);
}

inline void glFlushRasterSGIX()
{
    return glbinding::Binding::FlushRasterSGIX();
}

inline void glFlushStaticDataIBM(GLenum target)
{
    return glbinding::Binding::FlushStaticDataIBM(target);
}

inline void glFlushVertexArrayRangeAPPLE(GLsizei length, void * pointer)
{
    return glbinding::Binding::FlushVertexArrayRangeAPPLE(length, pointer);
}

inline void glFlushVertexArrayRangeNV()
{
    return glbinding::Binding::FlushVertexArrayRangeNV();
}

inline void glFogCoordFormatNV(GLenum type, GLsizei stride)
{
    return glbinding::Binding::FogCoordFormatNV(type, stride);
}

inline void glFogCoordPointerEXT(GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::FogCoordPointerEXT(type, stride, pointer);
}

inline void glFogCoordPointerListIBM(GLenum type, GLint stride, const void ** pointer, GLint ptrstride)
{
    return glbinding::Binding::FogCoordPointerListIBM(type, stride, pointer, ptrstride);
}

inline void glFogCoorddEXT(GLdouble coord)
{
    return glbinding::Binding::FogCoorddEXT(coord);
}

inline void glFogCoorddvEXT(const GLdouble * coord)
{
    return glbinding::Binding::FogCoorddvEXT(coord);
}

inline void glFogCoordfEXT(GLfloat coord)
{
    return glbinding::Binding::FogCoordfEXT(coord);
}

inline void glFogCoordfvEXT(const GLfloat * coord)
{
    return glbinding::Binding::FogCoordfvEXT(coord);
}

inline void glFogCoordhNV(GLhalfNV fog)
{
    return glbinding::Binding::FogCoordhNV(fog);
}

inline void glFogCoordhvNV(const GLhalfNV * fog)
{
    return glbinding::Binding::FogCoordhvNV(fog);
}

inline void glFogFuncSGIS(GLsizei n, const GLfloat * points)
{
    return glbinding::Binding::FogFuncSGIS(n, points);
}

inline void glFogxOES(GLenum pname, GLfixed param)
{
    return glbinding::Binding::FogxOES(pname, param);
}

inline void glFogxvOES(GLenum pname, const GLfixed * param)
{
    return glbinding::Binding::FogxvOES(pname, param);
}

inline void glFragmentColorMaterialSGIX(GLenum face, GLenum mode)
{
    return glbinding::Binding::FragmentColorMaterialSGIX(face, mode);
}

inline void glFragmentCoverageColorNV(GLuint color)
{
    return glbinding::Binding::FragmentCoverageColorNV(color);
}

inline void glFragmentLightModelfSGIX(GLenum pname, GLfloat param)
{
    return glbinding::Binding::FragmentLightModelfSGIX(pname, param);
}

inline void glFragmentLightModelfvSGIX(GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::FragmentLightModelfvSGIX(pname, params);
}

inline void glFragmentLightModeliSGIX(GLenum pname, GLint param)
{
    return glbinding::Binding::FragmentLightModeliSGIX(pname, param);
}

inline void glFragmentLightModelivSGIX(GLenum pname, const GLint * params)
{
    return glbinding::Binding::FragmentLightModelivSGIX(pname, params);
}

inline void glFragmentLightfSGIX(GLenum light, GLenum pname, GLfloat param)
{
    return glbinding::Binding::FragmentLightfSGIX(light, pname, param);
}

inline void glFragmentLightfvSGIX(GLenum light, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::FragmentLightfvSGIX(light, pname, params);
}

inline void glFragmentLightiSGIX(GLenum light, GLenum pname, GLint param)
{
    return glbinding::Binding::FragmentLightiSGIX(light, pname, param);
}

inline void glFragmentLightivSGIX(GLenum light, GLenum pname, const GLint * params)
{
    return glbinding::Binding::FragmentLightivSGIX(light, pname, params);
}

inline void glFragmentMaterialfSGIX(GLenum face, GLenum pname, GLfloat param)
{
    return glbinding::Binding::FragmentMaterialfSGIX(face, pname, param);
}

inline void glFragmentMaterialfvSGIX(GLenum face, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::FragmentMaterialfvSGIX(face, pname, params);
}

inline void glFragmentMaterialiSGIX(GLenum face, GLenum pname, GLint param)
{
    return glbinding::Binding::FragmentMaterialiSGIX(face, pname, param);
}

inline void glFragmentMaterialivSGIX(GLenum face, GLenum pname, const GLint * params)
{
    return glbinding::Binding::FragmentMaterialivSGIX(face, pname, params);
}

inline void glFrameTerminatorGREMEDY()
{
    return glbinding::Binding::FrameTerminatorGREMEDY();
}

inline void glFrameZoomSGIX(GLint factor)
{
    return glbinding::Binding::FrameZoomSGIX(factor);
}

inline void glFramebufferDrawBufferEXT(GLuint framebuffer, GLenum mode)
{
    return glbinding::Binding::FramebufferDrawBufferEXT(framebuffer, mode);
}

inline void glFramebufferDrawBuffersEXT(GLuint framebuffer, GLsizei n, const GLenum * bufs)
{
    return glbinding::Binding::FramebufferDrawBuffersEXT(framebuffer, n, bufs);
}

inline void glFramebufferParameteri(GLenum target, GLenum pname, GLint param)
{
    return glbinding::Binding::FramebufferParameteri(target, pname, param);
}

inline void glFramebufferReadBufferEXT(GLuint framebuffer, GLenum mode)
{
    return glbinding::Binding::FramebufferReadBufferEXT(framebuffer, mode);
}

inline void glFramebufferRenderbufferEXT(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    return glbinding::Binding::FramebufferRenderbufferEXT(target, attachment, renderbuffertarget, renderbuffer);
}

inline void glFramebufferSampleLocationsfvNV(GLenum target, GLuint start, GLsizei count, const GLfloat * v)
{
    return glbinding::Binding::FramebufferSampleLocationsfvNV(target, start, count, v);
}

inline void glFramebufferTexture1DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    return glbinding::Binding::FramebufferTexture1DEXT(target, attachment, textarget, texture, level);
}

inline void glFramebufferTexture2DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    return glbinding::Binding::FramebufferTexture2DEXT(target, attachment, textarget, texture, level);
}

inline void glFramebufferTexture3DEXT(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
    return glbinding::Binding::FramebufferTexture3DEXT(target, attachment, textarget, texture, level, zoffset);
}

inline void glFramebufferTextureARB(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
    return glbinding::Binding::FramebufferTextureARB(target, attachment, texture, level);
}

inline void glFramebufferTextureEXT(GLenum target, GLenum attachment, GLuint texture, GLint level)
{
    return glbinding::Binding::FramebufferTextureEXT(target, attachment, texture, level);
}

inline void glFramebufferTextureFaceARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face)
{
    return glbinding::Binding::FramebufferTextureFaceARB(target, attachment, texture, level, face);
}

inline void glFramebufferTextureFaceEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLenum face)
{
    return glbinding::Binding::FramebufferTextureFaceEXT(target, attachment, texture, level, face);
}

inline void glFramebufferTextureLayerARB(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
    return glbinding::Binding::FramebufferTextureLayerARB(target, attachment, texture, level, layer);
}

inline void glFramebufferTextureLayerEXT(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
    return glbinding::Binding::FramebufferTextureLayerEXT(target, attachment, texture, level, layer);
}

inline void glFreeObjectBufferATI(GLuint buffer)
{
    return glbinding::Binding::FreeObjectBufferATI(buffer);
}

inline void glFrustumfOES(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
{
    return glbinding::Binding::FrustumfOES(l, r, b, t, n, f);
}

inline void glFrustumxOES(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f)
{
    return glbinding::Binding::FrustumxOES(l, r, b, t, n, f);
}

inline GLuint glGenAsyncMarkersSGIX(GLsizei range)
{
    return glbinding::Binding::GenAsyncMarkersSGIX(range);
}

inline void glGenBuffersARB(GLsizei n, GLuint * buffers)
{
    return glbinding::Binding::GenBuffersARB(n, buffers);
}

inline void glGenFencesAPPLE(GLsizei n, GLuint * fences)
{
    return glbinding::Binding::GenFencesAPPLE(n, fences);
}

inline void glGenFencesNV(GLsizei n, GLuint * fences)
{
    return glbinding::Binding::GenFencesNV(n, fences);
}

inline GLuint glGenFragmentShadersATI(GLuint range)
{
    return glbinding::Binding::GenFragmentShadersATI(range);
}

inline void glGenFramebuffersEXT(GLsizei n, GLuint * framebuffers)
{
    return glbinding::Binding::GenFramebuffersEXT(n, framebuffers);
}

inline void glGenNamesAMD(GLenum identifier, GLuint num, GLuint * names)
{
    return glbinding::Binding::GenNamesAMD(identifier, num, names);
}

inline void glGenOcclusionQueriesNV(GLsizei n, GLuint * ids)
{
    return glbinding::Binding::GenOcclusionQueriesNV(n, ids);
}

inline GLuint glGenPathsNV(GLsizei range)
{
    return glbinding::Binding::GenPathsNV(range);
}

inline void glGenPerfMonitorsAMD(GLsizei n, GLuint * monitors)
{
    return glbinding::Binding::GenPerfMonitorsAMD(n, monitors);
}

inline void glGenProgramsARB(GLsizei n, GLuint * programs)
{
    return glbinding::Binding::GenProgramsARB(n, programs);
}

inline void glGenProgramsNV(GLsizei n, GLuint * programs)
{
    return glbinding::Binding::GenProgramsNV(n, programs);
}

inline void glGenQueriesARB(GLsizei n, GLuint * ids)
{
    return glbinding::Binding::GenQueriesARB(n, ids);
}

inline void glGenRenderbuffersEXT(GLsizei n, GLuint * renderbuffers)
{
    return glbinding::Binding::GenRenderbuffersEXT(n, renderbuffers);
}

inline GLuint glGenSymbolsEXT(GLenum datatype, GLenum storagetype, GLenum range, GLuint components)
{
    return glbinding::Binding::GenSymbolsEXT(datatype, storagetype, range, components);
}

inline void glGenTexturesEXT(GLsizei n, GLuint * textures)
{
    return glbinding::Binding::GenTexturesEXT(n, textures);
}

inline void glGenTransformFeedbacksNV(GLsizei n, GLuint * ids)
{
    return glbinding::Binding::GenTransformFeedbacksNV(n, ids);
}

inline void glGenVertexArraysAPPLE(GLsizei n, GLuint * arrays)
{
    return glbinding::Binding::GenVertexArraysAPPLE(n, arrays);
}

inline GLuint glGenVertexShadersEXT(GLuint range)
{
    return glbinding::Binding::GenVertexShadersEXT(range);
}

inline void glGenerateMipmapEXT(GLenum target)
{
    return glbinding::Binding::GenerateMipmapEXT(target);
}

inline void glGenerateMultiTexMipmapEXT(GLenum texunit, GLenum target)
{
    return glbinding::Binding::GenerateMultiTexMipmapEXT(texunit, target);
}

inline void glGenerateTextureMipmap(GLuint texture)
{
    return glbinding::Binding::GenerateTextureMipmap(texture);
}

inline void glGenerateTextureMipmapEXT(GLuint texture, GLenum target)
{
    return glbinding::Binding::GenerateTextureMipmapEXT(texture, target);
}

inline void glGetActiveAttribARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name)
{
    return glbinding::Binding::GetActiveAttribARB(programObj, index, maxLength, length, size, type, name);
}

inline void glGetActiveUniformARB(GLhandleARB programObj, GLuint index, GLsizei maxLength, GLsizei * length, GLint * size, GLenum * type, GLcharARB * name)
{
    return glbinding::Binding::GetActiveUniformARB(programObj, index, maxLength, length, size, type, name);
}

inline void glGetActiveVaryingNV(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
    return glbinding::Binding::GetActiveVaryingNV(program, index, bufSize, length, size, type, name);
}

inline void glGetArrayObjectfvATI(GLenum array, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetArrayObjectfvATI(array, pname, params);
}

inline void glGetArrayObjectivATI(GLenum array, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetArrayObjectivATI(array, pname, params);
}

inline void glGetAttachedObjectsARB(GLhandleARB containerObj, GLsizei maxCount, GLsizei * count, GLhandleARB * obj)
{
    return glbinding::Binding::GetAttachedObjectsARB(containerObj, maxCount, count, obj);
}

inline GLint glGetAttribLocationARB(GLhandleARB programObj, const GLcharARB * name)
{
    return glbinding::Binding::GetAttribLocationARB(programObj, name);
}

inline void glGetBooleanIndexedvEXT(GLenum target, GLuint index, GLboolean * data)
{
    return glbinding::Binding::GetBooleanIndexedvEXT(target, index, data);
}

inline void glGetBufferParameterivARB(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetBufferParameterivARB(target, pname, params);
}

inline void glGetBufferParameterui64vNV(GLenum target, GLenum pname, GLuint64EXT * params)
{
    return glbinding::Binding::GetBufferParameterui64vNV(target, pname, params);
}

inline void glGetBufferPointervARB(GLenum target, GLenum pname, void ** params)
{
    return glbinding::Binding::GetBufferPointervARB(target, pname, params);
}

inline void glGetBufferSubDataARB(GLenum target, GLintptrARB offset, GLsizeiptrARB size, void * data)
{
    return glbinding::Binding::GetBufferSubDataARB(target, offset, size, data);
}

inline void glGetClipPlanefOES(GLenum plane, GLfloat * equation)
{
    return glbinding::Binding::GetClipPlanefOES(plane, equation);
}

inline void glGetClipPlanexOES(GLenum plane, GLfixed * equation)
{
    return glbinding::Binding::GetClipPlanexOES(plane, equation);
}

inline void glGetColorTable(GLenum target, GLenum format, GLenum type, void * table)
{
    return glbinding::Binding::GetColorTable(target, format, type, table);
}

inline void glGetColorTableEXT(GLenum target, GLenum format, GLenum type, void * data)
{
    return glbinding::Binding::GetColorTableEXT(target, format, type, data);
}

inline void glGetColorTableParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetColorTableParameterfv(target, pname, params);
}

inline void glGetColorTableParameterfvEXT(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetColorTableParameterfvEXT(target, pname, params);
}

inline void glGetColorTableParameterfvSGI(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetColorTableParameterfvSGI(target, pname, params);
}

inline void glGetColorTableParameteriv(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetColorTableParameteriv(target, pname, params);
}

inline void glGetColorTableParameterivEXT(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetColorTableParameterivEXT(target, pname, params);
}

inline void glGetColorTableParameterivSGI(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetColorTableParameterivSGI(target, pname, params);
}

inline void glGetColorTableSGI(GLenum target, GLenum format, GLenum type, void * table)
{
    return glbinding::Binding::GetColorTableSGI(target, format, type, table);
}

inline void glGetCombinerInputParameterfvNV(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetCombinerInputParameterfvNV(stage, portion, variable, pname, params);
}

inline void glGetCombinerInputParameterivNV(GLenum stage, GLenum portion, GLenum variable, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetCombinerInputParameterivNV(stage, portion, variable, pname, params);
}

inline void glGetCombinerOutputParameterfvNV(GLenum stage, GLenum portion, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetCombinerOutputParameterfvNV(stage, portion, pname, params);
}

inline void glGetCombinerOutputParameterivNV(GLenum stage, GLenum portion, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetCombinerOutputParameterivNV(stage, portion, pname, params);
}

inline void glGetCombinerStageParameterfvNV(GLenum stage, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetCombinerStageParameterfvNV(stage, pname, params);
}

inline void glGetCompressedMultiTexImageEXT(GLenum texunit, GLenum target, GLint lod, void * img)
{
    return glbinding::Binding::GetCompressedMultiTexImageEXT(texunit, target, lod, img);
}

inline void glGetCompressedTexImageARB(GLenum target, GLint level, void * img)
{
    return glbinding::Binding::GetCompressedTexImageARB(target, level, img);
}

inline void glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels)
{
    return glbinding::Binding::GetCompressedTextureImage(texture, level, bufSize, pixels);
}

inline void glGetCompressedTextureImageEXT(GLuint texture, GLenum target, GLint lod, void * img)
{
    return glbinding::Binding::GetCompressedTextureImageEXT(texture, target, lod, img);
}

inline void glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels)
{
    return glbinding::Binding::GetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
}

inline void glGetConvolutionFilter(GLenum target, GLenum format, GLenum type, void * image)
{
    return glbinding::Binding::GetConvolutionFilter(target, format, type, image);
}

inline void glGetConvolutionFilterEXT(GLenum target, GLenum format, GLenum type, void * image)
{
    return glbinding::Binding::GetConvolutionFilterEXT(target, format, type, image);
}

inline void glGetConvolutionParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetConvolutionParameterfv(target, pname, params);
}

inline void glGetConvolutionParameterfvEXT(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetConvolutionParameterfvEXT(target, pname, params);
}

inline void glGetConvolutionParameteriv(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetConvolutionParameteriv(target, pname, params);
}

inline void glGetConvolutionParameterivEXT(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetConvolutionParameterivEXT(target, pname, params);
}

inline void glGetConvolutionParameterxvOES(GLenum target, GLenum pname, GLfixed * params)
{
    return glbinding::Binding::GetConvolutionParameterxvOES(target, pname, params);
}

inline void glGetCoverageModulationTableNV(GLsizei bufsize, GLfloat * v)
{
    return glbinding::Binding::GetCoverageModulationTableNV(bufsize, v);
}

inline GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
{
    return glbinding::Binding::GetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
}

inline GLuint glGetDebugMessageLogAMD(GLuint count, GLsizei bufsize, GLenum * categories, GLuint * severities, GLuint * ids, GLsizei * lengths, GLchar * message)
{
    return glbinding::Binding::GetDebugMessageLogAMD(count, bufsize, categories, severities, ids, lengths, message);
}

inline GLuint glGetDebugMessageLogARB(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog)
{
    return glbinding::Binding::GetDebugMessageLogARB(count, bufSize, sources, types, ids, severities, lengths, messageLog);
}

inline void glGetDetailTexFuncSGIS(GLenum target, GLfloat * points)
{
    return glbinding::Binding::GetDetailTexFuncSGIS(target, points);
}

inline void glGetDoubleIndexedvEXT(GLenum target, GLuint index, GLdouble * data)
{
    return glbinding::Binding::GetDoubleIndexedvEXT(target, index, data);
}

inline void glGetDoublei_vEXT(GLenum pname, GLuint index, GLdouble * params)
{
    return glbinding::Binding::GetDoublei_vEXT(pname, index, params);
}

inline void glGetFenceivNV(GLuint fence, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetFenceivNV(fence, pname, params);
}

inline void glGetFinalCombinerInputParameterfvNV(GLenum variable, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetFinalCombinerInputParameterfvNV(variable, pname, params);
}

inline void glGetFinalCombinerInputParameterivNV(GLenum variable, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetFinalCombinerInputParameterivNV(variable, pname, params);
}

inline void glGetFirstPerfQueryIdINTEL(GLuint * queryId)
{
    return glbinding::Binding::GetFirstPerfQueryIdINTEL(queryId);
}

inline void glGetFixedvOES(GLenum pname, GLfixed * params)
{
    return glbinding::Binding::GetFixedvOES(pname, params);
}

inline void glGetFloatIndexedvEXT(GLenum target, GLuint index, GLfloat * data)
{
    return glbinding::Binding::GetFloatIndexedvEXT(target, index, data);
}

inline void glGetFloati_vEXT(GLenum pname, GLuint index, GLfloat * params)
{
    return glbinding::Binding::GetFloati_vEXT(pname, index, params);
}

inline void glGetFogFuncSGIS(GLfloat * points)
{
    return glbinding::Binding::GetFogFuncSGIS(points);
}

inline GLint glGetFragDataLocationEXT(GLuint program, const GLchar * name)
{
    return glbinding::Binding::GetFragDataLocationEXT(program, name);
}

inline void glGetFragmentLightfvSGIX(GLenum light, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetFragmentLightfvSGIX(light, pname, params);
}

inline void glGetFragmentLightivSGIX(GLenum light, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetFragmentLightivSGIX(light, pname, params);
}

inline void glGetFragmentMaterialfvSGIX(GLenum face, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetFragmentMaterialfvSGIX(face, pname, params);
}

inline void glGetFragmentMaterialivSGIX(GLenum face, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetFragmentMaterialivSGIX(face, pname, params);
}

inline void glGetFramebufferAttachmentParameterivEXT(GLenum target, GLenum attachment, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetFramebufferAttachmentParameterivEXT(target, attachment, pname, params);
}

inline void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetFramebufferParameteriv(target, pname, params);
}

inline void glGetFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetFramebufferParameterivEXT(framebuffer, pname, params);
}

inline GLenum glGetGraphicsResetStatus()
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::GetGraphicsResetStatus());
}

inline GLenum glGetGraphicsResetStatusARB()
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::GetGraphicsResetStatusARB());
}

inline GLhandleARB glGetHandleARB(GLenum pname)
{
    return glbinding::Binding::GetHandleARB(pname);
}

inline void glGetHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, void * values)
{
    return glbinding::Binding::GetHistogram(target, reset, format, type, values);
}

inline void glGetHistogramEXT(GLenum target, GLboolean reset, GLenum format, GLenum type, void * values)
{
    return glbinding::Binding::GetHistogramEXT(target, reset, format, type, values);
}

inline void glGetHistogramParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetHistogramParameterfv(target, pname, params);
}

inline void glGetHistogramParameterfvEXT(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetHistogramParameterfvEXT(target, pname, params);
}

inline void glGetHistogramParameteriv(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetHistogramParameteriv(target, pname, params);
}

inline void glGetHistogramParameterivEXT(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetHistogramParameterivEXT(target, pname, params);
}

inline void glGetHistogramParameterxvOES(GLenum target, GLenum pname, GLfixed * params)
{
    return glbinding::Binding::GetHistogramParameterxvOES(target, pname, params);
}

inline GLuint64 glGetImageHandleARB(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format)
{
    return glbinding::Binding::GetImageHandleARB(texture, level, layered, layer, format);
}

inline GLuint64 glGetImageHandleNV(GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum format)
{
    return glbinding::Binding::GetImageHandleNV(texture, level, layered, layer, format);
}

inline void glGetImageTransformParameterfvHP(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetImageTransformParameterfvHP(target, pname, params);
}

inline void glGetImageTransformParameterivHP(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetImageTransformParameterivHP(target, pname, params);
}

inline void glGetInfoLogARB(GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * infoLog)
{
    return glbinding::Binding::GetInfoLogARB(obj, maxLength, length, infoLog);
}

inline GLint glGetInstrumentsSGIX()
{
    return glbinding::Binding::GetInstrumentsSGIX();
}

inline void glGetIntegerIndexedvEXT(GLenum target, GLuint index, GLint * data)
{
    return glbinding::Binding::GetIntegerIndexedvEXT(target, index, data);
}

inline void glGetIntegerui64i_vNV(GLenum value, GLuint index, GLuint64EXT * result)
{
    return glbinding::Binding::GetIntegerui64i_vNV(value, index, result);
}

inline void glGetIntegerui64vNV(GLenum value, GLuint64EXT * result)
{
    return glbinding::Binding::GetIntegerui64vNV(value, result);
}

inline void glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params)
{
    return glbinding::Binding::GetInternalformati64v(target, internalformat, pname, bufSize, params);
}

inline void glGetInvariantBooleanvEXT(GLuint id, GLenum value, GLboolean * data)
{
    return glbinding::Binding::GetInvariantBooleanvEXT(id, value, data);
}

inline void glGetInvariantFloatvEXT(GLuint id, GLenum value, GLfloat * data)
{
    return glbinding::Binding::GetInvariantFloatvEXT(id, value, data);
}

inline void glGetInvariantIntegervEXT(GLuint id, GLenum value, GLint * data)
{
    return glbinding::Binding::GetInvariantIntegervEXT(id, value, data);
}

inline void glGetLightxOES(GLenum light, GLenum pname, GLfixed * params)
{
    return glbinding::Binding::GetLightxOES(light, pname, params);
}

inline void glGetListParameterfvSGIX(GLuint list, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetListParameterfvSGIX(list, pname, params);
}

inline void glGetListParameterivSGIX(GLuint list, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetListParameterivSGIX(list, pname, params);
}

inline void glGetLocalConstantBooleanvEXT(GLuint id, GLenum value, GLboolean * data)
{
    return glbinding::Binding::GetLocalConstantBooleanvEXT(id, value, data);
}

inline void glGetLocalConstantFloatvEXT(GLuint id, GLenum value, GLfloat * data)
{
    return glbinding::Binding::GetLocalConstantFloatvEXT(id, value, data);
}

inline void glGetLocalConstantIntegervEXT(GLuint id, GLenum value, GLint * data)
{
    return glbinding::Binding::GetLocalConstantIntegervEXT(id, value, data);
}

inline void glGetMapAttribParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetMapAttribParameterfvNV(target, index, pname, params);
}

inline void glGetMapAttribParameterivNV(GLenum target, GLuint index, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMapAttribParameterivNV(target, index, pname, params);
}

inline void glGetMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLboolean packed, void * points)
{
    return glbinding::Binding::GetMapControlPointsNV(target, index, type, ustride, vstride, packed, points);
}

inline void glGetMapParameterfvNV(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetMapParameterfvNV(target, pname, params);
}

inline void glGetMapParameterivNV(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMapParameterivNV(target, pname, params);
}

inline void glGetMapxvOES(GLenum target, GLenum query, GLfixed * v)
{
    return glbinding::Binding::GetMapxvOES(target, query, v);
}

inline void glGetMaterialxOES(GLenum face, GLenum pname, GLfixed param)
{
    return glbinding::Binding::GetMaterialxOES(face, pname, param);
}

inline void glGetMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, void * values)
{
    return glbinding::Binding::GetMinmax(target, reset, format, type, values);
}

inline void glGetMinmaxEXT(GLenum target, GLboolean reset, GLenum format, GLenum type, void * values)
{
    return glbinding::Binding::GetMinmaxEXT(target, reset, format, type, values);
}

inline void glGetMinmaxParameterfv(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetMinmaxParameterfv(target, pname, params);
}

inline void glGetMinmaxParameterfvEXT(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetMinmaxParameterfvEXT(target, pname, params);
}

inline void glGetMinmaxParameteriv(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMinmaxParameteriv(target, pname, params);
}

inline void glGetMinmaxParameterivEXT(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMinmaxParameterivEXT(target, pname, params);
}

inline void glGetMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetMultiTexEnvfvEXT(texunit, target, pname, params);
}

inline void glGetMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMultiTexEnvivEXT(texunit, target, pname, params);
}

inline void glGetMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble * params)
{
    return glbinding::Binding::GetMultiTexGendvEXT(texunit, coord, pname, params);
}

inline void glGetMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetMultiTexGenfvEXT(texunit, coord, pname, params);
}

inline void glGetMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMultiTexGenivEXT(texunit, coord, pname, params);
}

inline void glGetMultiTexImageEXT(GLenum texunit, GLenum target, GLint level, GLenum format, GLenum type, void * pixels)
{
    return glbinding::Binding::GetMultiTexImageEXT(texunit, target, level, format, type, pixels);
}

inline void glGetMultiTexLevelParameterfvEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetMultiTexLevelParameterfvEXT(texunit, target, level, pname, params);
}

inline void glGetMultiTexLevelParameterivEXT(GLenum texunit, GLenum target, GLint level, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMultiTexLevelParameterivEXT(texunit, target, level, pname, params);
}

inline void glGetMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMultiTexParameterIivEXT(texunit, target, pname, params);
}

inline void glGetMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, GLuint * params)
{
    return glbinding::Binding::GetMultiTexParameterIuivEXT(texunit, target, pname, params);
}

inline void glGetMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetMultiTexParameterfvEXT(texunit, target, pname, params);
}

inline void glGetMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetMultiTexParameterivEXT(texunit, target, pname, params);
}

inline void glGetMultisamplefvNV(GLenum pname, GLuint index, GLfloat * val)
{
    return glbinding::Binding::GetMultisamplefvNV(pname, index, val);
}

inline void glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params)
{
    return glbinding::Binding::GetNamedBufferParameteri64v(buffer, pname, params);
}

inline void glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedBufferParameteriv(buffer, pname, params);
}

inline void glGetNamedBufferParameterivEXT(GLuint buffer, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedBufferParameterivEXT(buffer, pname, params);
}

inline void glGetNamedBufferParameterui64vNV(GLuint buffer, GLenum pname, GLuint64EXT * params)
{
    return glbinding::Binding::GetNamedBufferParameterui64vNV(buffer, pname, params);
}

inline void glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void ** params)
{
    return glbinding::Binding::GetNamedBufferPointerv(buffer, pname, params);
}

inline void glGetNamedBufferPointervEXT(GLuint buffer, GLenum pname, void ** params)
{
    return glbinding::Binding::GetNamedBufferPointervEXT(buffer, pname, params);
}

inline void glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizei size, void * data)
{
    return glbinding::Binding::GetNamedBufferSubData(buffer, offset, size, data);
}

inline void glGetNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data)
{
    return glbinding::Binding::GetNamedBufferSubDataEXT(buffer, offset, size, data);
}

inline void glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
}

inline void glGetNamedFramebufferAttachmentParameterivEXT(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedFramebufferAttachmentParameterivEXT(framebuffer, attachment, pname, params);
}

inline void glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param)
{
    return glbinding::Binding::GetNamedFramebufferParameteriv(framebuffer, pname, param);
}

inline void glGetNamedFramebufferParameterivEXT(GLuint framebuffer, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedFramebufferParameterivEXT(framebuffer, pname, params);
}

inline void glGetNamedProgramLocalParameterIivEXT(GLuint program, GLenum target, GLuint index, GLint * params)
{
    return glbinding::Binding::GetNamedProgramLocalParameterIivEXT(program, target, index, params);
}

inline void glGetNamedProgramLocalParameterIuivEXT(GLuint program, GLenum target, GLuint index, GLuint * params)
{
    return glbinding::Binding::GetNamedProgramLocalParameterIuivEXT(program, target, index, params);
}

inline void glGetNamedProgramLocalParameterdvEXT(GLuint program, GLenum target, GLuint index, GLdouble * params)
{
    return glbinding::Binding::GetNamedProgramLocalParameterdvEXT(program, target, index, params);
}

inline void glGetNamedProgramLocalParameterfvEXT(GLuint program, GLenum target, GLuint index, GLfloat * params)
{
    return glbinding::Binding::GetNamedProgramLocalParameterfvEXT(program, target, index, params);
}

inline void glGetNamedProgramStringEXT(GLuint program, GLenum target, GLenum pname, void * string)
{
    return glbinding::Binding::GetNamedProgramStringEXT(program, target, pname, string);
}

inline void glGetNamedProgramivEXT(GLuint program, GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedProgramivEXT(program, target, pname, params);
}

inline void glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedRenderbufferParameteriv(renderbuffer, pname, params);
}

inline void glGetNamedRenderbufferParameterivEXT(GLuint renderbuffer, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedRenderbufferParameterivEXT(renderbuffer, pname, params);
}

inline void glGetNamedStringARB(GLint namelen, const GLchar * name, GLsizei bufSize, GLint * stringlen, GLchar * string)
{
    return glbinding::Binding::GetNamedStringARB(namelen, name, bufSize, stringlen, string);
}

inline void glGetNamedStringivARB(GLint namelen, const GLchar * name, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetNamedStringivARB(namelen, name, pname, params);
}

inline void glGetNextPerfQueryIdINTEL(GLuint queryId, GLuint * nextQueryId)
{
    return glbinding::Binding::GetNextPerfQueryIdINTEL(queryId, nextQueryId);
}

inline void glGetObjectBufferfvATI(GLuint buffer, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetObjectBufferfvATI(buffer, pname, params);
}

inline void glGetObjectBufferivATI(GLuint buffer, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetObjectBufferivATI(buffer, pname, params);
}

inline void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label)
{
    return glbinding::Binding::GetObjectLabel(identifier, name, bufSize, length, label);
}

inline void glGetObjectLabelEXT(GLenum type, GLuint object, GLsizei bufSize, GLsizei * length, GLchar * label)
{
    return glbinding::Binding::GetObjectLabelEXT(type, object, bufSize, length, label);
}

inline void glGetObjectParameterfvARB(GLhandleARB obj, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetObjectParameterfvARB(obj, pname, params);
}

inline void glGetObjectParameterivAPPLE(GLenum objectType, GLuint name, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetObjectParameterivAPPLE(objectType, name, pname, params);
}

inline void glGetObjectParameterivARB(GLhandleARB obj, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetObjectParameterivARB(obj, pname, params);
}

inline void glGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label)
{
    return glbinding::Binding::GetObjectPtrLabel(ptr, bufSize, length, label);
}

inline void glGetOcclusionQueryivNV(GLuint id, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetOcclusionQueryivNV(id, pname, params);
}

inline void glGetOcclusionQueryuivNV(GLuint id, GLenum pname, GLuint * params)
{
    return glbinding::Binding::GetOcclusionQueryuivNV(id, pname, params);
}

inline void glGetPathColorGenfvNV(GLenum color, GLenum pname, GLfloat * value)
{
    return glbinding::Binding::GetPathColorGenfvNV(color, pname, value);
}

inline void glGetPathColorGenivNV(GLenum color, GLenum pname, GLint * value)
{
    return glbinding::Binding::GetPathColorGenivNV(color, pname, value);
}

inline void glGetPathCommandsNV(GLuint path, GLubyte * commands)
{
    return glbinding::Binding::GetPathCommandsNV(path, commands);
}

inline void glGetPathCoordsNV(GLuint path, GLfloat * coords)
{
    return glbinding::Binding::GetPathCoordsNV(path, coords);
}

inline void glGetPathDashArrayNV(GLuint path, GLfloat * dashArray)
{
    return glbinding::Binding::GetPathDashArrayNV(path, dashArray);
}

inline GLfloat glGetPathLengthNV(GLuint path, GLsizei startSegment, GLsizei numSegments)
{
    return glbinding::Binding::GetPathLengthNV(path, startSegment, numSegments);
}

inline void glGetPathMetricRangeNV(PathRenderingMaskNV metricQueryMask, GLuint firstPathName, GLsizei numPaths, GLsizei stride, GLfloat * metrics)
{
    return glbinding::Binding::GetPathMetricRangeNV(metricQueryMask, firstPathName, numPaths, stride, metrics);
}

inline void glGetPathMetricsNV(PathRenderingMaskNV metricQueryMask, GLsizei numPaths, GLenum pathNameType, const void * paths, GLuint pathBase, GLsizei stride, GLfloat * metrics)
{
    return glbinding::Binding::GetPathMetricsNV(metricQueryMask, numPaths, pathNameType, paths, pathBase, stride, metrics);
}

inline void glGetPathParameterfvNV(GLuint path, GLenum pname, GLfloat * value)
{
    return glbinding::Binding::GetPathParameterfvNV(path, pname, value);
}

inline void glGetPathParameterivNV(GLuint path, GLenum pname, GLint * value)
{
    return glbinding::Binding::GetPathParameterivNV(path, pname, value);
}

inline void glGetPathSpacingNV(GLenum pathListMode, GLsizei numPaths, GLenum pathNameType, const void * paths, GLuint pathBase, GLfloat advanceScale, GLfloat kerningScale, GLenum transformType, GLfloat * returnedSpacing)
{
    return glbinding::Binding::GetPathSpacingNV(pathListMode, numPaths, pathNameType, paths, pathBase, advanceScale, kerningScale, transformType, returnedSpacing);
}

inline void glGetPathTexGenfvNV(GLenum texCoordSet, GLenum pname, GLfloat * value)
{
    return glbinding::Binding::GetPathTexGenfvNV(texCoordSet, pname, value);
}

inline void glGetPathTexGenivNV(GLenum texCoordSet, GLenum pname, GLint * value)
{
    return glbinding::Binding::GetPathTexGenivNV(texCoordSet, pname, value);
}

inline void glGetPerfCounterInfoINTEL(GLuint queryId, GLuint counterId, GLuint counterNameLength, GLchar * counterName, GLuint counterDescLength, GLchar * counterDesc, GLuint * counterOffset, GLuint * counterDataSize, GLuint * counterTypeEnum, GLuint * counterDataTypeEnum, GLuint64 * rawCounterMaxValue)
{
    return glbinding::Binding::GetPerfCounterInfoINTEL(queryId, counterId, counterNameLength, counterName, counterDescLength, counterDesc, counterOffset, counterDataSize, counterTypeEnum, counterDataTypeEnum, rawCounterMaxValue);
}

inline void glGetPerfMonitorCounterDataAMD(GLuint monitor, GLenum pname, GLsizei dataSize, GLuint * data, GLint * bytesWritten)
{
    return glbinding::Binding::GetPerfMonitorCounterDataAMD(monitor, pname, dataSize, data, bytesWritten);
}

inline void glGetPerfMonitorCounterInfoAMD(GLuint group, GLuint counter, GLenum pname, void * data)
{
    return glbinding::Binding::GetPerfMonitorCounterInfoAMD(group, counter, pname, data);
}

inline void glGetPerfMonitorCounterStringAMD(GLuint group, GLuint counter, GLsizei bufSize, GLsizei * length, GLchar * counterString)
{
    return glbinding::Binding::GetPerfMonitorCounterStringAMD(group, counter, bufSize, length, counterString);
}

inline void glGetPerfMonitorCountersAMD(GLuint group, GLint * numCounters, GLint * maxActiveCounters, GLsizei counterSize, GLuint * counters)
{
    return glbinding::Binding::GetPerfMonitorCountersAMD(group, numCounters, maxActiveCounters, counterSize, counters);
}

inline void glGetPerfMonitorGroupStringAMD(GLuint group, GLsizei bufSize, GLsizei * length, GLchar * groupString)
{
    return glbinding::Binding::GetPerfMonitorGroupStringAMD(group, bufSize, length, groupString);
}

inline void glGetPerfMonitorGroupsAMD(GLint * numGroups, GLsizei groupsSize, GLuint * groups)
{
    return glbinding::Binding::GetPerfMonitorGroupsAMD(numGroups, groupsSize, groups);
}

inline void glGetPerfQueryDataINTEL(GLuint queryHandle, GLuint flags, GLsizei dataSize, GLvoid * data, GLuint * bytesWritten)
{
    return glbinding::Binding::GetPerfQueryDataINTEL(queryHandle, flags, dataSize, data, bytesWritten);
}

inline void glGetPerfQueryIdByNameINTEL(GLchar * queryName, GLuint * queryId)
{
    return glbinding::Binding::GetPerfQueryIdByNameINTEL(queryName, queryId);
}

inline void glGetPerfQueryInfoINTEL(GLuint queryId, GLuint queryNameLength, GLchar * queryName, GLuint * dataSize, GLuint * noCounters, GLuint * noInstances, GLuint * capsMask)
{
    return glbinding::Binding::GetPerfQueryInfoINTEL(queryId, queryNameLength, queryName, dataSize, noCounters, noInstances, capsMask);
}

inline void glGetPixelMapxv(GLenum map, GLint size, GLfixed * values)
{
    return glbinding::Binding::GetPixelMapxv(map, size, values);
}

inline void glGetPixelTexGenParameterfvSGIS(GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetPixelTexGenParameterfvSGIS(pname, params);
}

inline void glGetPixelTexGenParameterivSGIS(GLenum pname, GLint * params)
{
    return glbinding::Binding::GetPixelTexGenParameterivSGIS(pname, params);
}

inline void glGetPixelTransformParameterfvEXT(GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetPixelTransformParameterfvEXT(target, pname, params);
}

inline void glGetPixelTransformParameterivEXT(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetPixelTransformParameterivEXT(target, pname, params);
}

inline void glGetPointerIndexedvEXT(GLenum target, GLuint index, void ** data)
{
    return glbinding::Binding::GetPointerIndexedvEXT(target, index, data);
}

inline void glGetPointeri_vEXT(GLenum pname, GLuint index, void ** params)
{
    return glbinding::Binding::GetPointeri_vEXT(pname, index, params);
}

inline void glGetPointervEXT(GLenum pname, void ** params)
{
    return glbinding::Binding::GetPointervEXT(pname, params);
}

inline void glGetProgramEnvParameterIivNV(GLenum target, GLuint index, GLint * params)
{
    return glbinding::Binding::GetProgramEnvParameterIivNV(target, index, params);
}

inline void glGetProgramEnvParameterIuivNV(GLenum target, GLuint index, GLuint * params)
{
    return glbinding::Binding::GetProgramEnvParameterIuivNV(target, index, params);
}

inline void glGetProgramEnvParameterdvARB(GLenum target, GLuint index, GLdouble * params)
{
    return glbinding::Binding::GetProgramEnvParameterdvARB(target, index, params);
}

inline void glGetProgramEnvParameterfvARB(GLenum target, GLuint index, GLfloat * params)
{
    return glbinding::Binding::GetProgramEnvParameterfvARB(target, index, params);
}

inline void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetProgramInterfaceiv(program, programInterface, pname, params);
}

inline void glGetProgramLocalParameterIivNV(GLenum target, GLuint index, GLint * params)
{
    return glbinding::Binding::GetProgramLocalParameterIivNV(target, index, params);
}

inline void glGetProgramLocalParameterIuivNV(GLenum target, GLuint index, GLuint * params)
{
    return glbinding::Binding::GetProgramLocalParameterIuivNV(target, index, params);
}

inline void glGetProgramLocalParameterdvARB(GLenum target, GLuint index, GLdouble * params)
{
    return glbinding::Binding::GetProgramLocalParameterdvARB(target, index, params);
}

inline void glGetProgramLocalParameterfvARB(GLenum target, GLuint index, GLfloat * params)
{
    return glbinding::Binding::GetProgramLocalParameterfvARB(target, index, params);
}

inline void glGetProgramNamedParameterdvNV(GLuint id, GLsizei len, const GLubyte * name, GLdouble * params)
{
    return glbinding::Binding::GetProgramNamedParameterdvNV(id, len, name, params);
}

inline void glGetProgramNamedParameterfvNV(GLuint id, GLsizei len, const GLubyte * name, GLfloat * params)
{
    return glbinding::Binding::GetProgramNamedParameterfvNV(id, len, name, params);
}

inline void glGetProgramParameterdvNV(GLenum target, GLuint index, GLenum pname, GLdouble * params)
{
    return glbinding::Binding::GetProgramParameterdvNV(target, index, pname, params);
}

inline void glGetProgramParameterfvNV(GLenum target, GLuint index, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetProgramParameterfvNV(target, index, pname, params);
}

inline GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name)
{
    return glbinding::Binding::GetProgramResourceIndex(program, programInterface, name);
}

inline GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name)
{
    return glbinding::Binding::GetProgramResourceLocation(program, programInterface, name);
}

inline GLint glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name)
{
    return glbinding::Binding::GetProgramResourceLocationIndex(program, programInterface, name);
}

inline void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name)
{
    return glbinding::Binding::GetProgramResourceName(program, programInterface, index, bufSize, length, name);
}

inline void glGetProgramResourcefvNV(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLfloat * params)
{
    return glbinding::Binding::GetProgramResourcefvNV(program, programInterface, index, propCount, props, bufSize, length, params);
}

inline void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params)
{
    return glbinding::Binding::GetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
}

inline void glGetProgramStringARB(GLenum target, GLenum pname, void * string)
{
    return glbinding::Binding::GetProgramStringARB(target, pname, string);
}

inline void glGetProgramStringNV(GLuint id, GLenum pname, GLubyte * program)
{
    return glbinding::Binding::GetProgramStringNV(id, pname, program);
}

inline void glGetProgramSubroutineParameteruivNV(GLenum target, GLuint index, GLuint * param)
{
    return glbinding::Binding::GetProgramSubroutineParameteruivNV(target, index, param);
}

inline void glGetProgramivARB(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetProgramivARB(target, pname, params);
}

inline void glGetProgramivNV(GLuint id, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetProgramivNV(id, pname, params);
}

inline void glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
    return glbinding::Binding::GetQueryBufferObjecti64v(id, buffer, pname, offset);
}

inline void glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
    return glbinding::Binding::GetQueryBufferObjectiv(id, buffer, pname, offset);
}

inline void glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
    return glbinding::Binding::GetQueryBufferObjectui64v(id, buffer, pname, offset);
}

inline void glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset)
{
    return glbinding::Binding::GetQueryBufferObjectuiv(id, buffer, pname, offset);
}

inline void glGetQueryObjecti64vEXT(GLuint id, GLenum pname, GLint64 * params)
{
    return glbinding::Binding::GetQueryObjecti64vEXT(id, pname, params);
}

inline void glGetQueryObjectivARB(GLuint id, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetQueryObjectivARB(id, pname, params);
}

inline void glGetQueryObjectui64vEXT(GLuint id, GLenum pname, GLuint64 * params)
{
    return glbinding::Binding::GetQueryObjectui64vEXT(id, pname, params);
}

inline void glGetQueryObjectuivARB(GLuint id, GLenum pname, GLuint * params)
{
    return glbinding::Binding::GetQueryObjectuivARB(id, pname, params);
}

inline void glGetQueryivARB(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetQueryivARB(target, pname, params);
}

inline void glGetRenderbufferParameterivEXT(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetRenderbufferParameterivEXT(target, pname, params);
}

inline void glGetSeparableFilter(GLenum target, GLenum format, GLenum type, void * row, void * column, void * span)
{
    return glbinding::Binding::GetSeparableFilter(target, format, type, row, column, span);
}

inline void glGetSeparableFilterEXT(GLenum target, GLenum format, GLenum type, void * row, void * column, void * span)
{
    return glbinding::Binding::GetSeparableFilterEXT(target, format, type, row, column, span);
}

inline void glGetShaderSourceARB(GLhandleARB obj, GLsizei maxLength, GLsizei * length, GLcharARB * source)
{
    return glbinding::Binding::GetShaderSourceARB(obj, maxLength, length, source);
}

inline void glGetSharpenTexFuncSGIS(GLenum target, GLfloat * points)
{
    return glbinding::Binding::GetSharpenTexFuncSGIS(target, points);
}

inline void glGetTexBumpParameterfvATI(GLenum pname, GLfloat * param)
{
    return glbinding::Binding::GetTexBumpParameterfvATI(pname, param);
}

inline void glGetTexBumpParameterivATI(GLenum pname, GLint * param)
{
    return glbinding::Binding::GetTexBumpParameterivATI(pname, param);
}

inline void glGetTexEnvxvOES(GLenum target, GLenum pname, GLfixed * params)
{
    return glbinding::Binding::GetTexEnvxvOES(target, pname, params);
}

inline void glGetTexFilterFuncSGIS(GLenum target, GLenum filter, GLfloat * weights)
{
    return glbinding::Binding::GetTexFilterFuncSGIS(target, filter, weights);
}

inline void glGetTexGenxvOES(GLenum coord, GLenum pname, GLfixed * params)
{
    return glbinding::Binding::GetTexGenxvOES(coord, pname, params);
}

inline void glGetTexLevelParameterxvOES(GLenum target, GLint level, GLenum pname, GLfixed * params)
{
    return glbinding::Binding::GetTexLevelParameterxvOES(target, level, pname, params);
}

inline void glGetTexParameterIivEXT(GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetTexParameterIivEXT(target, pname, params);
}

inline void glGetTexParameterIuivEXT(GLenum target, GLenum pname, GLuint * params)
{
    return glbinding::Binding::GetTexParameterIuivEXT(target, pname, params);
}

inline void glGetTexParameterPointervAPPLE(GLenum target, GLenum pname, void ** params)
{
    return glbinding::Binding::GetTexParameterPointervAPPLE(target, pname, params);
}

inline void glGetTexParameterxvOES(GLenum target, GLenum pname, GLfixed * params)
{
    return glbinding::Binding::GetTexParameterxvOES(target, pname, params);
}

inline GLuint64 glGetTextureHandleARB(GLuint texture)
{
    return glbinding::Binding::GetTextureHandleARB(texture);
}

inline GLuint64 glGetTextureHandleNV(GLuint texture)
{
    return glbinding::Binding::GetTextureHandleNV(texture);
}

inline void glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
    return glbinding::Binding::GetTextureImage(texture, level, format, type, bufSize, pixels);
}

inline void glGetTextureImageEXT(GLuint texture, GLenum target, GLint level, GLenum format, GLenum type, void * pixels)
{
    return glbinding::Binding::GetTextureImageEXT(texture, target, level, format, type, pixels);
}

inline void glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetTextureLevelParameterfv(texture, level, pname, params);
}

inline void glGetTextureLevelParameterfvEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetTextureLevelParameterfvEXT(texture, target, level, pname, params);
}

inline void glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetTextureLevelParameteriv(texture, level, pname, params);
}

inline void glGetTextureLevelParameterivEXT(GLuint texture, GLenum target, GLint level, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetTextureLevelParameterivEXT(texture, target, level, pname, params);
}

inline void glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetTextureParameterIiv(texture, pname, params);
}

inline void glGetTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetTextureParameterIivEXT(texture, target, pname, params);
}

inline void glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params)
{
    return glbinding::Binding::GetTextureParameterIuiv(texture, pname, params);
}

inline void glGetTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, GLuint * params)
{
    return glbinding::Binding::GetTextureParameterIuivEXT(texture, target, pname, params);
}

inline void glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetTextureParameterfv(texture, pname, params);
}

inline void glGetTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetTextureParameterfvEXT(texture, target, pname, params);
}

inline void glGetTextureParameteriv(GLuint texture, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetTextureParameteriv(texture, pname, params);
}

inline void glGetTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetTextureParameterivEXT(texture, target, pname, params);
}

inline GLuint64 glGetTextureSamplerHandleARB(GLuint texture, GLuint sampler)
{
    return glbinding::Binding::GetTextureSamplerHandleARB(texture, sampler);
}

inline GLuint64 glGetTextureSamplerHandleNV(GLuint texture, GLuint sampler)
{
    return glbinding::Binding::GetTextureSamplerHandleNV(texture, sampler);
}

inline void glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
    return glbinding::Binding::GetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
}

inline void glGetTrackMatrixivNV(GLenum target, GLuint address, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetTrackMatrixivNV(target, address, pname, params);
}

inline void glGetTransformFeedbackVaryingEXT(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name)
{
    return glbinding::Binding::GetTransformFeedbackVaryingEXT(program, index, bufSize, length, size, type, name);
}

inline void glGetTransformFeedbackVaryingNV(GLuint program, GLuint index, GLint * location)
{
    return glbinding::Binding::GetTransformFeedbackVaryingNV(program, index, location);
}

inline void glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param)
{
    return glbinding::Binding::GetTransformFeedbacki64_v(xfb, pname, index, param);
}

inline void glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param)
{
    return glbinding::Binding::GetTransformFeedbacki_v(xfb, pname, index, param);
}

inline void glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param)
{
    return glbinding::Binding::GetTransformFeedbackiv(xfb, pname, param);
}

inline GLint glGetUniformBufferSizeEXT(GLuint program, GLint location)
{
    return glbinding::Binding::GetUniformBufferSizeEXT(program, location);
}

inline GLint glGetUniformLocationARB(GLhandleARB programObj, const GLcharARB * name)
{
    return glbinding::Binding::GetUniformLocationARB(programObj, name);
}

inline GLintptr glGetUniformOffsetEXT(GLuint program, GLint location)
{
    return glbinding::Binding::GetUniformOffsetEXT(program, location);
}

inline void glGetUniformfvARB(GLhandleARB programObj, GLint location, GLfloat * params)
{
    return glbinding::Binding::GetUniformfvARB(programObj, location, params);
}

inline void glGetUniformi64vNV(GLuint program, GLint location, GLint64EXT * params)
{
    return glbinding::Binding::GetUniformi64vNV(program, location, params);
}

inline void glGetUniformivARB(GLhandleARB programObj, GLint location, GLint * params)
{
    return glbinding::Binding::GetUniformivARB(programObj, location, params);
}

inline void glGetUniformui64vNV(GLuint program, GLint location, GLuint64EXT * params)
{
    return glbinding::Binding::GetUniformui64vNV(program, location, params);
}

inline void glGetUniformuivEXT(GLuint program, GLint location, GLuint * params)
{
    return glbinding::Binding::GetUniformuivEXT(program, location, params);
}

inline void glGetVariantArrayObjectfvATI(GLuint id, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetVariantArrayObjectfvATI(id, pname, params);
}

inline void glGetVariantArrayObjectivATI(GLuint id, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetVariantArrayObjectivATI(id, pname, params);
}

inline void glGetVariantBooleanvEXT(GLuint id, GLenum value, GLboolean * data)
{
    return glbinding::Binding::GetVariantBooleanvEXT(id, value, data);
}

inline void glGetVariantFloatvEXT(GLuint id, GLenum value, GLfloat * data)
{
    return glbinding::Binding::GetVariantFloatvEXT(id, value, data);
}

inline void glGetVariantIntegervEXT(GLuint id, GLenum value, GLint * data)
{
    return glbinding::Binding::GetVariantIntegervEXT(id, value, data);
}

inline void glGetVariantPointervEXT(GLuint id, GLenum value, void ** data)
{
    return glbinding::Binding::GetVariantPointervEXT(id, value, data);
}

inline GLint glGetVaryingLocationNV(GLuint program, const GLchar * name)
{
    return glbinding::Binding::GetVaryingLocationNV(program, name);
}

inline void glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param)
{
    return glbinding::Binding::GetVertexArrayIndexed64iv(vaobj, index, pname, param);
}

inline void glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param)
{
    return glbinding::Binding::GetVertexArrayIndexediv(vaobj, index, pname, param);
}

inline void glGetVertexArrayIntegeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, GLint * param)
{
    return glbinding::Binding::GetVertexArrayIntegeri_vEXT(vaobj, index, pname, param);
}

inline void glGetVertexArrayIntegervEXT(GLuint vaobj, GLenum pname, GLint * param)
{
    return glbinding::Binding::GetVertexArrayIntegervEXT(vaobj, pname, param);
}

inline void glGetVertexArrayPointeri_vEXT(GLuint vaobj, GLuint index, GLenum pname, void ** param)
{
    return glbinding::Binding::GetVertexArrayPointeri_vEXT(vaobj, index, pname, param);
}

inline void glGetVertexArrayPointervEXT(GLuint vaobj, GLenum pname, void ** param)
{
    return glbinding::Binding::GetVertexArrayPointervEXT(vaobj, pname, param);
}

inline void glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param)
{
    return glbinding::Binding::GetVertexArrayiv(vaobj, pname, param);
}

inline void glGetVertexAttribArrayObjectfvATI(GLuint index, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetVertexAttribArrayObjectfvATI(index, pname, params);
}

inline void glGetVertexAttribArrayObjectivATI(GLuint index, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetVertexAttribArrayObjectivATI(index, pname, params);
}

inline void glGetVertexAttribIivEXT(GLuint index, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetVertexAttribIivEXT(index, pname, params);
}

inline void glGetVertexAttribIuivEXT(GLuint index, GLenum pname, GLuint * params)
{
    return glbinding::Binding::GetVertexAttribIuivEXT(index, pname, params);
}

inline void glGetVertexAttribLdvEXT(GLuint index, GLenum pname, GLdouble * params)
{
    return glbinding::Binding::GetVertexAttribLdvEXT(index, pname, params);
}

inline void glGetVertexAttribLi64vNV(GLuint index, GLenum pname, GLint64EXT * params)
{
    return glbinding::Binding::GetVertexAttribLi64vNV(index, pname, params);
}

inline void glGetVertexAttribLui64vARB(GLuint index, GLenum pname, GLuint64EXT * params)
{
    return glbinding::Binding::GetVertexAttribLui64vARB(index, pname, params);
}

inline void glGetVertexAttribLui64vNV(GLuint index, GLenum pname, GLuint64EXT * params)
{
    return glbinding::Binding::GetVertexAttribLui64vNV(index, pname, params);
}

inline void glGetVertexAttribPointervARB(GLuint index, GLenum pname, void ** pointer)
{
    return glbinding::Binding::GetVertexAttribPointervARB(index, pname, pointer);
}

inline void glGetVertexAttribPointervNV(GLuint index, GLenum pname, void ** pointer)
{
    return glbinding::Binding::GetVertexAttribPointervNV(index, pname, pointer);
}

inline void glGetVertexAttribdvARB(GLuint index, GLenum pname, GLdouble * params)
{
    return glbinding::Binding::GetVertexAttribdvARB(index, pname, params);
}

inline void glGetVertexAttribdvNV(GLuint index, GLenum pname, GLdouble * params)
{
    return glbinding::Binding::GetVertexAttribdvNV(index, pname, params);
}

inline void glGetVertexAttribfvARB(GLuint index, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetVertexAttribfvARB(index, pname, params);
}

inline void glGetVertexAttribfvNV(GLuint index, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetVertexAttribfvNV(index, pname, params);
}

inline void glGetVertexAttribivARB(GLuint index, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetVertexAttribivARB(index, pname, params);
}

inline void glGetVertexAttribivNV(GLuint index, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetVertexAttribivNV(index, pname, params);
}

inline void glGetVideoCaptureStreamdvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLdouble * params)
{
    return glbinding::Binding::GetVideoCaptureStreamdvNV(video_capture_slot, stream, pname, params);
}

inline void glGetVideoCaptureStreamfvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLfloat * params)
{
    return glbinding::Binding::GetVideoCaptureStreamfvNV(video_capture_slot, stream, pname, params);
}

inline void glGetVideoCaptureStreamivNV(GLuint video_capture_slot, GLuint stream, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetVideoCaptureStreamivNV(video_capture_slot, stream, pname, params);
}

inline void glGetVideoCaptureivNV(GLuint video_capture_slot, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetVideoCaptureivNV(video_capture_slot, pname, params);
}

inline void glGetVideoi64vNV(GLuint video_slot, GLenum pname, GLint64EXT * params)
{
    return glbinding::Binding::GetVideoi64vNV(video_slot, pname, params);
}

inline void glGetVideoivNV(GLuint video_slot, GLenum pname, GLint * params)
{
    return glbinding::Binding::GetVideoivNV(video_slot, pname, params);
}

inline void glGetVideoui64vNV(GLuint video_slot, GLenum pname, GLuint64EXT * params)
{
    return glbinding::Binding::GetVideoui64vNV(video_slot, pname, params);
}

inline void glGetVideouivNV(GLuint video_slot, GLenum pname, GLuint * params)
{
    return glbinding::Binding::GetVideouivNV(video_slot, pname, params);
}

inline void glGetnColorTable(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * table)
{
    return glbinding::Binding::GetnColorTable(target, format, type, bufSize, table);
}

inline void glGetnColorTableARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * table)
{
    return glbinding::Binding::GetnColorTableARB(target, format, type, bufSize, table);
}

inline void glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels)
{
    return glbinding::Binding::GetnCompressedTexImage(target, lod, bufSize, pixels);
}

inline void glGetnCompressedTexImageARB(GLenum target, GLint lod, GLsizei bufSize, void * img)
{
    return glbinding::Binding::GetnCompressedTexImageARB(target, lod, bufSize, img);
}

inline void glGetnConvolutionFilter(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * image)
{
    return glbinding::Binding::GetnConvolutionFilter(target, format, type, bufSize, image);
}

inline void glGetnConvolutionFilterARB(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * image)
{
    return glbinding::Binding::GetnConvolutionFilterARB(target, format, type, bufSize, image);
}

inline void glGetnHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values)
{
    return glbinding::Binding::GetnHistogram(target, reset, format, type, bufSize, values);
}

inline void glGetnHistogramARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values)
{
    return glbinding::Binding::GetnHistogramARB(target, reset, format, type, bufSize, values);
}

inline void glGetnMapdv(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v)
{
    return glbinding::Binding::GetnMapdv(target, query, bufSize, v);
}

inline void glGetnMapdvARB(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v)
{
    return glbinding::Binding::GetnMapdvARB(target, query, bufSize, v);
}

inline void glGetnMapfv(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v)
{
    return glbinding::Binding::GetnMapfv(target, query, bufSize, v);
}

inline void glGetnMapfvARB(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v)
{
    return glbinding::Binding::GetnMapfvARB(target, query, bufSize, v);
}

inline void glGetnMapiv(GLenum target, GLenum query, GLsizei bufSize, GLint * v)
{
    return glbinding::Binding::GetnMapiv(target, query, bufSize, v);
}

inline void glGetnMapivARB(GLenum target, GLenum query, GLsizei bufSize, GLint * v)
{
    return glbinding::Binding::GetnMapivARB(target, query, bufSize, v);
}

inline void glGetnMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values)
{
    return glbinding::Binding::GetnMinmax(target, reset, format, type, bufSize, values);
}

inline void glGetnMinmaxARB(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values)
{
    return glbinding::Binding::GetnMinmaxARB(target, reset, format, type, bufSize, values);
}

inline void glGetnPixelMapfv(GLenum map, GLsizei bufSize, GLfloat * values)
{
    return glbinding::Binding::GetnPixelMapfv(map, bufSize, values);
}

inline void glGetnPixelMapfvARB(GLenum map, GLsizei bufSize, GLfloat * values)
{
    return glbinding::Binding::GetnPixelMapfvARB(map, bufSize, values);
}

inline void glGetnPixelMapuiv(GLenum map, GLsizei bufSize, GLuint * values)
{
    return glbinding::Binding::GetnPixelMapuiv(map, bufSize, values);
}

inline void glGetnPixelMapuivARB(GLenum map, GLsizei bufSize, GLuint * values)
{
    return glbinding::Binding::GetnPixelMapuivARB(map, bufSize, values);
}

inline void glGetnPixelMapusv(GLenum map, GLsizei bufSize, GLushort * values)
{
    return glbinding::Binding::GetnPixelMapusv(map, bufSize, values);
}

inline void glGetnPixelMapusvARB(GLenum map, GLsizei bufSize, GLushort * values)
{
    return glbinding::Binding::GetnPixelMapusvARB(map, bufSize, values);
}

inline void glGetnPolygonStipple(GLsizei bufSize, GLubyte * pattern)
{
    return glbinding::Binding::GetnPolygonStipple(bufSize, pattern);
}

inline void glGetnPolygonStippleARB(GLsizei bufSize, GLubyte * pattern)
{
    return glbinding::Binding::GetnPolygonStippleARB(bufSize, pattern);
}

inline void glGetnSeparableFilter(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void * row, GLsizei columnBufSize, void * column, void * span)
{
    return glbinding::Binding::GetnSeparableFilter(target, format, type, rowBufSize, row, columnBufSize, column, span);
}

inline void glGetnSeparableFilterARB(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void * row, GLsizei columnBufSize, void * column, void * span)
{
    return glbinding::Binding::GetnSeparableFilterARB(target, format, type, rowBufSize, row, columnBufSize, column, span);
}

inline void glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels)
{
    return glbinding::Binding::GetnTexImage(target, level, format, type, bufSize, pixels);
}

inline void glGetnTexImageARB(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * img)
{
    return glbinding::Binding::GetnTexImageARB(target, level, format, type, bufSize, img);
}

inline void glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
{
    return glbinding::Binding::GetnUniformdv(program, location, bufSize, params);
}

inline void glGetnUniformdvARB(GLuint program, GLint location, GLsizei bufSize, GLdouble * params)
{
    return glbinding::Binding::GetnUniformdvARB(program, location, bufSize, params);
}

inline void glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
{
    return glbinding::Binding::GetnUniformfv(program, location, bufSize, params);
}

inline void glGetnUniformfvARB(GLuint program, GLint location, GLsizei bufSize, GLfloat * params)
{
    return glbinding::Binding::GetnUniformfvARB(program, location, bufSize, params);
}

inline void glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params)
{
    return glbinding::Binding::GetnUniformiv(program, location, bufSize, params);
}

inline void glGetnUniformivARB(GLuint program, GLint location, GLsizei bufSize, GLint * params)
{
    return glbinding::Binding::GetnUniformivARB(program, location, bufSize, params);
}

inline void glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
{
    return glbinding::Binding::GetnUniformuiv(program, location, bufSize, params);
}

inline void glGetnUniformuivARB(GLuint program, GLint location, GLsizei bufSize, GLuint * params)
{
    return glbinding::Binding::GetnUniformuivARB(program, location, bufSize, params);
}

inline void glGlobalAlphaFactorbSUN(GLbyte factor)
{
    return glbinding::Binding::GlobalAlphaFactorbSUN(factor);
}

inline void glGlobalAlphaFactordSUN(GLdouble factor)
{
    return glbinding::Binding::GlobalAlphaFactordSUN(factor);
}

inline void glGlobalAlphaFactorfSUN(GLfloat factor)
{
    return glbinding::Binding::GlobalAlphaFactorfSUN(factor);
}

inline void glGlobalAlphaFactoriSUN(GLint factor)
{
    return glbinding::Binding::GlobalAlphaFactoriSUN(factor);
}

inline void glGlobalAlphaFactorsSUN(GLshort factor)
{
    return glbinding::Binding::GlobalAlphaFactorsSUN(factor);
}

inline void glGlobalAlphaFactorubSUN(GLubyte factor)
{
    return glbinding::Binding::GlobalAlphaFactorubSUN(factor);
}

inline void glGlobalAlphaFactoruiSUN(GLuint factor)
{
    return glbinding::Binding::GlobalAlphaFactoruiSUN(factor);
}

inline void glGlobalAlphaFactorusSUN(GLushort factor)
{
    return glbinding::Binding::GlobalAlphaFactorusSUN(factor);
}

inline void glHintPGI(GLenum target, GLint mode)
{
    return glbinding::Binding::HintPGI(target, mode);
}

inline void glHistogram(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink)
{
    return glbinding::Binding::Histogram(target, width, internalformat, sink);
}

inline void glHistogramEXT(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink)
{
    return glbinding::Binding::HistogramEXT(target, width, internalformat, sink);
}

inline void glIglooInterfaceSGIX(GLenum pname, const void * params)
{
    return glbinding::Binding::IglooInterfaceSGIX(pname, params);
}

inline void glImageTransformParameterfHP(GLenum target, GLenum pname, GLfloat param)
{
    return glbinding::Binding::ImageTransformParameterfHP(target, pname, param);
}

inline void glImageTransformParameterfvHP(GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::ImageTransformParameterfvHP(target, pname, params);
}

inline void glImageTransformParameteriHP(GLenum target, GLenum pname, GLint param)
{
    return glbinding::Binding::ImageTransformParameteriHP(target, pname, param);
}

inline void glImageTransformParameterivHP(GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::ImageTransformParameterivHP(target, pname, params);
}

inline GLsync glImportSyncEXT(GLenum external_sync_type, GLintptr external_sync, UnusedMask flags)
{
    return glbinding::Binding::ImportSyncEXT(external_sync_type, external_sync, flags);
}

inline void glIndexFormatNV(GLenum type, GLsizei stride)
{
    return glbinding::Binding::IndexFormatNV(type, stride);
}

inline void glIndexFuncEXT(GLenum func, GLclampf ref)
{
    return glbinding::Binding::IndexFuncEXT(func, ref);
}

inline void glIndexMaterialEXT(GLenum face, GLenum mode)
{
    return glbinding::Binding::IndexMaterialEXT(face, mode);
}

inline void glIndexPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void * pointer)
{
    return glbinding::Binding::IndexPointerEXT(type, stride, count, pointer);
}

inline void glIndexPointerListIBM(GLenum type, GLint stride, const void ** pointer, GLint ptrstride)
{
    return glbinding::Binding::IndexPointerListIBM(type, stride, pointer, ptrstride);
}

inline void glIndexxOES(GLfixed component)
{
    return glbinding::Binding::IndexxOES(component);
}

inline void glIndexxvOES(const GLfixed * component)
{
    return glbinding::Binding::IndexxvOES(component);
}

inline void glInsertComponentEXT(GLuint res, GLuint src, GLuint num)
{
    return glbinding::Binding::InsertComponentEXT(res, src, num);
}

inline void glInsertEventMarkerEXT(GLsizei length, const GLchar * marker)
{
    return glbinding::Binding::InsertEventMarkerEXT(length, marker);
}

inline void glInstrumentsBufferSGIX(GLsizei size, GLint * buffer)
{
    return glbinding::Binding::InstrumentsBufferSGIX(size, buffer);
}

inline void glInterpolatePathsNV(GLuint resultPath, GLuint pathA, GLuint pathB, GLfloat weight)
{
    return glbinding::Binding::InterpolatePathsNV(resultPath, pathA, pathB, weight);
}

inline void glInvalidateBufferData(GLuint buffer)
{
    return glbinding::Binding::InvalidateBufferData(buffer);
}

inline void glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length)
{
    return glbinding::Binding::InvalidateBufferSubData(buffer, offset, length);
}

inline void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments)
{
    return glbinding::Binding::InvalidateFramebuffer(target, numAttachments, attachments);
}

inline void glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments)
{
    return glbinding::Binding::InvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
}

inline void glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::InvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
}

inline void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
{
    return glbinding::Binding::InvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
}

inline void glInvalidateTexImage(GLuint texture, GLint level)
{
    return glbinding::Binding::InvalidateTexImage(texture, level);
}

inline void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth)
{
    return glbinding::Binding::InvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
}

inline GLboolean glIsAsyncMarkerSGIX(GLuint marker)
{
    return glbinding::Binding::IsAsyncMarkerSGIX(marker);
}

inline GLboolean glIsBufferARB(GLuint buffer)
{
    return glbinding::Binding::IsBufferARB(buffer);
}

inline GLboolean glIsBufferResidentNV(GLenum target)
{
    return glbinding::Binding::IsBufferResidentNV(target);
}

inline GLboolean glIsEnabledIndexedEXT(GLenum target, GLuint index)
{
    return glbinding::Binding::IsEnabledIndexedEXT(target, index);
}

inline GLboolean glIsFenceAPPLE(GLuint fence)
{
    return glbinding::Binding::IsFenceAPPLE(fence);
}

inline GLboolean glIsFenceNV(GLuint fence)
{
    return glbinding::Binding::IsFenceNV(fence);
}

inline GLboolean glIsFramebufferEXT(GLuint framebuffer)
{
    return glbinding::Binding::IsFramebufferEXT(framebuffer);
}

inline GLboolean glIsImageHandleResidentARB(GLuint64 handle)
{
    return glbinding::Binding::IsImageHandleResidentARB(handle);
}

inline GLboolean glIsImageHandleResidentNV(GLuint64 handle)
{
    return glbinding::Binding::IsImageHandleResidentNV(handle);
}

inline GLboolean glIsNameAMD(GLenum identifier, GLuint name)
{
    return glbinding::Binding::IsNameAMD(identifier, name);
}

inline GLboolean glIsNamedBufferResidentNV(GLuint buffer)
{
    return glbinding::Binding::IsNamedBufferResidentNV(buffer);
}

inline GLboolean glIsNamedStringARB(GLint namelen, const GLchar * name)
{
    return glbinding::Binding::IsNamedStringARB(namelen, name);
}

inline GLboolean glIsObjectBufferATI(GLuint buffer)
{
    return glbinding::Binding::IsObjectBufferATI(buffer);
}

inline GLboolean glIsOcclusionQueryNV(GLuint id)
{
    return glbinding::Binding::IsOcclusionQueryNV(id);
}

inline GLboolean glIsPathNV(GLuint path)
{
    return glbinding::Binding::IsPathNV(path);
}

inline GLboolean glIsPointInFillPathNV(GLuint path, GLuint mask, GLfloat x, GLfloat y)
{
    return glbinding::Binding::IsPointInFillPathNV(path, mask, x, y);
}

inline GLboolean glIsPointInStrokePathNV(GLuint path, GLfloat x, GLfloat y)
{
    return glbinding::Binding::IsPointInStrokePathNV(path, x, y);
}

inline GLboolean glIsProgramARB(GLuint program)
{
    return glbinding::Binding::IsProgramARB(program);
}

inline GLboolean glIsProgramNV(GLuint id)
{
    return glbinding::Binding::IsProgramNV(id);
}

inline GLboolean glIsQueryARB(GLuint id)
{
    return glbinding::Binding::IsQueryARB(id);
}

inline GLboolean glIsRenderbufferEXT(GLuint renderbuffer)
{
    return glbinding::Binding::IsRenderbufferEXT(renderbuffer);
}

inline GLboolean glIsTextureEXT(GLuint texture)
{
    return glbinding::Binding::IsTextureEXT(texture);
}

inline GLboolean glIsTextureHandleResidentARB(GLuint64 handle)
{
    return glbinding::Binding::IsTextureHandleResidentARB(handle);
}

inline GLboolean glIsTextureHandleResidentNV(GLuint64 handle)
{
    return glbinding::Binding::IsTextureHandleResidentNV(handle);
}

inline GLboolean glIsTransformFeedbackNV(GLuint id)
{
    return glbinding::Binding::IsTransformFeedbackNV(id);
}

inline GLboolean glIsVariantEnabledEXT(GLuint id, GLenum cap)
{
    return glbinding::Binding::IsVariantEnabledEXT(id, cap);
}

inline GLboolean glIsVertexArrayAPPLE(GLuint array)
{
    return glbinding::Binding::IsVertexArrayAPPLE(array);
}

inline GLboolean glIsVertexAttribEnabledAPPLE(GLuint index, GLenum pname)
{
    return glbinding::Binding::IsVertexAttribEnabledAPPLE(index, pname);
}

inline void glLabelObjectEXT(GLenum type, GLuint object, GLsizei length, const GLchar * label)
{
    return glbinding::Binding::LabelObjectEXT(type, object, length, label);
}

inline void glLightEnviSGIX(GLenum pname, GLint param)
{
    return glbinding::Binding::LightEnviSGIX(pname, param);
}

inline void glLightModelxOES(GLenum pname, GLfixed param)
{
    return glbinding::Binding::LightModelxOES(pname, param);
}

inline void glLightModelxvOES(GLenum pname, const GLfixed * param)
{
    return glbinding::Binding::LightModelxvOES(pname, param);
}

inline void glLightxOES(GLenum light, GLenum pname, GLfixed param)
{
    return glbinding::Binding::LightxOES(light, pname, param);
}

inline void glLightxvOES(GLenum light, GLenum pname, const GLfixed * params)
{
    return glbinding::Binding::LightxvOES(light, pname, params);
}

inline void glLineWidthxOES(GLfixed width)
{
    return glbinding::Binding::LineWidthxOES(width);
}

inline void glLinkProgramARB(GLhandleARB programObj)
{
    return glbinding::Binding::LinkProgramARB(programObj);
}

inline void glListParameterfSGIX(GLuint list, GLenum pname, GLfloat param)
{
    return glbinding::Binding::ListParameterfSGIX(list, pname, param);
}

inline void glListParameterfvSGIX(GLuint list, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::ListParameterfvSGIX(list, pname, params);
}

inline void glListParameteriSGIX(GLuint list, GLenum pname, GLint param)
{
    return glbinding::Binding::ListParameteriSGIX(list, pname, param);
}

inline void glListParameterivSGIX(GLuint list, GLenum pname, const GLint * params)
{
    return glbinding::Binding::ListParameterivSGIX(list, pname, params);
}

inline void glLoadIdentityDeformationMapSGIX(FfdMaskSGIX mask)
{
    return glbinding::Binding::LoadIdentityDeformationMapSGIX(mask);
}

inline void glLoadMatrixxOES(const GLfixed * m)
{
    return glbinding::Binding::LoadMatrixxOES(m);
}

inline void glLoadProgramNV(GLenum target, GLuint id, GLsizei len, const GLubyte * program)
{
    return glbinding::Binding::LoadProgramNV(target, id, len, program);
}

inline void glLoadTransposeMatrixdARB(const GLdouble * m)
{
    return glbinding::Binding::LoadTransposeMatrixdARB(m);
}

inline void glLoadTransposeMatrixfARB(const GLfloat * m)
{
    return glbinding::Binding::LoadTransposeMatrixfARB(m);
}

inline void glLoadTransposeMatrixxOES(const GLfixed * m)
{
    return glbinding::Binding::LoadTransposeMatrixxOES(m);
}

inline void glLockArraysEXT(GLint first, GLsizei count)
{
    return glbinding::Binding::LockArraysEXT(first, count);
}

inline void glMakeBufferNonResidentNV(GLenum target)
{
    return glbinding::Binding::MakeBufferNonResidentNV(target);
}

inline void glMakeBufferResidentNV(GLenum target, GLenum access)
{
    return glbinding::Binding::MakeBufferResidentNV(target, access);
}

inline void glMakeImageHandleNonResidentARB(GLuint64 handle)
{
    return glbinding::Binding::MakeImageHandleNonResidentARB(handle);
}

inline void glMakeImageHandleNonResidentNV(GLuint64 handle)
{
    return glbinding::Binding::MakeImageHandleNonResidentNV(handle);
}

inline void glMakeImageHandleResidentARB(GLuint64 handle, GLenum access)
{
    return glbinding::Binding::MakeImageHandleResidentARB(handle, access);
}

inline void glMakeImageHandleResidentNV(GLuint64 handle, GLenum access)
{
    return glbinding::Binding::MakeImageHandleResidentNV(handle, access);
}

inline void glMakeNamedBufferNonResidentNV(GLuint buffer)
{
    return glbinding::Binding::MakeNamedBufferNonResidentNV(buffer);
}

inline void glMakeNamedBufferResidentNV(GLuint buffer, GLenum access)
{
    return glbinding::Binding::MakeNamedBufferResidentNV(buffer, access);
}

inline void glMakeTextureHandleNonResidentARB(GLuint64 handle)
{
    return glbinding::Binding::MakeTextureHandleNonResidentARB(handle);
}

inline void glMakeTextureHandleNonResidentNV(GLuint64 handle)
{
    return glbinding::Binding::MakeTextureHandleNonResidentNV(handle);
}

inline void glMakeTextureHandleResidentARB(GLuint64 handle)
{
    return glbinding::Binding::MakeTextureHandleResidentARB(handle);
}

inline void glMakeTextureHandleResidentNV(GLuint64 handle)
{
    return glbinding::Binding::MakeTextureHandleResidentNV(handle);
}

inline void glMap1xOES(GLenum target, GLfixed u1, GLfixed u2, GLint stride, GLint order, GLfixed points)
{
    return glbinding::Binding::Map1xOES(target, u1, u2, stride, order, points);
}

inline void glMap2xOES(GLenum target, GLfixed u1, GLfixed u2, GLint ustride, GLint uorder, GLfixed v1, GLfixed v2, GLint vstride, GLint vorder, GLfixed points)
{
    return glbinding::Binding::Map2xOES(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

inline void * glMapBufferARB(GLenum target, GLenum access)
{
    return glbinding::Binding::MapBufferARB(target, access);
}

inline void glMapControlPointsNV(GLenum target, GLuint index, GLenum type, GLsizei ustride, GLsizei vstride, GLint uorder, GLint vorder, GLboolean packed, const void * points)
{
    return glbinding::Binding::MapControlPointsNV(target, index, type, ustride, vstride, uorder, vorder, packed, points);
}

inline void glMapGrid1xOES(GLint n, GLfixed u1, GLfixed u2)
{
    return glbinding::Binding::MapGrid1xOES(n, u1, u2);
}

inline void glMapGrid2xOES(GLint n, GLfixed u1, GLfixed u2, GLfixed v1, GLfixed v2)
{
    return glbinding::Binding::MapGrid2xOES(n, u1, u2, v1, v2);
}

inline void * glMapNamedBuffer(GLuint buffer, GLenum access)
{
    return glbinding::Binding::MapNamedBuffer(buffer, access);
}

inline void * glMapNamedBufferEXT(GLuint buffer, GLenum access)
{
    return glbinding::Binding::MapNamedBufferEXT(buffer, access);
}

inline void * glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizei length, BufferAccessMask access)
{
    return glbinding::Binding::MapNamedBufferRange(buffer, offset, length, access);
}

inline void * glMapNamedBufferRangeEXT(GLuint buffer, GLintptr offset, GLsizeiptr length, BufferAccessMask access)
{
    return glbinding::Binding::MapNamedBufferRangeEXT(buffer, offset, length, access);
}

inline void * glMapObjectBufferATI(GLuint buffer)
{
    return glbinding::Binding::MapObjectBufferATI(buffer);
}

inline void glMapParameterfvNV(GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::MapParameterfvNV(target, pname, params);
}

inline void glMapParameterivNV(GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::MapParameterivNV(target, pname, params);
}

inline void * glMapTexture2DINTEL(GLuint texture, GLint level, MapBufferUsageMask access, GLint * stride, GLenum * layout)
{
    return glbinding::Binding::MapTexture2DINTEL(texture, level, access, stride, layout);
}

inline void glMapVertexAttrib1dAPPLE(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points)
{
    return glbinding::Binding::MapVertexAttrib1dAPPLE(index, size, u1, u2, stride, order, points);
}

inline void glMapVertexAttrib1fAPPLE(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points)
{
    return glbinding::Binding::MapVertexAttrib1fAPPLE(index, size, u1, u2, stride, order, points);
}

inline void glMapVertexAttrib2dAPPLE(GLuint index, GLuint size, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points)
{
    return glbinding::Binding::MapVertexAttrib2dAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

inline void glMapVertexAttrib2fAPPLE(GLuint index, GLuint size, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points)
{
    return glbinding::Binding::MapVertexAttrib2fAPPLE(index, size, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

inline void glMaterialxOES(GLenum face, GLenum pname, GLfixed param)
{
    return glbinding::Binding::MaterialxOES(face, pname, param);
}

inline void glMaterialxvOES(GLenum face, GLenum pname, const GLfixed * param)
{
    return glbinding::Binding::MaterialxvOES(face, pname, param);
}

inline void glMatrixFrustumEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
    return glbinding::Binding::MatrixFrustumEXT(mode, left, right, bottom, top, zNear, zFar);
}

inline void glMatrixIndexPointerARB(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::MatrixIndexPointerARB(size, type, stride, pointer);
}

inline void glMatrixIndexubvARB(GLint size, const GLubyte * indices)
{
    return glbinding::Binding::MatrixIndexubvARB(size, indices);
}

inline void glMatrixIndexuivARB(GLint size, const GLuint * indices)
{
    return glbinding::Binding::MatrixIndexuivARB(size, indices);
}

inline void glMatrixIndexusvARB(GLint size, const GLushort * indices)
{
    return glbinding::Binding::MatrixIndexusvARB(size, indices);
}

inline void glMatrixLoad3x2fNV(GLenum matrixMode, const GLfloat * m)
{
    return glbinding::Binding::MatrixLoad3x2fNV(matrixMode, m);
}

inline void glMatrixLoad3x3fNV(GLenum matrixMode, const GLfloat * m)
{
    return glbinding::Binding::MatrixLoad3x3fNV(matrixMode, m);
}

inline void glMatrixLoadIdentityEXT(GLenum mode)
{
    return glbinding::Binding::MatrixLoadIdentityEXT(mode);
}

inline void glMatrixLoadTranspose3x3fNV(GLenum matrixMode, const GLfloat * m)
{
    return glbinding::Binding::MatrixLoadTranspose3x3fNV(matrixMode, m);
}

inline void glMatrixLoadTransposedEXT(GLenum mode, const GLdouble * m)
{
    return glbinding::Binding::MatrixLoadTransposedEXT(mode, m);
}

inline void glMatrixLoadTransposefEXT(GLenum mode, const GLfloat * m)
{
    return glbinding::Binding::MatrixLoadTransposefEXT(mode, m);
}

inline void glMatrixLoaddEXT(GLenum mode, const GLdouble * m)
{
    return glbinding::Binding::MatrixLoaddEXT(mode, m);
}

inline void glMatrixLoadfEXT(GLenum mode, const GLfloat * m)
{
    return glbinding::Binding::MatrixLoadfEXT(mode, m);
}

inline void glMatrixMult3x2fNV(GLenum matrixMode, const GLfloat * m)
{
    return glbinding::Binding::MatrixMult3x2fNV(matrixMode, m);
}

inline void glMatrixMult3x3fNV(GLenum matrixMode, const GLfloat * m)
{
    return glbinding::Binding::MatrixMult3x3fNV(matrixMode, m);
}

inline void glMatrixMultTranspose3x3fNV(GLenum matrixMode, const GLfloat * m)
{
    return glbinding::Binding::MatrixMultTranspose3x3fNV(matrixMode, m);
}

inline void glMatrixMultTransposedEXT(GLenum mode, const GLdouble * m)
{
    return glbinding::Binding::MatrixMultTransposedEXT(mode, m);
}

inline void glMatrixMultTransposefEXT(GLenum mode, const GLfloat * m)
{
    return glbinding::Binding::MatrixMultTransposefEXT(mode, m);
}

inline void glMatrixMultdEXT(GLenum mode, const GLdouble * m)
{
    return glbinding::Binding::MatrixMultdEXT(mode, m);
}

inline void glMatrixMultfEXT(GLenum mode, const GLfloat * m)
{
    return glbinding::Binding::MatrixMultfEXT(mode, m);
}

inline void glMatrixOrthoEXT(GLenum mode, GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
{
    return glbinding::Binding::MatrixOrthoEXT(mode, left, right, bottom, top, zNear, zFar);
}

inline void glMatrixPopEXT(GLenum mode)
{
    return glbinding::Binding::MatrixPopEXT(mode);
}

inline void glMatrixPushEXT(GLenum mode)
{
    return glbinding::Binding::MatrixPushEXT(mode);
}

inline void glMatrixRotatedEXT(GLenum mode, GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::MatrixRotatedEXT(mode, angle, x, y, z);
}

inline void glMatrixRotatefEXT(GLenum mode, GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::MatrixRotatefEXT(mode, angle, x, y, z);
}

inline void glMatrixScaledEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::MatrixScaledEXT(mode, x, y, z);
}

inline void glMatrixScalefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::MatrixScalefEXT(mode, x, y, z);
}

inline void glMatrixTranslatedEXT(GLenum mode, GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::MatrixTranslatedEXT(mode, x, y, z);
}

inline void glMatrixTranslatefEXT(GLenum mode, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::MatrixTranslatefEXT(mode, x, y, z);
}

inline void glMemoryBarrierByRegion(MemoryBarrierMask barriers)
{
    return glbinding::Binding::MemoryBarrierByRegion(barriers);
}

inline void glMemoryBarrierEXT(MemoryBarrierMask barriers)
{
    return glbinding::Binding::MemoryBarrierEXT(barriers);
}

inline void glMinSampleShadingARB(GLfloat value)
{
    return glbinding::Binding::MinSampleShadingARB(value);
}

inline void glMinmax(GLenum target, GLenum internalformat, GLboolean sink)
{
    return glbinding::Binding::Minmax(target, internalformat, sink);
}

inline void glMinmaxEXT(GLenum target, GLenum internalformat, GLboolean sink)
{
    return glbinding::Binding::MinmaxEXT(target, internalformat, sink);
}

inline void glMultMatrixxOES(const GLfixed * m)
{
    return glbinding::Binding::MultMatrixxOES(m);
}

inline void glMultTransposeMatrixdARB(const GLdouble * m)
{
    return glbinding::Binding::MultTransposeMatrixdARB(m);
}

inline void glMultTransposeMatrixfARB(const GLfloat * m)
{
    return glbinding::Binding::MultTransposeMatrixfARB(m);
}

inline void glMultTransposeMatrixxOES(const GLfixed * m)
{
    return glbinding::Binding::MultTransposeMatrixxOES(m);
}

inline void glMultiDrawArraysEXT(GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount)
{
    return glbinding::Binding::MultiDrawArraysEXT(mode, first, count, primcount);
}

inline void glMultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride)
{
    return glbinding::Binding::MultiDrawArraysIndirect(mode, indirect, drawcount, stride);
}

inline void glMultiDrawArraysIndirectAMD(GLenum mode, const void * indirect, GLsizei primcount, GLsizei stride)
{
    return glbinding::Binding::MultiDrawArraysIndirectAMD(mode, indirect, primcount, stride);
}

inline void glMultiDrawArraysIndirectBindlessCountNV(GLenum mode, const void * indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount)
{
    return glbinding::Binding::MultiDrawArraysIndirectBindlessCountNV(mode, indirect, drawCount, maxDrawCount, stride, vertexBufferCount);
}

inline void glMultiDrawArraysIndirectBindlessNV(GLenum mode, const void * indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount)
{
    return glbinding::Binding::MultiDrawArraysIndirectBindlessNV(mode, indirect, drawCount, stride, vertexBufferCount);
}

inline void glMultiDrawArraysIndirectCountARB(GLenum mode, GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
{
    return glbinding::Binding::MultiDrawArraysIndirectCountARB(mode, indirect, drawcount, maxdrawcount, stride);
}

inline void glMultiDrawElementArrayAPPLE(GLenum mode, const GLint * first, const GLsizei * count, GLsizei primcount)
{
    return glbinding::Binding::MultiDrawElementArrayAPPLE(mode, first, count, primcount);
}

inline void glMultiDrawElementsEXT(GLenum mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei primcount)
{
    return glbinding::Binding::MultiDrawElementsEXT(mode, count, type, indices, primcount);
}

inline void glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride)
{
    return glbinding::Binding::MultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
}

inline void glMultiDrawElementsIndirectAMD(GLenum mode, GLenum type, const void * indirect, GLsizei primcount, GLsizei stride)
{
    return glbinding::Binding::MultiDrawElementsIndirectAMD(mode, type, indirect, primcount, stride);
}

inline void glMultiDrawElementsIndirectBindlessCountNV(GLenum mode, GLenum type, const void * indirect, GLsizei drawCount, GLsizei maxDrawCount, GLsizei stride, GLint vertexBufferCount)
{
    return glbinding::Binding::MultiDrawElementsIndirectBindlessCountNV(mode, type, indirect, drawCount, maxDrawCount, stride, vertexBufferCount);
}

inline void glMultiDrawElementsIndirectBindlessNV(GLenum mode, GLenum type, const void * indirect, GLsizei drawCount, GLsizei stride, GLint vertexBufferCount)
{
    return glbinding::Binding::MultiDrawElementsIndirectBindlessNV(mode, type, indirect, drawCount, stride, vertexBufferCount);
}

inline void glMultiDrawElementsIndirectCountARB(GLenum mode, GLenum type, GLintptr indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride)
{
    return glbinding::Binding::MultiDrawElementsIndirectCountARB(mode, type, indirect, drawcount, maxdrawcount, stride);
}

inline void glMultiDrawRangeElementArrayAPPLE(GLenum mode, GLuint start, GLuint end, const GLint * first, const GLsizei * count, GLsizei primcount)
{
    return glbinding::Binding::MultiDrawRangeElementArrayAPPLE(mode, start, end, first, count, primcount);
}

inline void glMultiModeDrawArraysIBM(const GLenum * mode, const GLint * first, const GLsizei * count, GLsizei primcount, GLint modestride)
{
    return glbinding::Binding::MultiModeDrawArraysIBM(mode, first, count, primcount, modestride);
}

inline void glMultiModeDrawElementsIBM(const GLenum * mode, const GLsizei * count, GLenum type, const void *const* indices, GLsizei primcount, GLint modestride)
{
    return glbinding::Binding::MultiModeDrawElementsIBM(mode, count, type, indices, primcount, modestride);
}

inline void glMultiTexBufferEXT(GLenum texunit, GLenum target, GLenum internalformat, GLuint buffer)
{
    return glbinding::Binding::MultiTexBufferEXT(texunit, target, internalformat, buffer);
}

inline void glMultiTexCoord1bOES(GLenum texture, GLbyte s)
{
    return glbinding::Binding::MultiTexCoord1bOES(texture, s);
}

inline void glMultiTexCoord1bvOES(GLenum texture, const GLbyte * coords)
{
    return glbinding::Binding::MultiTexCoord1bvOES(texture, coords);
}

inline void glMultiTexCoord1dARB(GLenum target, GLdouble s)
{
    return glbinding::Binding::MultiTexCoord1dARB(target, s);
}

inline void glMultiTexCoord1dvARB(GLenum target, const GLdouble * v)
{
    return glbinding::Binding::MultiTexCoord1dvARB(target, v);
}

inline void glMultiTexCoord1fARB(GLenum target, GLfloat s)
{
    return glbinding::Binding::MultiTexCoord1fARB(target, s);
}

inline void glMultiTexCoord1fvARB(GLenum target, const GLfloat * v)
{
    return glbinding::Binding::MultiTexCoord1fvARB(target, v);
}

inline void glMultiTexCoord1hNV(GLenum target, GLhalfNV s)
{
    return glbinding::Binding::MultiTexCoord1hNV(target, s);
}

inline void glMultiTexCoord1hvNV(GLenum target, const GLhalfNV * v)
{
    return glbinding::Binding::MultiTexCoord1hvNV(target, v);
}

inline void glMultiTexCoord1iARB(GLenum target, GLint s)
{
    return glbinding::Binding::MultiTexCoord1iARB(target, s);
}

inline void glMultiTexCoord1ivARB(GLenum target, const GLint * v)
{
    return glbinding::Binding::MultiTexCoord1ivARB(target, v);
}

inline void glMultiTexCoord1sARB(GLenum target, GLshort s)
{
    return glbinding::Binding::MultiTexCoord1sARB(target, s);
}

inline void glMultiTexCoord1svARB(GLenum target, const GLshort * v)
{
    return glbinding::Binding::MultiTexCoord1svARB(target, v);
}

inline void glMultiTexCoord1xOES(GLenum texture, GLfixed s)
{
    return glbinding::Binding::MultiTexCoord1xOES(texture, s);
}

inline void glMultiTexCoord1xvOES(GLenum texture, const GLfixed * coords)
{
    return glbinding::Binding::MultiTexCoord1xvOES(texture, coords);
}

inline void glMultiTexCoord2bOES(GLenum texture, GLbyte s, GLbyte t)
{
    return glbinding::Binding::MultiTexCoord2bOES(texture, s, t);
}

inline void glMultiTexCoord2bvOES(GLenum texture, const GLbyte * coords)
{
    return glbinding::Binding::MultiTexCoord2bvOES(texture, coords);
}

inline void glMultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t)
{
    return glbinding::Binding::MultiTexCoord2dARB(target, s, t);
}

inline void glMultiTexCoord2dvARB(GLenum target, const GLdouble * v)
{
    return glbinding::Binding::MultiTexCoord2dvARB(target, v);
}

inline void glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t)
{
    return glbinding::Binding::MultiTexCoord2fARB(target, s, t);
}

inline void glMultiTexCoord2fvARB(GLenum target, const GLfloat * v)
{
    return glbinding::Binding::MultiTexCoord2fvARB(target, v);
}

inline void glMultiTexCoord2hNV(GLenum target, GLhalfNV s, GLhalfNV t)
{
    return glbinding::Binding::MultiTexCoord2hNV(target, s, t);
}

inline void glMultiTexCoord2hvNV(GLenum target, const GLhalfNV * v)
{
    return glbinding::Binding::MultiTexCoord2hvNV(target, v);
}

inline void glMultiTexCoord2iARB(GLenum target, GLint s, GLint t)
{
    return glbinding::Binding::MultiTexCoord2iARB(target, s, t);
}

inline void glMultiTexCoord2ivARB(GLenum target, const GLint * v)
{
    return glbinding::Binding::MultiTexCoord2ivARB(target, v);
}

inline void glMultiTexCoord2sARB(GLenum target, GLshort s, GLshort t)
{
    return glbinding::Binding::MultiTexCoord2sARB(target, s, t);
}

inline void glMultiTexCoord2svARB(GLenum target, const GLshort * v)
{
    return glbinding::Binding::MultiTexCoord2svARB(target, v);
}

inline void glMultiTexCoord2xOES(GLenum texture, GLfixed s, GLfixed t)
{
    return glbinding::Binding::MultiTexCoord2xOES(texture, s, t);
}

inline void glMultiTexCoord2xvOES(GLenum texture, const GLfixed * coords)
{
    return glbinding::Binding::MultiTexCoord2xvOES(texture, coords);
}

inline void glMultiTexCoord3bOES(GLenum texture, GLbyte s, GLbyte t, GLbyte r)
{
    return glbinding::Binding::MultiTexCoord3bOES(texture, s, t, r);
}

inline void glMultiTexCoord3bvOES(GLenum texture, const GLbyte * coords)
{
    return glbinding::Binding::MultiTexCoord3bvOES(texture, coords);
}

inline void glMultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
    return glbinding::Binding::MultiTexCoord3dARB(target, s, t, r);
}

inline void glMultiTexCoord3dvARB(GLenum target, const GLdouble * v)
{
    return glbinding::Binding::MultiTexCoord3dvARB(target, v);
}

inline void glMultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
    return glbinding::Binding::MultiTexCoord3fARB(target, s, t, r);
}

inline void glMultiTexCoord3fvARB(GLenum target, const GLfloat * v)
{
    return glbinding::Binding::MultiTexCoord3fvARB(target, v);
}

inline void glMultiTexCoord3hNV(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r)
{
    return glbinding::Binding::MultiTexCoord3hNV(target, s, t, r);
}

inline void glMultiTexCoord3hvNV(GLenum target, const GLhalfNV * v)
{
    return glbinding::Binding::MultiTexCoord3hvNV(target, v);
}

inline void glMultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r)
{
    return glbinding::Binding::MultiTexCoord3iARB(target, s, t, r);
}

inline void glMultiTexCoord3ivARB(GLenum target, const GLint * v)
{
    return glbinding::Binding::MultiTexCoord3ivARB(target, v);
}

inline void glMultiTexCoord3sARB(GLenum target, GLshort s, GLshort t, GLshort r)
{
    return glbinding::Binding::MultiTexCoord3sARB(target, s, t, r);
}

inline void glMultiTexCoord3svARB(GLenum target, const GLshort * v)
{
    return glbinding::Binding::MultiTexCoord3svARB(target, v);
}

inline void glMultiTexCoord3xOES(GLenum texture, GLfixed s, GLfixed t, GLfixed r)
{
    return glbinding::Binding::MultiTexCoord3xOES(texture, s, t, r);
}

inline void glMultiTexCoord3xvOES(GLenum texture, const GLfixed * coords)
{
    return glbinding::Binding::MultiTexCoord3xvOES(texture, coords);
}

inline void glMultiTexCoord4bOES(GLenum texture, GLbyte s, GLbyte t, GLbyte r, GLbyte q)
{
    return glbinding::Binding::MultiTexCoord4bOES(texture, s, t, r, q);
}

inline void glMultiTexCoord4bvOES(GLenum texture, const GLbyte * coords)
{
    return glbinding::Binding::MultiTexCoord4bvOES(texture, coords);
}

inline void glMultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
    return glbinding::Binding::MultiTexCoord4dARB(target, s, t, r, q);
}

inline void glMultiTexCoord4dvARB(GLenum target, const GLdouble * v)
{
    return glbinding::Binding::MultiTexCoord4dvARB(target, v);
}

inline void glMultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    return glbinding::Binding::MultiTexCoord4fARB(target, s, t, r, q);
}

inline void glMultiTexCoord4fvARB(GLenum target, const GLfloat * v)
{
    return glbinding::Binding::MultiTexCoord4fvARB(target, v);
}

inline void glMultiTexCoord4hNV(GLenum target, GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q)
{
    return glbinding::Binding::MultiTexCoord4hNV(target, s, t, r, q);
}

inline void glMultiTexCoord4hvNV(GLenum target, const GLhalfNV * v)
{
    return glbinding::Binding::MultiTexCoord4hvNV(target, v);
}

inline void glMultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r, GLint q)
{
    return glbinding::Binding::MultiTexCoord4iARB(target, s, t, r, q);
}

inline void glMultiTexCoord4ivARB(GLenum target, const GLint * v)
{
    return glbinding::Binding::MultiTexCoord4ivARB(target, v);
}

inline void glMultiTexCoord4sARB(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
    return glbinding::Binding::MultiTexCoord4sARB(target, s, t, r, q);
}

inline void glMultiTexCoord4svARB(GLenum target, const GLshort * v)
{
    return glbinding::Binding::MultiTexCoord4svARB(target, v);
}

inline void glMultiTexCoord4xOES(GLenum texture, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
    return glbinding::Binding::MultiTexCoord4xOES(texture, s, t, r, q);
}

inline void glMultiTexCoord4xvOES(GLenum texture, const GLfixed * coords)
{
    return glbinding::Binding::MultiTexCoord4xvOES(texture, coords);
}

inline void glMultiTexCoordPointerEXT(GLenum texunit, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::MultiTexCoordPointerEXT(texunit, size, type, stride, pointer);
}

inline void glMultiTexEnvfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param)
{
    return glbinding::Binding::MultiTexEnvfEXT(texunit, target, pname, param);
}

inline void glMultiTexEnvfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::MultiTexEnvfvEXT(texunit, target, pname, params);
}

inline void glMultiTexEnviEXT(GLenum texunit, GLenum target, GLenum pname, GLint param)
{
    return glbinding::Binding::MultiTexEnviEXT(texunit, target, pname, param);
}

inline void glMultiTexEnvivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::MultiTexEnvivEXT(texunit, target, pname, params);
}

inline void glMultiTexGendEXT(GLenum texunit, GLenum coord, GLenum pname, GLdouble param)
{
    return glbinding::Binding::MultiTexGendEXT(texunit, coord, pname, param);
}

inline void glMultiTexGendvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLdouble * params)
{
    return glbinding::Binding::MultiTexGendvEXT(texunit, coord, pname, params);
}

inline void glMultiTexGenfEXT(GLenum texunit, GLenum coord, GLenum pname, GLfloat param)
{
    return glbinding::Binding::MultiTexGenfEXT(texunit, coord, pname, param);
}

inline void glMultiTexGenfvEXT(GLenum texunit, GLenum coord, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::MultiTexGenfvEXT(texunit, coord, pname, params);
}

inline void glMultiTexGeniEXT(GLenum texunit, GLenum coord, GLenum pname, GLint param)
{
    return glbinding::Binding::MultiTexGeniEXT(texunit, coord, pname, param);
}

inline void glMultiTexGenivEXT(GLenum texunit, GLenum coord, GLenum pname, const GLint * params)
{
    return glbinding::Binding::MultiTexGenivEXT(texunit, coord, pname, params);
}

inline void glMultiTexImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::MultiTexImage1DEXT(texunit, target, level, internalformat, width, border, format, type, pixels);
}

inline void glMultiTexImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::MultiTexImage2DEXT(texunit, target, level, internalformat, width, height, border, format, type, pixels);
}

inline void glMultiTexImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::MultiTexImage3DEXT(texunit, target, level, internalformat, width, height, depth, border, format, type, pixels);
}

inline void glMultiTexParameterIivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::MultiTexParameterIivEXT(texunit, target, pname, params);
}

inline void glMultiTexParameterIuivEXT(GLenum texunit, GLenum target, GLenum pname, const GLuint * params)
{
    return glbinding::Binding::MultiTexParameterIuivEXT(texunit, target, pname, params);
}

inline void glMultiTexParameterfEXT(GLenum texunit, GLenum target, GLenum pname, GLfloat param)
{
    return glbinding::Binding::MultiTexParameterfEXT(texunit, target, pname, param);
}

inline void glMultiTexParameterfvEXT(GLenum texunit, GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::MultiTexParameterfvEXT(texunit, target, pname, params);
}

inline void glMultiTexParameteriEXT(GLenum texunit, GLenum target, GLenum pname, GLint param)
{
    return glbinding::Binding::MultiTexParameteriEXT(texunit, target, pname, param);
}

inline void glMultiTexParameterivEXT(GLenum texunit, GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::MultiTexParameterivEXT(texunit, target, pname, params);
}

inline void glMultiTexRenderbufferEXT(GLenum texunit, GLenum target, GLuint renderbuffer)
{
    return glbinding::Binding::MultiTexRenderbufferEXT(texunit, target, renderbuffer);
}

inline void glMultiTexSubImage1DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::MultiTexSubImage1DEXT(texunit, target, level, xoffset, width, format, type, pixels);
}

inline void glMultiTexSubImage2DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::MultiTexSubImage2DEXT(texunit, target, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void glMultiTexSubImage3DEXT(GLenum texunit, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::MultiTexSubImage3DEXT(texunit, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

inline void glNamedBufferData(GLuint buffer, GLsizei size, const void * data, GLenum usage)
{
    return glbinding::Binding::NamedBufferData(buffer, size, data, usage);
}

inline void glNamedBufferDataEXT(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage)
{
    return glbinding::Binding::NamedBufferDataEXT(buffer, size, data, usage);
}

inline void glNamedBufferPageCommitmentARB(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit)
{
    return glbinding::Binding::NamedBufferPageCommitmentARB(buffer, offset, size, commit);
}

inline void glNamedBufferPageCommitmentEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, GLboolean commit)
{
    return glbinding::Binding::NamedBufferPageCommitmentEXT(buffer, offset, size, commit);
}

inline void glNamedBufferStorage(GLuint buffer, GLsizei size, const void * data, MapBufferUsageMask flags)
{
    return glbinding::Binding::NamedBufferStorage(buffer, size, data, flags);
}

inline void glNamedBufferStorageEXT(GLuint buffer, GLsizeiptr size, const void * data, MapBufferUsageMask flags)
{
    return glbinding::Binding::NamedBufferStorageEXT(buffer, size, data, flags);
}

inline void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizei size, const void * data)
{
    return glbinding::Binding::NamedBufferSubData(buffer, offset, size, data);
}

inline void glNamedBufferSubDataEXT(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data)
{
    return glbinding::Binding::NamedBufferSubDataEXT(buffer, offset, size, data);
}

inline void glNamedCopyBufferSubDataEXT(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
{
    return glbinding::Binding::NamedCopyBufferSubDataEXT(readBuffer, writeBuffer, readOffset, writeOffset, size);
}

inline void glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf)
{
    return glbinding::Binding::NamedFramebufferDrawBuffer(framebuffer, buf);
}

inline void glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs)
{
    return glbinding::Binding::NamedFramebufferDrawBuffers(framebuffer, n, bufs);
}

inline void glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param)
{
    return glbinding::Binding::NamedFramebufferParameteri(framebuffer, pname, param);
}

inline void glNamedFramebufferParameteriEXT(GLuint framebuffer, GLenum pname, GLint param)
{
    return glbinding::Binding::NamedFramebufferParameteriEXT(framebuffer, pname, param);
}

inline void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src)
{
    return glbinding::Binding::NamedFramebufferReadBuffer(framebuffer, src);
}

inline void glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    return glbinding::Binding::NamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
}

inline void glNamedFramebufferRenderbufferEXT(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    return glbinding::Binding::NamedFramebufferRenderbufferEXT(framebuffer, attachment, renderbuffertarget, renderbuffer);
}

inline void glNamedFramebufferSampleLocationsfvNV(GLuint framebuffer, GLuint start, GLsizei count, const GLfloat * v)
{
    return glbinding::Binding::NamedFramebufferSampleLocationsfvNV(framebuffer, start, count, v);
}

inline void glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
{
    return glbinding::Binding::NamedFramebufferTexture(framebuffer, attachment, texture, level);
}

inline void glNamedFramebufferTexture1DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    return glbinding::Binding::NamedFramebufferTexture1DEXT(framebuffer, attachment, textarget, texture, level);
}

inline void glNamedFramebufferTexture2DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    return glbinding::Binding::NamedFramebufferTexture2DEXT(framebuffer, attachment, textarget, texture, level);
}

inline void glNamedFramebufferTexture3DEXT(GLuint framebuffer, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset)
{
    return glbinding::Binding::NamedFramebufferTexture3DEXT(framebuffer, attachment, textarget, texture, level, zoffset);
}

inline void glNamedFramebufferTextureEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level)
{
    return glbinding::Binding::NamedFramebufferTextureEXT(framebuffer, attachment, texture, level);
}

inline void glNamedFramebufferTextureFaceEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLenum face)
{
    return glbinding::Binding::NamedFramebufferTextureFaceEXT(framebuffer, attachment, texture, level, face);
}

inline void glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
    return glbinding::Binding::NamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
}

inline void glNamedFramebufferTextureLayerEXT(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer)
{
    return glbinding::Binding::NamedFramebufferTextureLayerEXT(framebuffer, attachment, texture, level, layer);
}

inline void glNamedProgramLocalParameter4dEXT(GLuint program, GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::NamedProgramLocalParameter4dEXT(program, target, index, x, y, z, w);
}

inline void glNamedProgramLocalParameter4dvEXT(GLuint program, GLenum target, GLuint index, const GLdouble * params)
{
    return glbinding::Binding::NamedProgramLocalParameter4dvEXT(program, target, index, params);
}

inline void glNamedProgramLocalParameter4fEXT(GLuint program, GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::NamedProgramLocalParameter4fEXT(program, target, index, x, y, z, w);
}

inline void glNamedProgramLocalParameter4fvEXT(GLuint program, GLenum target, GLuint index, const GLfloat * params)
{
    return glbinding::Binding::NamedProgramLocalParameter4fvEXT(program, target, index, params);
}

inline void glNamedProgramLocalParameterI4iEXT(GLuint program, GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w)
{
    return glbinding::Binding::NamedProgramLocalParameterI4iEXT(program, target, index, x, y, z, w);
}

inline void glNamedProgramLocalParameterI4ivEXT(GLuint program, GLenum target, GLuint index, const GLint * params)
{
    return glbinding::Binding::NamedProgramLocalParameterI4ivEXT(program, target, index, params);
}

inline void glNamedProgramLocalParameterI4uiEXT(GLuint program, GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
    return glbinding::Binding::NamedProgramLocalParameterI4uiEXT(program, target, index, x, y, z, w);
}

inline void glNamedProgramLocalParameterI4uivEXT(GLuint program, GLenum target, GLuint index, const GLuint * params)
{
    return glbinding::Binding::NamedProgramLocalParameterI4uivEXT(program, target, index, params);
}

inline void glNamedProgramLocalParameters4fvEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLfloat * params)
{
    return glbinding::Binding::NamedProgramLocalParameters4fvEXT(program, target, index, count, params);
}

inline void glNamedProgramLocalParametersI4ivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLint * params)
{
    return glbinding::Binding::NamedProgramLocalParametersI4ivEXT(program, target, index, count, params);
}

inline void glNamedProgramLocalParametersI4uivEXT(GLuint program, GLenum target, GLuint index, GLsizei count, const GLuint * params)
{
    return glbinding::Binding::NamedProgramLocalParametersI4uivEXT(program, target, index, count, params);
}

inline void glNamedProgramStringEXT(GLuint program, GLenum target, GLenum format, GLsizei len, const void * string)
{
    return glbinding::Binding::NamedProgramStringEXT(program, target, format, len, string);
}

inline void glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::NamedRenderbufferStorage(renderbuffer, internalformat, width, height);
}

inline void glNamedRenderbufferStorageEXT(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::NamedRenderbufferStorageEXT(renderbuffer, internalformat, width, height);
}

inline void glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::NamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
}

inline void glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint renderbuffer, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::NamedRenderbufferStorageMultisampleCoverageEXT(renderbuffer, coverageSamples, colorSamples, internalformat, width, height);
}

inline void glNamedRenderbufferStorageMultisampleEXT(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::NamedRenderbufferStorageMultisampleEXT(renderbuffer, samples, internalformat, width, height);
}

inline void glNamedStringARB(GLenum type, GLint namelen, const GLchar * name, GLint stringlen, const GLchar * string)
{
    return glbinding::Binding::NamedStringARB(type, namelen, name, stringlen, string);
}

inline GLuint glNewObjectBufferATI(GLsizei size, const void * pointer, GLenum usage)
{
    return glbinding::Binding::NewObjectBufferATI(size, pointer, usage);
}

inline void glNormal3fVertex3fSUN(GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::Normal3fVertex3fSUN(nx, ny, nz, x, y, z);
}

inline void glNormal3fVertex3fvSUN(const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::Normal3fVertex3fvSUN(n, v);
}

inline void glNormal3hNV(GLhalfNV nx, GLhalfNV ny, GLhalfNV nz)
{
    return glbinding::Binding::Normal3hNV(nx, ny, nz);
}

inline void glNormal3hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::Normal3hvNV(v);
}

inline void glNormal3xOES(GLfixed nx, GLfixed ny, GLfixed nz)
{
    return glbinding::Binding::Normal3xOES(nx, ny, nz);
}

inline void glNormal3xvOES(const GLfixed * coords)
{
    return glbinding::Binding::Normal3xvOES(coords);
}

inline void glNormalFormatNV(GLenum type, GLsizei stride)
{
    return glbinding::Binding::NormalFormatNV(type, stride);
}

inline void glNormalPointerEXT(GLenum type, GLsizei stride, GLsizei count, const void * pointer)
{
    return glbinding::Binding::NormalPointerEXT(type, stride, count, pointer);
}

inline void glNormalPointerListIBM(GLenum type, GLint stride, const void ** pointer, GLint ptrstride)
{
    return glbinding::Binding::NormalPointerListIBM(type, stride, pointer, ptrstride);
}

inline void glNormalPointervINTEL(GLenum type, const void ** pointer)
{
    return glbinding::Binding::NormalPointervINTEL(type, pointer);
}

inline void glNormalStream3bATI(GLenum stream, GLbyte nx, GLbyte ny, GLbyte nz)
{
    return glbinding::Binding::NormalStream3bATI(stream, nx, ny, nz);
}

inline void glNormalStream3bvATI(GLenum stream, const GLbyte * coords)
{
    return glbinding::Binding::NormalStream3bvATI(stream, coords);
}

inline void glNormalStream3dATI(GLenum stream, GLdouble nx, GLdouble ny, GLdouble nz)
{
    return glbinding::Binding::NormalStream3dATI(stream, nx, ny, nz);
}

inline void glNormalStream3dvATI(GLenum stream, const GLdouble * coords)
{
    return glbinding::Binding::NormalStream3dvATI(stream, coords);
}

inline void glNormalStream3fATI(GLenum stream, GLfloat nx, GLfloat ny, GLfloat nz)
{
    return glbinding::Binding::NormalStream3fATI(stream, nx, ny, nz);
}

inline void glNormalStream3fvATI(GLenum stream, const GLfloat * coords)
{
    return glbinding::Binding::NormalStream3fvATI(stream, coords);
}

inline void glNormalStream3iATI(GLenum stream, GLint nx, GLint ny, GLint nz)
{
    return glbinding::Binding::NormalStream3iATI(stream, nx, ny, nz);
}

inline void glNormalStream3ivATI(GLenum stream, const GLint * coords)
{
    return glbinding::Binding::NormalStream3ivATI(stream, coords);
}

inline void glNormalStream3sATI(GLenum stream, GLshort nx, GLshort ny, GLshort nz)
{
    return glbinding::Binding::NormalStream3sATI(stream, nx, ny, nz);
}

inline void glNormalStream3svATI(GLenum stream, const GLshort * coords)
{
    return glbinding::Binding::NormalStream3svATI(stream, coords);
}

inline void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label)
{
    return glbinding::Binding::ObjectLabel(identifier, name, length, label);
}

inline void glObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label)
{
    return glbinding::Binding::ObjectPtrLabel(ptr, length, label);
}

inline GLenum glObjectPurgeableAPPLE(GLenum objectType, GLuint name, GLenum option)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::ObjectPurgeableAPPLE(objectType, name, option));
}

inline GLenum glObjectUnpurgeableAPPLE(GLenum objectType, GLuint name, GLenum option)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::ObjectUnpurgeableAPPLE(objectType, name, option));
}

inline void glOrthofOES(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
{
    return glbinding::Binding::OrthofOES(l, r, b, t, n, f);
}

inline void glOrthoxOES(GLfixed l, GLfixed r, GLfixed b, GLfixed t, GLfixed n, GLfixed f)
{
    return glbinding::Binding::OrthoxOES(l, r, b, t, n, f);
}

inline void glPNTrianglesfATI(GLenum pname, GLfloat param)
{
    return glbinding::Binding::PNTrianglesfATI(pname, param);
}

inline void glPNTrianglesiATI(GLenum pname, GLint param)
{
    return glbinding::Binding::PNTrianglesiATI(pname, param);
}

inline void glPassTexCoordATI(GLuint dst, GLuint coord, GLenum swizzle)
{
    return glbinding::Binding::PassTexCoordATI(dst, coord, swizzle);
}

inline void glPassThroughxOES(GLfixed token)
{
    return glbinding::Binding::PassThroughxOES(token);
}

inline void glPathColorGenNV(GLenum color, GLenum genMode, GLenum colorFormat, const GLfloat * coeffs)
{
    return glbinding::Binding::PathColorGenNV(color, genMode, colorFormat, coeffs);
}

inline void glPathCommandsNV(GLuint path, GLsizei numCommands, const GLubyte * commands, GLsizei numCoords, GLenum coordType, const void * coords)
{
    return glbinding::Binding::PathCommandsNV(path, numCommands, commands, numCoords, coordType, coords);
}

inline void glPathCoordsNV(GLuint path, GLsizei numCoords, GLenum coordType, const void * coords)
{
    return glbinding::Binding::PathCoordsNV(path, numCoords, coordType, coords);
}

inline void glPathCoverDepthFuncNV(GLenum func)
{
    return glbinding::Binding::PathCoverDepthFuncNV(func);
}

inline void glPathDashArrayNV(GLuint path, GLsizei dashCount, const GLfloat * dashArray)
{
    return glbinding::Binding::PathDashArrayNV(path, dashCount, dashArray);
}

inline void glPathFogGenNV(GLenum genMode)
{
    return glbinding::Binding::PathFogGenNV(genMode);
}

inline GLenum glPathGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, const void * fontName, PathFontStyle fontStyle, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::PathGlyphIndexArrayNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale));
}

inline GLenum glPathGlyphIndexRangeNV(GLenum fontTarget, const void * fontName, PathFontStyle fontStyle, GLuint pathParameterTemplate, GLfloat emScale, GLuint_array_2 baseAndCount)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::PathGlyphIndexRangeNV(fontTarget, fontName, fontStyle, pathParameterTemplate, emScale, baseAndCount));
}

inline void glPathGlyphRangeNV(GLuint firstPathName, GLenum fontTarget, const void * fontName, PathFontStyle fontStyle, GLuint firstGlyph, GLsizei numGlyphs, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale)
{
    return glbinding::Binding::PathGlyphRangeNV(firstPathName, fontTarget, fontName, fontStyle, firstGlyph, numGlyphs, handleMissingGlyphs, pathParameterTemplate, emScale);
}

inline void glPathGlyphsNV(GLuint firstPathName, GLenum fontTarget, const void * fontName, PathFontStyle fontStyle, GLsizei numGlyphs, GLenum type, const void * charcodes, GLenum handleMissingGlyphs, GLuint pathParameterTemplate, GLfloat emScale)
{
    return glbinding::Binding::PathGlyphsNV(firstPathName, fontTarget, fontName, fontStyle, numGlyphs, type, charcodes, handleMissingGlyphs, pathParameterTemplate, emScale);
}

inline GLenum glPathMemoryGlyphIndexArrayNV(GLuint firstPathName, GLenum fontTarget, GLsizeiptr fontSize, const void * fontData, GLsizei faceIndex, GLuint firstGlyphIndex, GLsizei numGlyphs, GLuint pathParameterTemplate, GLfloat emScale)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::PathMemoryGlyphIndexArrayNV(firstPathName, fontTarget, fontSize, fontData, faceIndex, firstGlyphIndex, numGlyphs, pathParameterTemplate, emScale));
}

inline void glPathParameterfNV(GLuint path, GLenum pname, GLfloat value)
{
    return glbinding::Binding::PathParameterfNV(path, pname, value);
}

inline void glPathParameterfvNV(GLuint path, GLenum pname, const GLfloat * value)
{
    return glbinding::Binding::PathParameterfvNV(path, pname, value);
}

inline void glPathParameteriNV(GLuint path, GLenum pname, GLint value)
{
    return glbinding::Binding::PathParameteriNV(path, pname, value);
}

inline void glPathParameterivNV(GLuint path, GLenum pname, const GLint * value)
{
    return glbinding::Binding::PathParameterivNV(path, pname, value);
}

inline void glPathStencilDepthOffsetNV(GLfloat factor, GLfloat units)
{
    return glbinding::Binding::PathStencilDepthOffsetNV(factor, units);
}

inline void glPathStencilFuncNV(GLenum func, GLint ref, GLuint mask)
{
    return glbinding::Binding::PathStencilFuncNV(func, ref, mask);
}

inline void glPathStringNV(GLuint path, GLenum format, GLsizei length, const void * pathString)
{
    return glbinding::Binding::PathStringNV(path, format, length, pathString);
}

inline void glPathSubCommandsNV(GLuint path, GLsizei commandStart, GLsizei commandsToDelete, GLsizei numCommands, const GLubyte * commands, GLsizei numCoords, GLenum coordType, const void * coords)
{
    return glbinding::Binding::PathSubCommandsNV(path, commandStart, commandsToDelete, numCommands, commands, numCoords, coordType, coords);
}

inline void glPathSubCoordsNV(GLuint path, GLsizei coordStart, GLsizei numCoords, GLenum coordType, const void * coords)
{
    return glbinding::Binding::PathSubCoordsNV(path, coordStart, numCoords, coordType, coords);
}

inline void glPathTexGenNV(GLenum texCoordSet, GLenum genMode, GLint components, const GLfloat * coeffs)
{
    return glbinding::Binding::PathTexGenNV(texCoordSet, genMode, components, coeffs);
}

inline void glPauseTransformFeedbackNV()
{
    return glbinding::Binding::PauseTransformFeedbackNV();
}

inline void glPixelDataRangeNV(GLenum target, GLsizei length, const void * pointer)
{
    return glbinding::Binding::PixelDataRangeNV(target, length, pointer);
}

inline void glPixelMapx(GLenum map, GLint size, const GLfixed * values)
{
    return glbinding::Binding::PixelMapx(map, size, values);
}

inline void glPixelStorex(GLenum pname, GLfixed param)
{
    return glbinding::Binding::PixelStorex(pname, param);
}

inline void glPixelTexGenParameterfSGIS(GLenum pname, GLfloat param)
{
    return glbinding::Binding::PixelTexGenParameterfSGIS(pname, param);
}

inline void glPixelTexGenParameterfvSGIS(GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::PixelTexGenParameterfvSGIS(pname, params);
}

inline void glPixelTexGenParameteriSGIS(GLenum pname, GLint param)
{
    return glbinding::Binding::PixelTexGenParameteriSGIS(pname, param);
}

inline void glPixelTexGenParameterivSGIS(GLenum pname, const GLint * params)
{
    return glbinding::Binding::PixelTexGenParameterivSGIS(pname, params);
}

inline void glPixelTexGenSGIX(GLenum mode)
{
    return glbinding::Binding::PixelTexGenSGIX(mode);
}

inline void glPixelTransferxOES(GLenum pname, GLfixed param)
{
    return glbinding::Binding::PixelTransferxOES(pname, param);
}

inline void glPixelTransformParameterfEXT(GLenum target, GLenum pname, GLfloat param)
{
    return glbinding::Binding::PixelTransformParameterfEXT(target, pname, param);
}

inline void glPixelTransformParameterfvEXT(GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::PixelTransformParameterfvEXT(target, pname, params);
}

inline void glPixelTransformParameteriEXT(GLenum target, GLenum pname, GLint param)
{
    return glbinding::Binding::PixelTransformParameteriEXT(target, pname, param);
}

inline void glPixelTransformParameterivEXT(GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::PixelTransformParameterivEXT(target, pname, params);
}

inline void glPixelZoomxOES(GLfixed xfactor, GLfixed yfactor)
{
    return glbinding::Binding::PixelZoomxOES(xfactor, yfactor);
}

inline GLboolean glPointAlongPathNV(GLuint path, GLsizei startSegment, GLsizei numSegments, GLfloat distance, GLfloat * x, GLfloat * y, GLfloat * tangentX, GLfloat * tangentY)
{
    return glbinding::Binding::PointAlongPathNV(path, startSegment, numSegments, distance, x, y, tangentX, tangentY);
}

inline void glPointParameterfARB(GLenum pname, GLfloat param)
{
    return glbinding::Binding::PointParameterfARB(pname, param);
}

inline void glPointParameterfEXT(GLenum pname, GLfloat param)
{
    return glbinding::Binding::PointParameterfEXT(pname, param);
}

inline void glPointParameterfSGIS(GLenum pname, GLfloat param)
{
    return glbinding::Binding::PointParameterfSGIS(pname, param);
}

inline void glPointParameterfvARB(GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::PointParameterfvARB(pname, params);
}

inline void glPointParameterfvEXT(GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::PointParameterfvEXT(pname, params);
}

inline void glPointParameterfvSGIS(GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::PointParameterfvSGIS(pname, params);
}

inline void glPointParameteriNV(GLenum pname, GLint param)
{
    return glbinding::Binding::PointParameteriNV(pname, param);
}

inline void glPointParameterivNV(GLenum pname, const GLint * params)
{
    return glbinding::Binding::PointParameterivNV(pname, params);
}

inline void glPointParameterxvOES(GLenum pname, const GLfixed * params)
{
    return glbinding::Binding::PointParameterxvOES(pname, params);
}

inline void glPointSizexOES(GLfixed size)
{
    return glbinding::Binding::PointSizexOES(size);
}

inline GLint glPollAsyncSGIX(GLuint * markerp)
{
    return glbinding::Binding::PollAsyncSGIX(markerp);
}

inline GLint glPollInstrumentsSGIX(GLint * marker_p)
{
    return glbinding::Binding::PollInstrumentsSGIX(marker_p);
}

inline void glPolygonOffsetClampEXT(GLfloat factor, GLfloat units, GLfloat clamp)
{
    return glbinding::Binding::PolygonOffsetClampEXT(factor, units, clamp);
}

inline void glPolygonOffsetEXT(GLfloat factor, GLfloat bias)
{
    return glbinding::Binding::PolygonOffsetEXT(factor, bias);
}

inline void glPolygonOffsetxOES(GLfixed factor, GLfixed units)
{
    return glbinding::Binding::PolygonOffsetxOES(factor, units);
}

inline void glPopDebugGroup()
{
    return glbinding::Binding::PopDebugGroup();
}

inline void glPopGroupMarkerEXT()
{
    return glbinding::Binding::PopGroupMarkerEXT();
}

inline void glPresentFrameDualFillNV(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLenum target1, GLuint fill1, GLenum target2, GLuint fill2, GLenum target3, GLuint fill3)
{
    return glbinding::Binding::PresentFrameDualFillNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, target1, fill1, target2, fill2, target3, fill3);
}

inline void glPresentFrameKeyedNV(GLuint video_slot, GLuint64EXT minPresentTime, GLuint beginPresentTimeId, GLuint presentDurationId, GLenum type, GLenum target0, GLuint fill0, GLuint key0, GLenum target1, GLuint fill1, GLuint key1)
{
    return glbinding::Binding::PresentFrameKeyedNV(video_slot, minPresentTime, beginPresentTimeId, presentDurationId, type, target0, fill0, key0, target1, fill1, key1);
}

inline void glPrimitiveRestartIndexNV(GLuint index)
{
    return glbinding::Binding::PrimitiveRestartIndexNV(index);
}

inline void glPrimitiveRestartNV()
{
    return glbinding::Binding::PrimitiveRestartNV();
}

inline void glPrioritizeTexturesEXT(GLsizei n, const GLuint * textures, const GLclampf * priorities)
{
    return glbinding::Binding::PrioritizeTexturesEXT(n, textures, priorities);
}

inline void glPrioritizeTexturesxOES(GLsizei n, const GLuint * textures, const GLfixed * priorities)
{
    return glbinding::Binding::PrioritizeTexturesxOES(n, textures, priorities);
}

inline void glProgramBufferParametersIivNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLint * params)
{
    return glbinding::Binding::ProgramBufferParametersIivNV(target, bindingIndex, wordIndex, count, params);
}

inline void glProgramBufferParametersIuivNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLuint * params)
{
    return glbinding::Binding::ProgramBufferParametersIuivNV(target, bindingIndex, wordIndex, count, params);
}

inline void glProgramBufferParametersfvNV(GLenum target, GLuint bindingIndex, GLuint wordIndex, GLsizei count, const GLfloat * params)
{
    return glbinding::Binding::ProgramBufferParametersfvNV(target, bindingIndex, wordIndex, count, params);
}

inline void glProgramEnvParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::ProgramEnvParameter4dARB(target, index, x, y, z, w);
}

inline void glProgramEnvParameter4dvARB(GLenum target, GLuint index, const GLdouble * params)
{
    return glbinding::Binding::ProgramEnvParameter4dvARB(target, index, params);
}

inline void glProgramEnvParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::ProgramEnvParameter4fARB(target, index, x, y, z, w);
}

inline void glProgramEnvParameter4fvARB(GLenum target, GLuint index, const GLfloat * params)
{
    return glbinding::Binding::ProgramEnvParameter4fvARB(target, index, params);
}

inline void glProgramEnvParameterI4iNV(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w)
{
    return glbinding::Binding::ProgramEnvParameterI4iNV(target, index, x, y, z, w);
}

inline void glProgramEnvParameterI4ivNV(GLenum target, GLuint index, const GLint * params)
{
    return glbinding::Binding::ProgramEnvParameterI4ivNV(target, index, params);
}

inline void glProgramEnvParameterI4uiNV(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
    return glbinding::Binding::ProgramEnvParameterI4uiNV(target, index, x, y, z, w);
}

inline void glProgramEnvParameterI4uivNV(GLenum target, GLuint index, const GLuint * params)
{
    return glbinding::Binding::ProgramEnvParameterI4uivNV(target, index, params);
}

inline void glProgramEnvParameters4fvEXT(GLenum target, GLuint index, GLsizei count, const GLfloat * params)
{
    return glbinding::Binding::ProgramEnvParameters4fvEXT(target, index, count, params);
}

inline void glProgramEnvParametersI4ivNV(GLenum target, GLuint index, GLsizei count, const GLint * params)
{
    return glbinding::Binding::ProgramEnvParametersI4ivNV(target, index, count, params);
}

inline void glProgramEnvParametersI4uivNV(GLenum target, GLuint index, GLsizei count, const GLuint * params)
{
    return glbinding::Binding::ProgramEnvParametersI4uivNV(target, index, count, params);
}

inline void glProgramLocalParameter4dARB(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::ProgramLocalParameter4dARB(target, index, x, y, z, w);
}

inline void glProgramLocalParameter4dvARB(GLenum target, GLuint index, const GLdouble * params)
{
    return glbinding::Binding::ProgramLocalParameter4dvARB(target, index, params);
}

inline void glProgramLocalParameter4fARB(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::ProgramLocalParameter4fARB(target, index, x, y, z, w);
}

inline void glProgramLocalParameter4fvARB(GLenum target, GLuint index, const GLfloat * params)
{
    return glbinding::Binding::ProgramLocalParameter4fvARB(target, index, params);
}

inline void glProgramLocalParameterI4iNV(GLenum target, GLuint index, GLint x, GLint y, GLint z, GLint w)
{
    return glbinding::Binding::ProgramLocalParameterI4iNV(target, index, x, y, z, w);
}

inline void glProgramLocalParameterI4ivNV(GLenum target, GLuint index, const GLint * params)
{
    return glbinding::Binding::ProgramLocalParameterI4ivNV(target, index, params);
}

inline void glProgramLocalParameterI4uiNV(GLenum target, GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
    return glbinding::Binding::ProgramLocalParameterI4uiNV(target, index, x, y, z, w);
}

inline void glProgramLocalParameterI4uivNV(GLenum target, GLuint index, const GLuint * params)
{
    return glbinding::Binding::ProgramLocalParameterI4uivNV(target, index, params);
}

inline void glProgramLocalParameters4fvEXT(GLenum target, GLuint index, GLsizei count, const GLfloat * params)
{
    return glbinding::Binding::ProgramLocalParameters4fvEXT(target, index, count, params);
}

inline void glProgramLocalParametersI4ivNV(GLenum target, GLuint index, GLsizei count, const GLint * params)
{
    return glbinding::Binding::ProgramLocalParametersI4ivNV(target, index, count, params);
}

inline void glProgramLocalParametersI4uivNV(GLenum target, GLuint index, GLsizei count, const GLuint * params)
{
    return glbinding::Binding::ProgramLocalParametersI4uivNV(target, index, count, params);
}

inline void glProgramNamedParameter4dNV(GLuint id, GLsizei len, const GLubyte * name, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::ProgramNamedParameter4dNV(id, len, name, x, y, z, w);
}

inline void glProgramNamedParameter4dvNV(GLuint id, GLsizei len, const GLubyte * name, const GLdouble * v)
{
    return glbinding::Binding::ProgramNamedParameter4dvNV(id, len, name, v);
}

inline void glProgramNamedParameter4fNV(GLuint id, GLsizei len, const GLubyte * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::ProgramNamedParameter4fNV(id, len, name, x, y, z, w);
}

inline void glProgramNamedParameter4fvNV(GLuint id, GLsizei len, const GLubyte * name, const GLfloat * v)
{
    return glbinding::Binding::ProgramNamedParameter4fvNV(id, len, name, v);
}

inline void glProgramParameter4dNV(GLenum target, GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::ProgramParameter4dNV(target, index, x, y, z, w);
}

inline void glProgramParameter4dvNV(GLenum target, GLuint index, const GLdouble * v)
{
    return glbinding::Binding::ProgramParameter4dvNV(target, index, v);
}

inline void glProgramParameter4fNV(GLenum target, GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::ProgramParameter4fNV(target, index, x, y, z, w);
}

inline void glProgramParameter4fvNV(GLenum target, GLuint index, const GLfloat * v)
{
    return glbinding::Binding::ProgramParameter4fvNV(target, index, v);
}

inline void glProgramParameteriARB(GLuint program, GLenum pname, GLint value)
{
    return glbinding::Binding::ProgramParameteriARB(program, pname, value);
}

inline void glProgramParameteriEXT(GLuint program, GLenum pname, GLint value)
{
    return glbinding::Binding::ProgramParameteriEXT(program, pname, value);
}

inline void glProgramParameters4dvNV(GLenum target, GLuint index, GLsizei count, const GLdouble * v)
{
    return glbinding::Binding::ProgramParameters4dvNV(target, index, count, v);
}

inline void glProgramParameters4fvNV(GLenum target, GLuint index, GLsizei count, const GLfloat * v)
{
    return glbinding::Binding::ProgramParameters4fvNV(target, index, count, v);
}

inline void glProgramPathFragmentInputGenNV(GLuint program, GLint location, GLenum genMode, GLint components, const GLfloat * coeffs)
{
    return glbinding::Binding::ProgramPathFragmentInputGenNV(program, location, genMode, components, coeffs);
}

inline void glProgramStringARB(GLenum target, GLenum format, GLsizei len, const void * string)
{
    return glbinding::Binding::ProgramStringARB(target, format, len, string);
}

inline void glProgramSubroutineParametersuivNV(GLenum target, GLsizei count, const GLuint * params)
{
    return glbinding::Binding::ProgramSubroutineParametersuivNV(target, count, params);
}

inline void glProgramUniform1dEXT(GLuint program, GLint location, GLdouble x)
{
    return glbinding::Binding::ProgramUniform1dEXT(program, location, x);
}

inline void glProgramUniform1dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniform1dvEXT(program, location, count, value);
}

inline void glProgramUniform1fEXT(GLuint program, GLint location, GLfloat v0)
{
    return glbinding::Binding::ProgramUniform1fEXT(program, location, v0);
}

inline void glProgramUniform1fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniform1fvEXT(program, location, count, value);
}

inline void glProgramUniform1i64NV(GLuint program, GLint location, GLint64EXT x)
{
    return glbinding::Binding::ProgramUniform1i64NV(program, location, x);
}

inline void glProgramUniform1i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT * value)
{
    return glbinding::Binding::ProgramUniform1i64vNV(program, location, count, value);
}

inline void glProgramUniform1iEXT(GLuint program, GLint location, GLint v0)
{
    return glbinding::Binding::ProgramUniform1iEXT(program, location, v0);
}

inline void glProgramUniform1ivEXT(GLuint program, GLint location, GLsizei count, const GLint * value)
{
    return glbinding::Binding::ProgramUniform1ivEXT(program, location, count, value);
}

inline void glProgramUniform1ui64NV(GLuint program, GLint location, GLuint64EXT x)
{
    return glbinding::Binding::ProgramUniform1ui64NV(program, location, x);
}

inline void glProgramUniform1ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::ProgramUniform1ui64vNV(program, location, count, value);
}

inline void glProgramUniform1uiEXT(GLuint program, GLint location, GLuint v0)
{
    return glbinding::Binding::ProgramUniform1uiEXT(program, location, v0);
}

inline void glProgramUniform1uivEXT(GLuint program, GLint location, GLsizei count, const GLuint * value)
{
    return glbinding::Binding::ProgramUniform1uivEXT(program, location, count, value);
}

inline void glProgramUniform2dEXT(GLuint program, GLint location, GLdouble x, GLdouble y)
{
    return glbinding::Binding::ProgramUniform2dEXT(program, location, x, y);
}

inline void glProgramUniform2dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniform2dvEXT(program, location, count, value);
}

inline void glProgramUniform2fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1)
{
    return glbinding::Binding::ProgramUniform2fEXT(program, location, v0, v1);
}

inline void glProgramUniform2fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniform2fvEXT(program, location, count, value);
}

inline void glProgramUniform2i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y)
{
    return glbinding::Binding::ProgramUniform2i64NV(program, location, x, y);
}

inline void glProgramUniform2i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT * value)
{
    return glbinding::Binding::ProgramUniform2i64vNV(program, location, count, value);
}

inline void glProgramUniform2iEXT(GLuint program, GLint location, GLint v0, GLint v1)
{
    return glbinding::Binding::ProgramUniform2iEXT(program, location, v0, v1);
}

inline void glProgramUniform2ivEXT(GLuint program, GLint location, GLsizei count, const GLint * value)
{
    return glbinding::Binding::ProgramUniform2ivEXT(program, location, count, value);
}

inline void glProgramUniform2ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y)
{
    return glbinding::Binding::ProgramUniform2ui64NV(program, location, x, y);
}

inline void glProgramUniform2ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::ProgramUniform2ui64vNV(program, location, count, value);
}

inline void glProgramUniform2uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1)
{
    return glbinding::Binding::ProgramUniform2uiEXT(program, location, v0, v1);
}

inline void glProgramUniform2uivEXT(GLuint program, GLint location, GLsizei count, const GLuint * value)
{
    return glbinding::Binding::ProgramUniform2uivEXT(program, location, count, value);
}

inline void glProgramUniform3dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::ProgramUniform3dEXT(program, location, x, y, z);
}

inline void glProgramUniform3dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniform3dvEXT(program, location, count, value);
}

inline void glProgramUniform3fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    return glbinding::Binding::ProgramUniform3fEXT(program, location, v0, v1, v2);
}

inline void glProgramUniform3fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniform3fvEXT(program, location, count, value);
}

inline void glProgramUniform3i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z)
{
    return glbinding::Binding::ProgramUniform3i64NV(program, location, x, y, z);
}

inline void glProgramUniform3i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT * value)
{
    return glbinding::Binding::ProgramUniform3i64vNV(program, location, count, value);
}

inline void glProgramUniform3iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2)
{
    return glbinding::Binding::ProgramUniform3iEXT(program, location, v0, v1, v2);
}

inline void glProgramUniform3ivEXT(GLuint program, GLint location, GLsizei count, const GLint * value)
{
    return glbinding::Binding::ProgramUniform3ivEXT(program, location, count, value);
}

inline void glProgramUniform3ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z)
{
    return glbinding::Binding::ProgramUniform3ui64NV(program, location, x, y, z);
}

inline void glProgramUniform3ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::ProgramUniform3ui64vNV(program, location, count, value);
}

inline void glProgramUniform3uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2)
{
    return glbinding::Binding::ProgramUniform3uiEXT(program, location, v0, v1, v2);
}

inline void glProgramUniform3uivEXT(GLuint program, GLint location, GLsizei count, const GLuint * value)
{
    return glbinding::Binding::ProgramUniform3uivEXT(program, location, count, value);
}

inline void glProgramUniform4dEXT(GLuint program, GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::ProgramUniform4dEXT(program, location, x, y, z, w);
}

inline void glProgramUniform4dvEXT(GLuint program, GLint location, GLsizei count, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniform4dvEXT(program, location, count, value);
}

inline void glProgramUniform4fEXT(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    return glbinding::Binding::ProgramUniform4fEXT(program, location, v0, v1, v2, v3);
}

inline void glProgramUniform4fvEXT(GLuint program, GLint location, GLsizei count, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniform4fvEXT(program, location, count, value);
}

inline void glProgramUniform4i64NV(GLuint program, GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w)
{
    return glbinding::Binding::ProgramUniform4i64NV(program, location, x, y, z, w);
}

inline void glProgramUniform4i64vNV(GLuint program, GLint location, GLsizei count, const GLint64EXT * value)
{
    return glbinding::Binding::ProgramUniform4i64vNV(program, location, count, value);
}

inline void glProgramUniform4iEXT(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    return glbinding::Binding::ProgramUniform4iEXT(program, location, v0, v1, v2, v3);
}

inline void glProgramUniform4ivEXT(GLuint program, GLint location, GLsizei count, const GLint * value)
{
    return glbinding::Binding::ProgramUniform4ivEXT(program, location, count, value);
}

inline void glProgramUniform4ui64NV(GLuint program, GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w)
{
    return glbinding::Binding::ProgramUniform4ui64NV(program, location, x, y, z, w);
}

inline void glProgramUniform4ui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::ProgramUniform4ui64vNV(program, location, count, value);
}

inline void glProgramUniform4uiEXT(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
    return glbinding::Binding::ProgramUniform4uiEXT(program, location, v0, v1, v2, v3);
}

inline void glProgramUniform4uivEXT(GLuint program, GLint location, GLsizei count, const GLuint * value)
{
    return glbinding::Binding::ProgramUniform4uivEXT(program, location, count, value);
}

inline void glProgramUniformHandleui64ARB(GLuint program, GLint location, GLuint64 value)
{
    return glbinding::Binding::ProgramUniformHandleui64ARB(program, location, value);
}

inline void glProgramUniformHandleui64NV(GLuint program, GLint location, GLuint64 value)
{
    return glbinding::Binding::ProgramUniformHandleui64NV(program, location, value);
}

inline void glProgramUniformHandleui64vARB(GLuint program, GLint location, GLsizei count, const GLuint64 * values)
{
    return glbinding::Binding::ProgramUniformHandleui64vARB(program, location, count, values);
}

inline void glProgramUniformHandleui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64 * values)
{
    return glbinding::Binding::ProgramUniformHandleui64vNV(program, location, count, values);
}

inline void glProgramUniformMatrix2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix2dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix2fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix2x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix2x3dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix2x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix2x3fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix2x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix2x4dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix2x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix2x4fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix3dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix3fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix3x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix3x2dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix3x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix3x2fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix3x4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix3x4dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix3x4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix3x4fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix4dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix4dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix4fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix4fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix4x2dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix4x2dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix4x2fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix4x2fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix4x3dvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value)
{
    return glbinding::Binding::ProgramUniformMatrix4x3dvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformMatrix4x3fvEXT(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::ProgramUniformMatrix4x3fvEXT(program, location, count, transpose, value);
}

inline void glProgramUniformui64NV(GLuint program, GLint location, GLuint64EXT value)
{
    return glbinding::Binding::ProgramUniformui64NV(program, location, value);
}

inline void glProgramUniformui64vNV(GLuint program, GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::ProgramUniformui64vNV(program, location, count, value);
}

inline void glProgramVertexLimitNV(GLenum target, GLint limit)
{
    return glbinding::Binding::ProgramVertexLimitNV(target, limit);
}

inline void glProvokingVertexEXT(GLenum mode)
{
    return glbinding::Binding::ProvokingVertexEXT(mode);
}

inline void glPushClientAttribDefaultEXT(ClientAttribMask mask)
{
    return glbinding::Binding::PushClientAttribDefaultEXT(mask);
}

inline void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message)
{
    return glbinding::Binding::PushDebugGroup(source, id, length, message);
}

inline void glPushGroupMarkerEXT(GLsizei length, const GLchar * marker)
{
    return glbinding::Binding::PushGroupMarkerEXT(length, marker);
}

inline GLbitfield glQueryMatrixxOES(GLfixed * mantissa, GLint * exponent)
{
    return static_cast<gl42ext::GLbitfield>(glbinding::Binding::QueryMatrixxOES(mantissa, exponent));
}

inline void glQueryObjectParameteruiAMD(GLenum target, GLuint id, GLenum pname, GLuint param)
{
    return glbinding::Binding::QueryObjectParameteruiAMD(target, id, pname, param);
}

inline void glRasterPos2xOES(GLfixed x, GLfixed y)
{
    return glbinding::Binding::RasterPos2xOES(x, y);
}

inline void glRasterPos2xvOES(const GLfixed * coords)
{
    return glbinding::Binding::RasterPos2xvOES(coords);
}

inline void glRasterPos3xOES(GLfixed x, GLfixed y, GLfixed z)
{
    return glbinding::Binding::RasterPos3xOES(x, y, z);
}

inline void glRasterPos3xvOES(const GLfixed * coords)
{
    return glbinding::Binding::RasterPos3xvOES(coords);
}

inline void glRasterPos4xOES(GLfixed x, GLfixed y, GLfixed z, GLfixed w)
{
    return glbinding::Binding::RasterPos4xOES(x, y, z, w);
}

inline void glRasterPos4xvOES(const GLfixed * coords)
{
    return glbinding::Binding::RasterPos4xvOES(coords);
}

inline void glRasterSamplesEXT(GLuint samples, GLboolean fixedsamplelocations)
{
    return glbinding::Binding::RasterSamplesEXT(samples, fixedsamplelocations);
}

inline void glReadInstrumentsSGIX(GLint marker)
{
    return glbinding::Binding::ReadInstrumentsSGIX(marker);
}

inline void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data)
{
    return glbinding::Binding::ReadnPixels(x, y, width, height, format, type, bufSize, data);
}

inline void glReadnPixelsARB(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data)
{
    return glbinding::Binding::ReadnPixelsARB(x, y, width, height, format, type, bufSize, data);
}

inline void glRectxOES(GLfixed x1, GLfixed y1, GLfixed x2, GLfixed y2)
{
    return glbinding::Binding::RectxOES(x1, y1, x2, y2);
}

inline void glRectxvOES(const GLfixed * v1, const GLfixed * v2)
{
    return glbinding::Binding::RectxvOES(v1, v2);
}

inline void glReferencePlaneSGIX(const GLdouble * equation)
{
    return glbinding::Binding::ReferencePlaneSGIX(equation);
}

inline void glRenderbufferStorageEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::RenderbufferStorageEXT(target, internalformat, width, height);
}

inline void glRenderbufferStorageMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::RenderbufferStorageMultisampleCoverageNV(target, coverageSamples, colorSamples, internalformat, width, height);
}

inline void glRenderbufferStorageMultisampleEXT(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::RenderbufferStorageMultisampleEXT(target, samples, internalformat, width, height);
}

inline void glReplacementCodePointerSUN(GLenum type, GLsizei stride, const void ** pointer)
{
    return glbinding::Binding::ReplacementCodePointerSUN(type, stride, pointer);
}

inline void glReplacementCodeubSUN(GLubyte code)
{
    return glbinding::Binding::ReplacementCodeubSUN(code);
}

inline void glReplacementCodeubvSUN(const GLubyte * code)
{
    return glbinding::Binding::ReplacementCodeubvSUN(code);
}

inline void glReplacementCodeuiColor3fVertex3fSUN(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::ReplacementCodeuiColor3fVertex3fSUN(rc, r, g, b, x, y, z);
}

inline void glReplacementCodeuiColor3fVertex3fvSUN(const GLuint * rc, const GLfloat * c, const GLfloat * v)
{
    return glbinding::Binding::ReplacementCodeuiColor3fVertex3fvSUN(rc, c, v);
}

inline void glReplacementCodeuiColor4fNormal3fVertex3fSUN(GLuint rc, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::ReplacementCodeuiColor4fNormal3fVertex3fSUN(rc, r, g, b, a, nx, ny, nz, x, y, z);
}

inline void glReplacementCodeuiColor4fNormal3fVertex3fvSUN(const GLuint * rc, const GLfloat * c, const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::ReplacementCodeuiColor4fNormal3fVertex3fvSUN(rc, c, n, v);
}

inline void glReplacementCodeuiColor4ubVertex3fSUN(GLuint rc, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::ReplacementCodeuiColor4ubVertex3fSUN(rc, r, g, b, a, x, y, z);
}

inline void glReplacementCodeuiColor4ubVertex3fvSUN(const GLuint * rc, const GLubyte * c, const GLfloat * v)
{
    return glbinding::Binding::ReplacementCodeuiColor4ubVertex3fvSUN(rc, c, v);
}

inline void glReplacementCodeuiNormal3fVertex3fSUN(GLuint rc, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::ReplacementCodeuiNormal3fVertex3fSUN(rc, nx, ny, nz, x, y, z);
}

inline void glReplacementCodeuiNormal3fVertex3fvSUN(const GLuint * rc, const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::ReplacementCodeuiNormal3fVertex3fvSUN(rc, n, v);
}

inline void glReplacementCodeuiSUN(GLuint code)
{
    return glbinding::Binding::ReplacementCodeuiSUN(code);
}

inline void glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN(rc, s, t, r, g, b, a, nx, ny, nz, x, y, z);
}

inline void glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(const GLuint * rc, const GLfloat * tc, const GLfloat * c, const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN(rc, tc, c, n, v);
}

inline void glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::ReplacementCodeuiTexCoord2fNormal3fVertex3fSUN(rc, s, t, nx, ny, nz, x, y, z);
}

inline void glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(const GLuint * rc, const GLfloat * tc, const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::ReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN(rc, tc, n, v);
}

inline void glReplacementCodeuiTexCoord2fVertex3fSUN(GLuint rc, GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::ReplacementCodeuiTexCoord2fVertex3fSUN(rc, s, t, x, y, z);
}

inline void glReplacementCodeuiTexCoord2fVertex3fvSUN(const GLuint * rc, const GLfloat * tc, const GLfloat * v)
{
    return glbinding::Binding::ReplacementCodeuiTexCoord2fVertex3fvSUN(rc, tc, v);
}

inline void glReplacementCodeuiVertex3fSUN(GLuint rc, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::ReplacementCodeuiVertex3fSUN(rc, x, y, z);
}

inline void glReplacementCodeuiVertex3fvSUN(const GLuint * rc, const GLfloat * v)
{
    return glbinding::Binding::ReplacementCodeuiVertex3fvSUN(rc, v);
}

inline void glReplacementCodeuivSUN(const GLuint * code)
{
    return glbinding::Binding::ReplacementCodeuivSUN(code);
}

inline void glReplacementCodeusSUN(GLushort code)
{
    return glbinding::Binding::ReplacementCodeusSUN(code);
}

inline void glReplacementCodeusvSUN(const GLushort * code)
{
    return glbinding::Binding::ReplacementCodeusvSUN(code);
}

inline void glRequestResidentProgramsNV(GLsizei n, const GLuint * programs)
{
    return glbinding::Binding::RequestResidentProgramsNV(n, programs);
}

inline void glResetHistogram(GLenum target)
{
    return glbinding::Binding::ResetHistogram(target);
}

inline void glResetHistogramEXT(GLenum target)
{
    return glbinding::Binding::ResetHistogramEXT(target);
}

inline void glResetMinmax(GLenum target)
{
    return glbinding::Binding::ResetMinmax(target);
}

inline void glResetMinmaxEXT(GLenum target)
{
    return glbinding::Binding::ResetMinmaxEXT(target);
}

inline void glResizeBuffersMESA()
{
    return glbinding::Binding::ResizeBuffersMESA();
}

inline void glResolveDepthValuesNV()
{
    return glbinding::Binding::ResolveDepthValuesNV();
}

inline void glResumeTransformFeedbackNV()
{
    return glbinding::Binding::ResumeTransformFeedbackNV();
}

inline void glRotatexOES(GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
    return glbinding::Binding::RotatexOES(angle, x, y, z);
}

inline void glSampleCoverageARB(GLfloat value, GLboolean invert)
{
    return glbinding::Binding::SampleCoverageARB(value, invert);
}

inline void glSampleCoverageOES(GLfixed value, GLboolean invert)
{
    return glbinding::Binding::SampleCoverageOES(value, invert);
}

inline void glSampleMapATI(GLuint dst, GLuint interp, GLenum swizzle)
{
    return glbinding::Binding::SampleMapATI(dst, interp, swizzle);
}

inline void glSampleMaskEXT(GLclampf value, GLboolean invert)
{
    return glbinding::Binding::SampleMaskEXT(value, invert);
}

inline void glSampleMaskIndexedNV(GLuint index, GLbitfield mask)
{
    return glbinding::Binding::SampleMaskIndexedNV(index, mask);
}

inline void glSampleMaskSGIS(GLclampf value, GLboolean invert)
{
    return glbinding::Binding::SampleMaskSGIS(value, invert);
}

inline void glSamplePatternEXT(GLenum pattern)
{
    return glbinding::Binding::SamplePatternEXT(pattern);
}

inline void glSamplePatternSGIS(GLenum pattern)
{
    return glbinding::Binding::SamplePatternSGIS(pattern);
}

inline void glScalexOES(GLfixed x, GLfixed y, GLfixed z)
{
    return glbinding::Binding::ScalexOES(x, y, z);
}

inline void glSecondaryColor3bEXT(GLbyte red, GLbyte green, GLbyte blue)
{
    return glbinding::Binding::SecondaryColor3bEXT(red, green, blue);
}

inline void glSecondaryColor3bvEXT(const GLbyte * v)
{
    return glbinding::Binding::SecondaryColor3bvEXT(v);
}

inline void glSecondaryColor3dEXT(GLdouble red, GLdouble green, GLdouble blue)
{
    return glbinding::Binding::SecondaryColor3dEXT(red, green, blue);
}

inline void glSecondaryColor3dvEXT(const GLdouble * v)
{
    return glbinding::Binding::SecondaryColor3dvEXT(v);
}

inline void glSecondaryColor3fEXT(GLfloat red, GLfloat green, GLfloat blue)
{
    return glbinding::Binding::SecondaryColor3fEXT(red, green, blue);
}

inline void glSecondaryColor3fvEXT(const GLfloat * v)
{
    return glbinding::Binding::SecondaryColor3fvEXT(v);
}

inline void glSecondaryColor3hNV(GLhalfNV red, GLhalfNV green, GLhalfNV blue)
{
    return glbinding::Binding::SecondaryColor3hNV(red, green, blue);
}

inline void glSecondaryColor3hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::SecondaryColor3hvNV(v);
}

inline void glSecondaryColor3iEXT(GLint red, GLint green, GLint blue)
{
    return glbinding::Binding::SecondaryColor3iEXT(red, green, blue);
}

inline void glSecondaryColor3ivEXT(const GLint * v)
{
    return glbinding::Binding::SecondaryColor3ivEXT(v);
}

inline void glSecondaryColor3sEXT(GLshort red, GLshort green, GLshort blue)
{
    return glbinding::Binding::SecondaryColor3sEXT(red, green, blue);
}

inline void glSecondaryColor3svEXT(const GLshort * v)
{
    return glbinding::Binding::SecondaryColor3svEXT(v);
}

inline void glSecondaryColor3ubEXT(GLubyte red, GLubyte green, GLubyte blue)
{
    return glbinding::Binding::SecondaryColor3ubEXT(red, green, blue);
}

inline void glSecondaryColor3ubvEXT(const GLubyte * v)
{
    return glbinding::Binding::SecondaryColor3ubvEXT(v);
}

inline void glSecondaryColor3uiEXT(GLuint red, GLuint green, GLuint blue)
{
    return glbinding::Binding::SecondaryColor3uiEXT(red, green, blue);
}

inline void glSecondaryColor3uivEXT(const GLuint * v)
{
    return glbinding::Binding::SecondaryColor3uivEXT(v);
}

inline void glSecondaryColor3usEXT(GLushort red, GLushort green, GLushort blue)
{
    return glbinding::Binding::SecondaryColor3usEXT(red, green, blue);
}

inline void glSecondaryColor3usvEXT(const GLushort * v)
{
    return glbinding::Binding::SecondaryColor3usvEXT(v);
}

inline void glSecondaryColorFormatNV(GLint size, GLenum type, GLsizei stride)
{
    return glbinding::Binding::SecondaryColorFormatNV(size, type, stride);
}

inline void glSecondaryColorPointerEXT(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::SecondaryColorPointerEXT(size, type, stride, pointer);
}

inline void glSecondaryColorPointerListIBM(GLint size, GLenum type, GLint stride, const void ** pointer, GLint ptrstride)
{
    return glbinding::Binding::SecondaryColorPointerListIBM(size, type, stride, pointer, ptrstride);
}

inline void glSelectPerfMonitorCountersAMD(GLuint monitor, GLboolean enable, GLuint group, GLint numCounters, GLuint * counterList)
{
    return glbinding::Binding::SelectPerfMonitorCountersAMD(monitor, enable, group, numCounters, counterList);
}

inline void glSeparableFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * row, const void * column)
{
    return glbinding::Binding::SeparableFilter2D(target, internalformat, width, height, format, type, row, column);
}

inline void glSeparableFilter2DEXT(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * row, const void * column)
{
    return glbinding::Binding::SeparableFilter2DEXT(target, internalformat, width, height, format, type, row, column);
}

inline void glSetFenceAPPLE(GLuint fence)
{
    return glbinding::Binding::SetFenceAPPLE(fence);
}

inline void glSetFenceNV(GLuint fence, GLenum condition)
{
    return glbinding::Binding::SetFenceNV(fence, condition);
}

inline void glSetFragmentShaderConstantATI(GLuint dst, const GLfloat * value)
{
    return glbinding::Binding::SetFragmentShaderConstantATI(dst, value);
}

inline void glSetInvariantEXT(GLuint id, GLenum type, const void * addr)
{
    return glbinding::Binding::SetInvariantEXT(id, type, addr);
}

inline void glSetLocalConstantEXT(GLuint id, GLenum type, const void * addr)
{
    return glbinding::Binding::SetLocalConstantEXT(id, type, addr);
}

inline void glSetMultisamplefvAMD(GLenum pname, GLuint index, const GLfloat * val)
{
    return glbinding::Binding::SetMultisamplefvAMD(pname, index, val);
}

inline void glShaderOp1EXT(GLenum op, GLuint res, GLuint arg1)
{
    return glbinding::Binding::ShaderOp1EXT(op, res, arg1);
}

inline void glShaderOp2EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2)
{
    return glbinding::Binding::ShaderOp2EXT(op, res, arg1, arg2);
}

inline void glShaderOp3EXT(GLenum op, GLuint res, GLuint arg1, GLuint arg2, GLuint arg3)
{
    return glbinding::Binding::ShaderOp3EXT(op, res, arg1, arg2, arg3);
}

inline void glShaderSourceARB(GLhandleARB shaderObj, GLsizei count, const GLcharARB ** string, const GLint * length)
{
    return glbinding::Binding::ShaderSourceARB(shaderObj, count, string, length);
}

inline void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding)
{
    return glbinding::Binding::ShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
}

inline void glSharpenTexFuncSGIS(GLenum target, GLsizei n, const GLfloat * points)
{
    return glbinding::Binding::SharpenTexFuncSGIS(target, n, points);
}

inline void glSpriteParameterfSGIX(GLenum pname, GLfloat param)
{
    return glbinding::Binding::SpriteParameterfSGIX(pname, param);
}

inline void glSpriteParameterfvSGIX(GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::SpriteParameterfvSGIX(pname, params);
}

inline void glSpriteParameteriSGIX(GLenum pname, GLint param)
{
    return glbinding::Binding::SpriteParameteriSGIX(pname, param);
}

inline void glSpriteParameterivSGIX(GLenum pname, const GLint * params)
{
    return glbinding::Binding::SpriteParameterivSGIX(pname, params);
}

inline void glStartInstrumentsSGIX()
{
    return glbinding::Binding::StartInstrumentsSGIX();
}

inline void glStencilClearTagEXT(GLsizei stencilTagBits, GLuint stencilClearTag)
{
    return glbinding::Binding::StencilClearTagEXT(stencilTagBits, stencilClearTag);
}

inline void glStencilFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void * paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum transformType, const GLfloat * transformValues)
{
    return glbinding::Binding::StencilFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, transformType, transformValues);
}

inline void glStencilFillPathNV(GLuint path, GLenum fillMode, GLuint mask)
{
    return glbinding::Binding::StencilFillPathNV(path, fillMode, mask);
}

inline void glStencilFuncSeparateATI(GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask)
{
    return glbinding::Binding::StencilFuncSeparateATI(frontfunc, backfunc, ref, mask);
}

inline void glStencilOpSeparateATI(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass)
{
    return glbinding::Binding::StencilOpSeparateATI(face, sfail, dpfail, dppass);
}

inline void glStencilOpValueAMD(GLenum face, GLuint value)
{
    return glbinding::Binding::StencilOpValueAMD(face, value);
}

inline void glStencilStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void * paths, GLuint pathBase, GLint reference, GLuint mask, GLenum transformType, const GLfloat * transformValues)
{
    return glbinding::Binding::StencilStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, transformType, transformValues);
}

inline void glStencilStrokePathNV(GLuint path, GLint reference, GLuint mask)
{
    return glbinding::Binding::StencilStrokePathNV(path, reference, mask);
}

inline void glStencilThenCoverFillPathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void * paths, GLuint pathBase, GLenum fillMode, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat * transformValues)
{
    return glbinding::Binding::StencilThenCoverFillPathInstancedNV(numPaths, pathNameType, paths, pathBase, fillMode, mask, coverMode, transformType, transformValues);
}

inline void glStencilThenCoverFillPathNV(GLuint path, GLenum fillMode, GLuint mask, GLenum coverMode)
{
    return glbinding::Binding::StencilThenCoverFillPathNV(path, fillMode, mask, coverMode);
}

inline void glStencilThenCoverStrokePathInstancedNV(GLsizei numPaths, GLenum pathNameType, const void * paths, GLuint pathBase, GLint reference, GLuint mask, GLenum coverMode, GLenum transformType, const GLfloat * transformValues)
{
    return glbinding::Binding::StencilThenCoverStrokePathInstancedNV(numPaths, pathNameType, paths, pathBase, reference, mask, coverMode, transformType, transformValues);
}

inline void glStencilThenCoverStrokePathNV(GLuint path, GLint reference, GLuint mask, GLenum coverMode)
{
    return glbinding::Binding::StencilThenCoverStrokePathNV(path, reference, mask, coverMode);
}

inline void glStopInstrumentsSGIX(GLint marker)
{
    return glbinding::Binding::StopInstrumentsSGIX(marker);
}

inline void glStringMarkerGREMEDY(GLsizei len, const void * string)
{
    return glbinding::Binding::StringMarkerGREMEDY(len, string);
}

inline void glSubpixelPrecisionBiasNV(GLuint xbits, GLuint ybits)
{
    return glbinding::Binding::SubpixelPrecisionBiasNV(xbits, ybits);
}

inline void glSwizzleEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW)
{
    return glbinding::Binding::SwizzleEXT(res, in, outX, outY, outZ, outW);
}

inline void glSyncTextureINTEL(GLuint texture)
{
    return glbinding::Binding::SyncTextureINTEL(texture);
}

inline void glTagSampleBufferSGIX()
{
    return glbinding::Binding::TagSampleBufferSGIX();
}

inline void glTangent3bEXT(GLbyte tx, GLbyte ty, GLbyte tz)
{
    return glbinding::Binding::Tangent3bEXT(tx, ty, tz);
}

inline void glTangent3bvEXT(const GLbyte * v)
{
    return glbinding::Binding::Tangent3bvEXT(v);
}

inline void glTangent3dEXT(GLdouble tx, GLdouble ty, GLdouble tz)
{
    return glbinding::Binding::Tangent3dEXT(tx, ty, tz);
}

inline void glTangent3dvEXT(const GLdouble * v)
{
    return glbinding::Binding::Tangent3dvEXT(v);
}

inline void glTangent3fEXT(GLfloat tx, GLfloat ty, GLfloat tz)
{
    return glbinding::Binding::Tangent3fEXT(tx, ty, tz);
}

inline void glTangent3fvEXT(const GLfloat * v)
{
    return glbinding::Binding::Tangent3fvEXT(v);
}

inline void glTangent3iEXT(GLint tx, GLint ty, GLint tz)
{
    return glbinding::Binding::Tangent3iEXT(tx, ty, tz);
}

inline void glTangent3ivEXT(const GLint * v)
{
    return glbinding::Binding::Tangent3ivEXT(v);
}

inline void glTangent3sEXT(GLshort tx, GLshort ty, GLshort tz)
{
    return glbinding::Binding::Tangent3sEXT(tx, ty, tz);
}

inline void glTangent3svEXT(const GLshort * v)
{
    return glbinding::Binding::Tangent3svEXT(v);
}

inline void glTangentPointerEXT(GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::TangentPointerEXT(type, stride, pointer);
}

inline void glTbufferMask3DFX(GLuint mask)
{
    return glbinding::Binding::TbufferMask3DFX(mask);
}

inline void glTessellationFactorAMD(GLfloat factor)
{
    return glbinding::Binding::TessellationFactorAMD(factor);
}

inline void glTessellationModeAMD(GLenum mode)
{
    return glbinding::Binding::TessellationModeAMD(mode);
}

inline GLboolean glTestFenceAPPLE(GLuint fence)
{
    return glbinding::Binding::TestFenceAPPLE(fence);
}

inline GLboolean glTestFenceNV(GLuint fence)
{
    return glbinding::Binding::TestFenceNV(fence);
}

inline GLboolean glTestObjectAPPLE(GLenum object, GLuint name)
{
    return glbinding::Binding::TestObjectAPPLE(object, name);
}

inline void glTexBufferARB(GLenum target, GLenum internalformat, GLuint buffer)
{
    return glbinding::Binding::TexBufferARB(target, internalformat, buffer);
}

inline void glTexBufferEXT(GLenum target, GLenum internalformat, GLuint buffer)
{
    return glbinding::Binding::TexBufferEXT(target, internalformat, buffer);
}

inline void glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
    return glbinding::Binding::TexBufferRange(target, internalformat, buffer, offset, size);
}

inline void glTexBumpParameterfvATI(GLenum pname, const GLfloat * param)
{
    return glbinding::Binding::TexBumpParameterfvATI(pname, param);
}

inline void glTexBumpParameterivATI(GLenum pname, const GLint * param)
{
    return glbinding::Binding::TexBumpParameterivATI(pname, param);
}

inline void glTexCoord1bOES(GLbyte s)
{
    return glbinding::Binding::TexCoord1bOES(s);
}

inline void glTexCoord1bvOES(const GLbyte * coords)
{
    return glbinding::Binding::TexCoord1bvOES(coords);
}

inline void glTexCoord1hNV(GLhalfNV s)
{
    return glbinding::Binding::TexCoord1hNV(s);
}

inline void glTexCoord1hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::TexCoord1hvNV(v);
}

inline void glTexCoord1xOES(GLfixed s)
{
    return glbinding::Binding::TexCoord1xOES(s);
}

inline void glTexCoord1xvOES(const GLfixed * coords)
{
    return glbinding::Binding::TexCoord1xvOES(coords);
}

inline void glTexCoord2bOES(GLbyte s, GLbyte t)
{
    return glbinding::Binding::TexCoord2bOES(s, t);
}

inline void glTexCoord2bvOES(const GLbyte * coords)
{
    return glbinding::Binding::TexCoord2bvOES(coords);
}

inline void glTexCoord2fColor3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::TexCoord2fColor3fVertex3fSUN(s, t, r, g, b, x, y, z);
}

inline void glTexCoord2fColor3fVertex3fvSUN(const GLfloat * tc, const GLfloat * c, const GLfloat * v)
{
    return glbinding::Binding::TexCoord2fColor3fVertex3fvSUN(tc, c, v);
}

inline void glTexCoord2fColor4fNormal3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::TexCoord2fColor4fNormal3fVertex3fSUN(s, t, r, g, b, a, nx, ny, nz, x, y, z);
}

inline void glTexCoord2fColor4fNormal3fVertex3fvSUN(const GLfloat * tc, const GLfloat * c, const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::TexCoord2fColor4fNormal3fVertex3fvSUN(tc, c, n, v);
}

inline void glTexCoord2fColor4ubVertex3fSUN(GLfloat s, GLfloat t, GLubyte r, GLubyte g, GLubyte b, GLubyte a, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::TexCoord2fColor4ubVertex3fSUN(s, t, r, g, b, a, x, y, z);
}

inline void glTexCoord2fColor4ubVertex3fvSUN(const GLfloat * tc, const GLubyte * c, const GLfloat * v)
{
    return glbinding::Binding::TexCoord2fColor4ubVertex3fvSUN(tc, c, v);
}

inline void glTexCoord2fNormal3fVertex3fSUN(GLfloat s, GLfloat t, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::TexCoord2fNormal3fVertex3fSUN(s, t, nx, ny, nz, x, y, z);
}

inline void glTexCoord2fNormal3fVertex3fvSUN(const GLfloat * tc, const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::TexCoord2fNormal3fVertex3fvSUN(tc, n, v);
}

inline void glTexCoord2fVertex3fSUN(GLfloat s, GLfloat t, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::TexCoord2fVertex3fSUN(s, t, x, y, z);
}

inline void glTexCoord2fVertex3fvSUN(const GLfloat * tc, const GLfloat * v)
{
    return glbinding::Binding::TexCoord2fVertex3fvSUN(tc, v);
}

inline void glTexCoord2hNV(GLhalfNV s, GLhalfNV t)
{
    return glbinding::Binding::TexCoord2hNV(s, t);
}

inline void glTexCoord2hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::TexCoord2hvNV(v);
}

inline void glTexCoord2xOES(GLfixed s, GLfixed t)
{
    return glbinding::Binding::TexCoord2xOES(s, t);
}

inline void glTexCoord2xvOES(const GLfixed * coords)
{
    return glbinding::Binding::TexCoord2xvOES(coords);
}

inline void glTexCoord3bOES(GLbyte s, GLbyte t, GLbyte r)
{
    return glbinding::Binding::TexCoord3bOES(s, t, r);
}

inline void glTexCoord3bvOES(const GLbyte * coords)
{
    return glbinding::Binding::TexCoord3bvOES(coords);
}

inline void glTexCoord3hNV(GLhalfNV s, GLhalfNV t, GLhalfNV r)
{
    return glbinding::Binding::TexCoord3hNV(s, t, r);
}

inline void glTexCoord3hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::TexCoord3hvNV(v);
}

inline void glTexCoord3xOES(GLfixed s, GLfixed t, GLfixed r)
{
    return glbinding::Binding::TexCoord3xOES(s, t, r);
}

inline void glTexCoord3xvOES(const GLfixed * coords)
{
    return glbinding::Binding::TexCoord3xvOES(coords);
}

inline void glTexCoord4bOES(GLbyte s, GLbyte t, GLbyte r, GLbyte q)
{
    return glbinding::Binding::TexCoord4bOES(s, t, r, q);
}

inline void glTexCoord4bvOES(const GLbyte * coords)
{
    return glbinding::Binding::TexCoord4bvOES(coords);
}

inline void glTexCoord4fColor4fNormal3fVertex4fSUN(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat nx, GLfloat ny, GLfloat nz, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::TexCoord4fColor4fNormal3fVertex4fSUN(s, t, p, q, r, g, b, a, nx, ny, nz, x, y, z, w);
}

inline void glTexCoord4fColor4fNormal3fVertex4fvSUN(const GLfloat * tc, const GLfloat * c, const GLfloat * n, const GLfloat * v)
{
    return glbinding::Binding::TexCoord4fColor4fNormal3fVertex4fvSUN(tc, c, n, v);
}

inline void glTexCoord4fVertex4fSUN(GLfloat s, GLfloat t, GLfloat p, GLfloat q, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::TexCoord4fVertex4fSUN(s, t, p, q, x, y, z, w);
}

inline void glTexCoord4fVertex4fvSUN(const GLfloat * tc, const GLfloat * v)
{
    return glbinding::Binding::TexCoord4fVertex4fvSUN(tc, v);
}

inline void glTexCoord4hNV(GLhalfNV s, GLhalfNV t, GLhalfNV r, GLhalfNV q)
{
    return glbinding::Binding::TexCoord4hNV(s, t, r, q);
}

inline void glTexCoord4hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::TexCoord4hvNV(v);
}

inline void glTexCoord4xOES(GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
    return glbinding::Binding::TexCoord4xOES(s, t, r, q);
}

inline void glTexCoord4xvOES(const GLfixed * coords)
{
    return glbinding::Binding::TexCoord4xvOES(coords);
}

inline void glTexCoordFormatNV(GLint size, GLenum type, GLsizei stride)
{
    return glbinding::Binding::TexCoordFormatNV(size, type, stride);
}

inline void glTexCoordPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer)
{
    return glbinding::Binding::TexCoordPointerEXT(size, type, stride, count, pointer);
}

inline void glTexCoordPointerListIBM(GLint size, GLenum type, GLint stride, const void ** pointer, GLint ptrstride)
{
    return glbinding::Binding::TexCoordPointerListIBM(size, type, stride, pointer, ptrstride);
}

inline void glTexCoordPointervINTEL(GLint size, GLenum type, const void ** pointer)
{
    return glbinding::Binding::TexCoordPointervINTEL(size, type, pointer);
}

inline void glTexEnvxOES(GLenum target, GLenum pname, GLfixed param)
{
    return glbinding::Binding::TexEnvxOES(target, pname, param);
}

inline void glTexEnvxvOES(GLenum target, GLenum pname, const GLfixed * params)
{
    return glbinding::Binding::TexEnvxvOES(target, pname, params);
}

inline void glTexFilterFuncSGIS(GLenum target, GLenum filter, GLsizei n, const GLfloat * weights)
{
    return glbinding::Binding::TexFilterFuncSGIS(target, filter, n, weights);
}

inline void glTexGenxOES(GLenum coord, GLenum pname, GLfixed param)
{
    return glbinding::Binding::TexGenxOES(coord, pname, param);
}

inline void glTexGenxvOES(GLenum coord, GLenum pname, const GLfixed * params)
{
    return glbinding::Binding::TexGenxvOES(coord, pname, params);
}

inline void glTexImage2DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
    return glbinding::Binding::TexImage2DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations);
}

inline void glTexImage3DEXT(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TexImage3DEXT(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

inline void glTexImage3DMultisampleCoverageNV(GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
    return glbinding::Binding::TexImage3DMultisampleCoverageNV(target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations);
}

inline void glTexImage4DSGIS(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TexImage4DSGIS(target, level, internalformat, width, height, depth, size4d, border, format, type, pixels);
}

inline void glTexPageCommitmentARB(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean resident)
{
    return glbinding::Binding::TexPageCommitmentARB(target, level, xoffset, yoffset, zoffset, width, height, depth, resident);
}

inline void glTexParameterIivEXT(GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::TexParameterIivEXT(target, pname, params);
}

inline void glTexParameterIuivEXT(GLenum target, GLenum pname, const GLuint * params)
{
    return glbinding::Binding::TexParameterIuivEXT(target, pname, params);
}

inline void glTexParameterxOES(GLenum target, GLenum pname, GLfixed param)
{
    return glbinding::Binding::TexParameterxOES(target, pname, param);
}

inline void glTexParameterxvOES(GLenum target, GLenum pname, const GLfixed * params)
{
    return glbinding::Binding::TexParameterxvOES(target, pname, params);
}

inline void glTexRenderbufferNV(GLenum target, GLuint renderbuffer)
{
    return glbinding::Binding::TexRenderbufferNV(target, renderbuffer);
}

inline void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
    return glbinding::Binding::TexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

inline void glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
    return glbinding::Binding::TexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

inline void glTexStorageSparseAMD(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, TextureStorageMaskAMD flags)
{
    return glbinding::Binding::TexStorageSparseAMD(target, internalFormat, width, height, depth, layers, flags);
}

inline void glTexSubImage1DEXT(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TexSubImage1DEXT(target, level, xoffset, width, format, type, pixels);
}

inline void glTexSubImage2DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TexSubImage2DEXT(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void glTexSubImage3DEXT(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TexSubImage3DEXT(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

inline void glTexSubImage4DSGIS(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint woffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei size4d, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TexSubImage4DSGIS(target, level, xoffset, yoffset, zoffset, woffset, width, height, depth, size4d, format, type, pixels);
}

inline void glTextureBarrier()
{
    return glbinding::Binding::TextureBarrier();
}

inline void glTextureBarrierNV()
{
    return glbinding::Binding::TextureBarrierNV();
}

inline void glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer)
{
    return glbinding::Binding::TextureBuffer(texture, internalformat, buffer);
}

inline void glTextureBufferEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer)
{
    return glbinding::Binding::TextureBufferEXT(texture, target, internalformat, buffer);
}

inline void glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizei size)
{
    return glbinding::Binding::TextureBufferRange(texture, internalformat, buffer, offset, size);
}

inline void glTextureBufferRangeEXT(GLuint texture, GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size)
{
    return glbinding::Binding::TextureBufferRangeEXT(texture, target, internalformat, buffer, offset, size);
}

inline void glTextureColorMaskSGIS(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    return glbinding::Binding::TextureColorMaskSGIS(red, green, blue, alpha);
}

inline void glTextureImage1DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureImage1DEXT(texture, target, level, internalformat, width, border, format, type, pixels);
}

inline void glTextureImage2DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureImage2DEXT(texture, target, level, internalformat, width, height, border, format, type, pixels);
}

inline void glTextureImage2DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
    return glbinding::Binding::TextureImage2DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, fixedSampleLocations);
}

inline void glTextureImage2DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
    return glbinding::Binding::TextureImage2DMultisampleNV(texture, target, samples, internalFormat, width, height, fixedSampleLocations);
}

inline void glTextureImage3DEXT(GLuint texture, GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureImage3DEXT(texture, target, level, internalformat, width, height, depth, border, format, type, pixels);
}

inline void glTextureImage3DMultisampleCoverageNV(GLuint texture, GLenum target, GLsizei coverageSamples, GLsizei colorSamples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
    return glbinding::Binding::TextureImage3DMultisampleCoverageNV(texture, target, coverageSamples, colorSamples, internalFormat, width, height, depth, fixedSampleLocations);
}

inline void glTextureImage3DMultisampleNV(GLuint texture, GLenum target, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
    return glbinding::Binding::TextureImage3DMultisampleNV(texture, target, samples, internalFormat, width, height, depth, fixedSampleLocations);
}

inline void glTextureLightEXT(GLenum pname)
{
    return glbinding::Binding::TextureLightEXT(pname);
}

inline void glTextureMaterialEXT(GLenum face, GLenum mode)
{
    return glbinding::Binding::TextureMaterialEXT(face, mode);
}

inline void glTextureNormalEXT(GLenum mode)
{
    return glbinding::Binding::TextureNormalEXT(mode);
}

inline void glTexturePageCommitmentEXT(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLboolean resident)
{
    return glbinding::Binding::TexturePageCommitmentEXT(texture, level, xoffset, yoffset, zoffset, width, height, depth, resident);
}

inline void glTextureParameterIiv(GLuint texture, GLenum pname, const GLint * params)
{
    return glbinding::Binding::TextureParameterIiv(texture, pname, params);
}

inline void glTextureParameterIivEXT(GLuint texture, GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::TextureParameterIivEXT(texture, target, pname, params);
}

inline void glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params)
{
    return glbinding::Binding::TextureParameterIuiv(texture, pname, params);
}

inline void glTextureParameterIuivEXT(GLuint texture, GLenum target, GLenum pname, const GLuint * params)
{
    return glbinding::Binding::TextureParameterIuivEXT(texture, target, pname, params);
}

inline void glTextureParameterf(GLuint texture, GLenum pname, GLfloat param)
{
    return glbinding::Binding::TextureParameterf(texture, pname, param);
}

inline void glTextureParameterfEXT(GLuint texture, GLenum target, GLenum pname, GLfloat param)
{
    return glbinding::Binding::TextureParameterfEXT(texture, target, pname, param);
}

inline void glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param)
{
    return glbinding::Binding::TextureParameterfv(texture, pname, param);
}

inline void glTextureParameterfvEXT(GLuint texture, GLenum target, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::TextureParameterfvEXT(texture, target, pname, params);
}

inline void glTextureParameteri(GLuint texture, GLenum pname, GLint param)
{
    return glbinding::Binding::TextureParameteri(texture, pname, param);
}

inline void glTextureParameteriEXT(GLuint texture, GLenum target, GLenum pname, GLint param)
{
    return glbinding::Binding::TextureParameteriEXT(texture, target, pname, param);
}

inline void glTextureParameteriv(GLuint texture, GLenum pname, const GLint * param)
{
    return glbinding::Binding::TextureParameteriv(texture, pname, param);
}

inline void glTextureParameterivEXT(GLuint texture, GLenum target, GLenum pname, const GLint * params)
{
    return glbinding::Binding::TextureParameterivEXT(texture, target, pname, params);
}

inline void glTextureRangeAPPLE(GLenum target, GLsizei length, const void * pointer)
{
    return glbinding::Binding::TextureRangeAPPLE(target, length, pointer);
}

inline void glTextureRenderbufferEXT(GLuint texture, GLenum target, GLuint renderbuffer)
{
    return glbinding::Binding::TextureRenderbufferEXT(texture, target, renderbuffer);
}

inline void glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width)
{
    return glbinding::Binding::TextureStorage1D(texture, levels, internalformat, width);
}

inline void glTextureStorage1DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width)
{
    return glbinding::Binding::TextureStorage1DEXT(texture, target, levels, internalformat, width);
}

inline void glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::TextureStorage2D(texture, levels, internalformat, width, height);
}

inline void glTextureStorage2DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
    return glbinding::Binding::TextureStorage2DEXT(texture, target, levels, internalformat, width, height);
}

inline void glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
    return glbinding::Binding::TextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
}

inline void glTextureStorage2DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
{
    return glbinding::Binding::TextureStorage2DMultisampleEXT(texture, target, samples, internalformat, width, height, fixedsamplelocations);
}

inline void glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
    return glbinding::Binding::TextureStorage3D(texture, levels, internalformat, width, height, depth);
}

inline void glTextureStorage3DEXT(GLuint texture, GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth)
{
    return glbinding::Binding::TextureStorage3DEXT(texture, target, levels, internalformat, width, height, depth);
}

inline void glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
    return glbinding::Binding::TextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
}

inline void glTextureStorage3DMultisampleEXT(GLuint texture, GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
{
    return glbinding::Binding::TextureStorage3DMultisampleEXT(texture, target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

inline void glTextureStorageSparseAMD(GLuint texture, GLenum target, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLsizei layers, TextureStorageMaskAMD flags)
{
    return glbinding::Binding::TextureStorageSparseAMD(texture, target, internalFormat, width, height, depth, layers, flags);
}

inline void glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
}

inline void glTextureSubImage1DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureSubImage1DEXT(texture, target, level, xoffset, width, format, type, pixels);
}

inline void glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void glTextureSubImage2DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

inline void glTextureSubImage3DEXT(GLuint texture, GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels)
{
    return glbinding::Binding::TextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

inline void glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers)
{
    return glbinding::Binding::TextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
}

inline void glTrackMatrixNV(GLenum target, GLuint address, GLenum matrix, GLenum transform)
{
    return glbinding::Binding::TrackMatrixNV(target, address, matrix, transform);
}

inline void glTransformFeedbackAttribsNV(GLsizei count, const GLint * attribs, GLenum bufferMode)
{
    return glbinding::Binding::TransformFeedbackAttribsNV(count, attribs, bufferMode);
}

inline void glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer)
{
    return glbinding::Binding::TransformFeedbackBufferBase(xfb, index, buffer);
}

inline void glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizei size)
{
    return glbinding::Binding::TransformFeedbackBufferRange(xfb, index, buffer, offset, size);
}

inline void glTransformFeedbackStreamAttribsNV(GLsizei count, const GLint * attribs, GLsizei nbuffers, const GLint * bufstreams, GLenum bufferMode)
{
    return glbinding::Binding::TransformFeedbackStreamAttribsNV(count, attribs, nbuffers, bufstreams, bufferMode);
}

inline void glTransformFeedbackVaryingsEXT(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode)
{
    return glbinding::Binding::TransformFeedbackVaryingsEXT(program, count, varyings, bufferMode);
}

inline void glTransformFeedbackVaryingsNV(GLuint program, GLsizei count, const GLint * locations, GLenum bufferMode)
{
    return glbinding::Binding::TransformFeedbackVaryingsNV(program, count, locations, bufferMode);
}

inline void glTransformPathNV(GLuint resultPath, GLuint srcPath, GLenum transformType, const GLfloat * transformValues)
{
    return glbinding::Binding::TransformPathNV(resultPath, srcPath, transformType, transformValues);
}

inline void glTranslatexOES(GLfixed x, GLfixed y, GLfixed z)
{
    return glbinding::Binding::TranslatexOES(x, y, z);
}

inline void glUniform1fARB(GLint location, GLfloat v0)
{
    return glbinding::Binding::Uniform1fARB(location, v0);
}

inline void glUniform1fvARB(GLint location, GLsizei count, const GLfloat * value)
{
    return glbinding::Binding::Uniform1fvARB(location, count, value);
}

inline void glUniform1i64NV(GLint location, GLint64EXT x)
{
    return glbinding::Binding::Uniform1i64NV(location, x);
}

inline void glUniform1i64vNV(GLint location, GLsizei count, const GLint64EXT * value)
{
    return glbinding::Binding::Uniform1i64vNV(location, count, value);
}

inline void glUniform1iARB(GLint location, GLint v0)
{
    return glbinding::Binding::Uniform1iARB(location, v0);
}

inline void glUniform1ivARB(GLint location, GLsizei count, const GLint * value)
{
    return glbinding::Binding::Uniform1ivARB(location, count, value);
}

inline void glUniform1ui64NV(GLint location, GLuint64EXT x)
{
    return glbinding::Binding::Uniform1ui64NV(location, x);
}

inline void glUniform1ui64vNV(GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::Uniform1ui64vNV(location, count, value);
}

inline void glUniform1uiEXT(GLint location, GLuint v0)
{
    return glbinding::Binding::Uniform1uiEXT(location, v0);
}

inline void glUniform1uivEXT(GLint location, GLsizei count, const GLuint * value)
{
    return glbinding::Binding::Uniform1uivEXT(location, count, value);
}

inline void glUniform2fARB(GLint location, GLfloat v0, GLfloat v1)
{
    return glbinding::Binding::Uniform2fARB(location, v0, v1);
}

inline void glUniform2fvARB(GLint location, GLsizei count, const GLfloat * value)
{
    return glbinding::Binding::Uniform2fvARB(location, count, value);
}

inline void glUniform2i64NV(GLint location, GLint64EXT x, GLint64EXT y)
{
    return glbinding::Binding::Uniform2i64NV(location, x, y);
}

inline void glUniform2i64vNV(GLint location, GLsizei count, const GLint64EXT * value)
{
    return glbinding::Binding::Uniform2i64vNV(location, count, value);
}

inline void glUniform2iARB(GLint location, GLint v0, GLint v1)
{
    return glbinding::Binding::Uniform2iARB(location, v0, v1);
}

inline void glUniform2ivARB(GLint location, GLsizei count, const GLint * value)
{
    return glbinding::Binding::Uniform2ivARB(location, count, value);
}

inline void glUniform2ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y)
{
    return glbinding::Binding::Uniform2ui64NV(location, x, y);
}

inline void glUniform2ui64vNV(GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::Uniform2ui64vNV(location, count, value);
}

inline void glUniform2uiEXT(GLint location, GLuint v0, GLuint v1)
{
    return glbinding::Binding::Uniform2uiEXT(location, v0, v1);
}

inline void glUniform2uivEXT(GLint location, GLsizei count, const GLuint * value)
{
    return glbinding::Binding::Uniform2uivEXT(location, count, value);
}

inline void glUniform3fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    return glbinding::Binding::Uniform3fARB(location, v0, v1, v2);
}

inline void glUniform3fvARB(GLint location, GLsizei count, const GLfloat * value)
{
    return glbinding::Binding::Uniform3fvARB(location, count, value);
}

inline void glUniform3i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z)
{
    return glbinding::Binding::Uniform3i64NV(location, x, y, z);
}

inline void glUniform3i64vNV(GLint location, GLsizei count, const GLint64EXT * value)
{
    return glbinding::Binding::Uniform3i64vNV(location, count, value);
}

inline void glUniform3iARB(GLint location, GLint v0, GLint v1, GLint v2)
{
    return glbinding::Binding::Uniform3iARB(location, v0, v1, v2);
}

inline void glUniform3ivARB(GLint location, GLsizei count, const GLint * value)
{
    return glbinding::Binding::Uniform3ivARB(location, count, value);
}

inline void glUniform3ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z)
{
    return glbinding::Binding::Uniform3ui64NV(location, x, y, z);
}

inline void glUniform3ui64vNV(GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::Uniform3ui64vNV(location, count, value);
}

inline void glUniform3uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2)
{
    return glbinding::Binding::Uniform3uiEXT(location, v0, v1, v2);
}

inline void glUniform3uivEXT(GLint location, GLsizei count, const GLuint * value)
{
    return glbinding::Binding::Uniform3uivEXT(location, count, value);
}

inline void glUniform4fARB(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    return glbinding::Binding::Uniform4fARB(location, v0, v1, v2, v3);
}

inline void glUniform4fvARB(GLint location, GLsizei count, const GLfloat * value)
{
    return glbinding::Binding::Uniform4fvARB(location, count, value);
}

inline void glUniform4i64NV(GLint location, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w)
{
    return glbinding::Binding::Uniform4i64NV(location, x, y, z, w);
}

inline void glUniform4i64vNV(GLint location, GLsizei count, const GLint64EXT * value)
{
    return glbinding::Binding::Uniform4i64vNV(location, count, value);
}

inline void glUniform4iARB(GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    return glbinding::Binding::Uniform4iARB(location, v0, v1, v2, v3);
}

inline void glUniform4ivARB(GLint location, GLsizei count, const GLint * value)
{
    return glbinding::Binding::Uniform4ivARB(location, count, value);
}

inline void glUniform4ui64NV(GLint location, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w)
{
    return glbinding::Binding::Uniform4ui64NV(location, x, y, z, w);
}

inline void glUniform4ui64vNV(GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::Uniform4ui64vNV(location, count, value);
}

inline void glUniform4uiEXT(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
    return glbinding::Binding::Uniform4uiEXT(location, v0, v1, v2, v3);
}

inline void glUniform4uivEXT(GLint location, GLsizei count, const GLuint * value)
{
    return glbinding::Binding::Uniform4uivEXT(location, count, value);
}

inline void glUniformBufferEXT(GLuint program, GLint location, GLuint buffer)
{
    return glbinding::Binding::UniformBufferEXT(program, location, buffer);
}

inline void glUniformHandleui64ARB(GLint location, GLuint64 value)
{
    return glbinding::Binding::UniformHandleui64ARB(location, value);
}

inline void glUniformHandleui64NV(GLint location, GLuint64 value)
{
    return glbinding::Binding::UniformHandleui64NV(location, value);
}

inline void glUniformHandleui64vARB(GLint location, GLsizei count, const GLuint64 * value)
{
    return glbinding::Binding::UniformHandleui64vARB(location, count, value);
}

inline void glUniformHandleui64vNV(GLint location, GLsizei count, const GLuint64 * value)
{
    return glbinding::Binding::UniformHandleui64vNV(location, count, value);
}

inline void glUniformMatrix2fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::UniformMatrix2fvARB(location, count, transpose, value);
}

inline void glUniformMatrix3fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::UniformMatrix3fvARB(location, count, transpose, value);
}

inline void glUniformMatrix4fvARB(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value)
{
    return glbinding::Binding::UniformMatrix4fvARB(location, count, transpose, value);
}

inline void glUniformui64NV(GLint location, GLuint64EXT value)
{
    return glbinding::Binding::Uniformui64NV(location, value);
}

inline void glUniformui64vNV(GLint location, GLsizei count, const GLuint64EXT * value)
{
    return glbinding::Binding::Uniformui64vNV(location, count, value);
}

inline void glUnlockArraysEXT()
{
    return glbinding::Binding::UnlockArraysEXT();
}

inline GLboolean glUnmapBufferARB(GLenum target)
{
    return glbinding::Binding::UnmapBufferARB(target);
}

inline GLboolean glUnmapNamedBuffer(GLuint buffer)
{
    return glbinding::Binding::UnmapNamedBuffer(buffer);
}

inline GLboolean glUnmapNamedBufferEXT(GLuint buffer)
{
    return glbinding::Binding::UnmapNamedBufferEXT(buffer);
}

inline void glUnmapObjectBufferATI(GLuint buffer)
{
    return glbinding::Binding::UnmapObjectBufferATI(buffer);
}

inline void glUnmapTexture2DINTEL(GLuint texture, GLint level)
{
    return glbinding::Binding::UnmapTexture2DINTEL(texture, level);
}

inline void glUpdateObjectBufferATI(GLuint buffer, GLuint offset, GLsizei size, const void * pointer, GLenum preserve)
{
    return glbinding::Binding::UpdateObjectBufferATI(buffer, offset, size, pointer, preserve);
}

inline void glUseProgramObjectARB(GLhandleARB programObj)
{
    return glbinding::Binding::UseProgramObjectARB(programObj);
}

inline void glUseShaderProgramEXT(GLenum type, GLuint program)
{
    return glbinding::Binding::UseShaderProgramEXT(type, program);
}

inline void glVDPAUFiniNV()
{
    return glbinding::Binding::VDPAUFiniNV();
}

inline void glVDPAUGetSurfaceivNV(GLvdpauSurfaceNV surface, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values)
{
    return glbinding::Binding::VDPAUGetSurfaceivNV(surface, pname, bufSize, length, values);
}

inline void glVDPAUInitNV(const void * vdpDevice, const void * getProcAddress)
{
    return glbinding::Binding::VDPAUInitNV(vdpDevice, getProcAddress);
}

inline GLboolean glVDPAUIsSurfaceNV(GLvdpauSurfaceNV surface)
{
    return glbinding::Binding::VDPAUIsSurfaceNV(surface);
}

inline void glVDPAUMapSurfacesNV(GLsizei numSurfaces, const GLvdpauSurfaceNV * surfaces)
{
    return glbinding::Binding::VDPAUMapSurfacesNV(numSurfaces, surfaces);
}

inline GLvdpauSurfaceNV glVDPAURegisterOutputSurfaceNV(const void * vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint * textureNames)
{
    return glbinding::Binding::VDPAURegisterOutputSurfaceNV(vdpSurface, target, numTextureNames, textureNames);
}

inline GLvdpauSurfaceNV glVDPAURegisterVideoSurfaceNV(const void * vdpSurface, GLenum target, GLsizei numTextureNames, const GLuint * textureNames)
{
    return glbinding::Binding::VDPAURegisterVideoSurfaceNV(vdpSurface, target, numTextureNames, textureNames);
}

inline void glVDPAUSurfaceAccessNV(GLvdpauSurfaceNV surface, GLenum access)
{
    return glbinding::Binding::VDPAUSurfaceAccessNV(surface, access);
}

inline void glVDPAUUnmapSurfacesNV(GLsizei numSurface, const GLvdpauSurfaceNV * surfaces)
{
    return glbinding::Binding::VDPAUUnmapSurfacesNV(numSurface, surfaces);
}

inline void glVDPAUUnregisterSurfaceNV(GLvdpauSurfaceNV surface)
{
    return glbinding::Binding::VDPAUUnregisterSurfaceNV(surface);
}

inline void glValidateProgramARB(GLhandleARB programObj)
{
    return glbinding::Binding::ValidateProgramARB(programObj);
}

inline void glVariantArrayObjectATI(GLuint id, GLenum type, GLsizei stride, GLuint buffer, GLuint offset)
{
    return glbinding::Binding::VariantArrayObjectATI(id, type, stride, buffer, offset);
}

inline void glVariantPointerEXT(GLuint id, GLenum type, GLuint stride, const void * addr)
{
    return glbinding::Binding::VariantPointerEXT(id, type, stride, addr);
}

inline void glVariantbvEXT(GLuint id, const GLbyte * addr)
{
    return glbinding::Binding::VariantbvEXT(id, addr);
}

inline void glVariantdvEXT(GLuint id, const GLdouble * addr)
{
    return glbinding::Binding::VariantdvEXT(id, addr);
}

inline void glVariantfvEXT(GLuint id, const GLfloat * addr)
{
    return glbinding::Binding::VariantfvEXT(id, addr);
}

inline void glVariantivEXT(GLuint id, const GLint * addr)
{
    return glbinding::Binding::VariantivEXT(id, addr);
}

inline void glVariantsvEXT(GLuint id, const GLshort * addr)
{
    return glbinding::Binding::VariantsvEXT(id, addr);
}

inline void glVariantubvEXT(GLuint id, const GLubyte * addr)
{
    return glbinding::Binding::VariantubvEXT(id, addr);
}

inline void glVariantuivEXT(GLuint id, const GLuint * addr)
{
    return glbinding::Binding::VariantuivEXT(id, addr);
}

inline void glVariantusvEXT(GLuint id, const GLushort * addr)
{
    return glbinding::Binding::VariantusvEXT(id, addr);
}

inline void glVertex2bOES(GLbyte x, GLbyte y)
{
    return glbinding::Binding::Vertex2bOES(x, y);
}

inline void glVertex2bvOES(const GLbyte * coords)
{
    return glbinding::Binding::Vertex2bvOES(coords);
}

inline void glVertex2hNV(GLhalfNV x, GLhalfNV y)
{
    return glbinding::Binding::Vertex2hNV(x, y);
}

inline void glVertex2hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::Vertex2hvNV(v);
}

inline void glVertex2xOES(GLfixed x)
{
    return glbinding::Binding::Vertex2xOES(x);
}

inline void glVertex2xvOES(const GLfixed * coords)
{
    return glbinding::Binding::Vertex2xvOES(coords);
}

inline void glVertex3bOES(GLbyte x, GLbyte y, GLbyte z)
{
    return glbinding::Binding::Vertex3bOES(x, y, z);
}

inline void glVertex3bvOES(const GLbyte * coords)
{
    return glbinding::Binding::Vertex3bvOES(coords);
}

inline void glVertex3hNV(GLhalfNV x, GLhalfNV y, GLhalfNV z)
{
    return glbinding::Binding::Vertex3hNV(x, y, z);
}

inline void glVertex3hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::Vertex3hvNV(v);
}

inline void glVertex3xOES(GLfixed x, GLfixed y)
{
    return glbinding::Binding::Vertex3xOES(x, y);
}

inline void glVertex3xvOES(const GLfixed * coords)
{
    return glbinding::Binding::Vertex3xvOES(coords);
}

inline void glVertex4bOES(GLbyte x, GLbyte y, GLbyte z, GLbyte w)
{
    return glbinding::Binding::Vertex4bOES(x, y, z, w);
}

inline void glVertex4bvOES(const GLbyte * coords)
{
    return glbinding::Binding::Vertex4bvOES(coords);
}

inline void glVertex4hNV(GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w)
{
    return glbinding::Binding::Vertex4hNV(x, y, z, w);
}

inline void glVertex4hvNV(const GLhalfNV * v)
{
    return glbinding::Binding::Vertex4hvNV(v);
}

inline void glVertex4xOES(GLfixed x, GLfixed y, GLfixed z)
{
    return glbinding::Binding::Vertex4xOES(x, y, z);
}

inline void glVertex4xvOES(const GLfixed * coords)
{
    return glbinding::Binding::Vertex4xvOES(coords);
}

inline void glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
{
    return glbinding::Binding::VertexArrayAttribBinding(vaobj, attribindex, bindingindex);
}

inline void glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
    return glbinding::Binding::VertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
}

inline void glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
    return glbinding::Binding::VertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
}

inline void glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
    return glbinding::Binding::VertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
}

inline void glVertexArrayBindVertexBufferEXT(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
    return glbinding::Binding::VertexArrayBindVertexBufferEXT(vaobj, bindingindex, buffer, offset, stride);
}

inline void glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor)
{
    return glbinding::Binding::VertexArrayBindingDivisor(vaobj, bindingindex, divisor);
}

inline void glVertexArrayColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayColorOffsetEXT(vaobj, buffer, size, type, stride, offset);
}

inline void glVertexArrayEdgeFlagOffsetEXT(GLuint vaobj, GLuint buffer, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayEdgeFlagOffsetEXT(vaobj, buffer, stride, offset);
}

inline void glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer)
{
    return glbinding::Binding::VertexArrayElementBuffer(vaobj, buffer);
}

inline void glVertexArrayFogCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayFogCoordOffsetEXT(vaobj, buffer, type, stride, offset);
}

inline void glVertexArrayIndexOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayIndexOffsetEXT(vaobj, buffer, type, stride, offset);
}

inline void glVertexArrayMultiTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLenum texunit, GLint size, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayMultiTexCoordOffsetEXT(vaobj, buffer, texunit, size, type, stride, offset);
}

inline void glVertexArrayNormalOffsetEXT(GLuint vaobj, GLuint buffer, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayNormalOffsetEXT(vaobj, buffer, type, stride, offset);
}

inline void glVertexArrayParameteriAPPLE(GLenum pname, GLint param)
{
    return glbinding::Binding::VertexArrayParameteriAPPLE(pname, param);
}

inline void glVertexArrayRangeAPPLE(GLsizei length, void * pointer)
{
    return glbinding::Binding::VertexArrayRangeAPPLE(length, pointer);
}

inline void glVertexArrayRangeNV(GLsizei length, const void * pointer)
{
    return glbinding::Binding::VertexArrayRangeNV(length, pointer);
}

inline void glVertexArraySecondaryColorOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArraySecondaryColorOffsetEXT(vaobj, buffer, size, type, stride, offset);
}

inline void glVertexArrayTexCoordOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayTexCoordOffsetEXT(vaobj, buffer, size, type, stride, offset);
}

inline void glVertexArrayVertexAttribBindingEXT(GLuint vaobj, GLuint attribindex, GLuint bindingindex)
{
    return glbinding::Binding::VertexArrayVertexAttribBindingEXT(vaobj, attribindex, bindingindex);
}

inline void glVertexArrayVertexAttribDivisorEXT(GLuint vaobj, GLuint index, GLuint divisor)
{
    return glbinding::Binding::VertexArrayVertexAttribDivisorEXT(vaobj, index, divisor);
}

inline void glVertexArrayVertexAttribFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
    return glbinding::Binding::VertexArrayVertexAttribFormatEXT(vaobj, attribindex, size, type, normalized, relativeoffset);
}

inline void glVertexArrayVertexAttribIFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
    return glbinding::Binding::VertexArrayVertexAttribIFormatEXT(vaobj, attribindex, size, type, relativeoffset);
}

inline void glVertexArrayVertexAttribIOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayVertexAttribIOffsetEXT(vaobj, buffer, index, size, type, stride, offset);
}

inline void glVertexArrayVertexAttribLFormatEXT(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
    return glbinding::Binding::VertexArrayVertexAttribLFormatEXT(vaobj, attribindex, size, type, relativeoffset);
}

inline void glVertexArrayVertexAttribLOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayVertexAttribLOffsetEXT(vaobj, buffer, index, size, type, stride, offset);
}

inline void glVertexArrayVertexAttribOffsetEXT(GLuint vaobj, GLuint buffer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayVertexAttribOffsetEXT(vaobj, buffer, index, size, type, normalized, stride, offset);
}

inline void glVertexArrayVertexBindingDivisorEXT(GLuint vaobj, GLuint bindingindex, GLuint divisor)
{
    return glbinding::Binding::VertexArrayVertexBindingDivisorEXT(vaobj, bindingindex, divisor);
}

inline void glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride)
{
    return glbinding::Binding::VertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
}

inline void glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides)
{
    return glbinding::Binding::VertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
}

inline void glVertexArrayVertexOffsetEXT(GLuint vaobj, GLuint buffer, GLint size, GLenum type, GLsizei stride, GLintptr offset)
{
    return glbinding::Binding::VertexArrayVertexOffsetEXT(vaobj, buffer, size, type, stride, offset);
}

inline void glVertexAttrib1dARB(GLuint index, GLdouble x)
{
    return glbinding::Binding::VertexAttrib1dARB(index, x);
}

inline void glVertexAttrib1dNV(GLuint index, GLdouble x)
{
    return glbinding::Binding::VertexAttrib1dNV(index, x);
}

inline void glVertexAttrib1dvARB(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttrib1dvARB(index, v);
}

inline void glVertexAttrib1dvNV(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttrib1dvNV(index, v);
}

inline void glVertexAttrib1fARB(GLuint index, GLfloat x)
{
    return glbinding::Binding::VertexAttrib1fARB(index, x);
}

inline void glVertexAttrib1fNV(GLuint index, GLfloat x)
{
    return glbinding::Binding::VertexAttrib1fNV(index, x);
}

inline void glVertexAttrib1fvARB(GLuint index, const GLfloat * v)
{
    return glbinding::Binding::VertexAttrib1fvARB(index, v);
}

inline void glVertexAttrib1fvNV(GLuint index, const GLfloat * v)
{
    return glbinding::Binding::VertexAttrib1fvNV(index, v);
}

inline void glVertexAttrib1hNV(GLuint index, GLhalfNV x)
{
    return glbinding::Binding::VertexAttrib1hNV(index, x);
}

inline void glVertexAttrib1hvNV(GLuint index, const GLhalfNV * v)
{
    return glbinding::Binding::VertexAttrib1hvNV(index, v);
}

inline void glVertexAttrib1sARB(GLuint index, GLshort x)
{
    return glbinding::Binding::VertexAttrib1sARB(index, x);
}

inline void glVertexAttrib1sNV(GLuint index, GLshort x)
{
    return glbinding::Binding::VertexAttrib1sNV(index, x);
}

inline void glVertexAttrib1svARB(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib1svARB(index, v);
}

inline void glVertexAttrib1svNV(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib1svNV(index, v);
}

inline void glVertexAttrib2dARB(GLuint index, GLdouble x, GLdouble y)
{
    return glbinding::Binding::VertexAttrib2dARB(index, x, y);
}

inline void glVertexAttrib2dNV(GLuint index, GLdouble x, GLdouble y)
{
    return glbinding::Binding::VertexAttrib2dNV(index, x, y);
}

inline void glVertexAttrib2dvARB(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttrib2dvARB(index, v);
}

inline void glVertexAttrib2dvNV(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttrib2dvNV(index, v);
}

inline void glVertexAttrib2fARB(GLuint index, GLfloat x, GLfloat y)
{
    return glbinding::Binding::VertexAttrib2fARB(index, x, y);
}

inline void glVertexAttrib2fNV(GLuint index, GLfloat x, GLfloat y)
{
    return glbinding::Binding::VertexAttrib2fNV(index, x, y);
}

inline void glVertexAttrib2fvARB(GLuint index, const GLfloat * v)
{
    return glbinding::Binding::VertexAttrib2fvARB(index, v);
}

inline void glVertexAttrib2fvNV(GLuint index, const GLfloat * v)
{
    return glbinding::Binding::VertexAttrib2fvNV(index, v);
}

inline void glVertexAttrib2hNV(GLuint index, GLhalfNV x, GLhalfNV y)
{
    return glbinding::Binding::VertexAttrib2hNV(index, x, y);
}

inline void glVertexAttrib2hvNV(GLuint index, const GLhalfNV * v)
{
    return glbinding::Binding::VertexAttrib2hvNV(index, v);
}

inline void glVertexAttrib2sARB(GLuint index, GLshort x, GLshort y)
{
    return glbinding::Binding::VertexAttrib2sARB(index, x, y);
}

inline void glVertexAttrib2sNV(GLuint index, GLshort x, GLshort y)
{
    return glbinding::Binding::VertexAttrib2sNV(index, x, y);
}

inline void glVertexAttrib2svARB(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib2svARB(index, v);
}

inline void glVertexAttrib2svNV(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib2svNV(index, v);
}

inline void glVertexAttrib3dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::VertexAttrib3dARB(index, x, y, z);
}

inline void glVertexAttrib3dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::VertexAttrib3dNV(index, x, y, z);
}

inline void glVertexAttrib3dvARB(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttrib3dvARB(index, v);
}

inline void glVertexAttrib3dvNV(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttrib3dvNV(index, v);
}

inline void glVertexAttrib3fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::VertexAttrib3fARB(index, x, y, z);
}

inline void glVertexAttrib3fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::VertexAttrib3fNV(index, x, y, z);
}

inline void glVertexAttrib3fvARB(GLuint index, const GLfloat * v)
{
    return glbinding::Binding::VertexAttrib3fvARB(index, v);
}

inline void glVertexAttrib3fvNV(GLuint index, const GLfloat * v)
{
    return glbinding::Binding::VertexAttrib3fvNV(index, v);
}

inline void glVertexAttrib3hNV(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z)
{
    return glbinding::Binding::VertexAttrib3hNV(index, x, y, z);
}

inline void glVertexAttrib3hvNV(GLuint index, const GLhalfNV * v)
{
    return glbinding::Binding::VertexAttrib3hvNV(index, v);
}

inline void glVertexAttrib3sARB(GLuint index, GLshort x, GLshort y, GLshort z)
{
    return glbinding::Binding::VertexAttrib3sARB(index, x, y, z);
}

inline void glVertexAttrib3sNV(GLuint index, GLshort x, GLshort y, GLshort z)
{
    return glbinding::Binding::VertexAttrib3sNV(index, x, y, z);
}

inline void glVertexAttrib3svARB(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib3svARB(index, v);
}

inline void glVertexAttrib3svNV(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib3svNV(index, v);
}

inline void glVertexAttrib4NbvARB(GLuint index, const GLbyte * v)
{
    return glbinding::Binding::VertexAttrib4NbvARB(index, v);
}

inline void glVertexAttrib4NivARB(GLuint index, const GLint * v)
{
    return glbinding::Binding::VertexAttrib4NivARB(index, v);
}

inline void glVertexAttrib4NsvARB(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib4NsvARB(index, v);
}

inline void glVertexAttrib4NubARB(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
    return glbinding::Binding::VertexAttrib4NubARB(index, x, y, z, w);
}

inline void glVertexAttrib4NubvARB(GLuint index, const GLubyte * v)
{
    return glbinding::Binding::VertexAttrib4NubvARB(index, v);
}

inline void glVertexAttrib4NuivARB(GLuint index, const GLuint * v)
{
    return glbinding::Binding::VertexAttrib4NuivARB(index, v);
}

inline void glVertexAttrib4NusvARB(GLuint index, const GLushort * v)
{
    return glbinding::Binding::VertexAttrib4NusvARB(index, v);
}

inline void glVertexAttrib4bvARB(GLuint index, const GLbyte * v)
{
    return glbinding::Binding::VertexAttrib4bvARB(index, v);
}

inline void glVertexAttrib4dARB(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::VertexAttrib4dARB(index, x, y, z, w);
}

inline void glVertexAttrib4dNV(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::VertexAttrib4dNV(index, x, y, z, w);
}

inline void glVertexAttrib4dvARB(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttrib4dvARB(index, v);
}

inline void glVertexAttrib4dvNV(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttrib4dvNV(index, v);
}

inline void glVertexAttrib4fARB(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::VertexAttrib4fARB(index, x, y, z, w);
}

inline void glVertexAttrib4fNV(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::VertexAttrib4fNV(index, x, y, z, w);
}

inline void glVertexAttrib4fvARB(GLuint index, const GLfloat * v)
{
    return glbinding::Binding::VertexAttrib4fvARB(index, v);
}

inline void glVertexAttrib4fvNV(GLuint index, const GLfloat * v)
{
    return glbinding::Binding::VertexAttrib4fvNV(index, v);
}

inline void glVertexAttrib4hNV(GLuint index, GLhalfNV x, GLhalfNV y, GLhalfNV z, GLhalfNV w)
{
    return glbinding::Binding::VertexAttrib4hNV(index, x, y, z, w);
}

inline void glVertexAttrib4hvNV(GLuint index, const GLhalfNV * v)
{
    return glbinding::Binding::VertexAttrib4hvNV(index, v);
}

inline void glVertexAttrib4ivARB(GLuint index, const GLint * v)
{
    return glbinding::Binding::VertexAttrib4ivARB(index, v);
}

inline void glVertexAttrib4sARB(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
    return glbinding::Binding::VertexAttrib4sARB(index, x, y, z, w);
}

inline void glVertexAttrib4sNV(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w)
{
    return glbinding::Binding::VertexAttrib4sNV(index, x, y, z, w);
}

inline void glVertexAttrib4svARB(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib4svARB(index, v);
}

inline void glVertexAttrib4svNV(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttrib4svNV(index, v);
}

inline void glVertexAttrib4ubNV(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w)
{
    return glbinding::Binding::VertexAttrib4ubNV(index, x, y, z, w);
}

inline void glVertexAttrib4ubvARB(GLuint index, const GLubyte * v)
{
    return glbinding::Binding::VertexAttrib4ubvARB(index, v);
}

inline void glVertexAttrib4ubvNV(GLuint index, const GLubyte * v)
{
    return glbinding::Binding::VertexAttrib4ubvNV(index, v);
}

inline void glVertexAttrib4uivARB(GLuint index, const GLuint * v)
{
    return glbinding::Binding::VertexAttrib4uivARB(index, v);
}

inline void glVertexAttrib4usvARB(GLuint index, const GLushort * v)
{
    return glbinding::Binding::VertexAttrib4usvARB(index, v);
}

inline void glVertexAttribArrayObjectATI(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint buffer, GLuint offset)
{
    return glbinding::Binding::VertexAttribArrayObjectATI(index, size, type, normalized, stride, buffer, offset);
}

inline void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex)
{
    return glbinding::Binding::VertexAttribBinding(attribindex, bindingindex);
}

inline void glVertexAttribDivisorARB(GLuint index, GLuint divisor)
{
    return glbinding::Binding::VertexAttribDivisorARB(index, divisor);
}

inline void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset)
{
    return glbinding::Binding::VertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
}

inline void glVertexAttribFormatNV(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride)
{
    return glbinding::Binding::VertexAttribFormatNV(index, size, type, normalized, stride);
}

inline void glVertexAttribI1iEXT(GLuint index, GLint x)
{
    return glbinding::Binding::VertexAttribI1iEXT(index, x);
}

inline void glVertexAttribI1ivEXT(GLuint index, const GLint * v)
{
    return glbinding::Binding::VertexAttribI1ivEXT(index, v);
}

inline void glVertexAttribI1uiEXT(GLuint index, GLuint x)
{
    return glbinding::Binding::VertexAttribI1uiEXT(index, x);
}

inline void glVertexAttribI1uivEXT(GLuint index, const GLuint * v)
{
    return glbinding::Binding::VertexAttribI1uivEXT(index, v);
}

inline void glVertexAttribI2iEXT(GLuint index, GLint x, GLint y)
{
    return glbinding::Binding::VertexAttribI2iEXT(index, x, y);
}

inline void glVertexAttribI2ivEXT(GLuint index, const GLint * v)
{
    return glbinding::Binding::VertexAttribI2ivEXT(index, v);
}

inline void glVertexAttribI2uiEXT(GLuint index, GLuint x, GLuint y)
{
    return glbinding::Binding::VertexAttribI2uiEXT(index, x, y);
}

inline void glVertexAttribI2uivEXT(GLuint index, const GLuint * v)
{
    return glbinding::Binding::VertexAttribI2uivEXT(index, v);
}

inline void glVertexAttribI3iEXT(GLuint index, GLint x, GLint y, GLint z)
{
    return glbinding::Binding::VertexAttribI3iEXT(index, x, y, z);
}

inline void glVertexAttribI3ivEXT(GLuint index, const GLint * v)
{
    return glbinding::Binding::VertexAttribI3ivEXT(index, v);
}

inline void glVertexAttribI3uiEXT(GLuint index, GLuint x, GLuint y, GLuint z)
{
    return glbinding::Binding::VertexAttribI3uiEXT(index, x, y, z);
}

inline void glVertexAttribI3uivEXT(GLuint index, const GLuint * v)
{
    return glbinding::Binding::VertexAttribI3uivEXT(index, v);
}

inline void glVertexAttribI4bvEXT(GLuint index, const GLbyte * v)
{
    return glbinding::Binding::VertexAttribI4bvEXT(index, v);
}

inline void glVertexAttribI4iEXT(GLuint index, GLint x, GLint y, GLint z, GLint w)
{
    return glbinding::Binding::VertexAttribI4iEXT(index, x, y, z, w);
}

inline void glVertexAttribI4ivEXT(GLuint index, const GLint * v)
{
    return glbinding::Binding::VertexAttribI4ivEXT(index, v);
}

inline void glVertexAttribI4svEXT(GLuint index, const GLshort * v)
{
    return glbinding::Binding::VertexAttribI4svEXT(index, v);
}

inline void glVertexAttribI4ubvEXT(GLuint index, const GLubyte * v)
{
    return glbinding::Binding::VertexAttribI4ubvEXT(index, v);
}

inline void glVertexAttribI4uiEXT(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w)
{
    return glbinding::Binding::VertexAttribI4uiEXT(index, x, y, z, w);
}

inline void glVertexAttribI4uivEXT(GLuint index, const GLuint * v)
{
    return glbinding::Binding::VertexAttribI4uivEXT(index, v);
}

inline void glVertexAttribI4usvEXT(GLuint index, const GLushort * v)
{
    return glbinding::Binding::VertexAttribI4usvEXT(index, v);
}

inline void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
    return glbinding::Binding::VertexAttribIFormat(attribindex, size, type, relativeoffset);
}

inline void glVertexAttribIFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride)
{
    return glbinding::Binding::VertexAttribIFormatNV(index, size, type, stride);
}

inline void glVertexAttribIPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::VertexAttribIPointerEXT(index, size, type, stride, pointer);
}

inline void glVertexAttribL1dEXT(GLuint index, GLdouble x)
{
    return glbinding::Binding::VertexAttribL1dEXT(index, x);
}

inline void glVertexAttribL1dvEXT(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttribL1dvEXT(index, v);
}

inline void glVertexAttribL1i64NV(GLuint index, GLint64EXT x)
{
    return glbinding::Binding::VertexAttribL1i64NV(index, x);
}

inline void glVertexAttribL1i64vNV(GLuint index, const GLint64EXT * v)
{
    return glbinding::Binding::VertexAttribL1i64vNV(index, v);
}

inline void glVertexAttribL1ui64ARB(GLuint index, GLuint64EXT x)
{
    return glbinding::Binding::VertexAttribL1ui64ARB(index, x);
}

inline void glVertexAttribL1ui64NV(GLuint index, GLuint64EXT x)
{
    return glbinding::Binding::VertexAttribL1ui64NV(index, x);
}

inline void glVertexAttribL1ui64vARB(GLuint index, const GLuint64EXT * v)
{
    return glbinding::Binding::VertexAttribL1ui64vARB(index, v);
}

inline void glVertexAttribL1ui64vNV(GLuint index, const GLuint64EXT * v)
{
    return glbinding::Binding::VertexAttribL1ui64vNV(index, v);
}

inline void glVertexAttribL2dEXT(GLuint index, GLdouble x, GLdouble y)
{
    return glbinding::Binding::VertexAttribL2dEXT(index, x, y);
}

inline void glVertexAttribL2dvEXT(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttribL2dvEXT(index, v);
}

inline void glVertexAttribL2i64NV(GLuint index, GLint64EXT x, GLint64EXT y)
{
    return glbinding::Binding::VertexAttribL2i64NV(index, x, y);
}

inline void glVertexAttribL2i64vNV(GLuint index, const GLint64EXT * v)
{
    return glbinding::Binding::VertexAttribL2i64vNV(index, v);
}

inline void glVertexAttribL2ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y)
{
    return glbinding::Binding::VertexAttribL2ui64NV(index, x, y);
}

inline void glVertexAttribL2ui64vNV(GLuint index, const GLuint64EXT * v)
{
    return glbinding::Binding::VertexAttribL2ui64vNV(index, v);
}

inline void glVertexAttribL3dEXT(GLuint index, GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::VertexAttribL3dEXT(index, x, y, z);
}

inline void glVertexAttribL3dvEXT(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttribL3dvEXT(index, v);
}

inline void glVertexAttribL3i64NV(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z)
{
    return glbinding::Binding::VertexAttribL3i64NV(index, x, y, z);
}

inline void glVertexAttribL3i64vNV(GLuint index, const GLint64EXT * v)
{
    return glbinding::Binding::VertexAttribL3i64vNV(index, v);
}

inline void glVertexAttribL3ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z)
{
    return glbinding::Binding::VertexAttribL3ui64NV(index, x, y, z);
}

inline void glVertexAttribL3ui64vNV(GLuint index, const GLuint64EXT * v)
{
    return glbinding::Binding::VertexAttribL3ui64vNV(index, v);
}

inline void glVertexAttribL4dEXT(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::VertexAttribL4dEXT(index, x, y, z, w);
}

inline void glVertexAttribL4dvEXT(GLuint index, const GLdouble * v)
{
    return glbinding::Binding::VertexAttribL4dvEXT(index, v);
}

inline void glVertexAttribL4i64NV(GLuint index, GLint64EXT x, GLint64EXT y, GLint64EXT z, GLint64EXT w)
{
    return glbinding::Binding::VertexAttribL4i64NV(index, x, y, z, w);
}

inline void glVertexAttribL4i64vNV(GLuint index, const GLint64EXT * v)
{
    return glbinding::Binding::VertexAttribL4i64vNV(index, v);
}

inline void glVertexAttribL4ui64NV(GLuint index, GLuint64EXT x, GLuint64EXT y, GLuint64EXT z, GLuint64EXT w)
{
    return glbinding::Binding::VertexAttribL4ui64NV(index, x, y, z, w);
}

inline void glVertexAttribL4ui64vNV(GLuint index, const GLuint64EXT * v)
{
    return glbinding::Binding::VertexAttribL4ui64vNV(index, v);
}

inline void glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset)
{
    return glbinding::Binding::VertexAttribLFormat(attribindex, size, type, relativeoffset);
}

inline void glVertexAttribLFormatNV(GLuint index, GLint size, GLenum type, GLsizei stride)
{
    return glbinding::Binding::VertexAttribLFormatNV(index, size, type, stride);
}

inline void glVertexAttribLPointerEXT(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::VertexAttribLPointerEXT(index, size, type, stride, pointer);
}

inline void glVertexAttribParameteriAMD(GLuint index, GLenum pname, GLint param)
{
    return glbinding::Binding::VertexAttribParameteriAMD(index, pname, param);
}

inline void glVertexAttribPointerARB(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::VertexAttribPointerARB(index, size, type, normalized, stride, pointer);
}

inline void glVertexAttribPointerNV(GLuint index, GLint fsize, GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::VertexAttribPointerNV(index, fsize, type, stride, pointer);
}

inline void glVertexAttribs1dvNV(GLuint index, GLsizei count, const GLdouble * v)
{
    return glbinding::Binding::VertexAttribs1dvNV(index, count, v);
}

inline void glVertexAttribs1fvNV(GLuint index, GLsizei count, const GLfloat * v)
{
    return glbinding::Binding::VertexAttribs1fvNV(index, count, v);
}

inline void glVertexAttribs1hvNV(GLuint index, GLsizei n, const GLhalfNV * v)
{
    return glbinding::Binding::VertexAttribs1hvNV(index, n, v);
}

inline void glVertexAttribs1svNV(GLuint index, GLsizei count, const GLshort * v)
{
    return glbinding::Binding::VertexAttribs1svNV(index, count, v);
}

inline void glVertexAttribs2dvNV(GLuint index, GLsizei count, const GLdouble * v)
{
    return glbinding::Binding::VertexAttribs2dvNV(index, count, v);
}

inline void glVertexAttribs2fvNV(GLuint index, GLsizei count, const GLfloat * v)
{
    return glbinding::Binding::VertexAttribs2fvNV(index, count, v);
}

inline void glVertexAttribs2hvNV(GLuint index, GLsizei n, const GLhalfNV * v)
{
    return glbinding::Binding::VertexAttribs2hvNV(index, n, v);
}

inline void glVertexAttribs2svNV(GLuint index, GLsizei count, const GLshort * v)
{
    return glbinding::Binding::VertexAttribs2svNV(index, count, v);
}

inline void glVertexAttribs3dvNV(GLuint index, GLsizei count, const GLdouble * v)
{
    return glbinding::Binding::VertexAttribs3dvNV(index, count, v);
}

inline void glVertexAttribs3fvNV(GLuint index, GLsizei count, const GLfloat * v)
{
    return glbinding::Binding::VertexAttribs3fvNV(index, count, v);
}

inline void glVertexAttribs3hvNV(GLuint index, GLsizei n, const GLhalfNV * v)
{
    return glbinding::Binding::VertexAttribs3hvNV(index, n, v);
}

inline void glVertexAttribs3svNV(GLuint index, GLsizei count, const GLshort * v)
{
    return glbinding::Binding::VertexAttribs3svNV(index, count, v);
}

inline void glVertexAttribs4dvNV(GLuint index, GLsizei count, const GLdouble * v)
{
    return glbinding::Binding::VertexAttribs4dvNV(index, count, v);
}

inline void glVertexAttribs4fvNV(GLuint index, GLsizei count, const GLfloat * v)
{
    return glbinding::Binding::VertexAttribs4fvNV(index, count, v);
}

inline void glVertexAttribs4hvNV(GLuint index, GLsizei n, const GLhalfNV * v)
{
    return glbinding::Binding::VertexAttribs4hvNV(index, n, v);
}

inline void glVertexAttribs4svNV(GLuint index, GLsizei count, const GLshort * v)
{
    return glbinding::Binding::VertexAttribs4svNV(index, count, v);
}

inline void glVertexAttribs4ubvNV(GLuint index, GLsizei count, const GLubyte * v)
{
    return glbinding::Binding::VertexAttribs4ubvNV(index, count, v);
}

inline void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
{
    return glbinding::Binding::VertexBindingDivisor(bindingindex, divisor);
}

inline void glVertexBlendARB(GLint count)
{
    return glbinding::Binding::VertexBlendARB(count);
}

inline void glVertexBlendEnvfATI(GLenum pname, GLfloat param)
{
    return glbinding::Binding::VertexBlendEnvfATI(pname, param);
}

inline void glVertexBlendEnviATI(GLenum pname, GLint param)
{
    return glbinding::Binding::VertexBlendEnviATI(pname, param);
}

inline void glVertexFormatNV(GLint size, GLenum type, GLsizei stride)
{
    return glbinding::Binding::VertexFormatNV(size, type, stride);
}

inline void glVertexPointerEXT(GLint size, GLenum type, GLsizei stride, GLsizei count, const void * pointer)
{
    return glbinding::Binding::VertexPointerEXT(size, type, stride, count, pointer);
}

inline void glVertexPointerListIBM(GLint size, GLenum type, GLint stride, const void ** pointer, GLint ptrstride)
{
    return glbinding::Binding::VertexPointerListIBM(size, type, stride, pointer, ptrstride);
}

inline void glVertexPointervINTEL(GLint size, GLenum type, const void ** pointer)
{
    return glbinding::Binding::VertexPointervINTEL(size, type, pointer);
}

inline void glVertexStream1dATI(GLenum stream, GLdouble x)
{
    return glbinding::Binding::VertexStream1dATI(stream, x);
}

inline void glVertexStream1dvATI(GLenum stream, const GLdouble * coords)
{
    return glbinding::Binding::VertexStream1dvATI(stream, coords);
}

inline void glVertexStream1fATI(GLenum stream, GLfloat x)
{
    return glbinding::Binding::VertexStream1fATI(stream, x);
}

inline void glVertexStream1fvATI(GLenum stream, const GLfloat * coords)
{
    return glbinding::Binding::VertexStream1fvATI(stream, coords);
}

inline void glVertexStream1iATI(GLenum stream, GLint x)
{
    return glbinding::Binding::VertexStream1iATI(stream, x);
}

inline void glVertexStream1ivATI(GLenum stream, const GLint * coords)
{
    return glbinding::Binding::VertexStream1ivATI(stream, coords);
}

inline void glVertexStream1sATI(GLenum stream, GLshort x)
{
    return glbinding::Binding::VertexStream1sATI(stream, x);
}

inline void glVertexStream1svATI(GLenum stream, const GLshort * coords)
{
    return glbinding::Binding::VertexStream1svATI(stream, coords);
}

inline void glVertexStream2dATI(GLenum stream, GLdouble x, GLdouble y)
{
    return glbinding::Binding::VertexStream2dATI(stream, x, y);
}

inline void glVertexStream2dvATI(GLenum stream, const GLdouble * coords)
{
    return glbinding::Binding::VertexStream2dvATI(stream, coords);
}

inline void glVertexStream2fATI(GLenum stream, GLfloat x, GLfloat y)
{
    return glbinding::Binding::VertexStream2fATI(stream, x, y);
}

inline void glVertexStream2fvATI(GLenum stream, const GLfloat * coords)
{
    return glbinding::Binding::VertexStream2fvATI(stream, coords);
}

inline void glVertexStream2iATI(GLenum stream, GLint x, GLint y)
{
    return glbinding::Binding::VertexStream2iATI(stream, x, y);
}

inline void glVertexStream2ivATI(GLenum stream, const GLint * coords)
{
    return glbinding::Binding::VertexStream2ivATI(stream, coords);
}

inline void glVertexStream2sATI(GLenum stream, GLshort x, GLshort y)
{
    return glbinding::Binding::VertexStream2sATI(stream, x, y);
}

inline void glVertexStream2svATI(GLenum stream, const GLshort * coords)
{
    return glbinding::Binding::VertexStream2svATI(stream, coords);
}

inline void glVertexStream3dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::VertexStream3dATI(stream, x, y, z);
}

inline void glVertexStream3dvATI(GLenum stream, const GLdouble * coords)
{
    return glbinding::Binding::VertexStream3dvATI(stream, coords);
}

inline void glVertexStream3fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::VertexStream3fATI(stream, x, y, z);
}

inline void glVertexStream3fvATI(GLenum stream, const GLfloat * coords)
{
    return glbinding::Binding::VertexStream3fvATI(stream, coords);
}

inline void glVertexStream3iATI(GLenum stream, GLint x, GLint y, GLint z)
{
    return glbinding::Binding::VertexStream3iATI(stream, x, y, z);
}

inline void glVertexStream3ivATI(GLenum stream, const GLint * coords)
{
    return glbinding::Binding::VertexStream3ivATI(stream, coords);
}

inline void glVertexStream3sATI(GLenum stream, GLshort x, GLshort y, GLshort z)
{
    return glbinding::Binding::VertexStream3sATI(stream, x, y, z);
}

inline void glVertexStream3svATI(GLenum stream, const GLshort * coords)
{
    return glbinding::Binding::VertexStream3svATI(stream, coords);
}

inline void glVertexStream4dATI(GLenum stream, GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::VertexStream4dATI(stream, x, y, z, w);
}

inline void glVertexStream4dvATI(GLenum stream, const GLdouble * coords)
{
    return glbinding::Binding::VertexStream4dvATI(stream, coords);
}

inline void glVertexStream4fATI(GLenum stream, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::VertexStream4fATI(stream, x, y, z, w);
}

inline void glVertexStream4fvATI(GLenum stream, const GLfloat * coords)
{
    return glbinding::Binding::VertexStream4fvATI(stream, coords);
}

inline void glVertexStream4iATI(GLenum stream, GLint x, GLint y, GLint z, GLint w)
{
    return glbinding::Binding::VertexStream4iATI(stream, x, y, z, w);
}

inline void glVertexStream4ivATI(GLenum stream, const GLint * coords)
{
    return glbinding::Binding::VertexStream4ivATI(stream, coords);
}

inline void glVertexStream4sATI(GLenum stream, GLshort x, GLshort y, GLshort z, GLshort w)
{
    return glbinding::Binding::VertexStream4sATI(stream, x, y, z, w);
}

inline void glVertexStream4svATI(GLenum stream, const GLshort * coords)
{
    return glbinding::Binding::VertexStream4svATI(stream, coords);
}

inline void glVertexWeightPointerEXT(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::VertexWeightPointerEXT(size, type, stride, pointer);
}

inline void glVertexWeightfEXT(GLfloat weight)
{
    return glbinding::Binding::VertexWeightfEXT(weight);
}

inline void glVertexWeightfvEXT(const GLfloat * weight)
{
    return glbinding::Binding::VertexWeightfvEXT(weight);
}

inline void glVertexWeighthNV(GLhalfNV weight)
{
    return glbinding::Binding::VertexWeighthNV(weight);
}

inline void glVertexWeighthvNV(const GLhalfNV * weight)
{
    return glbinding::Binding::VertexWeighthvNV(weight);
}

inline GLenum glVideoCaptureNV(GLuint video_capture_slot, GLuint * sequence_num, GLuint64EXT * capture_time)
{
    return static_cast<gl42ext::GLenum>(glbinding::Binding::VideoCaptureNV(video_capture_slot, sequence_num, capture_time));
}

inline void glVideoCaptureStreamParameterdvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLdouble * params)
{
    return glbinding::Binding::VideoCaptureStreamParameterdvNV(video_capture_slot, stream, pname, params);
}

inline void glVideoCaptureStreamParameterfvNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLfloat * params)
{
    return glbinding::Binding::VideoCaptureStreamParameterfvNV(video_capture_slot, stream, pname, params);
}

inline void glVideoCaptureStreamParameterivNV(GLuint video_capture_slot, GLuint stream, GLenum pname, const GLint * params)
{
    return glbinding::Binding::VideoCaptureStreamParameterivNV(video_capture_slot, stream, pname, params);
}

inline void glWeightPathsNV(GLuint resultPath, GLsizei numPaths, const GLuint * paths, const GLfloat * weights)
{
    return glbinding::Binding::WeightPathsNV(resultPath, numPaths, paths, weights);
}

inline void glWeightPointerARB(GLint size, GLenum type, GLsizei stride, const void * pointer)
{
    return glbinding::Binding::WeightPointerARB(size, type, stride, pointer);
}

inline void glWeightbvARB(GLint size, const GLbyte * weights)
{
    return glbinding::Binding::WeightbvARB(size, weights);
}

inline void glWeightdvARB(GLint size, const GLdouble * weights)
{
    return glbinding::Binding::WeightdvARB(size, weights);
}

inline void glWeightfvARB(GLint size, const GLfloat * weights)
{
    return glbinding::Binding::WeightfvARB(size, weights);
}

inline void glWeightivARB(GLint size, const GLint * weights)
{
    return glbinding::Binding::WeightivARB(size, weights);
}

inline void glWeightsvARB(GLint size, const GLshort * weights)
{
    return glbinding::Binding::WeightsvARB(size, weights);
}

inline void glWeightubvARB(GLint size, const GLubyte * weights)
{
    return glbinding::Binding::WeightubvARB(size, weights);
}

inline void glWeightuivARB(GLint size, const GLuint * weights)
{
    return glbinding::Binding::WeightuivARB(size, weights);
}

inline void glWeightusvARB(GLint size, const GLushort * weights)
{
    return glbinding::Binding::WeightusvARB(size, weights);
}

inline void glWindowPos2dARB(GLdouble x, GLdouble y)
{
    return glbinding::Binding::WindowPos2dARB(x, y);
}

inline void glWindowPos2dMESA(GLdouble x, GLdouble y)
{
    return glbinding::Binding::WindowPos2dMESA(x, y);
}

inline void glWindowPos2dvARB(const GLdouble * v)
{
    return glbinding::Binding::WindowPos2dvARB(v);
}

inline void glWindowPos2dvMESA(const GLdouble * v)
{
    return glbinding::Binding::WindowPos2dvMESA(v);
}

inline void glWindowPos2fARB(GLfloat x, GLfloat y)
{
    return glbinding::Binding::WindowPos2fARB(x, y);
}

inline void glWindowPos2fMESA(GLfloat x, GLfloat y)
{
    return glbinding::Binding::WindowPos2fMESA(x, y);
}

inline void glWindowPos2fvARB(const GLfloat * v)
{
    return glbinding::Binding::WindowPos2fvARB(v);
}

inline void glWindowPos2fvMESA(const GLfloat * v)
{
    return glbinding::Binding::WindowPos2fvMESA(v);
}

inline void glWindowPos2iARB(GLint x, GLint y)
{
    return glbinding::Binding::WindowPos2iARB(x, y);
}

inline void glWindowPos2iMESA(GLint x, GLint y)
{
    return glbinding::Binding::WindowPos2iMESA(x, y);
}

inline void glWindowPos2ivARB(const GLint * v)
{
    return glbinding::Binding::WindowPos2ivARB(v);
}

inline void glWindowPos2ivMESA(const GLint * v)
{
    return glbinding::Binding::WindowPos2ivMESA(v);
}

inline void glWindowPos2sARB(GLshort x, GLshort y)
{
    return glbinding::Binding::WindowPos2sARB(x, y);
}

inline void glWindowPos2sMESA(GLshort x, GLshort y)
{
    return glbinding::Binding::WindowPos2sMESA(x, y);
}

inline void glWindowPos2svARB(const GLshort * v)
{
    return glbinding::Binding::WindowPos2svARB(v);
}

inline void glWindowPos2svMESA(const GLshort * v)
{
    return glbinding::Binding::WindowPos2svMESA(v);
}

inline void glWindowPos3dARB(GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::WindowPos3dARB(x, y, z);
}

inline void glWindowPos3dMESA(GLdouble x, GLdouble y, GLdouble z)
{
    return glbinding::Binding::WindowPos3dMESA(x, y, z);
}

inline void glWindowPos3dvARB(const GLdouble * v)
{
    return glbinding::Binding::WindowPos3dvARB(v);
}

inline void glWindowPos3dvMESA(const GLdouble * v)
{
    return glbinding::Binding::WindowPos3dvMESA(v);
}

inline void glWindowPos3fARB(GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::WindowPos3fARB(x, y, z);
}

inline void glWindowPos3fMESA(GLfloat x, GLfloat y, GLfloat z)
{
    return glbinding::Binding::WindowPos3fMESA(x, y, z);
}

inline void glWindowPos3fvARB(const GLfloat * v)
{
    return glbinding::Binding::WindowPos3fvARB(v);
}

inline void glWindowPos3fvMESA(const GLfloat * v)
{
    return glbinding::Binding::WindowPos3fvMESA(v);
}

inline void glWindowPos3iARB(GLint x, GLint y, GLint z)
{
    return glbinding::Binding::WindowPos3iARB(x, y, z);
}

inline void glWindowPos3iMESA(GLint x, GLint y, GLint z)
{
    return glbinding::Binding::WindowPos3iMESA(x, y, z);
}

inline void glWindowPos3ivARB(const GLint * v)
{
    return glbinding::Binding::WindowPos3ivARB(v);
}

inline void glWindowPos3ivMESA(const GLint * v)
{
    return glbinding::Binding::WindowPos3ivMESA(v);
}

inline void glWindowPos3sARB(GLshort x, GLshort y, GLshort z)
{
    return glbinding::Binding::WindowPos3sARB(x, y, z);
}

inline void glWindowPos3sMESA(GLshort x, GLshort y, GLshort z)
{
    return glbinding::Binding::WindowPos3sMESA(x, y, z);
}

inline void glWindowPos3svARB(const GLshort * v)
{
    return glbinding::Binding::WindowPos3svARB(v);
}

inline void glWindowPos3svMESA(const GLshort * v)
{
    return glbinding::Binding::WindowPos3svMESA(v);
}

inline void glWindowPos4dMESA(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    return glbinding::Binding::WindowPos4dMESA(x, y, z, w);
}

inline void glWindowPos4dvMESA(const GLdouble * v)
{
    return glbinding::Binding::WindowPos4dvMESA(v);
}

inline void glWindowPos4fMESA(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    return glbinding::Binding::WindowPos4fMESA(x, y, z, w);
}

inline void glWindowPos4fvMESA(const GLfloat * v)
{
    return glbinding::Binding::WindowPos4fvMESA(v);
}

inline void glWindowPos4iMESA(GLint x, GLint y, GLint z, GLint w)
{
    return glbinding::Binding::WindowPos4iMESA(x, y, z, w);
}

inline void glWindowPos4ivMESA(const GLint * v)
{
    return glbinding::Binding::WindowPos4ivMESA(v);
}

inline void glWindowPos4sMESA(GLshort x, GLshort y, GLshort z, GLshort w)
{
    return glbinding::Binding::WindowPos4sMESA(x, y, z, w);
}

inline void glWindowPos4svMESA(const GLshort * v)
{
    return glbinding::Binding::WindowPos4svMESA(v);
}

inline void glWriteMaskEXT(GLuint res, GLuint in, GLenum outX, GLenum outY, GLenum outZ, GLenum outW)
{
    return glbinding::Binding::WriteMaskEXT(res, in, outX, outY, outZ, outW);
}


} // namespace gl42ext
