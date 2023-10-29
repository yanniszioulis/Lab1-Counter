#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    Vcounter* top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    // init Vbuddy
    if(vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

    //initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    int pause9_count = 0;

    //run simulations for many clock cycles
    for(i=0; i<1000; i++){

        // dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++){
            tfp->dump (2*i+clk);       // unit is in ps!!!
            top->clk = !top->clk;
            top->eval ();
        }

        // ++++ Send count value to Vbuddy
        // vbdHex(4, (int(top->count) >> 16) & 0xF);
        // vbdHex(3, (int(top->count) >> 8) & 0xF);
        // vbdHex(2, (int(top->count) >> 4) & 0xF);
        // vbdHex(1, int(top->count) & 0xF);
        vbdPlot(int(top->count), 0, 255);
        vbdCycle(i+1);
        // ---- end of Vbuddy output section

        top->rst = (i<2) | (i == 19);
        top->en = vbdFlag(); // MODIFIED FROM: top->en = (i>4);
        bool pause9 = false;
        if(top->count == 9){
            if(pause9_count == 0){
            pause9 = true;
            top->en = 0;
            pause9_count++;
            }
            else if(pause9_count < 2){
                top->en = 0;
                pause9_count++;
            }
            else{
                pause9_count = 0;
                pause9 = false;
                top->en = 1;
            }
        }
        if (Verilated::gotFinish()) exit(0);
    }
    vbdClose(); // ++++
    tfp->close();
    exit(0);
}