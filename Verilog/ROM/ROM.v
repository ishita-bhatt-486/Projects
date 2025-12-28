`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 25.12.2025 22:10:35
// Design Name: 
// Module Name: ROM
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


module ROM #(
    
    parameter DATA_WIDTH = 8,
    parameter ADDRESS_WIDTH = 10,
    parameter ROM_FILENAME= "rom.mem"
    
    )(
    
    input  wire clk,
    input  wire en,
    input  wire [ADDRESS_WIDTH-1:0] address,
    output reg [DATA_WIDTH-1:0] output_data
    
    );
    
    reg [DATA_WIDTH-1:0] mem [0:(1<<ADDRESS_WIDTH)-1];
    
    initial begin
    
        $readmemh(ROM_FILENAME, mem);
    
    end
    
    always @(posedge clk) begin
        if (en)
            output_data <= mem[address];
    end
    
endmodule