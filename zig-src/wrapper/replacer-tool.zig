const std = @import("std");
const def = @import("definition.zig"); // Assuming this defines `def.replace`

pub fn main() !void {
    // Get command-line arguments.
    // The first argument is the executable's path.
    var args = std.process.args();
    const executable_name = args.next().?; // Store the executable name for usage message

    const input_file_path_arg = args.next();
    const replacement_string_arg = args.next();
    const output_file_path_arg = args.next(); // <--- NEW: Third argument for output file

    // Check if the correct number of arguments is provided.
    // We now expect 3 arguments after the executable name.
    if (input_file_path_arg == null or replacement_string_arg == null or output_file_path_arg == null or args.next() != null) {
        std.log.err("Usage: {s} <input_file_path> <replacement_string> <output_file_path>\n", .{executable_name});
        return error.InputError;
    }

    const input_file_path = input_file_path_arg.?;
    const replacement_string = replacement_string_arg.?;
    const output_file_path = output_file_path_arg.?; // <--- Store the output file path

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    std.log.info("Opening input file: {s}", .{input_file_path});

    // Open the input file for reading.
    const input_file = try std.fs.cwd().openFile(input_file_path, .{ .mode = .read_only });
    defer input_file.close();

    // Read the entire content of the file into memory.
    const file_content = try input_file.readToEndAlloc(allocator, std.math.maxInt(usize));
    defer allocator.free(file_content);

    std.log.info("Input file read successfully. Performing replacements...", .{});

    // Define the string to be replaced (from definition.zig).
    const search_string = def.replace; // Assuming def.replace is a `[]const u8` or `[]u8`

    // Perform the replacement.
    // `std.mem.replaceOwned` is good as it ensures the new memory is owned by `allocator`.
    const modified_content = try std.mem.replaceOwned(u8, allocator, file_content, search_string, replacement_string);
    defer allocator.free(modified_content);

    std.log.info("Replacements complete. Writing to output file: {s}", .{output_file_path});

    // --- NEW: Open/Create the output file for writing ---
    // `createFile` will create the file if it doesn't exist, or truncate it if it does.
    const output_file = try std.fs.cwd().createFile(output_file_path, .{ .read = true });
    defer output_file.close(); // Ensure the output file is closed

    // Get a writer for the output file.
    const output_writer = output_file.writer();

    // Write the modified content to the output file.
    try output_writer.writeAll(modified_content);

    std.log.info("Operation finished successfully.\n", .{});
}
