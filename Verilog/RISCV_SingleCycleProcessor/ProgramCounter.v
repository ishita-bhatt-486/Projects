`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 09.01.2026 10:01:25
// Design Name: 
// Module Name: ProgramCounter
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


module ProgramCounter(
    
    input clk,
    input reset,
    input [31:0] PC_input,
    output reg [31:0] PC_output
    );
    
    always @(posedge clk or posedge reset)
        begin
            if (reset)
                PC_output <= 32'b00;
            else
                PC_output<=PC_input;
        end
endmodule
