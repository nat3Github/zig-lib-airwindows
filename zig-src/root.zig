const std = @import("std");
// const c = @cImport({
//     @cInclude("Acceleration_c_api.h");
// });
const c = @import("Acceleration");

test "main" {
    const allocator = std.testing.allocator;

    var plugin_ptr: ?*c.Acceleration = null;
    errdefer {
        if (plugin_ptr) |p| {
            c.Acceleration_uninit(p);
        }
    }

    plugin_ptr = c.Acceleration_init(null);
    std.log.warn("Acceleration plugin initialized.\n", .{});
    std.log.warn("constants: {} {} {} {}", .{
        c.Acceleration_KNUM_INPUTS,
        c.Acceleration_KNUM_OUTPUTS,
        c.Acceleration_KNUM_PROGRAMS,
        c.Acceleration_KNUM_PARAMETERS,
    });

    const sample_frames: c_int = 64;

    const input_data_left = try allocator.alloc(f32, sample_frames);
    defer allocator.free(input_data_left);
    const input_data_right = try allocator.alloc(f32, sample_frames);
    defer allocator.free(input_data_right);

    const output_data_left = try allocator.alloc(f32, sample_frames);
    defer allocator.free(output_data_left);
    const output_data_right = try allocator.alloc(f32, sample_frames);
    defer allocator.free(output_data_right);

    for (0..sample_frames) |i| {
        input_data_left[i] = @as(f32, @floatFromInt(i)) / @as(f32, @floatFromInt(sample_frames));
        input_data_right[i] = 1.0 - (@as(f32, @floatFromInt(i)) / @as(f32, @floatFromInt(sample_frames)));
    }

    var inputs_array: [2]*f32 = undefined;
    inputs_array[0] = @ptrCast(input_data_left.ptr);
    inputs_array[1] = @ptrCast(input_data_right.ptr);
    var outputs_array: [2]*f32 = undefined;
    outputs_array[0] = @ptrCast(output_data_left.ptr);
    outputs_array[1] = @ptrCast(output_data_right.ptr);

    const c_inputs: [*c][*c]f32 = @ptrCast(&inputs_array);
    const c_outputs: [*c][*c]f32 = @ptrCast(&outputs_array);

    std.log.warn("Processing {d} sample frames...\n", .{sample_frames});
    if (plugin_ptr) |p| {
        c.Acceleration_process_replacing(p, c_inputs, c_outputs, sample_frames);
    } else {
        return error.PluginNotInitialized;
    }
    std.log.warn("Processing complete.\n", .{});

    std.log.warn("\n--- Processed Output Samples (first 5) ---\n", .{});
    for (0..5) |i| {
        std.log.warn("Sample {d}: Left = {d:.4}, Right = {d:.4}\n", .{
            i,
            output_data_left[i],
            output_data_right[i],
        });
    }

    std.log.warn("\n--- Processed Output Samples (last 5) ---\n", .{});
    for (sample_frames - 5..sample_frames) |i| {
        std.log.warn("Sample {d}: Left = {d:.4}, Right = {d:.4}\n", .{
            i,
            output_data_left[i],
            output_data_right[i],
        });
    }

    std.log.warn("\nTest finished.\n", .{});
}
