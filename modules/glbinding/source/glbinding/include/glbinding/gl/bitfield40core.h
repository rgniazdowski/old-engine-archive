#pragma once

#include <glbinding/gl/nogl.h>
#include <glbinding/gl/types.h>

#include <glbinding/gl/bitfield.h>

#include <glbinding/SharedBitfield.hpp>

namespace gl40core
{

// import bitfields to namespace
static const gl::ContextProfileMask GL_CONTEXT_CORE_PROFILE_BIT = gl::ContextProfileMask::GL_CONTEXT_CORE_PROFILE_BIT;
static const gl::ContextFlagMask GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT = gl::ContextFlagMask::GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT;
static const gl::SyncObjectMask GL_SYNC_FLUSH_COMMANDS_BIT = gl::SyncObjectMask::GL_SYNC_FLUSH_COMMANDS_BIT;
static const gl::ContextProfileMask GL_CONTEXT_COMPATIBILITY_PROFILE_BIT = gl::ContextProfileMask::GL_CONTEXT_COMPATIBILITY_PROFILE_BIT;
static const glbinding::SharedBitfield<gl::AttribMask, gl::ClearBufferMask> GL_DEPTH_BUFFER_BIT = gl::AttribMask::GL_DEPTH_BUFFER_BIT;
static const glbinding::SharedBitfield<gl::AttribMask, gl::ClearBufferMask> GL_STENCIL_BUFFER_BIT = gl::AttribMask::GL_STENCIL_BUFFER_BIT;
static const glbinding::SharedBitfield<gl::AttribMask, gl::ClearBufferMask> GL_COLOR_BUFFER_BIT = gl::AttribMask::GL_COLOR_BUFFER_BIT;
static const glbinding::SharedBitfield<gl::BufferAccessMask, gl::MapBufferUsageMask> GL_MAP_READ_BIT = gl::BufferAccessMask::GL_MAP_READ_BIT;
static const glbinding::SharedBitfield<gl::BufferAccessMask, gl::MapBufferUsageMask> GL_MAP_WRITE_BIT = gl::BufferAccessMask::GL_MAP_WRITE_BIT;
static const glbinding::SharedBitfield<gl::BufferAccessMask, gl::MapBufferUsageMask> GL_MAP_INVALIDATE_RANGE_BIT = gl::BufferAccessMask::GL_MAP_INVALIDATE_RANGE_BIT;
static const glbinding::SharedBitfield<gl::BufferAccessMask, gl::MapBufferUsageMask> GL_MAP_INVALIDATE_BUFFER_BIT = gl::BufferAccessMask::GL_MAP_INVALIDATE_BUFFER_BIT;
static const glbinding::SharedBitfield<gl::BufferAccessMask, gl::MapBufferUsageMask> GL_MAP_FLUSH_EXPLICIT_BIT = gl::BufferAccessMask::GL_MAP_FLUSH_EXPLICIT_BIT;
static const glbinding::SharedBitfield<gl::BufferAccessMask, gl::MapBufferUsageMask> GL_MAP_UNSYNCHRONIZED_BIT = gl::BufferAccessMask::GL_MAP_UNSYNCHRONIZED_BIT;

} // namespace gl40core
