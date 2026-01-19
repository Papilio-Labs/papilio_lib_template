# Simulation Tests

This directory contains simulation testbenches for the papilio_template gateware module.

## Overview

Simulation tests verify the Wishbone interface and hardware functionality before deploying to FPGA.

## Running Tests

### Using papilio_dev_tools (Recommended)

```powershell
# From this directory
python run_all_sims.py
```

### Manual Simulation

```powershell
# Using iverilog (if installed)
iverilog -o tb_template.vvp tb_template.v ../papilio_template.v
vvp tb_template.vvp
gtkwave template.vcd  # View waveforms
```

## Test Cases

### tb_template.v

Main testbench that verifies:

TODO: Document your test cases
- Wishbone interface timing
- Single-cycle read/write operations
- Register functionality (CONTROL, STATUS, DATA)
- Reset behavior
- Error conditions

## Writing New Tests

1. Create a new testbench file: `tb_<feature>.v`
2. Include the module under test
3. Generate clock and reset
4. Perform Wishbone transactions
5. Verify expected behavior
6. Add to `run_all_sims.py` if using papilio_dev_tools

### Example Test Template

```verilog
`timescale 1ns/1ps

module tb_my_test;
    reg clk, rst;
    reg [15:0] wb_adr_i;
    reg [7:0] wb_dat_i;
    wire [7:0] wb_dat_o;
    reg wb_we_i, wb_cyc_i, wb_stb_i;
    wire wb_ack_o;

    // Instantiate module
    papilio_template #(
        .DATA_WIDTH(8)
    ) dut (
        .clk(clk),
        .rst(rst),
        .wb_adr_i(wb_adr_i),
        .wb_dat_i(wb_dat_i),
        .wb_dat_o(wb_dat_o),
        .wb_we_i(wb_we_i),
        .wb_cyc_i(wb_cyc_i),
        .wb_stb_i(wb_stb_i),
        .wb_ack_o(wb_ack_o)
    );

    // Clock generation
    always #5 clk = ~clk;

    initial begin
        // Initialize
        clk = 0;
        rst = 1;
        wb_adr_i = 0;
        wb_dat_i = 0;
        wb_we_i = 0;
        wb_cyc_i = 0;
        wb_stb_i = 0;

        // Release reset
        #20 rst = 0;

        // Test case 1: Write CONTROL register
        #10;
        wb_adr_i = 16'h0000;
        wb_dat_i = 8'h01;  // Enable
        wb_we_i = 1;
        wb_cyc_i = 1;
        wb_stb_i = 1;
        
        // Wait for ack
        @(posedge wb_ack_o);
        #1;
        wb_cyc_i = 0;
        wb_stb_i = 0;

        // Add more test cases...

        #100 $finish;
    end

    // Monitor
    initial begin
        $monitor("Time=%0t rst=%b adr=%h dat_i=%h dat_o=%h we=%b ack=%b",
                 $time, rst, wb_adr_i, wb_dat_i, wb_dat_o, wb_we_i, wb_ack_o);
    end
endmodule
```

## VCD Waveform Analysis

Generate VCD files for waveform viewing:

```verilog
initial begin
    $dumpfile("template.vcd");
    $dumpvars(0, tb_template);
end
```

View with GTKWave:
```bash
gtkwave template.vcd
```

For automated VCD analysis, see `papilio_dev_tools/docs/VCD_ANALYSIS.md`.

## Integration with papilio_dev_tools

The `papilio_dev_tools` library provides:
- Standard test runner (`run_all_sims.py`)
- VCD parsing and analysis tools
- Common test patterns and utilities

See `papilio_dev_tools/AI_SKILL.md` for detailed guidance on:
- Writing effective testbenches
- Debugging with VCD files
- Integration patterns

## References

- Wishbone B4 Specification
- Icarus Verilog documentation
- GTKWave user guide
- papilio_dev_tools testing patterns
