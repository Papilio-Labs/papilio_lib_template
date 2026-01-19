// Papilio Template Wishbone Module
// TODO: Describe what this module does and what hardware it controls
//
// This is a template Wishbone slave module that implements:
// - Standard Wishbone classic interface
// - Simple register map for control and data
// - TODO: Add your hardware-specific functionality
//
// Register Map:
// - 0x00: CONTROL (RW) - Control register
//         [0] ENABLE  - Enable device
//         [1] RESET   - Soft reset
//         [7:2] Reserved
// - 0x04: STATUS (RO) - Status register
//         [0] READY   - Device ready
//         [1] ERROR   - Error flag
//         [7:2] Reserved
// - 0x08: DATA (RW) - Data register (32-bit)
//
// TODO: Document additional registers as you add them

module papilio_template #(
    parameter DATA_WIDTH = 8    // TODO: Change to 16 or 32 if needed
) (
    input  wire                  clk,
    input  wire                  rst,

    // Wishbone interface (classic single-cycle acknowledge)
    input  wire [15:0]           wb_adr_i,
    input  wire [DATA_WIDTH-1:0] wb_dat_i,
    output reg  [DATA_WIDTH-1:0] wb_dat_o,
    input  wire                  wb_we_i,
    input  wire                  wb_cyc_i,
    input  wire                  wb_stb_i,
    output reg                   wb_ack_o

    // TODO: Add external hardware interface signals here
    // Examples:
    // output wire                  ext_signal_out,
    // input  wire                  ext_signal_in,
    // output wire [7:0]            ext_data_out
);

    // Register addresses (byte addresses)
    localparam ADDR_CONTROL = 16'h0000;
    localparam ADDR_STATUS  = 16'h0004;
    localparam ADDR_DATA    = 16'h0008;

    // Control register bits
    localparam CTRL_ENABLE = 0;
    localparam CTRL_RESET  = 1;

    // Status register bits
    localparam STATUS_READY = 0;
    localparam STATUS_ERROR = 1;

    // Internal registers
    reg [7:0]  control_reg;
    reg [7:0]  status_reg;
    reg [31:0] data_reg;

    // TODO: Add your internal logic signals here
    wire enable;
    wire soft_reset;
    
    assign enable = control_reg[CTRL_ENABLE];
    assign soft_reset = control_reg[CTRL_RESET];

    // TODO: Implement your hardware logic
    // Example: Generate ready signal based on your hardware state
    always @(posedge clk) begin
        if (rst || soft_reset) begin
            status_reg[STATUS_READY] <= 1'b0;
            status_reg[STATUS_ERROR] <= 1'b0;
            // TODO: Reset your hardware state
        end else if (enable) begin
            status_reg[STATUS_READY] <= 1'b1;  // TODO: Update based on actual hardware
            status_reg[STATUS_ERROR] <= 1'b0;
            // TODO: Implement your hardware functionality
        end
    end

    // Wishbone interface logic
    always @(posedge clk) begin
        if (rst) begin
            wb_ack_o    <= 1'b0;
            wb_dat_o    <= {DATA_WIDTH{1'b0}};
            control_reg <= 8'h00;
            data_reg    <= 32'h00000000;
        end else begin
            // Default deassert ack
            wb_ack_o <= 1'b0;

            // Clear soft reset bit after one cycle
            if (control_reg[CTRL_RESET]) begin
                control_reg[CTRL_RESET] <= 1'b0;
            end

            if (wb_cyc_i && wb_stb_i && !wb_ack_o) begin
                // One-cycle acknowledge for each request
                wb_ack_o <= 1'b1;

                if (wb_we_i) begin
                    // Write operations
                    case (wb_adr_i)
                        ADDR_CONTROL: begin
                            control_reg <= wb_dat_i[7:0];
                        end
                        ADDR_DATA: begin
                            // TODO: Adjust based on your DATA_WIDTH
                            if (DATA_WIDTH == 8)
                                data_reg[7:0] <= wb_dat_i;
                            else if (DATA_WIDTH == 16)
                                data_reg[15:0] <= wb_dat_i;
                            else
                                data_reg <= wb_dat_i;
                        end
                        // TODO: Add more write registers
                        default: begin
                            // Ignore writes to undefined addresses
                        end
                    endcase
                end else begin
                    // Read operations
                    case (wb_adr_i)
                        ADDR_CONTROL: begin
                            wb_dat_o <= {{(DATA_WIDTH-8){1'b0}}, control_reg};
                        end
                        ADDR_STATUS: begin
                            wb_dat_o <= {{(DATA_WIDTH-8){1'b0}}, status_reg};
                        end
                        ADDR_DATA: begin
                            // TODO: Adjust based on your DATA_WIDTH
                            if (DATA_WIDTH == 8)
                                wb_dat_o <= data_reg[7:0];
                            else if (DATA_WIDTH == 16)
                                wb_dat_o <= data_reg[15:0];
                            else
                                wb_dat_o <= data_reg;
                        end
                        // TODO: Add more read registers
                        default: begin
                            wb_dat_o <= {DATA_WIDTH{1'b0}};
                        end
                    endcase
                end
            end
        end
    end

    // TODO: Add your hardware-specific logic here
    // Examples:
    // - PWM generation
    // - LED control
    // - Sensor interface
    // - Timer/counter
    // - Communication protocol handler

endmodule
