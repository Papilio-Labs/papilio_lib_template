# Papilio Template Gateware

This directory contains the FPGA (gateware) implementation for the papilio_template module.

## Module: papilio_template

TODO: Describe your Wishbone module and what hardware it controls.

### Features

TODO: List key hardware features
- Feature 1
- Feature 2
- Feature 3

### Interface

#### Wishbone Signals

| Signal | Direction | Width | Description |
|--------|-----------|-------|-------------|
| `clk` | Input | 1 | System clock |
| `rst` | Input | 1 | Synchronous reset (active high) |
| `wb_adr_i` | Input | 16 | Wishbone address (byte addressing) |
| `wb_dat_i` | Input | 8/16/32 | Wishbone write data |
| `wb_dat_o` | Output | 8/16/32 | Wishbone read data |
| `wb_we_i` | Input | 1 | Write enable (1=write, 0=read) |
| `wb_cyc_i` | Input | 1 | Wishbone cycle |
| `wb_stb_i` | Input | 1 | Wishbone strobe |
| `wb_ack_o` | Output | 1 | Wishbone acknowledge |

#### External Hardware Signals

TODO: Document your external hardware interface

| Signal | Direction | Width | Description |
|--------|-----------|-------|-------------|
| `ext_signal_out` | Output | 1 | Example output signal |
| `ext_signal_in` | Input | 1 | Example input signal |

### Parameters

| Parameter | Default | Description |
|-----------|---------|-------------|
| `DATA_WIDTH` | 8 | Wishbone data width (8, 16, or 32) |

TODO: Document additional parameters

### Register Map

All addresses are byte addresses relative to the module's base address.

#### CONTROL Register (0x00, RW)

Control register for device configuration.

| Bit | Name | Access | Description |
|-----|------|--------|-------------|
| 0 | ENABLE | RW | Enable device (1=enabled, 0=disabled) |
| 1 | RESET | RW | Soft reset (pulse high for 1 cycle) |
| 7:2 | Reserved | - | Reserved for future use |

#### STATUS Register (0x04, RO)

Status register indicating device state.

| Bit | Name | Access | Description |
|-----|------|--------|-------------|
| 0 | READY | RO | Device ready (1=ready, 0=not ready) |
| 1 | ERROR | RO | Error flag (1=error, 0=no error) |
| 7:2 | Reserved | - | Reserved for future use |

#### DATA Register (0x08, RW)

Data register for device data.

| Bits | Access | Description |
|------|--------|-------------|
| 31:0 | RW | Data value (TODO: document data format) |

TODO: Add documentation for additional registers

### Usage Example

```verilog
// Instantiate the module in your top-level design
papilio_template #(
    .DATA_WIDTH(32)  // Use 32-bit data width
) template_inst (
    .clk(clk),
    .rst(rst),
    
    // Wishbone interface
    .wb_adr_i(wb_adr),
    .wb_dat_i(wb_dat_m2s),
    .wb_dat_o(wb_dat_s2m),
    .wb_we_i(wb_we),
    .wb_cyc_i(wb_cyc),
    .wb_stb_i(wb_stb),
    .wb_ack_o(wb_ack)
    
    // External hardware signals
    // .ext_signal_out(led_out),
    // .ext_signal_in(button_in)
);
```

## Constraint Files

Pin constraint files for different Papilio boards are located in the `constraints/` directory.

### Supported Boards

- **Papilio Retrocade** - `papilio_retrocade.cst`
- **Papilio Synth** - `papilio_synth.cst`

TODO: Document pin assignments for each board

### Adding a New Board

1. Create a new constraint file: `constraints/<board_name>.cst`
2. Define all external pins used by the module
3. Include comments explaining each pin
4. Test with hardware
5. Update this README

## Simulation

Simulation testbenches are located in `../../tests/sim/`. See the test directory README for details on running simulations.

Key test cases:
- TODO: List your test cases
- Wishbone read/write timing
- Register functionality
- Hardware interface behavior

## Integration

### Clock Requirements

TODO: Document clock requirements
- System clock: XX MHz
- Timing constraints: TODO

### Reset Behavior

- Synchronous reset (active high)
- All registers reset to 0
- TODO: Document additional reset behavior

### Resource Utilization

TODO: Measure and document resource usage after synthesis
- LUTs: ~XX
- FFs: ~XX
- BRAMs: ~XX

## Development Notes

### Adding New Registers

1. Define register address constant in module
2. Add register declaration
3. Add case in Wishbone write logic
4. Add case in Wishbone read logic
5. Update this README register map
6. Update firmware constants in `../src/PapilioTemplate.h`
7. Update `../AI_SKILL.md` with register documentation

### Hardware Implementation Tips

TODO: Add tips specific to your hardware functionality

## References

- Wishbone B4 Specification
- Papilio Dev Tools documentation
- Reference implementation: `papilio_wb_register`
