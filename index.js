const fs = require("fs");
const process = require("process");

// Get the mode from command-line arguments
const mode = process.argv[2];

if (mode === "cache") {
    // Cache user.hpp to cache-user.hpp
    fs.writeFileSync("cache-user.hpp", fs.readFileSync("src/user.hpp"));
    process.exit(0);
}

if (mode === "re-cache") {
    // Restore cache-user.hpp to src/user.hpp
    fs.writeFileSync("src/user.hpp", fs.readFileSync("cache-user.hpp"));
    fs.unlinkSync("cache-user.hpp");
    process.exit(0);
}

if (mode === "sender" || mode === "receiver") {
    // Determine whether we're in sender mode
    const isSending = mode === "sender";

    const fileContent = `#pragma once
// Don't edit this file
#define IS_SENDING ${isSending ? "true" : "false"}
`;

    fs.writeFileSync("src/user.hpp", fileContent, "ascii");
    process.exit(0);
}

// Invalid mode
console.error("Invalid mode. Use 'cache', 're-cache', 'sender', or 'receiver'.");
process.exit(1);