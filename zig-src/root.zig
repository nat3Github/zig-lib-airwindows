const std = @import("std");
pub fn slice_to_cPtr_array(T: type, size: comptime_int, slice: [][]T) [size]?*T {
    var c_inputs_array: [size]?*T = undefined;
    for (0..slice.len) |i| {
        c_inputs_array[i] = @ptrCast(slice[i].ptr);
    }
    return c_inputs_array;
}

pub fn wrap(comptime effect_name: []const u8, comptime cmodule: type) type {
    return struct {
        const Self = @This();
        c_handle: *@field(cmodule, effect_name),

        pub fn knum_inputs(self: *Self) u16 {
            _ = self;
            const num = @field(cmodule, effect_name ++ "_KNUM_INPUTS");
            return @intCast(num);
        }
        pub fn knum_parameters(self: *Self) u16 {
            _ = self;
            const num = @field(cmodule, effect_name ++ "_KNUM_PARAMETERS");
            return @intCast(num);
        }
        pub fn knum_programs(self: *Self) u16 {
            _ = self;
            const num = @field(cmodule, effect_name ++ "_KNUM_PROGRAMS");
            return @intCast(num);
        }
        pub fn knum_outputs(self: *Self) u16 {
            _ = self;
            const num = @field(cmodule, effect_name ++ "_KNUM_OUTPUTS");
            return @intCast(num);
        }

        pub fn init() !Self {
            const handle = @field(cmodule, effect_name ++ "_init")(null);
            if (handle == null) {
                return error.PluginInitializationFailed;
            }
            return Self{ .c_handle = handle.? };
        }

        pub fn deinit(self: *Self) void {
            @field(cmodule, effect_name ++ "_uninit")(self.c_handle);
        }

        /// NOTE: directly casting slices donst work since a slice has a length field and a *C pointer does not
        pub fn process_replacing(self: *Self, inputs: [*c][*c]f32, outputs: [*c][*c]f32, sample_frames: usize) void {
            @field(cmodule, effect_name ++ "_process_replacing")(
                self.c_handle,
                inputs,
                outputs,
                @intCast(sample_frames),
            );
        }
        /// NOTE: directly casting slices donst work since a slice has a length field and a *C pointer does not
        pub fn process_double_replacing(self: *Self, inputs: [*c][*c]f32, outputs: [*c][*c]f32, sample_frames: usize) void {
            @field(cmodule, effect_name ++ "_process_double_replacing")(
                self.c_handle,
                inputs,
                outputs,
                @intCast(sample_frames),
            );
        }

        pub fn get_parameter(self: *Self, index: i32) f32 {
            return @field(cmodule, effect_name ++ "_get_parameter")(self.c_handle, index);
        }

        pub fn set_parameter(self: *Self, index: i32, value: f32) void {
            @field(cmodule, effect_name ++ "_set_parameter")(self.c_handle, index, value);
        }
    };
}

pub const Acceleration = wrap("Acceleration", @import("Acceleration"));

test "Acceleration plugin wrapper test" {
    const allocator = std.testing.allocator;
    var plugin = try Acceleration.init();
    defer plugin.deinit();
    std.log.warn("Acceleration plugin initialized via wrapper.\n", .{});

    std.log.warn("Constants: Inputs: {d}, Outputs: {d}, Programs: {d}, Parameters: {d}\n", .{
        plugin.knum_inputs(),
        plugin.knum_outputs(),
        plugin.knum_programs(),
        plugin.knum_parameters(),
    });

    const sample_frames: i32 = 64;

    const input_data_left_f32 = try allocator.alloc(f32, @as(usize, @intCast(sample_frames)));
    defer allocator.free(input_data_left_f32);
    const input_data_right_f32 = try allocator.alloc(f32, @as(usize, @intCast(sample_frames)));
    defer allocator.free(input_data_right_f32);

    const output_data_left_f32 = try allocator.alloc(f32, @as(usize, @intCast(sample_frames)));
    defer allocator.free(output_data_left_f32);
    const output_data_right_f32 = try allocator.alloc(f32, @as(usize, @intCast(sample_frames)));
    defer allocator.free(output_data_right_f32);

    for (0..@as(usize, @intCast(sample_frames))) |i| {
        input_data_left_f32[i] = @as(f32, @floatFromInt(i)) / @as(f32, @floatFromInt(sample_frames));
        input_data_right_f32[i] = 1.0 - (@as(f32, @floatFromInt(i)) / @as(f32, @floatFromInt(sample_frames)));
    }

    const inputs_f32: []const []f32 = &.{ input_data_left_f32, input_data_right_f32 };
    const outputs_f32: []const []f32 = &.{ output_data_left_f32, output_data_right_f32 };
    var inp_c_arr = slice_to_cPtr_array(f32, 2, @constCast(inputs_f32));
    var outp_c_arr = slice_to_cPtr_array(f32, 2, @constCast(outputs_f32));

    std.log.warn("Processing {d} sample frames (float) via wrapper...\n", .{sample_frames});
    plugin.process_replacing(
        &inp_c_arr,
        &outp_c_arr,
        sample_frames,
    );
    std.log.warn("Float processing complete.\n", .{});

    std.log.warn("\n--- Processed Output Samples (float, first 5) ---\n", .{});
    for (0..5) |i| {
        std.log.warn("Sample {d}: Left = {d:.4}, Right = {d:.4}\n", .{
            i,
            output_data_left_f32[i],
            output_data_right_f32[i],
        });
    }

    std.log.warn("\n--- Processed Output Samples (float, last 5) ---\n", .{});
    for (@as(usize, @intCast(sample_frames)) - 5..@as(usize, @intCast(sample_frames))) |i| {
        std.log.warn("Sample {d}: Left = {d:.4}, Right = {d:.4}\n", .{
            i,
            output_data_left_f32[i],
            output_data_right_f32[i],
        });
    }
    std.log.warn("\nTest finished successfully.\n", .{});
}
