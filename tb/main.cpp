#include <systemc>
#include <uvm>
using namespace uvm;


#include "verilated_vcd_sc.h"


// V{RTL_TOP}.h
#include "Vtop.h"

#define TRACE

template <typename REQ = uvm::uvm_sequence_item, typename RSP = REQ>
class master_driver : public uvm::uvm_driver<REQ,RSP>
{

 public:
  UVM_COMPONENT_UTILS(master_driver<REQ,RSP>);
    
  master_driver(uvm::uvm_component_name name) : uvm::uvm_driver<REQ,RSP>(name)
  {
  }


  void run_phase(uvm_phase& phase)
  {
  
  }

};



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

   Vtop dut("top_verilog");

   dut.clk (clk);
   dut.nrst(nrst);
   dut.pwm(pwm);

#ifdef TRACE
   // Verilator trace file, depth
   dut.trace(tfp, 10);
   tfp->open("simu.vcd");
#endif

   nrst = 0;
   sc_start(10*T);
   nrst = 1;
   sc_start(Tsim);

#ifdef TRACE
   tfp->close();
#endif
   return 0;
}
