#include <systemc>
#include <uvm>
using namespace uvm;

#include "verilated_vcd_sc.h"
#include "uvm/vip_if.h"
#include "uvm/monitor.h"

// V{RTL_TOP}.h
#include "Vtop.h"

#define TRACE

   int local_time, local_time_buf;  
   void get_local_time()    
    {
        int fd;
        int res;
        res = system("date +%s > local_time");
        FILE* iFile;
        iFile = fopen ("local_time","rb");
        res = fscanf(iFile, "%d", &local_time);      
    }


int sc_main(int argc, char * argv[])
{
#ifdef TRACE
   // Verilator trace file
   Verilated::traceEverOn(true);
   VerilatedVcdSc* tfp = new VerilatedVcdSc;
#endif
    
   
   sc_time T(10,SC_NS);
   sc_clock clk("clk",T);

    vip_if* dut_vif_1 =new vip_if();
    uvm::uvm_config_db<vip_if*>::set(0, "", "vif1", dut_vif_1);
    

    sc_signal<bool> nrst;   
    sc_signal<bool> pwm;


   Vtop dut("top_verilog");

   dut.clk (clk);
   dut.nrst(dut_vif_1-> nrst);
   dut.pwm(dut_vif_1->pwm);



    monitor e1("vif1");   
   
#ifdef TRACE
   // Verilator trace file, depth
   dut.trace(tfp, 0);
   tfp->open("simu.vcd");
#endif


    get_local_time();
    local_time_buf = local_time;
    uvm::run_test();
    get_local_time();
    printf("RESULT TIME = %d sec\n",local_time - local_time_buf );



#ifdef TRACE
   tfp->close();
#endif
   return 0;
}
