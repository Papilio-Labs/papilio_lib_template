#include "PapilioTemplate.h"

PapilioTemplate::PapilioTemplate(uint16_t baseAddress)
    : _baseAddress(baseAddress) {
    // Constructor - initialization happens in begin()
}

bool PapilioTemplate::begin() {
    // TODO: Implement initialization logic
    // Example:
    // 1. Reset the device
    // 2. Configure initial settings
    // 3. Verify device is responding
    
    reset();
    
    // Wait for device to be ready
    unsigned long startTime = millis();
    while (!isReady() && (millis() - startTime) < 1000) {
        delay(10);
    }
    
    return isReady();
}

bool PapilioTemplate::isReady() {
    uint8_t status = getStatus();
    return (status & STATUS_READY) != 0;
}

uint8_t PapilioTemplate::getStatus() {
    return readReg8(REG_STATUS);
}

void PapilioTemplate::setEnable(bool enable) {
    uint8_t ctrl = readReg8(REG_CONTROL);
    
    if (enable) {
        ctrl |= CTRL_ENABLE;
    } else {
        ctrl &= ~CTRL_ENABLE;
    }
    
    writeReg8(REG_CONTROL, ctrl);
}

void PapilioTemplate::writeData(uint32_t data) {
    // TODO: Add any validation or pre-processing
    writeReg32(REG_DATA, data);
}

uint32_t PapilioTemplate::readData() {
    // TODO: Add any post-processing
    return readReg32(REG_DATA);
}

void PapilioTemplate::reset() {
    // Pulse reset bit
    uint8_t ctrl = readReg8(REG_CONTROL);
    ctrl |= CTRL_RESET;
    writeReg8(REG_CONTROL, ctrl);
    
    delayMicroseconds(10);
    
    ctrl &= ~CTRL_RESET;
    writeReg8(REG_CONTROL, ctrl);
    
    delay(10);  // Allow device to stabilize
}

// Helper methods for register access

void PapilioTemplate::writeReg8(uint16_t offset, uint8_t value) {
    wishboneWrite8(_baseAddress + offset, value);
}

uint8_t PapilioTemplate::readReg8(uint16_t offset) {
    return wishboneRead8(_baseAddress + offset);
}

void PapilioTemplate::writeReg32(uint16_t offset, uint32_t value) {
    wishboneWrite32(_baseAddress + offset, value);
}

uint32_t PapilioTemplate::readReg32(uint16_t offset) {
    return wishboneRead32(_baseAddress + offset);
}
