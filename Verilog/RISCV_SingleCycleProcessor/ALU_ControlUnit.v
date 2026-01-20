`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 15.01.2026 14:18:39
// Design Name: 
// Module Name: ALU_ControlUnit
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


module ALU_ControlUnit(
    input fun7,
    input [2:0] fun3,
    input [1:0]ALUop,
    output reg [3:0] ALU_Control_out
    );
    
    always@(*)
        begin
            case({ALUop, fun7, fun3})
            6'b00_0_000: ALU_Control_out=4'b0010;
            6'b01_0_000: ALU_Control_out=4'b0110;
            6'b10_0_000: ALU_Control_out=4'b0010;
            6'b10_1_000: ALU_Control_out=4'b0110;
            6'b10_0_111: ALU_Control_out=4'b0000;
            6'b10_0_110: ALU_Control_out=4'b0001;
            endcase
        end
endmodule
