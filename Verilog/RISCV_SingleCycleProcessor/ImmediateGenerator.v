`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.01.2026 16:40:31
// Design Name: 
// Module Name: ImmediateGenerator
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


module ImmediateGenerator(
    input [6:0] opcode,
    input [31:0] instruction,
    output reg [31:0] ImmExt
);

    always @(*) begin
        case(opcode)
            7'b0000011 : ImmExt <= {{20{instruction[31]}}, instruction[31:20]};
            7'b0100011 : ImmExt <= {{20{instruction[31]}}, instruction[31:25], instruction[11:7]};
            7'b1100011 : ImmExt <= {{19{instruction[31]}}, instruction[31], instruction[7], instruction[30:25], instruction[11:8], 1'b0};
            default    : ImmExt <= 32'b0; 
        endcase
    end
        
endmodule
