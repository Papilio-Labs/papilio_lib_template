# Papilio Template Library - AI Skill

Instructions for AI assistants working with the papilio_lib_template library.

## Purpose

TODO: Briefly describe what this library does and what hardware it controls.

## Architecture

### Firmware (ESP32)

The library provides two interfaces:

1. **Programmatic API** (`PapilioTemplate` class) - Always available
   - Direct function calls for library functionality
   - No dependencies on papilio_os

2. **CLI Interface** (`PapilioTemplateOS` plugin) - Optional
   - Enabled when `ENABLE_PAPILIO_OS` is defined
   - Auto-registers with papilio_os via static constructor
   - Zero overhead when disabled (no code included)

### Gateware (FPGA)

TODO: Describe your Wishbone module architecture

The `papilio_template` module implements a Wishbone slave interface with the following registers:

## Hardware Registers

TODO: Document your register map with exact addresses and bit layouts

| Address | Name | Access | Bits | Description |
|---------|------|--------|------|-------------|
| 0x00 | CONTROL | RW | [7:0] | Control register |
| 0x04 | STATUS | RO | [7:0] | Status register |
| 0x08 | DATA | RW | [31:0] | Data register |

### Control Register (0x00)

TODO: Document bit fields

- Bit 0: Enable
- Bit 1: Reset
- Bits 7-2: Reserved

### Status Register (0x04)

TODO: Document bit fields

- Bit 0: Ready
- Bit 1: Error
- Bits 7-2: Reserved

### Data Register (0x08)

TODO: Document data format

## Common Operations

### Initialize the Device

**API:**
```cpp
myDevice.begin();
```

**CLI:**
```
> template init
```

**Registers:**
1. Write 0x01 to CONTROL to enable
2. Wait for STATUS bit 0 (Ready)

### Read Status

**API:**
```cpp
uint8_t status = myDevice.getStatus();
```

**CLI:**
```
> template status
```

**Registers:**
- Read STATUS register (0x04)

### Write Data

**API:**
```cpp
myDevice.writeData(value);
```

**CLI:**
```
> template write <value>
```

**Registers:**
1. Write value to DATA register (0x08)
2. Check STATUS for completion

## Board-Specific Information

### Papilio Retrocade

TODO: Document board-specific pin assignments

Constraint file: `gateware/constraints/papilio_retrocade.cst`
- Pin X: Signal Y
- Pin A: Signal B

### Papilio Synth

TODO: Document board-specific pin assignments

Constraint file: `gateware/constraints/papilio_synth.cst`
- Pin X: Signal Y
- Pin A: Signal B

## Adding New Features

### Adding a New Register

1. **Gateware** (`gateware/papilio_template.v`):
   - Add register to address decoder
   - Implement read/write logic
   - Update register map in comments

2. **Firmware** (`src/PapilioTemplate.h/cpp`):
   - Add register address constant
   - Add API function to access register
   - Update documentation

3. **CLI** (if applicable) (`src/PapilioTemplateOS.cpp`):
   - Add CLI command to access feature
   - Update tutorial to demonstrate new feature
   - Update help text

4. **Documentation**:
   - Update this AI_SKILL.md register map
   - Update gateware/README.md
   - Update main README.md

### Adding a New CLI Command

1. Add command to `PapilioTemplateOS::registerCommands()`:
```cpp
PapilioOS.registerCommand("template", "mycommand", handleMyCommand, 
                          "Description of command");
```

2. Implement handler function:
```cpp
void PapilioTemplateOS::handleMyCommand(int argc, char** argv) {
    // Parse arguments
    // Call API functions
    // Print results
}
```

3. Update tutorial to demonstrate new command
4. Update help text and documentation

## Testing

### Simulation Tests

Location: `tests/sim/`

Run with:
```powershell
cd tests/sim
python run_all_sims.py
```

Tests verify:
- Wishbone interface timing
- Register read/write operations
- TODO: Add your test cases

### Hardware Tests

Location: `tests/hw/`

Run with:
```powershell
cd tests/hw
pio test
```

Tests verify:
- TODO: Add your test cases

## Development Patterns

### General Development Skills

For general Papilio development patterns, see:
- `papilio_dev_tools/AI_SKILL.md` - Testing infrastructure, simulation patterns
- `papilio_dev_tools/docs/SIMULATION.md` - Simulation workflow
- `papilio_dev_tools/docs/VCD_ANALYSIS.md` - Debugging with VCD files

### Reference Implementations

- `papilio_wb_register` - Minimal Wishbone register block
- `papilio_wishbone_bus` - Complete library with testing infrastructure

## Troubleshooting

### Common Issues

TODO: Document common issues and solutions

#### Issue 1: Description
**Symptoms:** 
**Cause:** 
**Solution:**

#### Issue 2: Description
**Symptoms:**
**Cause:**
**Solution:**

### Hardware Debugging

1. Check STATUS register for error flags
2. Verify pin assignments match constraint file
3. Use simulation to verify Wishbone timing
4. Check VCD waveforms for signal issues

### Firmware Debugging

1. Enable serial debug output
2. Check return values from API calls
3. Verify ENABLE_PAPILIO_OS is defined (if using CLI)
4. Test with simple commands first

## Version History

TODO: Document major changes

- v0.1.0 - Initial implementation
