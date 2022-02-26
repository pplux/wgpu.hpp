# [wgpu.hpp](wgpu.hpp) a WebGPU header for C++17

If you are stuck on C++17 waiting for [C++20 Aggregate initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization) this header will help you use C++ chaining to achieve the same.


```cpp
wgpu::RenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(wgpu->device,
        wgpu::RenderPipelineDescriptor()
            .label("Render Pipeline")
            .layout(wgpuDeviceCreatePipelineLayout(wgpu->device,
                wgpu::PipelineLayoutDescriptor()
                    .label("pipeline layout")
            ))
            .vertex(wgpu::VertexState()
                .module(shader)
                .entryPoint("vs_main")
            )
            .primitive(wgpu::PrimitiveState()
                .topology(WGPUPrimitiveTopology_TriangleList)
                .stripIndexFormat(WGPUIndexFormat_Undefined)
                .frontFace(WGPUFrontFace_CCW)
                .cullMode(WGPUCullMode_None)
            )
            .multisample(wgpu::MultisampleState()
                .count(1)
                .mask(~0)
                .alphaToCoverageEnabled(false)
            )
            .fragment(wgpu::FragmentState()
                .module(shader)
                .entryPoint("fs_main")
                .targets(
                    { wgpu::ColorTargetState()
                        .format(swapChainFormat)
                        .writeMask(WGPUColorWriteMask_All)
                        .blend(wgpu::BlendState()
                            .color(wgpu::BlendComponent()
                                .dstFactor(WGPUBlendFactor_Zero)
                                .srcFactor(WGPUBlendFactor_One)
                                .operation(WGPUBlendOperation_Add))
                            .alpha(wgpu::BlendComponent()
                                .dstFactor(WGPUBlendFactor_Zero)
                                .srcFactor(WGPUBlendFactor_One)
                                .operation(WGPUBlendOperation_Add)))
                    })
            ));
```

## Notes:
  * WGPUClass has the equivalent wgpu::Class
  * targets and targetCount like memember are translated into a single targets { ... } and the count is inferred from there
  * Some chains are automatically derived
      ``` 
           WGPUShaderModule shader = wgpuDeviceCreateShaderModule(wgpu->device, wgpu::ShaderModuleDescriptor()
              .label("shader")
              .nextInChain(wgpu::ShaderModuleWGSLDescriptor()
                      .code(shaderCode)
              )); 
      ```
  * There is an automatic conversion from pointers/references to the appropiate pointer for WebGPU
  * *WARNING* in C++ temporal objects are only valid within the calling expression, so you should only use this approach inside the function call:
      ```
            wgpuCall(device, wgpu::Object().setA(...).setB(...).setC(...));
      ```
      
## Generation
   The current [wgpu.hpp](wgpu.hpp) header is generated from the reference [wgpu-native](https://github.com/webgpu-native/webgpu-headers) but you can generate your own by running [generate.py](generate.py) as:
     ```./generate.py inputHeader.h new-webgpu.hpp```
