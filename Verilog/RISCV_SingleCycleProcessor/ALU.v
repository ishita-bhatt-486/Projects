`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 15.01.2026 14:04:43
// Design Name: 
// Module Name: ALU
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

module ALU(
    input [31:0] A, B,
    input [3:0] ALU_control_in,
    output reg zero,
    output reg [31:0] ALU_result
    );

    always @(*)
    begin
        zero = 0;
        ALU_result = 0;

        case(ALU_control_in)
            4'b0000: ALU_result = A & B;
            4'b0001: ALU_result = A | B;
            4'b0010: ALU_result = A + B;
            4'b0110: begin
                     ALU_result = A - B;
                     
                     if (A == B) 
                        zero = 1;
                     else 
                        zero = 0;
                     end
            default: ALU_result = 0;
        endcase
    end
endmodule