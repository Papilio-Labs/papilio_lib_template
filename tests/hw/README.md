# Hardware Tests

This directory contains hardware tests for the papilio_template library.

## Overview

Hardware tests verify the firmware and gateware integration on actual Papilio hardware.

## Test Structure

Tests use PlatformIO's native testing framework. The `platformio.ini` file can be:
- **Standalone**: Self-contained test environment
- **Workspace-integrated**: Uses parent workspace configuration

Choose the approach that best fits your development workflow.

## Running Tests

### From this directory (standalone)

```powershell
# Run all tests
pio test

# Run specific test
pio test -f test_template_basic

# Run with specific environment
pio test -e esp32
```

### From workspace root (integrated)

```powershell
# If platformio.ini references workspace configuration
pio test -d libs/papilio_lib_template/tests/hw
```

## Writing Tests

Tests go in the `test/` directory following PlatformIO conventions:

### Test File Structure

```cpp
// test/test_template_basic.cpp
#include <unity.h>
#include <PapilioTemplate.h>

PapilioTemplate device;

void setUp(void) {
    // Runs before each test
    device.begin();
}

void tearDown(void) {
    // Runs after each test
}

void test_device_initialization(void) {
    TEST_ASSERT_TRUE(device.isReady());
}

void test_enable_disable(void) {
    device.setEnable(true);
    uint8_t status = device.getStatus();
    TEST_ASSERT_TRUE(status & 0x01);  // Ready bit
    
    device.setEnable(false);
    status = device.getStatus();
    TEST_ASSERT_FALSE(status & 0x01);
}

void test_write_read_data(void) {
    uint32_t testValue = 0x12345678;
    device.writeData(testValue);
    uint32_t readValue = device.readData();
    TEST_ASSERT_EQUAL_UINT32(testValue, readValue);
}

void setup() {
    // Wait for serial connection
    delay(2000);
    
    UNITY_BEGIN();
    RUN_TEST(test_device_initialization);
    RUN_TEST(test_enable_disable);
    RUN_TEST(test_write_read_data);
    UNITY_END();
}

void loop() {
    // Tests run once in setup()
}
```

### Test Organization

- `test_template_basic.cpp` - Basic functionality tests
- `test_template_registers.cpp` - Register read/write tests
- `test_template_cli.cpp` - CLI interface tests (with ENABLE_PAPILIO_OS)
- TODO: Add your test files

## Unity Test Framework

PlatformIO uses Unity for testing. Key assertions:

```cpp
// Boolean assertions
TEST_ASSERT_TRUE(condition);
TEST_ASSERT_FALSE(condition);

// Equality assertions
TEST_ASSERT_EQUAL(expected, actual);
TEST_ASSERT_EQUAL_UINT8(expected, actual);
TEST_ASSERT_EQUAL_UINT32(expected, actual);

// Comparison assertions
TEST_ASSERT_GREATER_THAN(threshold, actual);
TEST_ASSERT_LESS_THAN(threshold, actual);

// Special assertions
TEST_FAIL_MESSAGE("Custom failure message");
TEST_IGNORE_MESSAGE("Skipping this test");
```

## Integration Patterns

See `papilio_dev_tools/docs/INTEGRATION_PATTERNS.md` for:
- Standalone vs workspace-integrated tests
- Test runner patterns
- Hardware test best practices

## Hardware Requirements

TODO: Document hardware requirements for testing
- Papilio board with FPGA programmed
- External connections (if any)
- Test fixtures or hardware

## Troubleshooting

### Tests Fail to Run
- Ensure FPGA is programmed with correct bitstream
- Check serial connection and baud rate
- Verify hardware connections

### Tests Fail Unexpectedly
- Check wishbone bus initialization
- Verify gateware is loaded correctly
- Use simulation tests to verify gateware first

### No Serial Output
- Check USB connection
- Verify correct COM port
- Try `pio device monitor` to see output

## References

- PlatformIO Testing: https://docs.platformio.org/en/latest/plus/unit-testing.html
- Unity Test Framework: http://www.throwtheswitch.org/unity
- papilio_dev_tools integration patterns
