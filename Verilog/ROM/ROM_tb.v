`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 28.12.2025 09:54:52
// Design Name: 
// Module Name: ROM_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


`timescale 1ns / 1ps

module ROM_tb;

    parameter DATA_WIDTH = 8;
    parameter ADDRESS_WIDTH =10;

    reg clk;
    reg en;
    reg [ADDRESS_WIDTH-1:0] address;
    wire [DATA_WIDTH-1:0] output_data;

    ROM #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDRESS_WIDTH(ADDRESS_WIDTH),
        .ROM_FILENAME("../../../../rom.mem")
    ) dut (
        .clk(clk),
        .en(en),
        .address(address),
        .output_data(output_data)
    );

    always #5 clk = ~clk;

    initial begin
        $dumpfile("rom_dump.vcd");
        $dumpvars(0, ROM_tb);

        clk = 0;
        en = 0;
        address = 0;
        
        #20;

        $display("Read address 0");
        en = 1;
        address = 4'h0;
        #10;

        $display("Read address 2");
        address = 4'h2;
        #10;

        $display("Address change to 15 with enable=0");
        en = 0;
        address = 4'hF;
        #10;
        
        $display("Enable on");
        en = 1;
        #10;

        $finish;
    end

    always @(posedge clk) begin
        if (en)
            $display("Time: %0t\
            Address: %h\
            Output: %h\n", $time, address, output_data);
    end

endmodule