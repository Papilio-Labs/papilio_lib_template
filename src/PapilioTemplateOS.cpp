#include "PapilioTemplateOS.h"

#ifdef ENABLE_PAPILIO_OS

// Singleton instance for static callbacks
PapilioTemplateOS* PapilioTemplateOS::_instance = nullptr;

PapilioTemplateOS::PapilioTemplateOS(PapilioTemplate* device)
    : _device(device) {
    _instance = this;
    registerCommands();
}

void PapilioTemplateOS::setDevice(PapilioTemplate* device) {
    _device = device;
}

void PapilioTemplateOS::registerCommands() {
    // Register all commands with the "template" module prefix
    PapilioOS.registerCommand("template", "tutorial", handleTutorial, 
                              "Interactive step-by-step tutorial");
    PapilioOS.registerCommand("template", "help", handleHelp, 
                              "Show all available commands");
    PapilioOS.registerCommand("template", "status", handleStatus, 
                              "Display device status");
    PapilioOS.registerCommand("template", "enable", handleEnable, 
                              "Enable the device");
    PapilioOS.registerCommand("template", "disable", handleDisable, 
                              "Disable the device");
    PapilioOS.registerCommand("template", "write", handleWrite, 
                              "Write data to device: template write <value>");
    PapilioOS.registerCommand("template", "read", handleRead, 
                              "Read data from device");
    PapilioOS.registerCommand("template", "reset", handleReset, 
                              "Reset the device");
}

// Command Handlers

void PapilioTemplateOS::handleTutorial(int argc, char** argv) {
    runTutorial();
}

void PapilioTemplateOS::handleHelp(int argc, char** argv) {
    Serial.println("\nPapilioTemplate Commands:");
    Serial.println("  template tutorial       - Interactive step-by-step tutorial");
    Serial.println("  template status         - Display device status");
    Serial.println("  template enable         - Enable the device");
    Serial.println("  template disable        - Disable the device");
    Serial.println("  template write <value>  - Write data to device (hex or decimal)");
    Serial.println("  template read           - Read data from device");
    Serial.println("  template reset          - Reset the device");
    Serial.println("\nFor detailed guidance, run: template tutorial");
}

void PapilioTemplateOS::handleStatus(int argc, char** argv) {
    if (!_instance || !_instance->_device) {
        Serial.println("Error: Device not initialized");
        return;
    }

    uint8_t status = _instance->_device->getStatus();
    
    Serial.println("\nDevice Status:");
    Serial.printf("  Status Register: 0x%02X\n", status);
    Serial.printf("  Ready: %s\n", (status & 0x01) ? "Yes" : "No");
    Serial.printf("  Error: %s\n", (status & 0x02) ? "Yes" : "No");
    Serial.printf("  Base Address: 0x%04X\n", _instance->_device->getBaseAddress());
}

void PapilioTemplateOS::handleEnable(int argc, char** argv) {
    if (!_instance || !_instance->_device) {
        Serial.println("Error: Device not initialized");
        return;
    }

    _instance->_device->setEnable(true);
    Serial.println("Device enabled");
}

void PapilioTemplateOS::handleDisable(int argc, char** argv) {
    if (!_instance || !_instance->_device) {
        Serial.println("Error: Device not initialized");
        return;
    }

    _instance->_device->setEnable(false);
    Serial.println("Device disabled");
}

void PapilioTemplateOS::handleWrite(int argc, char** argv) {
    if (!_instance || !_instance->_device) {
        Serial.println("Error: Device not initialized");
        return;
    }

    if (argc < 2) {
        Serial.println("Usage: template write <value>");
        Serial.println("  value: decimal or hex (0x prefix)");
        return;
    }

    // Parse value (supports decimal and hex)
    uint32_t value;
    if (strncmp(argv[1], "0x", 2) == 0 || strncmp(argv[1], "0X", 2) == 0) {
        value = strtoul(argv[1], nullptr, 16);
    } else {
        value = strtoul(argv[1], nullptr, 10);
    }

    _instance->_device->writeData(value);
    Serial.printf("Wrote 0x%08X to device\n", value);
}

