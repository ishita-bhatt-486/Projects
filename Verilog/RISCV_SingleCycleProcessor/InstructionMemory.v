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
    
    always @(posedge clk or posedge reset)
        begin
            if (reset)
                    begin
                        for (int k=0; k<64; k=k+1)
                            Instruction_Memory[k]<=32'b00;
                    end
            else
                output_instruction<= Instruction_Memory[read_address]; 
        end
        
    
endmodule
