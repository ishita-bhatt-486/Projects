`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 15.01.2026 13:36:14
// Design Name: 
// Module Name: ControlUnit
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

module ControlUnit(
    input [6:0] instruction,
    output reg branch, MemRead, MemToReg, MemWrite, ALUsrc, RegWrite,
    output reg [1:0] ALUop
    );
    
    always @(*)
    begin

        case(instruction)
            
            7'b0110011: {ALUsrc, MemToReg, RegWrite, MemRead, MemWrite, branch, ALUop} = 8'b001000_10;
            7'b0000011: {ALUsrc, MemToReg, RegWrite, MemRead, MemWrite, branch, ALUop} = 8'b111100_00;
            7'b0100011: {ALUsrc, MemToReg, RegWrite, MemRead, MemWrite, branch, ALUop} = 8'b100010_00;
            7'b1100011: {ALUsrc, MemToReg, RegWrite, MemRead, MemWrite, branch, ALUop} = 8'b000001_01;
            
            default:    {ALUsrc, MemToReg, RegWrite, MemRead, MemWrite, branch, ALUop} = 8'b000000_00;
        endcase
    end
    
endmodule