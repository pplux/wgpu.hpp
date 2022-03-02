
//-----------------------------------
// https://github.com/pplux/wgpu.hpp
//-----------------------------------
#pragma once

#ifndef WEBGPU_H_
#error "You must include the WEBGPU header before this one"
#endif

#include <type_traits>

namespace wgpu {

    #define BASIC_CLASS(Type) \
        struct Type : public WGPU ## Type{ \
            typedef Type S; /* S == Self */ \
            typedef WGPU ## Type W; /* W == WGPU Type */ \
            operator const W*() const { return this; } \
    
    #define CLASS(Type) \
        BASIC_CLASS(Type) \
        Type() : W() {} \

    #define SUBCLASS(Type, WGPUSType_value) \
        BASIC_CLASS(Type) \
        Type() : W({nullptr, WGPUSType_value}) {} \

    #define DESCRIPTOR(Type) \
        BASIC_CLASS(Type) \
        Type() : W() {} \
        template<class T> \
        S& nextInChain(const T *obj) \
        { \
            W::nextInChain = (const WGPUChainedStruct*) &(obj->chain); \
            return *this; \
        }\
        template<class T> \
        S& nextInChain(const T &obj) { return nextInChain(&obj); }


    #define PROP(Name) \
        S& Name(decltype(W::Name) arg) { W::Name = arg; return *this; }\

    #define LIST(List, Count) \
        template<size_t N> \
        S& List(std::remove_cv_t<std::remove_pointer_t<decltype(W::List)>> const (&args)[N]) { \
            W::Count = (decltype(W::Count)) N; \
            W::List = args; \
            return *this; \
        } \

    #define END };

    // Manually Generated
    CLASS(Color)
        PROP(r)
        PROP(g)
        PROP(b)
        PROP(a)
        Color(double r, double g, double b, double a = 1.0) : 
            W({r,g,b,a}){}
    END

    CLASS(Origin3D)
        PROP(x)
        PROP(y)
        PROP(z)
        Origin3D(uint32_t x = 0.0, uint32_t y = 0.0, uint32_t z = 0.0) : 
            W({x,y,z}){}
    END

    // Automatically generated
    typedef WGPUAdapter Adapter;
    typedef WGPUBindGroup BindGroup;
    typedef WGPUBindGroupLayout BindGroupLayout;
    typedef WGPUBuffer Buffer;
    typedef WGPUCommandBuffer CommandBuffer;
    typedef WGPUCommandEncoder CommandEncoder;
    typedef WGPUComputePassEncoder ComputePassEncoder;
    typedef WGPUComputePipeline ComputePipeline;
    typedef WGPUDevice Device;
    typedef WGPUInstance Instance;
    typedef WGPUPipelineLayout PipelineLayout;
    typedef WGPUQuerySet QuerySet;
    typedef WGPUQueue Queue;
    typedef WGPURenderBundle RenderBundle;
    typedef WGPURenderBundleEncoder RenderBundleEncoder;
    typedef WGPURenderPassEncoder RenderPassEncoder;
    typedef WGPURenderPipeline RenderPipeline;
    typedef WGPUSampler Sampler;
    typedef WGPUShaderModule ShaderModule;
    typedef WGPUSurface Surface;
    typedef WGPUSwapChain SwapChain;
    typedef WGPUTexture Texture;
    typedef WGPUTextureView TextureView;

    CLASS(ChainedStruct)
        PROP(next)
        PROP(sType)
    END

    CLASS(ChainedStructOut)
        PROP(next)
        PROP(sType)
    END

    CLASS(AdapterProperties)
        PROP(nextInChain)
        PROP(vendorID)
        PROP(deviceID)
        PROP(name)
        PROP(driverDescription)
        PROP(adapterType)
        PROP(backendType)
    END

    DESCRIPTOR(BindGroupEntry)
        PROP(binding)
        PROP(buffer)
        PROP(offset)
        PROP(size)
        PROP(sampler)
        PROP(textureView)
    END

