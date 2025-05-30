const std = @import("std");
const def = @import("zig-src/wrapper/definition.zig");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    const cpp_flags = &.{
        "-std=c++11",
        "-fno-rtti",
    };

    const module = b.addModule("airwindows", .{
        .root_source_file = b.path("zig-src/root.zig"),
        .target = target,
        .optimize = optimize,
        .link_libc = true,
        .link_libcpp = true,
    });
    const audioeffectx_h = b.path("zig-src/shim/");
    const audioeffectx_cpp = b.path("zig-src/shim/audioeffect.cpp");
    module.addIncludePath(audioeffectx_h.dirname());
    module.addCSourceFile(.{
        .file = audioeffectx_cpp,
        .language = .cpp,
        .flags = cpp_flags,
    });

    const T_name = "Acceleration";
    const T_UPPER = std.ascii.allocUpperString(b.allocator, T_name) catch unreachable;
    const replace_tool = b.addExecutable(.{
        .name = "replace tool",
        .root_source_file = b.path("zig-src/wrapper/replacer-tool.zig"),
        .target = target,
        .optimize = optimize,
    });
    @setEvalBranchQuota(10000);
    inline for (def.complete_index) |fx_name| {
        const dir_sub_path = def.plugin_base_path ++ fx_name;
        const cpp_file = dir_sub_path ++ "/" ++ fx_name ++ ".cpp";
        const replaye_effect_cpp_run = b.addRunArtifact(replace_tool);
        replaye_effect_cpp_run.addArg(cpp_file);
        const modified_effect_cpp_path = replaye_effect_cpp_run.addOutputFileArg(fx_name ++ ".cpp");
        replaye_effect_cpp_run.addArg("AudioEffect* createEffectInstance(audioMasterCallback audioMaster)");
        replaye_effect_cpp_run.addArg("static AudioEffect* createEffectInstance(audioMasterCallback audioMaster)");

        const effec_proc_cpp = dir_sub_path ++ "/" ++ fx_name ++ "Proc.cpp";

        const replace_c_api_header_run = b.addRunArtifact(replace_tool);
        replace_c_api_header_run.addArg("zig-src/wrapper/Acceleration_c_api.h");
        const header_file_auto_gen = replace_c_api_header_run.addOutputFileArg(fx_name ++ "_c_api.h");
        const T_name_replace = fx_name;
        replace_c_api_header_run.addArg(T_name);
        replace_c_api_header_run.addArg(T_name_replace);
        replace_c_api_header_run.addArg(T_UPPER);
        replace_c_api_header_run.addArg(std.ascii.allocUpperString(b.allocator, fx_name) catch unreachable);

        const replace_c_api_cpp_run = b.addRunArtifact(replace_tool);
        replace_c_api_cpp_run.addArg("zig-src/wrapper/Acceleration_c_api.cpp");
        const cpp_file_auto_gen = replace_c_api_cpp_run.addOutputFileArg(fx_name ++ "_c_api.cpp");
        replace_c_api_cpp_run.addArg(T_name);
        replace_c_api_cpp_run.addArg(T_name_replace);

        const translate_c = b.addTranslateC(.{
            .optimize = optimize,
            .root_source_file = header_file_auto_gen,
            .target = target,
            .link_libc = true,
            .use_clang = true,
        });

        translate_c.step.dependOn(&replace_c_api_header_run.step);
        translate_c.step.dependOn(&replace_c_api_cpp_run.step);
        translate_c.step.dependOn(&replaye_effect_cpp_run.step);

        const cmod = translate_c.createModule();
        cmod.addIncludePath(audioeffectx_h);
        cmod.addIncludePath(header_file_auto_gen.dirname());
        cmod.addIncludePath(b.path(dir_sub_path));

        inline for (&.{
            modified_effect_cpp_path,
            b.path(effec_proc_cpp),
            cpp_file_auto_gen,
        }) |cxx_file| {
            cmod.addCSourceFile(.{ .file = cxx_file, .language = .cpp, .flags = cpp_flags });
        }
        cmod.link_libc = true;
        cmod.link_libcpp = true;
        module.addImport(fx_name, cmod);
    }

    const test_c = b.addTest(.{
        .optimize = optimize,
        .target = target,
        .root_module = module,
    });
    const test_run = b.addRunArtifact(test_c);
    const test_step = b.step("test", "Run unit tests");
    test_step.dependOn(&test_run.step);
}
