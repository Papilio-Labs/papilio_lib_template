#include <unity.h>
#include <PapilioTemplate.h>
#include <WishboneSPI.h>

// Test device instance
PapilioTemplate device;

// Test setup - runs before each test
void setUp(void) {
    // Device initialization happens in test_device_initialization
}

// Test teardown - runs after each test
void tearDown(void) {
    // Cleanup if needed
}

// Test 1: Device initialization
void test_device_initialization(void) {
    // Initialize Wishbone SPI
    // TODO: Adjust SPI pins for your board
    SPIClass* spi = &SPI;
    int cs_pin = 5;
    wishboneInit(spi, cs_pin);
    
    // Wait for FPGA to be ready
    TEST_ASSERT_TRUE_MESSAGE(wishboneIsReady(), "FPGA not responding");
    
    // Initialize device
    bool initResult = device.begin();
    TEST_ASSERT_TRUE_MESSAGE(initResult, "Device initialization failed");
    
    // Verify device is ready
    TEST_ASSERT_TRUE_MESSAGE(device.isReady(), "Device not ready after init");
}

// Test 2: Enable/Disable functionality
void test_enable_disable(void) {
    // Enable device
    device.setEnable(true);
    delay(10);
    
    uint8_t status = device.getStatus();
    TEST_ASSERT_TRUE_MESSAGE(status & 0x01, "Device not ready after enable");
    
    // Disable device
    device.setEnable(false);
    delay(10);
    
    status = device.getStatus();
    TEST_ASSERT_FALSE_MESSAGE(status & 0x01, "Device still ready after disable");
}

// Test 3: Write and read data register
void test_write_read_data(void) {
    // Test with 8-bit value
    uint32_t testValue1 = 0x42;
    device.writeData(testValue1);
    delay(1);
    uint32_t readValue1 = device.readData();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(testValue1, readValue1, 
                                     "Data mismatch for 0x42");
    
    // Test with different value
    uint32_t testValue2 = 0xA5;
    device.writeData(testValue2);
    delay(1);
    uint32_t readValue2 = device.readData();
    TEST_ASSERT_EQUAL_UINT32_MESSAGE(testValue2, readValue2, 
                                     "Data mismatch for 0xA5");
}

// Test 4: Reset functionality
void test_reset(void) {
    // Write some data
    device.writeData(0x12345678);
    
    // Reset device
    device.reset();
    delay(10);
    
    // Verify device returned to initial state
    TEST_ASSERT_TRUE_MESSAGE(device.isReady(), "Device not ready after reset");
    
    // TODO: Add checks for reset state of your registers
}

// Test 5: Multiple sequential operations
void test_sequential_operations(void) {
    // Enable device
    device.setEnable(true);
    delay(1);
    
    // Perform multiple write/read cycles
    for (uint32_t i = 0; i < 10; i++) {
        device.writeData(i);
        delay(1);
        uint32_t readValue = device.readData();
        TEST_ASSERT_EQUAL_UINT32(i, readValue);
    }
}

// Test 6: Status register bits
void test_status_register(void) {
    uint8_t status = device.getStatus();
    
    // Check that reserved bits are 0
    // Bits 7:2 should be reserved
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(0, status & 0xFC, "Reserved bits not zero");
    
    // TODO: Add checks for your status bits
}

// Test 7: Base address configuration
void test_base_address(void) {
    // Create device with custom base address
    PapilioTemplate device2(0x2000);
    
    TEST_ASSERT_EQUAL_UINT16(0x2000, device2.getBaseAddress());
    
    // TODO: Test that device operates correctly at different base address
}

// TODO: Add more hardware-specific tests
// - Test 8: Interrupt functionality (if applicable)
// - Test 9: DMA operations (if applicable)
// - Test 10: Error conditions
// - Test 11: Performance testing
// - Test 12: Stress testing

void setup() {
    // Wait for serial connection (2 seconds)
    delay(2000);
    
    // Initialize serial for test output
    Serial.begin(115200);
    
    // Begin Unity testing
    UNITY_BEGIN();
    
    // Run tests in order
    RUN_TEST(test_device_initialization);
    RUN_TEST(test_enable_disable);
    RUN_TEST(test_write_read_data);
    RUN_TEST(test_reset);
    RUN_TEST(test_sequential_operations);
    RUN_TEST(test_status_register);
    RUN_TEST(test_base_address);
    
    // End Unity testing
    UNITY_END();
}

void loop() {
    // Tests run once in setup()
    // Loop does nothing
}