    CLASS(BlendComponent)
        PROP(operation)
        PROP(srcFactor)
        PROP(dstFactor)
    END

    DESCRIPTOR(BufferBindingLayout)
        PROP(type)
        PROP(hasDynamicOffset)
        PROP(minBindingSize)
    END

    DESCRIPTOR(BufferDescriptor)
        PROP(label)
        PROP(usage)
        PROP(size)
        PROP(mappedAtCreation)
    END

    DESCRIPTOR(CommandBufferDescriptor)
        PROP(label)
    END

    DESCRIPTOR(CommandEncoderDescriptor)
        PROP(label)
    END

    DESCRIPTOR(CompilationMessage)
        PROP(message)
        PROP(type)
        PROP(lineNum)
        PROP(linePos)
        PROP(offset)
        PROP(length)
    END

    CLASS(ComputePassTimestampWrite)
        PROP(querySet)
        PROP(queryIndex)
        PROP(location)
    END

    DESCRIPTOR(ConstantEntry)
        PROP(key)
        PROP(value)
    END

    CLASS(Extent3D)
        PROP(width)
        PROP(height)
        PROP(depthOrArrayLayers)
    END

    DESCRIPTOR(InstanceDescriptor)
    END

    CLASS(Limits)
        PROP(maxTextureDimension1D)
        PROP(maxTextureDimension2D)
        PROP(maxTextureDimension3D)
        PROP(maxTextureArrayLayers)
        PROP(maxBindGroups)
        PROP(maxDynamicUniformBuffersPerPipelineLayout)
        PROP(maxDynamicStorageBuffersPerPipelineLayout)
        PROP(maxSampledTexturesPerShaderStage)
        PROP(maxSamplersPerShaderStage)
        PROP(maxStorageBuffersPerShaderStage)
        PROP(maxStorageTexturesPerShaderStage)
        PROP(maxUniformBuffersPerShaderStage)
        PROP(maxUniformBufferBindingSize)
        PROP(maxStorageBufferBindingSize)
        PROP(minUniformBufferOffsetAlignment)
        PROP(minStorageBufferOffsetAlignment)
        PROP(maxVertexBuffers)
        PROP(maxVertexAttributes)
        PROP(maxVertexBufferArrayStride)
        PROP(maxInterStageShaderComponents)
        PROP(maxComputeWorkgroupStorageSize)
        PROP(maxComputeInvocationsPerWorkgroup)
        PROP(maxComputeWorkgroupSizeX)
        PROP(maxComputeWorkgroupSizeY)
        PROP(maxComputeWorkgroupSizeZ)
        PROP(maxComputeWorkgroupsPerDimension)
    END

    DESCRIPTOR(MultisampleState)
        PROP(count)
        PROP(mask)
        PROP(alphaToCoverageEnabled)
    END

    DESCRIPTOR(PipelineLayoutDescriptor)
        LIST(bindGroupLayouts,bindGroupLayoutCount)
        PROP(label)
    END

    SUBCLASS(PrimitiveDepthClipControl, WGPUSType_PrimitiveDepthClipControl)
        PROP(unclippedDepth)
    END

    DESCRIPTOR(PrimitiveState)
        PROP(topology)
        PROP(stripIndexFormat)
        PROP(frontFace)
        PROP(cullMode)
    END

    DESCRIPTOR(QuerySetDescriptor)
        LIST(pipelineStatistics,pipelineStatisticsCount)
        PROP(label)
        PROP(type)
        PROP(count)
    END

    DESCRIPTOR(RenderBundleDescriptor)
        PROP(label)
    END

    DESCRIPTOR(RenderBundleEncoderDescriptor)
        LIST(colorFormats,colorFormatsCount)
        PROP(label)
        PROP(depthStencilFormat)
        PROP(depthReadOnly)
        PROP(stencilReadOnly)
        PROP(sampleCount)
    END

