# papilio_lib_template

TODO: Brief description of what this library does and what hardware it controls.

## Features

TODO: List key features
- Feature 1
- Feature 2
- Feature 3

## Hardware Requirements

TODO: Describe hardware requirements
- Papilio board with [specific features]
- External components (if any)
- Pin connections

## Installation

1. Copy this library to your PlatformIO project's `lib/` directory
2. Include the header in your sketch:

```cpp
#include <PapilioTemplate.h>
```

## Programmatic API

### Initialization

```cpp
#include <PapilioTemplate.h>

PapilioTemplate myDevice;

void setup() {
    // Initialize the device
    myDevice.begin();
}
```

### Basic Operations

#### Operation 1

```cpp
// TODO: Document your API functions
myDevice.doSomething(parameter);
```

#### Operation 2

```cpp
// TODO: Add more API examples
int result = myDevice.getSomething();
```

## CLI Interface (with papilio_os)

When `ENABLE_PAPILIO_OS` is defined, this library provides interactive CLI commands.

### Setup

```cpp
#define ENABLE_PAPILIO_OS
#include <PapilioOS.h>
#include <PapilioTemplate.h>

PapilioTemplate myDevice;

void setup() {
    Serial.begin(115200);
    PapilioOS.begin();
    myDevice.begin();
}

void loop() {
    PapilioOS.update();
}
```

### Available Commands

| Command | Description |
|---------|-------------|
| `template tutorial` | Interactive step-by-step tutorial |
| `template help` | Show all available commands |
| `template status` | TODO: Document your commands |
| `template set <value>` | TODO: Document your commands |

### Tutorial

The interactive tutorial guides you through using the library:

```
> template tutorial
```

## Gateware

### Module: papilio_template

TODO: Describe your Wishbone module

#### Ports

| Port | Direction | Width | Description |
|------|-----------|-------|-------------|
| `clk` | Input | 1 | System clock |
| `rst` | Input | 1 | Synchronous reset (active high) |
| `wb_adr_i` | Input | N | Wishbone address |
| `wb_dat_i` | Input | 8/16/32 | Wishbone write data |
| `wb_dat_o` | Output | 8/16/32 | Wishbone read data |
| `wb_we_i` | Input | 1 | Write enable |
| `wb_cyc_i` | Input | 1 | Wishbone cycle |
| `wb_stb_i` | Input | 1 | Wishbone strobe |
| `wb_ack_o` | Output | 1 | Wishbone acknowledge |

#### Register Map

| Address | Name | Access | Description |
|---------|------|--------|-------------|
| 0x00 | CONTROL | RW | TODO: Document registers |
| 0x04 | STATUS | RO | TODO: Document registers |
| 0x08 | DATA | RW | TODO: Document registers |

See [gateware/README.md](gateware/README.md) for detailed hardware documentation.

### Supported Boards

- Papilio Retrocade (constraint file: `papilio_retrocade.cst`)
- Papilio Synth (constraint file: `papilio_synth.cst`)

Pin assignments are defined in `gateware/constraints/` directory.

## Examples

See [examples/TemplateCLI/](examples/TemplateCLI/) for a complete example demonstrating both API and CLI usage.

## Testing

### Simulation Tests

```powershell
cd tests/sim
python run_all_sims.py
```

### Hardware Tests

```powershell
cd tests/hw
pio test
```

## Development

### Adding a New Feature

1. Update gateware module and register map
2. Update firmware API in `src/PapilioTemplate.h` and `.cpp`
3. If adding CLI commands, update `src/PapilioTemplateOS.h` and `.cpp`
4. Update `AI_SKILL.md` with new register information
5. Add tests in `tests/sim/` and/or `tests/hw/`
6. Update this README

### Adding Board Support

1. Create `gateware/constraints/<board_name>.cst`
2. Define all external pin assignments
3. Test with hardware
4. Update this README

## Reference

This library follows the Papilio Library Standards. For more information:
- See `papilio_dev_tools` for development patterns
- See `papilio_wb_register` for a minimal reference implementation
- See project `AGENTS.md` for library standards

## License

MIT License - see LICENSE file for details
