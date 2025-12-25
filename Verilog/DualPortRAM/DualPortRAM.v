`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 24.12.2025 21:28:28
// Design Name: 
// Module Name: DualPortRAM
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


module DualPortRAM(
    input clk,
    
    input [7:0] input_data_a,
    input [5:0] address_a,
    input we_a,
    
    output reg [7:0] output_data_a,
    
    input [7:0] input_data_b,
    input [5:0] address_b,
    input we_b,
        
    output reg [7:0] output_data_b
    );
    
    reg [7:0] ram [63:0];
    
    always @ (posedge clk)
        begin
            if (we_a)
                ram[address_a]<=input_data_a;
            else
                output_data_a <= ram[address_a];
        end
    
    always @ (posedge clk)
        begin
            if (we_b)
                ram[address_b]<=input_data_b;
            else
                output_data_b <= ram[address_b];
        end    
        
    
endmodule
