#ifndef PAPILIO_TEMPLATE_OS_H
#define PAPILIO_TEMPLATE_OS_H

// Only compile this file when papilio_os is enabled
#ifdef ENABLE_PAPILIO_OS

#include <PapilioOS.h>
#include "PapilioTemplate.h"

/**
 * @brief OS plugin for PapilioTemplate library
 * 
 * Provides CLI commands and interactive tutorial for the PapilioTemplate library.
 * This plugin automatically registers itself with papilio_os when ENABLE_PAPILIO_OS
 * is defined. No explicit registration is needed in user code.
 * 
 * Available commands:
 * - template tutorial - Interactive step-by-step tutorial
 * - template help     - Show all available commands
 * - template status   - Display device status
 * - template enable   - Enable the device
 * - template disable  - Disable the device
 * - template write    - Write data to device
 * - template read     - Read data from device
 * - template reset    - Reset the device
 */
class PapilioTemplateOS {
public:
    /**
     * @brief Construct and auto-register the plugin
     * 
     * Uses static constructor pattern to automatically register with
     * papilio_os during static initialization.
     * 
     * @param device Pointer to PapilioTemplate instance to control
     */
    PapilioTemplateOS(PapilioTemplate* device);

    /**
     * @brief Set the device instance
     * 
     * Allows changing the controlled device after construction.
     * 
     * @param device Pointer to PapilioTemplate instance
     */
    void setDevice(PapilioTemplate* device);

private:
    PapilioTemplate* _device;

    // Register all CLI commands
    void registerCommands();

    // Command handlers
    static void handleTutorial(int argc, char** argv);
    static void handleHelp(int argc, char** argv);
    static void handleStatus(int argc, char** argv);
    static void handleEnable(int argc, char** argv);
    static void handleDisable(int argc, char** argv);
    static void handleWrite(int argc, char** argv);
    static void handleRead(int argc, char** argv);
    static void handleReset(int argc, char** argv);

    // Tutorial implementation
    static void runTutorial();
    static bool tutorialStep(int stepNum, const char* description, const char* command);

    // Singleton instance for static callbacks
    static PapilioTemplateOS* _instance;
};

#endif // ENABLE_PAPILIO_OS

#endif // PAPILIO_TEMPLATE_OS_H
