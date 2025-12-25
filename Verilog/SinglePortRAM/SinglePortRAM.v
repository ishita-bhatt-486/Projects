`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 24.12.2025 11:02:51
// Design Name: 
// Module Name: SinglePortRAM_64x8
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


module SinglePortRAM_64x8(
    input [7:0] input_data,
    input [5:0] address,
    input we,
    input clk,
    
    output [7:0] output_data
    );
    
    reg [7:0] ram [63:0];
    reg [5:0] address_register;
    
    always @ (posedge clk)
        begin
            if (we)
                ram[address]<=input_data;
            else
                address_register<=address;
        end
        
    assign output_data = ram[address_register];
    
endmodule
