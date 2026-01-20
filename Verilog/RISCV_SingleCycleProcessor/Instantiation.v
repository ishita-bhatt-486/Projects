`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 20.01.2026 15:29:18
// Design Name: 
// Module Name: Instantiation
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


module top(
    input clk,reset
    );
    
    wire [31:0] PC_out_top, InstMemory_out_top, read_data1_out_top, read_data2_out_top, Imm_out_top,mux1_out_top,adder1_out_top;
    wire [31:0] adder2_out_top, mux_out2_top, ALU_out_top, mem_data_out_top, WriteData_back_top;
    wire Reg_write_CU_top, ALU_src_CU_top, zero_top, branch_CU_top, mux2_selectLine_top, MemtoReg_CU_top, memWrite_CU_top, MemRead_CU_top;
    wire [1:0] ALUop_CU_top;
    wire [3:0] ALU_ctrl_out_top; 
    
    ProgramCounter PC(. clk(clk), .reset(reset), .PC_input(mux_out2_top), .PC_output(PC_out_top));
    
    adder1 adder1(.pc_Adder_in(PC_out_top), .pc_Adder_out(adder1_out_top));
    adder2 adder2(.in1(PC_out_top), .in2(Imm_out_top), .sum_out(adder2_out_top));
        
    InstructionMemory InstrMemory( .clk(clk), .reset(reset), .read_address(PC_out_top), .output_instruction(InstMemory_out_top));
    
    RegisterFile Reg_file(.clk(clk), .reset(reset), .Reg_write(Reg_write_CU_top), .reg1(InstMemory_out_top[19:15]), .reg2(InstMemory_out_top[24:20]), .destination_reg(InstMemory_out_top[11:7]), .write_data(WriteData_back_top), .read_data1_output(read_data1_out_top), .read_data2_output(read_data2_out_top));
    
    ImmediateGenerator ImmGen(.opcode(InstMemory_out_top[6:0]), .instruction(InstMemory_out_top), .ImmExt(Imm_out_top));
    ControlUnit CU(.instruction(InstMemory_out_top[6:0]), .branch(branch_CU_top), .MemRead(MemRead_CU_top), .MemToReg(MemtoReg_CU_top), .MemWrite(memWrite_CU_top), .ALUsrc(ALU_src_CU_top),.RegWrite(Reg_write_CU_top),.ALUop(ALUop_CU_top));
    
    ALU_ControlUnit ALU_CU (.fun7(InstMemory_out_top[30]), .fun3(InstMemory_out_top[14:12]), .ALUop(ALUop_CU_top), .ALU_Control_out(ALU_ctrl_out_top));
    ALU ALU(.A(read_data1_out_top),.B(mux1_out_top), .ALU_control_in(ALU_ctrl_out_top),.zero(zero_top), .ALU_result(ALU_out_top));
    
    Mux1 Mux1(.s1(ALU_src_CU_top), .A1(read_data2_out_top), .B1(Imm_out_top), .Mux1_out(mux1_out_top));
    Mux2 Mux2(.s2(mux2_selectLine_top), .A2(adder1_out_top), .B2(adder2_out_top), .Mux2_out(mux_out2_top));
    Mux3 Mux3(.s3(MemtoReg_CU_top), .A3(ALU_out_top), .B3(mem_data_out_top), .Mux3_out(WriteData_back_top));
    
    AND_gate AND_gate(. branch(branch_CU_top), .zero(zero_top), .and_out(mux2_selectLine_top));
    
    DataMemory DM(.clk(clk), .reset(reset), .MemoryWrite(memWrite_CU_top), .MemoryRead(MemRead_CU_top), .read_address(ALU_out_top), .Write_data(read_data2_out_top), .Memory_dataout(mem_data_out_top));
    
endmodule