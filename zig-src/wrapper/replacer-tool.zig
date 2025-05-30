const std = @import("std");

pub fn main() !void {
    var args = std.process.args();
    const executable_name = args.next().?;

    const input_file_path_arg = args.next();
    const output_file_path_arg = args.next();

    // Check for minimum arguments: executable + input + output
    if (input_file_path_arg == null or output_file_path_arg == null) {
        std.log.err("Usage: {s} <input_file_path> <output_file_path> [<search_string> <replacement_string> ...]\n", .{executable_name});
        return error.InputError;
    }

    const input_file_path = input_file_path_arg.?;
    const output_file_path = output_file_path_arg.?;

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    var arena = std.heap.ArenaAllocator.init(gpa.allocator());
    defer arena.deinit();
    const alloc = arena.allocator();

    std.log.info("Opening input file: {s}", .{input_file_path});
    const input_file = try std.fs.cwd().openFile(input_file_path, .{ .mode = .read_only });
    defer input_file.close();

    var current_content = try input_file.readToEndAlloc(alloc, std.math.maxInt(usize));

    while (args.next()) |search_string_arg| {
        const replacement_string_arg = args.next();
        if (replacement_string_arg == null) {
            std.log.err("Error: Missing replacement string for search string '{s}'\n", .{search_string_arg});
            return error.InputError;
        }

        const search_string = search_string_arg;
        const replacement_string = replacement_string_arg.?;

        std.log.info("Replacing '{s}' with '{s}'", .{ search_string, replacement_string });

        current_content = try std.mem.replaceOwned(u8, alloc, current_content, search_string, replacement_string);
    }

    const output_file = try std.fs.cwd().createFile(output_file_path, .{ .read = true });
    defer output_file.close();

    const output_writer = output_file.writer();

    try output_writer.writeAll(current_content);
    std.log.info("All replacements complete. Writing to output file: {s}", .{output_file_path});
}
