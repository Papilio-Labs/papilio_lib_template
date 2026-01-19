#ifndef PAPILIO_TEMPLATE_H
#define PAPILIO_TEMPLATE_H

#include <Arduino.h>
#include <WishboneSPI.h>

/**
 * @brief Main class for PapilioTemplate library
 * 
 * TODO: Describe what this library does and what hardware it controls.
 * 
 * This class provides the programmatic API for the library. It is always
 * available and has no dependencies on papilio_os.
 * 
 * When ENABLE_PAPILIO_OS is defined, a CLI interface is also available
 * via the PapilioTemplateOS plugin.
 */
class PapilioTemplate {
public:
    /**
     * @brief Construct a new PapilioTemplate object
     * 
     * @param baseAddress Wishbone base address for this device (default 0x1000)
     */
    PapilioTemplate(uint16_t baseAddress = 0x1000);

    /**
     * @brief Initialize the device
     * 
     * Sets up initial register values and prepares the hardware for operation.
     * 
     * @return true if initialization successful, false otherwise
     */
    bool begin();

    /**
     * @brief Check if device is ready for operation
     * 
     * @return true if device is ready, false otherwise
     */
    bool isReady();

    /**
     * @brief Get device status
     * 
     * @return uint8_t Status register value
     */
    uint8_t getStatus();

    /**
     * @brief Enable or disable the device
     * 
     * @param enable true to enable, false to disable
     */
    void setEnable(bool enable);

    /**
     * @brief Write data to the device
     * 
     * TODO: Document what this data represents and valid ranges
     * 
     * @param data Data value to write
     */
    void writeData(uint32_t data);

    /**
     * @brief Read data from the device
     * 
     * TODO: Document what this data represents
     * 
     * @return uint32_t Data value
     */
    uint32_t readData();

    /**
     * @brief Reset the device to initial state
     */
    void reset();

    /**
     * @brief Get the base address of this device
     * 
     * @return uint16_t Base address
     */
    uint16_t getBaseAddress() const { return _baseAddress; }

private:
    // TODO: Define your register addresses relative to base address
    static constexpr uint16_t REG_CONTROL = 0x00;  // Control register
    static constexpr uint16_t REG_STATUS  = 0x04;  // Status register (read-only)
    static constexpr uint16_t REG_DATA    = 0x08;  // Data register

    // Control register bits
    static constexpr uint8_t CTRL_ENABLE = 0x01;   // Enable bit
    static constexpr uint8_t CTRL_RESET  = 0x02;   // Reset bit

    // Status register bits
    static constexpr uint8_t STATUS_READY = 0x01;  // Ready bit
    static constexpr uint8_t STATUS_ERROR = 0x02;  // Error bit

    uint16_t _baseAddress;  // Wishbone base address

    // Helper methods for register access
    void writeReg8(uint16_t offset, uint8_t value);
    uint8_t readReg8(uint16_t offset);
    void writeReg32(uint16_t offset, uint32_t value);
    uint32_t readReg32(uint16_t offset);
};

#endif // PAPILIO_TEMPLATE_H
