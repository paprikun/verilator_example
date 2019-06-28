#include <systemc>
#include <uvm>
using namespace uvm;

#include "verilated_vcd_sc.h"
#include "uvm/vip_if.h"
#include "uvm/monitor.h"

// V{RTL_TOP}.h
#include "Vtop.h"

#define TRACE

int sc_main(int argc, char * argv[])
{
#ifdef TRACE
   // Verilator trace file
   Verilated::traceEverOn(true);
   VerilatedVcdSc* tfp = new VerilatedVcdSc;
#endif

   sc_time T(10,SC_NS);

   const unsigned int STEPS     = 256;
   const unsigned int MAIN_DIV  = 4;
   const unsigned int DIV_RATIO = 1;

   sc_time Tsim = T * STEPS * MAIN_DIV * DIV_RATIO * 1024 * 2;

   sc_clock clk("clk",T);
   sc_signal<bool> nrst("nrst");
   sc_signal<bool> pwm ("pwm");

    vip_if* dut_vif_1 =new vip_if();
    uvm::uvm_config_db<vip_if*>::set(0, "", "vif1", dut_vif_1);
    
   
   Vtop dut("top_verilog");

   dut.clk (clk);
   dut.nrst(dut_vif_1 -> nrst);
   dut.pwm(dut_vif_1 -> pwm);



    monitor e1("vif1");   
   
#ifdef TRACE
   // Verilator trace file, depth
   dut.trace(tfp, 10);
   tfp->open("simu.vcd");
#endif

   uvm::run_test();
   

#ifdef TRACE
   tfp->close();
#endif
   return 0;
}
