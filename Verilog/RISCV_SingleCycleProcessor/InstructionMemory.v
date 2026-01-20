`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 13.01.2026 15:54:12
// Design Name: 
// Module Name: InstructionMemory
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


module InstructionMemory(
    input clk, reset,
    input [31:0] read_address,
    output reg [31:0] output_instruction
    );
    reg [31:0] Instruction_Memory[63:0];
    integer k;
    
    always @(posedge clk or posedge reset)
        begin
            if (reset)
                    begin
                        for (k=0; k<64; k=k+1)
                            Instruction_Memory[k]<=32'b00;
                    end
            else
                // R-type
            Instruction_Memory[0]  = 32'b00000000000000000000000000000000 ;   // no operation
            Instruction_Memory[4]  = 32'b0000000_11001_10000_000_01101_0110011; // add x13, x16, x25
            Instruction_Memory[8]  = 32'b0100000_00011_01000_000_00101_0110011; // sub x5, x8, x3
            Instruction_Memory[12] = 32'b0000000_00011_00010_111_00001_0110011; // and x1, x2, x3
            Instruction_Memory[16] = 32'b0000000_00101_00011_110_00100_0110011; // or x4, x3, x5
            
            // I-type
            Instruction_Memory[20] = 32'b000000000011_10101_000_10110_0010011; // addi x22, x21, 3
            Instruction_Memory[24] = 32'b000000000001_01000_110_01001_0010011; // ori x9, x8, 1
            
            // L-type
            Instruction_Memory[28] = 32'b000000001111_00101_010_01000_0000011; // lw x8, 15(x5)
            Instruction_Memory[32] = 32'b000000000011_00011_010_01001_0000011; // lw x9, 3(x3)
            
            // S-type
            Instruction_Memory[36] = 32'b0000000_01111_00101_010_01100_0100011; // sw x15, 12(x5)
            Instruction_Memory[40] = 32'b0000000_01110_00110_010_01010_0100011; // sw x14, 10(x6)
            
            // SB-type
            Instruction_Memory[44] = 32'h00948663; // beq x9, x9, 12
         end
        
    
endmodule