    CLASS(RenderPassDepthStencilAttachment)
        PROP(view)
        PROP(depthLoadOp)
        PROP(depthStoreOp)
        PROP(clearDepth)
        PROP(depthReadOnly)
        PROP(stencilLoadOp)
        PROP(stencilStoreOp)
        PROP(clearStencil)
        PROP(stencilReadOnly)
    END

    CLASS(RenderPassTimestampWrite)
        PROP(querySet)
        PROP(queryIndex)
        PROP(location)
    END

    DESCRIPTOR(RequestAdapterOptions)
        PROP(compatibleSurface)
        PROP(powerPreference)
        PROP(forceFallbackAdapter)
    END

    DESCRIPTOR(SamplerBindingLayout)
        PROP(type)
    END

    DESCRIPTOR(SamplerDescriptor)
        PROP(label)
        PROP(addressModeU)
        PROP(addressModeV)
        PROP(addressModeW)
        PROP(magFilter)
        PROP(minFilter)
        PROP(mipmapFilter)
        PROP(lodMinClamp)
        PROP(lodMaxClamp)
        PROP(compare)
        PROP(maxAnisotropy)
    END

    DESCRIPTOR(ShaderModuleDescriptor)
        PROP(label)
    END

    SUBCLASS(ShaderModuleSPIRVDescriptor, WGPUSType_ShaderModuleSPIRVDescriptor)
        PROP(codeSize)
        PROP(code)
    END

    SUBCLASS(ShaderModuleWGSLDescriptor, WGPUSType_ShaderModuleWGSLDescriptor)
        PROP(code)
    END

    CLASS(StencilFaceState)
        PROP(compare)
        PROP(failOp)
        PROP(depthFailOp)
        PROP(passOp)
    END

    DESCRIPTOR(StorageTextureBindingLayout)
        PROP(access)
        PROP(format)
        PROP(viewDimension)
    END

    DESCRIPTOR(SurfaceDescriptor)
        PROP(label)
    END

    SUBCLASS(SurfaceDescriptorFromCanvasHTMLSelector, WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector)
        PROP(selector)
    END

    SUBCLASS(SurfaceDescriptorFromMetalLayer, WGPUSType_SurfaceDescriptorFromMetalLayer)
        PROP(layer)
    END

    SUBCLASS(SurfaceDescriptorFromWindowsHWND, WGPUSType_SurfaceDescriptorFromWindowsHWND)
        PROP(hinstance)
        PROP(hwnd)
    END

    SUBCLASS(SurfaceDescriptorFromXlib, WGPUSType_SurfaceDescriptorFromXlib)
        PROP(display)
        PROP(window)
    END

    SUBCLASS(SurfaceDescriptorFromWaylandSurface, WGPUSType_SurfaceDescriptorFromWaylandSurface)
        PROP(display)
        PROP(surface)
    END

    SUBCLASS(SurfaceDescriptorFromAndroidNativeWindow, WGPUSType_SurfaceDescriptorFromAndroidNativeWindow)
        PROP(window)
    END

    DESCRIPTOR(SwapChainDescriptor)
        PROP(label)
        PROP(usage)
        PROP(format)
        PROP(width)
        PROP(height)
        PROP(presentMode)
    END

    DESCRIPTOR(TextureBindingLayout)
        PROP(sampleType)
        PROP(viewDimension)
        PROP(multisampled)
    END

    DESCRIPTOR(TextureDataLayout)
        PROP(offset)
        PROP(bytesPerRow)
        PROP(rowsPerImage)
    END

    DESCRIPTOR(TextureViewDescriptor)
        PROP(label)
        PROP(format)
        PROP(dimension)
        PROP(baseMipLevel)
        PROP(baseArrayLayer)
        PROP(aspect)
        PROP(mipLevelCount)
        PROP(arrayLayerCount)
    END

    CLASS(VertexAttribute)
        PROP(format)
        PROP(offset)
        PROP(shaderLocation)
    END

