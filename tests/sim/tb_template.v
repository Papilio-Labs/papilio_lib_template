`timescale 1ns/1ps

// Testbench for papilio_template module
// Tests basic Wishbone interface and register functionality

module tb_template;
    // Clock and reset
    reg clk;
    reg rst;

    // Wishbone signals
    reg [15:0] wb_adr_i;
    reg [7:0] wb_dat_i;
    wire [7:0] wb_dat_o;
    reg wb_we_i;
    reg wb_cyc_i;
    reg wb_stb_i;
    wire wb_ack_o;

    // Instantiate the module under test
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

    // Clock generation (100MHz = 10ns period)
    always #5 clk = ~clk;

    // Test control variables
    integer errors = 0;
    integer tests = 0;

    // Task: Write to Wishbone register
    task wb_write;
        input [15:0] addr;
        input [7:0] data;
        begin
            @(posedge clk);
            wb_adr_i = addr;
            wb_dat_i = data;
            wb_we_i = 1;
            wb_cyc_i = 1;
            wb_stb_i = 1;
            
            // Wait for acknowledge
            @(posedge wb_ack_o);
            @(posedge clk);
            #1;
            wb_cyc_i = 0;
            wb_stb_i = 0;
            wb_we_i = 0;
        end
    endtask

    // Task: Read from Wishbone register
    task wb_read;
        input [15:0] addr;
        output [7:0] data;
        begin
            @(posedge clk);
            wb_adr_i = addr;
            wb_we_i = 0;
            wb_cyc_i = 1;
            wb_stb_i = 1;
            
            // Wait for acknowledge
            @(posedge wb_ack_o);
            @(posedge clk);
            #1;
            data = wb_dat_o;
            wb_cyc_i = 0;
            wb_stb_i = 0;
        end
    endtask

    // Task: Check read value
    task check_value;
        input [15:0] addr;
        input [7:0] expected;
        reg [7:0] actual;
        begin
            wb_read(addr, actual);
            tests = tests + 1;
            if (actual !== expected) begin
                $display("ERROR: Address 0x%04X: Expected 0x%02X, Got 0x%02X", 
                         addr, expected, actual);
                errors = errors + 1;
            end else begin
                $display("PASS: Address 0x%04X = 0x%02X", addr, actual);
            end
        end
    endtask

    // Main test sequence
    initial begin
        // Initialize signals
        clk = 0;
        rst = 1;
        wb_adr_i = 0;
        wb_dat_i = 0;
        wb_we_i = 0;
        wb_cyc_i = 0;
        wb_stb_i = 0;

        // Generate VCD for waveform viewing
        $dumpfile("template.vcd");
        $dumpvars(0, tb_template);

        $display("\n========================================");
        $display("  Papilio Template Testbench");
        $display("========================================\n");

        // Release reset
        #20;
        @(posedge clk);
        rst = 0;
        #10;

        // Test 1: Verify reset state
        $display("\nTest 1: Verify reset state");
        check_value(16'h0000, 8'h00);  // CONTROL should be 0
        check_value(16'h0004, 8'h00);  // STATUS should be 0
        check_value(16'h0008, 8'h00);  // DATA should be 0

        // Test 2: Write and read CONTROL register
        $display("\nTest 2: Write and read CONTROL register");
        wb_write(16'h0000, 8'h01);     // Enable device
        check_value(16'h0000, 8'h01);  // Verify written value

        // Test 3: Write and read DATA register
        $display("\nTest 3: Write and read DATA register");
        wb_write(16'h0008, 8'h42);
        check_value(16'h0008, 8'h42);

        // Test 4: Verify STATUS register (read-only)
        $display("\nTest 4: Verify STATUS register");
        check_value(16'h0004, 8'h01);  // Should be READY after enable

        // Test 5: Test soft reset
        $display("\nTest 5: Test soft reset");
        wb_write(16'h0000, 8'h02);     // Pulse reset bit
        #20;
        check_value(16'h0000, 8'h00);  // Reset bit should auto-clear

        // Test 6: Multiple writes/reads
        $display("\nTest 6: Multiple sequential operations");
        wb_write(16'h0008, 8'h11);
        wb_write(16'h0008, 8'h22);
        wb_write(16'h0008, 8'h33);
        check_value(16'h0008, 8'h33);  // Should have last written value

        // Test 7: TODO: Add your hardware-specific tests
        $display("\nTest 7: TODO - Add hardware-specific tests");

        // Test complete
        #100;
        $display("\n========================================");
        $display("  Test Summary");
        $display("========================================");
        $display("  Tests run:    %0d", tests);
        $display("  Tests passed: %0d", tests - errors);
        $display("  Tests failed: %0d", errors);
        
        if (errors == 0) begin
            $display("  Status: ALL TESTS PASSED");
        end else begin
            $display("  Status: SOME TESTS FAILED");
        end
        $display("========================================\n");

        $finish;
    end

    // Timeout watchdog
    initial begin
        #100000;  // 100us timeout
        $display("\nERROR: Test timeout!");
        $finish;
    end

    // Optional: Monitor all transactions
    // Uncomment for detailed debugging
    /*
    always @(posedge clk) begin
        if (wb_cyc_i && wb_stb_i && wb_ack_o) begin
            if (wb_we_i)
                $display("Time %0t: WRITE addr=0x%04X data=0x%02X", 
                         $time, wb_adr_i, wb_dat_i);
            else
                $display("Time %0t: READ  addr=0x%04X data=0x%02X", 
                         $time, wb_adr_i, wb_dat_o);
        end
    end
    */

endmodule
