#!/usr/bin/python3

import argparse
import re

STypes = {}
DoNotGenerate = ["Color", "Origin3D"]

template_begin = """
//-----------------------------------
// https://github.com/pplux/wgpu.hpp
//-----------------------------------
#pragma once

#ifndef WEBGPU_H_
#error "You must include the WEBGPU header before this one"
#endif

#include <type_traits>

namespace wgpu {

    #define BASIC_CLASS(Type) \\
        struct Type : public WGPU ## Type{ \\
            typedef Type S; /* S == Self */ \\
            typedef WGPU ## Type W; /* W == WGPU Type */ \\
            operator const W*() const { return this; } \\
    
    #define CLASS(Type) \\
        BASIC_CLASS(Type) \\
        Type() : W() {} \\

    #define SUBCLASS(Type, WGPUSType_value) \\
        BASIC_CLASS(Type) \\
        Type() : W({nullptr, WGPUSType_value}) {} \\

    #define DESCRIPTOR(Type) \\
        BASIC_CLASS(Type) \\
        Type() : W() {} \\
        template<class T> \\
        S& nextInChain(const T *obj) \\
        { \\
            W::nextInChain = (const WGPUChainedStruct*) &(obj->chain); \\
            return *this; \\
        }\\
        template<class T> \\
        S& nextInChain(const T &obj) { return nextInChain(&obj); }


    #define PROP(Name) \\
        S& Name(decltype(W::Name) arg) { W::Name = arg; return *this; }\\

    #define LIST(List, Count) \\
        template<size_t N> \\
        S& List(std::remove_cv_t<std::remove_pointer_t<decltype(W::List)>> const (&args)[N]) { \\
            W::Count = (decltype(W::Count)) N; \\
            W::List = args; \\
            return *this; \\
        } \\

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
"""
template_end = """
    #undef CLASS
    #undef SUBCLASS
    #undef DESCRIPTOR
    #undef END
    #undef PROP
} // end wgpu namespace
"""

def produceClass(name, it):
    x = next(it)
    regular_properties = []
    count_properties = []
    list_properties = {}
    is_subclass = False
    out = f"    CLASS({name})\n"
    if name in STypes:
        out = f"    SUBCLASS({name}, {STypes[name]})\n"
        is_subclass = True
    while(not re.search(".*}",x)):
        if (re.search("WGPUChainedStruct .* nextInChain;",x)):
            out = f"    DESCRIPTOR({name})\n"
        else:
            match = re.search("(\w+);",x)
            if match:
                p = match.group(1);
                if p[-5:] == "Count":
                    count_properties.append(p)
                else:
                    regular_properties.append(p)
        x = next(it)

    if is_subclass:
        regular_properties.remove("chain")
        
    for i in count_properties:
        # entri|ies -> entr|yCount
        # colorFormat|s -> colorFormat|sCount
        prefix = i[:-6]
        for r in regular_properties:
            if r.find(prefix) == 0:
                list_properties[r] = i
                regular_properties.remove(r)
                break
    for k in list_properties:
        out = out + f"        LIST({k},{list_properties[k]})\n"
    for p in regular_properties:
        out = out + f"        PROP({p})\n"
    out = out + "    END\n\n"
    return out

def process(file):
    with open(file, 'r') as f:
        lines = f.readlines()
    it = iter(lines)
    result = ""
    typedefs = ""
    while (x := next(it, None)) is not None:
        match = re.search("struct *WGPU(\w+) *{", x)
        if (match):
            struct_name = match.group(1)
            if struct_name not in DoNotGenerate:
                result = result + produceClass(struct_name, it)
            continue
        match = re.search("typedef struct .*WGPU(\w+);", x)
        if (match):
            s = match.group(1)
            typedefs = typedefs + f"    typedef WGPU{s} {s};\n"
            continue
        match = re.search("WGPUSType_(\w+)", x)
        if (match):
            STypes[match.group(1)] = match.group(0)
            continue
    return typedefs + "\n" + result

def generateOutput(file, bindings):
    with open(file, 'w') as f:
        f.write(template_begin)
        f.write(bindings)
        f.write(template_end)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="wgpu++ binding generator, for example use it as: './generate.py ../deps/wgpu-native/ffi/webgpu-headers/webgpu.h ../include/wgpu++.h'")
    parser.add_argument("input")
    parser.add_argument("output")
    args = parser.parse_args() 
    bindings = process(args.input)
    generateOutput(args.output, bindings)
    