    DESCRIPTOR(BindGroupDescriptor)
        LIST(entries,entryCount)
        PROP(label)
        PROP(layout)
    END

    DESCRIPTOR(BindGroupLayoutEntry)
        PROP(binding)
        PROP(visibility)
        PROP(buffer)
        PROP(sampler)
        PROP(texture)
        PROP(storageTexture)
    END

    CLASS(BlendState)
        PROP(color)
        PROP(alpha)
    END

    DESCRIPTOR(CompilationInfo)
        LIST(messages,messageCount)
    END

    DESCRIPTOR(ComputePassDescriptor)
        LIST(timestampWrites,timestampWriteCount)
        PROP(label)
    END

    DESCRIPTOR(DepthStencilState)
        PROP(format)
        PROP(depthWriteEnabled)
        PROP(depthCompare)
        PROP(stencilFront)
        PROP(stencilBack)
        PROP(stencilReadMask)
        PROP(stencilWriteMask)
        PROP(depthBias)
        PROP(depthBiasSlopeScale)
        PROP(depthBiasClamp)
    END

    DESCRIPTOR(ImageCopyBuffer)
        PROP(layout)
        PROP(buffer)
    END

    DESCRIPTOR(ImageCopyTexture)
        PROP(texture)
        PROP(mipLevel)
        PROP(origin)
        PROP(aspect)
    END

    DESCRIPTOR(ProgrammableStageDescriptor)
        LIST(constants,constantCount)
        PROP(module)
        PROP(entryPoint)
    END

    CLASS(RenderPassColorAttachment)
        PROP(view)
        PROP(resolveTarget)
        PROP(loadOp)
        PROP(storeOp)
        PROP(clearColor)
    END

    DESCRIPTOR(RequiredLimits)
        PROP(limits)
    END

    CLASS(SupportedLimits)
        PROP(nextInChain)
        PROP(limits)
    END

    DESCRIPTOR(TextureDescriptor)
        PROP(label)
        PROP(usage)
        PROP(dimension)
        PROP(size)
        PROP(format)
        PROP(mipLevelCount)
        PROP(sampleCount)
    END

    CLASS(VertexBufferLayout)
        LIST(attributes,attributeCount)
        PROP(arrayStride)
        PROP(stepMode)
    END

    DESCRIPTOR(BindGroupLayoutDescriptor)
        LIST(entries,entryCount)
        PROP(label)
    END

    DESCRIPTOR(ColorTargetState)
        PROP(format)
        PROP(blend)
        PROP(writeMask)
    END

    DESCRIPTOR(ComputePipelineDescriptor)
        PROP(label)
        PROP(layout)
        PROP(compute)
    END

    DESCRIPTOR(DeviceDescriptor)
        LIST(requiredFeatures,requiredFeaturesCount)
        PROP(label)
        PROP(requiredLimits)
    END

    DESCRIPTOR(RenderPassDescriptor)
        LIST(colorAttachments,colorAttachmentCount)
        LIST(timestampWrites,timestampWriteCount)
        PROP(label)
        PROP(depthStencilAttachment)
        PROP(occlusionQuerySet)
    END

    DESCRIPTOR(VertexState)
        LIST(constants,constantCount)
        LIST(buffers,bufferCount)
        PROP(module)
        PROP(entryPoint)
    END

    DESCRIPTOR(FragmentState)
        LIST(constants,constantCount)
        LIST(targets,targetCount)
        PROP(module)
        PROP(entryPoint)
    END

    DESCRIPTOR(RenderPipelineDescriptor)
        PROP(label)
        PROP(layout)
        PROP(vertex)
        PROP(primitive)
        PROP(depthStencil)
        PROP(multisample)
        PROP(fragment)
    END


    #undef CLASS
    #undef SUBCLASS
    #undef DESCRIPTOR
    #undef END
    #undef PROP
} // end wgpu namespace