void PapilioTemplateOS::handleRead(int argc, char** argv) {
    if (!_instance || !_instance->_device) {
        Serial.println("Error: Device not initialized");
        return;
    }

    uint32_t value = _instance->_device->readData();
    Serial.printf("Read: 0x%08X (%u)\n", value, value);
}

void PapilioTemplateOS::handleReset(int argc, char** argv) {
    if (!_instance || !_instance->_device) {
        Serial.println("Error: Device not initialized");
        return;
    }

    _instance->_device->reset();
    Serial.println("Device reset");
}

// Tutorial Implementation

void PapilioTemplateOS::runTutorial() {
    Serial.println("\n========================================");
    Serial.println("   PapilioTemplate Interactive Tutorial");
    Serial.println("========================================\n");

    Serial.println("This tutorial will guide you through using the PapilioTemplate library.");
    Serial.println("Type 'exit' at any prompt to quit the tutorial.\n");

    delay(1000);

    // Check if device is initialized
    if (!_instance || !_instance->_device) {
        Serial.println("Note: Device not initialized. Tutorial will show commands anyway.");
        Serial.println("In a real application, you would initialize the device in setup():\n");
        Serial.println("  PapilioTemplate myDevice;");
        Serial.println("  myDevice.begin();\n");
        delay(1000);
    }

    // Step 1: Check device status
    if (!tutorialStep(1, "Check device status", "template status")) {
        return;
    }

    // Step 2: Enable device
    if (!tutorialStep(2, "Enable the device", "template enable")) {
        return;
    }

    // Step 3: Write data
    if (!tutorialStep(3, "Write data to device", "template write 0x1234")) {
        return;
    }

    // Step 4: Read data
    if (!tutorialStep(4, "Read data from device", "template read")) {
        return;
    }

    // Step 5: Disable device
    if (!tutorialStep(5, "Disable the device", "template disable")) {
        return;
    }

    Serial.println("\n========================================");
    Serial.println("   Tutorial Complete!");
    Serial.println("========================================\n");

    Serial.println("You've learned the basic commands for PapilioTemplate.");
    Serial.println("For more information, see the README.md or run: template help\n");
}

bool PapilioTemplateOS::tutorialStep(int stepNum, const char* description, const char* command) {
    Serial.printf("\nStep %d: %s\n", stepNum, description);
    Serial.printf("Try the command: %s\n", command);
    Serial.print("\nPress Enter when ready (or type 'exit' to quit): ");

    // Wait for user input
    while (!Serial.available()) {
        delay(10);
    }

    // Read the line
    String input = Serial.readStringUntil('\n');
    input.trim();

    Serial.println();  // New line after input

    // Check for exit
    if (input.equalsIgnoreCase("exit") || input.equalsIgnoreCase("quit")) {
        Serial.println("Tutorial exited.");
        return false;
    }

    // Show the command being executed
    Serial.printf("> %s\n", command);

    // Parse and execute the command
    // Note: This is a simplified version - real implementation would
    // use the actual command parser from PapilioOS
    char cmdCopy[128];
    strncpy(cmdCopy, command, sizeof(cmdCopy) - 1);
    cmdCopy[sizeof(cmdCopy) - 1] = '\0';

    char* argv[10];
    int argc = 0;
    char* token = strtok(cmdCopy, " ");
    while (token && argc < 10) {
        argv[argc++] = token;
        token = strtok(nullptr, " ");
    }

    // Route to appropriate handler
    if (argc >= 2) {
        if (strcmp(argv[1], "status") == 0) {
            handleStatus(argc - 1, &argv[1]);
        } else if (strcmp(argv[1], "enable") == 0) {
            handleEnable(argc - 1, &argv[1]);
        } else if (strcmp(argv[1], "disable") == 0) {
            handleDisable(argc - 1, &argv[1]);
        } else if (strcmp(argv[1], "write") == 0) {
            handleWrite(argc - 1, &argv[1]);
        } else if (strcmp(argv[1], "read") == 0) {
            handleRead(argc - 1, &argv[1]);
        } else if (strcmp(argv[1], "reset") == 0) {
            handleReset(argc - 1, &argv[1]);
        }
    }

    delay(1000);
    return true;
}

#endif // ENABLE_PAPILIO_OS
