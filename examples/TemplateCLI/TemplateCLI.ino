/*
 * PapilioTemplate CLI Example
 * 
 * This example demonstrates both the programmatic API and the CLI interface
 * for the PapilioTemplate library.
 * 
 * Hardware Requirements:
 * - Papilio board (Retrocade or Synth)
 * - FPGA programmed with papilio_template module
 * - ESP32 connected via SPI to FPGA
 * 
 * Features demonstrated:
 * - Device initialization
 * - Register read/write operations
 * - Status monitoring
 * - Interactive CLI commands (when ENABLE_PAPILIO_OS is defined)
 */

#include <Arduino.h>
#include <PapilioTemplate.h>

// Enable CLI interface by uncommenting:
// #define ENABLE_PAPILIO_OS

#ifdef ENABLE_PAPILIO_OS
#include <PapilioOS.h>
#include <PapilioTemplateOS.h>
#endif

// Create device instance
// Base address 0x1000 (adjust if your module is at different address)
PapilioTemplate myDevice(0x1000);

#ifdef ENABLE_PAPILIO_OS
// Create OS plugin instance (auto-registers with papilio_os)
PapilioTemplateOS myDeviceOS(&myDevice);
#endif

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);  // Wait for serial connection
    }
    
    Serial.println("\n========================================");
    Serial.println("  PapilioTemplate Example");
    Serial.println("========================================\n");
    
#ifdef ENABLE_PAPILIO_OS
    Serial.println("Mode: CLI Enabled");
    Serial.println("Type 'help' for available commands");
    Serial.println("Type 'template tutorial' for interactive guide\n");
    
    // Initialize PapilioOS
    PapilioOS.begin();
#else
    Serial.println("Mode: Programmatic API only");
    Serial.println("To enable CLI, define ENABLE_PAPILIO_OS\n");
#endif
    
    // Initialize device
    Serial.println("Initializing device...");
    if (myDevice.begin()) {
        Serial.println("Device initialized successfully!");
    } else {
        Serial.println("ERROR: Device initialization failed!");
        Serial.println("Check FPGA programming and connections");
        return;
    }
    
    // Display device information
    Serial.printf("Base Address: 0x%04X\n", myDevice.getBaseAddress());
    Serial.printf("Device Ready: %s\n\n", myDevice.isReady() ? "Yes" : "No");
    
#ifndef ENABLE_PAPILIO_OS
    // If CLI is not enabled, run programmatic examples
    runProgrammaticExamples();
#endif
}

void loop() {
#ifdef ENABLE_PAPILIO_OS
    // Update PapilioOS to process CLI commands
    PapilioOS.update();
#else
    // In programmatic mode, run continuous examples
    delay(5000);
    runProgrammaticExamples();
#endif
}

#ifndef ENABLE_PAPILIO_OS
// Programmatic API examples
void runProgrammaticExamples() {
    Serial.println("\n--- Programmatic API Examples ---\n");
    
    // Example 1: Enable device and check status
    Serial.println("Example 1: Enable device");
    myDevice.setEnable(true);
    delay(10);
    
    uint8_t status = myDevice.getStatus();
    Serial.printf("Status: 0x%02X (Ready: %s, Error: %s)\n",
                  status,
                  (status & 0x01) ? "Yes" : "No",
                  (status & 0x02) ? "Yes" : "No");
    
    // Example 2: Write and read data
    Serial.println("\nExample 2: Write and read data");
    uint32_t testData = 0x12345678;
    Serial.printf("Writing: 0x%08X\n", testData);
    myDevice.writeData(testData);
    
    delay(1);
    
    uint32_t readData = myDevice.readData();
    Serial.printf("Read back: 0x%08X\n", readData);
    
    if (readData == testData) {
        Serial.println("Success: Data matches!");
    } else {
        Serial.println("ERROR: Data mismatch!");
    }
    
    // Example 3: Multiple sequential operations
    Serial.println("\nExample 3: Sequential operations");
    for (uint32_t i = 0; i < 5; i++) {
        myDevice.writeData(i);
        delay(1);
        uint32_t value = myDevice.readData();
        Serial.printf("  %u: Wrote %u, Read %u - %s\n",
                      i, i, value,
                      (value == i) ? "OK" : "FAIL");
    }
    
    // Example 4: Reset device
    Serial.println("\nExample 4: Reset device");
    Serial.println("Resetting...");
    myDevice.reset();
    delay(10);
    
    status = myDevice.getStatus();
    Serial.printf("Status after reset: 0x%02X\n", status);
    
    // Example 5: Disable device
    Serial.println("\nExample 5: Disable device");
    myDevice.setEnable(false);
    delay(10);
    
    status = myDevice.getStatus();
    Serial.printf("Status: 0x%02X (Ready: %s)\n",
                  status,
                  (status & 0x01) ? "Yes" : "No");
    
    Serial.println("\n--- Examples complete ---");
    Serial.println("Define ENABLE_PAPILIO_OS for CLI interface");
}
#endif

/*
 * CLI Equivalent Commands:
 * 
 * When ENABLE_PAPILIO_OS is defined, you can perform the same operations
 * interactively via CLI:
 * 
 * > template enable           # Enable device
 * > template status           # Check status
 * > template write 0x1234     # Write data
 * > template read             # Read data
 * > template reset            # Reset device
 * > template disable          # Disable device
 * 
 * For a complete tutorial:
 * > template tutorial
 * 
 * For all commands:
 * > template help
 */
